#include "puestoDeComida.h"

Nat aplicarDescuento(Nat precio, Nat descuento) {
    return precio * (100 - descuento) / 100;
}

PuestoDeComida::PuestoDeComida(const Stock& stockP, const Menu& menuP, const Promociones& promocionesP) {
    // Guardamos el diccionario de stock y de menu en la parte privada
    stock = stockP;
    promociones = promocionesP;
    menu = menuP;

    // "Rellenamos" el diccionario de promociones para que nos sea mas facil usarlo despues
    for (auto& [producto, promocionesDeProducto] : promociones) {
        Nat cantidadAnterior = 0;
        Nat descuentoAnterior = 0;
        for (auto& [cantidad, descuento] : promocionesDeProducto) {
            for (Nat i = cantidadAnterior + 1; i < cantidad; i++)
                promocionesDeProducto.emplace(i, descuentoAnterior);

            cantidadAnterior = cantidad;
            descuentoAnterior = descuento;
        }
    }
}

PuestoDeComida::~PuestoDeComida(){
    return;
}

Nat PuestoDeComida::obtenerStock(Producto i) const {
    // Por precondicion: i pertenece a claves(stock).
    return stock.at(i);
}

Nat PuestoDeComida::precioDeItem(Producto i) {
    // Por precondicion: i pertenece a claves(menu).
    return menu.at(i);
}

Nat PuestoDeComida::obtenerDescuento(Producto i, Nat c) const {
    
    if ( !promociones.count(i) )
        return 0;

    auto& descuentosDeItem = promociones.at(i);

    if ( !descuentosDeItem.size() )
        return 0;

    Nat maximaCantidad = descuentosDeItem.end()->first;
    c = c < maximaCantidad ? c : maximaCantidad;
    
    return descuentosDeItem.at(c);
}

Nat PuestoDeComida::gastosDe(Persona a) {
    Nat gastos = 0;
    
    if ( gastosPorPersona.count(a) ) {
        pair<Nat, Producto2Compras>& gastosPersona = gastosPorPersona.at(a);
        gastos = gastosPersona.first;
    }

    return gastos;
}

bool PuestoDeComida::existeItem(Producto i) const {
    return (bool)menu.count(i);
}

void PuestoDeComida::vender(Persona a, Producto i, Nat c) {
    // Redefino el Stock
    stock[i] -= c;

    // Redefino los gastos
    pair<Nat, map<Producto, list<Compra>>>& gastoPersonaDetalle= gastosPorPersona[a];
    Nat& gastoTotalPersona = gastoPersonaDetalle.first;
    map<Producto, list<Compra>>& producto2compras = gastoPersonaDetalle.second;

    Nat precio = menu.find(i)->second * c;
    Nat descuento = this->obtenerDescuento(i,c);

    Nat precioDescontado = aplicarDescuento(precio, descuento);
    gastoTotalPersona += precioDescontado;
    
    Compra compra (precioDescontado, c);

    if (producto2compras.count(i)) {
        list<Compra> listaCompras = producto2compras[i];
        
        if(descuento == 0) {
            listaCompras.push_front(compra);
        } else {
            listaCompras.push_back(compra);
        }

    } else {
        list<Compra> unicaCompra;
        unicaCompra.push_front(compra);
        producto2compras[i] = unicaCompra;
    }
}

void PuestoDeComida::devolverItem(Persona p, Producto i){
    // Redefino el Stock
    Nat& stockAnterior = stock[i];
    stockAnterior++;


    // Redefino los gastos
    auto& [gastoPersona, producto2compras] = gastosPorPersona[p];

    Nat precio = menu[i];
    
    // Le resto el precio del item al gasto de dinero
    gastoPersona -= precio;

    // Eliminamos la compra
    list<Compra>& compras = producto2compras[i];
    auto& [precioCompra, cantidadCompra] = compras.front();

    // Se le resta 1 a la cantidad de esa compra.
    if (cantidadCompra == 1) {
        compras.pop_front();
    } else {
        cantidadCompra--;
        precioCompra -= precio;
    }
}