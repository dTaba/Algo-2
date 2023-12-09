#include "Lollapatuza.h"

Lollapatuza::Lollapatuza(Dicc<PuestoID, Puesto> ps, Conj<Persona> as){
    puestos = ps; // Por copia: #ps * copy(puesto)

    for (Persona a : as) {
        definir(gastos, a, 0);
        definir(ItemsHackeables, a, vacio());
        definir(maxGastador, 0, a)
    } // O(#as)
    
    personas = as; // Por copia: O(#as)
}

Lollapatuza::~Lollapatuza();

Lollapatuza::void vender(Persona a, PuestoID pi, Item i, Nat c) {
    
    // Traigo el puesto x ID
    PuestoDeComida puesto = puestos.significado(pi);    // O(log(P))
    
    // Me guardo el gasto de la persona en el puesto antes de que compre algo
    Dinero gastoPersona = puesto.gastosDe(a);

    // Realizo la venta
    puesto.vender(a,i,c);                               // O(log(A) + log(I) + log(c))

    // Calculo cuanto le salio lo que compró
    gastoPersona = puesto.gastosDe(a) - gastoPersona;

    // Guardo el gasto total antes de la compra para usarlo mas adelante

    Dinero gastoPrevio = gastos.significado(a);

    // Sumo lo que gastó recien a su gasto total
    gastoPersona += gastos.significado(a);        // O(log(A))
    
    // Actualizo sus gastos totales
    gastos.definir(a, gastoPersona);    // O(log(A))
    
    
    // Ahora tengo que modificar la estructura de maxGastador
    
    // Primeramente tengo que eliminarlo de su gasto anterior
    // Asumo que va a estar definido

    // Verifico que ese monto tenga mas de una persona
    if(maxGastador.significado(gastoPrevio).size > 1){
        maxGastador.definir(gastoPrevio, maxGastador.significado(gastoPrevio).borrar(a))
    } 
    else{
        maxGastador.borrar(gastoPrevio)
    }


    // Agregar - 2 Casos, Esta, No esta
    if(maxGastador.definido(gastoPersona)){
        
        // Como el gasto estaba definido, traigo su conjunto de personas
        Conj<Persona> gastadores = maxGastador.significado(gastoPersona);

        // A ese conjunto de personas le agrego este comprador
        maxGastador.definir(gastoPersona, gastadores.ag(a))
    }
    else{
        // Si el monto no está definido

        // Defino el monto y agrego a la persona al conjunto vacio
        maxGastador.definir(gastoPersona, Vacio().ag(a))
    }

    if(puesto.obtenerDescuento(i,c) == 0){
        if (itemsHackeables.significado(a).significado(i).definido?(pi))
        {
            tupla<Puesto, Nat> detalle = itemsHackeables.significado(a).significado(i).significado(pi);
            itemsHackeables.significado(a).significado(i).definir(pi, make_tuple(detalle[0], detalle[1] + c));
        } else {
            itemsHackeables.significado(a).significado(i).definir(pi, puesto, c);
        }
    }
}

Lollapatuza::Dinero gastoTotal(Persona a) {
    return gastos.significado(a);
}

Lollapatuza::Persona masGasto() {
    itGastos = crearIt(maxGastador);
    itGastos.siguiente(); //Apunta al maxGasto

    itPersona = crearIt(itGastos);

    return itPersona.siguiente();
}

Lollapatuza::PuestoID menorStock(Item i) {                                                                              // O(log(I)+log(P))
    Iterator it = CrearItBi(puestos);       // O(1)
    PuestoID elMenor;                       // O(1)

    while( HaySiguiente?(it) ) {                                                                                        // O(log(P))
        if(puestos.siguientesignificado(it).existeItem(i)){                                                             // O(log(I))
            if(puestos.siguientesignificado(it).obtenerStock(i) < puestos.significado(elMenor).obtenerStock(i)){        // O(log(I))
                elMenor = puestos.siguienteclave(it)            // O(1)
                it = siguiente(it);                             // O(1)
            }else if(puestos.significado(esMenor).obtenerStock(i) < puestos.siguientesignificado(it).obtenerStock(i)){  // O(log(I))
                it = siguiente(it);                             // O(1)
            }else{
                if(puestos.siguienteclave(it) < esMenor) {              // O(1)
                    elMenor = puestos.siguienteclave(it);               // O(1)
                    it = siguiente(it);                                 // O(1)
                }else{
                    it = siguiente(it);                         // O(1)
                }
            }
        }
        it = siguiente(it);                                     // O(1)
    }

    return esMenor;

}

Lollapatuza::Conj<Persona>& personas() {
    return personas;
}

// Como precondicion se tiene que consumió
// ese item sin descuento en algún puesto.

Lollapatuza::void hackear(Persona a, Item i) {
    PuestoDeComida puesto;
    
    // Traigo el puesto con menor ID en el que la persona a compró el item i
    puesto = ItemsHackeables.significado(a).significado(i).begin().significado()[0];

    // Le devolvemos al puesto el item i comprado por la persona a
    puesto.devolverItem(a,i);
    
    // Guardo el gasto previo para su uso posterior
    gastoPrevio = gastos.significado(a);

    // Se le resta de los gastos de la persona la compra realizada
    gastos.significado(a) -= puesto.precioDeItem(i);

    // Tengo que actualizar la estructura de maxGastador
    
    // Primero borro el gasto anterior
    if(maxGastador.significado(gastoPrevio).size > 1){
        // Si ese conjunto tiene mas elementos solo borro este
        maxGastador.definir(gastoPrevio, maxGastador.significado(gastoPrevio).borrar(a))
    } 
    else{
        // Si no tiene elementos borro la clave
        maxGastador.borrar(gastoPrevio)
    }


    Dinero gastoPersona = gastos.significado(a);
    
    // Agregar - 2 Casos, Esta, No esta
    if(maxGastador.definido(gastoPersona)){
        
        // Como el gasto estaba definido, traigo su conjunto de personas
        Conj<Persona> gastadores = maxGastador.significado(gastoPersona);

        // A ese conjunto de personas le agrego este comprador
        maxGastador.definir(gastoPersona, gastadores.ag(a))
    }
    else{
        // Si el monto no está definido

        // Defino el monto y agrego a la persona al conjunto vacio
        maxGastador.definir(gastoPersona, Vacio().ag(a))
    }

    // Restamos el item hackeado de itemsHackeables

    Dicc<PuestoID <Puesto, Nat>> puestosHackeables = itemsHackeables.significado(a).significado(i);  // O(log a) + O(log i)

    PuestoID pid = puestosHackeables.begin().clave(); // O(1)
    tupla<Puesto, Nat> detalles = puestosHackeables.begin().significado(); // O(1)

    // Si la cantidad del item es 1 el item deja de ser hackeable directamente sino se resta la cantidad

    if(detalles[2] == 1){
        puestosHackeables.borrar(PuestoID); // O(1)
    }
    else{
        detalles[2]--;
    }
}
