#include "Lollapatuza.h"

Lollapatuza::Lollapatuza(map<IdPuesto, aed2_Puesto> ps, set<Persona> as){
    for (auto [pi, puestoCatedra] : ps) {
        _puestos.emplace(pi, PuestoDeComida(
                puestoCatedra.stock,
                puestoCatedra.menu,
                puestoCatedra.promociones
            )
        );
    }

    _personas = as;

    for (Persona a : as) {
        _gastos[a] = 0;

        Hackeables2Puesto empty_map;
        _persona2hackeables[a] = empty_map;

    }
    
    _gasto2personas[0] = as;
    
}

Lollapatuza::~Lollapatuza() {
    // Completar.
    return;
}

void Lollapatuza::vender(Persona a, IdPuesto pi, Producto i, Nat c) {
    
    // Traigo una referencia al puesto
    PuestoDeComida& puesto = _puestos.at(pi);
    
    // Me guardo el gasto de la persona en el puesto antes de que compre algo
    Nat gastoPersona = puesto.gastosDe(a);

    // Realizo la venta
    puesto.vender(a,i,c);

    // Calculo cuanto le salio lo que compró
    Nat gastoVenta = puesto.gastosDe(a) - gastoPersona;
    Nat gastoTotalPrevio = _gastos.at(a);
    Nat gastoTotalActual = gastoTotalPrevio + gastoVenta;

    // Actualizo sus gastos totales
    _gastos[a] = gastoTotalActual;
    
    // Elimino a la persona del Conjunto de personas que gastó gastoTotalPrevio
    set<Persona>& personasMismoGasto = _gasto2personas[gastoTotalPrevio];
    if(personasMismoGasto.size() > 1) {
        personasMismoGasto.erase(a);
    } else {
        _gasto2personas.erase(gastoTotalPrevio);
    }


    // Agrego a la persona al Conjunto de personas que gastó gastoTotalActual
    if(_gasto2personas.count(gastoTotalActual)){
        // Como el gasto estaba definido, traigo su conjunto de personas
        _gasto2personas[gastoPersona].insert(a);
    } else {
        // Defino el monto y agrego a la persona al conjunto vacio
        set<Persona> personaSola;
        personaSola.insert(a);
        _gasto2personas.emplace(gastoTotalActual, personaSola);
    }

    // Determino si es hackeable la compra, en cuyo caso lo agrego a persona2hackeables
    if(puesto.obtenerDescuento(i,c) != 0) return;

    map<Producto, map<IdPuesto, Nat>>& hackeable2puesto = _persona2hackeables[a];
    
    if(hackeable2puesto.count(i) == 0) {
        // Defino la el puesto.
        map<IdPuesto, Nat> puesto2detalle;
        hackeable2puesto[i] = puesto2detalle;
    }

    map<IdPuesto, Nat>& puesto2detalle = hackeable2puesto[i];
    
    if (puesto2detalle.count(pi)) {
        puesto2detalle[pi] += c;
    } else {
        puesto2detalle[pi] = c;
    }
}

Nat Lollapatuza::gastoTotal(Persona a) const {
    return _gastos.find(a)->second;
}

Persona Lollapatuza::masGasto() const {
    const set<Persona>& _persona2hackeables = _gasto2personas.rbegin()->second;
    return *(_persona2hackeables.begin());
}

IdPuesto Lollapatuza::menorStock(Producto i) const {                                                                              // O(log(I)+log(P))
    IdPuesto menorPI = _puestos.begin()->first;
    Nat menorStock = 0;
    bool first = true;

    for (auto& [pi, p] : _puestos) {
        if ( !p.existeItem(i) )
            continue;

        Nat sp = p.obtenerStock(i);
        if (sp < menorStock || first) {
            menorStock = sp;
            menorPI = pi;
            first = false;
        }
    }
    
    return menorPI;
}

const map<IdPuesto, PuestoDeComida>& Lollapatuza::puestos() const {
    return _puestos;
}

const set<Persona>& Lollapatuza::personas() const {
    return _personas;
}

// Como precondicion se tiene que consumió
// ese item sin descuento en algún puesto.

void Lollapatuza::hackear(Persona a, Producto i) {    
    // Obtengo el puesto en donde se realiza el hackeo
    map<Producto, map<IdPuesto, Nat>>& hackeables2puesto = _persona2hackeables[a];
    map<IdPuesto, Nat>& puestoDetalles = hackeables2puesto[i];
    IdPuesto pi = puestoDetalles.begin()->first; // PuestoID
    PuestoDeComida& p = _puestos.at(pi); // Puesto
    Nat c = puestoDetalles.at(pi); // Cantidad de veces que se puede hackear

    // Retribuimos al stock el producto hackeado.
    p.devolverItem(a,i);
    
    // Guardo el gasto previo para su uso posterior
    auto& gastoPrevio = _gastos.at(a);
    Nat gastoActual = gastoPrevio - p.precioDeItem(i);
    

    // Quito a la persona del grupo de personas con mismo gastoPrevio
    auto& personasMismoGasto = _gasto2personas.at(gastoPrevio);
    if (personasMismoGasto.size() > 1) {
        // Si ese conjunto tiene mas elementos solo borro este
        personasMismoGasto.erase(a);
    } else {
        // Si no tiene elementos borro la clave
        _gasto2personas.erase(gastoPrevio);
    }
    
    // Agrego a la persona al grupo de personas con mismo gastoActual
    if ( _gasto2personas.count(gastoActual) ) { // Hay mas personas con mismo gastoActual 
        _gasto2personas[gastoActual].insert(a);
    } else { // Primera persona con esta gastoActual
        set<Persona> unicaPersona;
        unicaPersona.insert(a);
        _gasto2personas[gastoActual] = unicaPersona;
    }

    // Si la cantidad del item es 1 el item deja de ser hackeable directamente sino se resta la cantidad
    if (c == 1) {
        hackeables2puesto.at(i).erase(pi); // O(1)
    } else {
        c--;
    }

    gastoPrevio = gastoActual;
}
