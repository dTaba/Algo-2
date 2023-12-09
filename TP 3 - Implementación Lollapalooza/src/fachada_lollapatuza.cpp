#include "fachada_lollapatuza.h"


FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos) : lolla(Lollapatuza(infoPuestos, personas)) { }

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    lolla.vender(persona, idPuesto, producto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    lolla.hackear(persona, producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return lolla.gastoTotal(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return lolla.masGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
   return lolla.menorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return lolla.personas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    auto puestos = lolla.puestos();
    
    if ( !puestos.count(idPuesto) ) return 0;
    
    auto puesto = puestos.at(idPuesto);
    
    if ( !puesto.existeItem(producto) ) return 0;

    return puesto.obtenerStock(producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    auto puestos = lolla.puestos();

    if ( !puestos.count(idPuesto) ) return 0;

    auto puesto = puestos.at(idPuesto);
    
    return puesto.obtenerDescuento(producto, cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    auto puestos = lolla.puestos();

    if ( !puestos.count(idPuesto) ) return 0;

    auto puesto = puestos.at(idPuesto);

    return puesto.gastosDe(persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    set<IdPuesto> ids;
    for (auto& [pi,p]  : lolla.puestos())
        ids.insert(pi);

    return ids;
}