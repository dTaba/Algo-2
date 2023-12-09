#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <list>

using namespace std;

using Persona = int;
using IdPuesto = int;
using Producto = int;
using Nat = unsigned int;

// Map es un diccionario Logaritmico

using Stock = map<Producto, Nat>;                   // Diccionario { Producto -> Stock }
using Promociones = map<Producto, map<Nat, Nat>>;   // Diccionario { Producto -> Diccionario [Cantidad -> Descuento]}
using Menu = map<Producto, Nat>;                    // Diccionario { Producto -> Precio }

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};

#endif //SOLUCION_TIPOS_H
