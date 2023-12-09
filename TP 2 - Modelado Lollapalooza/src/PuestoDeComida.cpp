#include "PuestoDeComida.h"

PuestoDeComida::PuestoDeComida(Dicc<item, nat> stockI, dicc<item, Dinero> preciosI, dicc<item, Dicc<cant, nat> descuentosI){
    stock = stockI; // Por copia: O(#claves(stockI))
    precios = preciosI; // Por copia O(#claves(preciosI))

    
    // "Llenamos el diccionario de <cant, descuento> para que nos sea mas facil usarlo despues"
    it itItem = descuentosI.begin(); // Me sirve para recorrer los items

    while itItem.sig != itItem.end {

        desc = descuentosI.significado(itItem); // Dicc<cant, nat>

        conjuntoClavesDescuentos = claves(desc); // Me trae las cantidades definidas con descuento

        it itConj; // Lo uso para recorrer el conj de claves
        
        cantMax = itConj.end;
        cantMin = itConj.begin;

        i = 1;
        cantDesc = 0;


        // Me fijo desde 1 hasta la cantidad maxima definida si ese i esta definido,
        // Si lo está obtengo un nuevo cant desc, caso contrario lo defino con su cantDesc.

        while  i != cantMax end {
            if definido(i, desc){
                cantDesc = desc.significado(i);
            }else{
                definir(desc, i, candtDesc);
            }
            cant++;
        }
    }

    gastos = vacio();

    descuentos = descuentosI; // Ya lo modifique ahora lo guardo
}

PuestoDeComida::~PuestoDeComida();

PuestoDeComida::Nat obtenerStock(Item i) {
    return stock.significado(i);                                    // O(log(I))
}

PuestoDeComida::Nat precioDeItem(Item i) {
    return precios.significado(i);                                    // O(log(I))
}

PuestoDeComida::Nat obtenerDescuento(Item i, Nat c) {
    Dicc<Nat, Nat> descuentosDeItem = descuentos.significado(i); // O(log(I))

    c = min(descuentosDeItem.end, c); // O(1)

    Nat descuento = descuentosDeItem.significado(c); // O(log(cant))

    return descuento;
}

PuestoDeComida::Dinero gastosDe(Persona a) {
    if(definido?(a)) {
        return gastos.significado(a).dinero;                            // O(log(a))
    } else {
        return 0;
    }
}

PuestoDeComida::bool existeItem(Item i){
    return precios.definido?(i);                                    // O(log(I))
}

PuestoDeComida::void vender(Persona a, Item i, Nat c) {
    // Redefino el Stock

    Nat stock_anterior = stock.significado(i);                      // O(log(I))

    Nat stock_nuevo = stock_anterior - c;

    stock.definir(i, stock_nuevo);                                  // O(log(I))

    // Redefino los gastos

    tupla<Dinero, Dicc<Item, ListaEnlazada<Compra>>> comprasPersona = gastos.significado(a);  // O(log(A))

    Dinero precio = precios.significado(i);                         // O(log(I))
    Nat descuento = obtenerDescuento(i,c);                          // O(log(I) + log(c))

    comprasPersona[0] += aplicarDescuento(precio, descuento);
    

    Compra compra = [i, c, descuento];

    if comprasPersona[1].definido?(i){
        if(descuento == 0) {
            comprasPersona[1].significado(i).agregarAdelante(compra);
        } else {
            comprasPersona[1].significado(i).agregarAtras(compra);
        }
    }else{
        comprasPersona[1].definir(i,vacia().agregarAtras(compras));
    }
}

PuestoDeComida::void devolverItem(Persona p, Item i){
    // Redefino el Stock

    Nat stock_anterior = stock.significado(i);                                      // O(log(I))

    Nat stock_nuevo = stock_anterior + 1;

    stock.definir(i, stock_nuevo);                                                  // O(log(I))

    // Redefino los gastos

    tupla<Dinero, Dicc<Item, ListaEnlazada<Compra>>> comprasPersona = gastos.significado(p);  // O(log(A))

    Dinero precio = precios.significado(i);                                         // O(log(I))
    
    // Le resto el precio del item al gasto de dinero

    comprasPersona[1] = comprasPersona[1] - precio

    // Eliminamos la compra

    Compra compra = comprasPersona[1].significado(i).Primero();                   // O(1)


    // Se le resta 1 a la cantidad de esa compra.
    if (compra.cantidad == 1){
        comprasPersona[1].significado(i) = comprasPersona[1].significado(i).fin();
    }else{
        comprasPersona[1].significado(i) = comprasPersona[1].significado(i).fin();
        compra.cantidad--;
        comprasPersona[1].significado(i).agregarAdelante(compra);
    }
}