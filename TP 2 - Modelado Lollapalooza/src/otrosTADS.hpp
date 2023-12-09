#ifndef OTROS_TADS_H_
#define OTROS_TADS_H_

#include "diccionarioLogaritmico.h"
#include "minHeap.h"

using namespace std;

typedef unsigned int Nat;
typedef unsigned int Item;
typedef unsigned int Dinero;
typedef unsigned int Persona;
typedef unsigned int PuestoID;

typedef tupla<Item,Nat,Nat> Compra; // <Item, Cantidad, Descuento>
bool Compra::operator<(const Compra& c) {
    return this.descuento < c.descuento;
} // Se perfectamente que no se escribe asi, pero no sabria como escribirlo...

typedef std::set Conj;

#endif // OTROS_TADS_H_
