#ifndef PUESTO_H_
#define PUESTO_H_
#include "tipos.h"
#include <list>
#include <set>

/*
    Constantes:
    - A: Cantidad de personas.
    - I: Cantidad total de productos en todo el festival.
    - P: Cantidad de puestos.
*/


class PuestoDeComida
{
    public:

        // Constructor.
        // Complejidad: O((#claves(stockP) + #claves(menuP) + #claves(promocionesP))
        PuestoDeComida(const Stock&, const Menu&, const Promociones&);

        // Destructor.
        ~PuestoDeComida();

        /*
            Dado un producto i devuelve su Stock
            PRE: {i pertenece menu(p)} donde p === self.
            POST: {res = obtenerStock(p, i)} donde p === self, res === p.obtenerStock(i)
            Complejidad: O(log(I))
            Aliasing: Se obtiene una referencia modificable al stock
        */
        Nat obtenerStock(Producto i) const;

        /*
            Dado un producto i y una cantidad c devuelve el descuento a aplicar.
            PRE: {i pertenece menu(p)} donde p === self
            POST: {res = obtenerDescuento(p, i , c)} donde p === self
            Complejidad: O(log(I) + log(cant))
            Aliasing: No genera.
        */
        Nat obtenerDescuento(Producto i, Nat c) const;

        /*
            Dada una persona a devuelve el dinero que gastó en el puesto.
            PRE: {true}
            POST: {res = gastosDe(p, a)} donde p === self, res === p.gastosDe(a)
            Complejidad: O(log(A))
            Aliasing: No genera.
        */
        Nat gastosDe(Persona a);
        
        /*
            Dado un producto devuelve su precio.
            Complejidad: O(log(I))
            PRE: {i pertece menu(p)} donde p === self
            POST: {res = precio(p, i)} donde p === self, res === p.precioDeItem(i) 
            Aliasing: No genera.
        */
        Nat precioDeItem(Producto I);

        /*
            Dada una persona a, un item i, y una cantidad c registra una compra.
            Complejidad: O(log(A) + log(I) + log(c))
            PRE: {  i pertenece menu(p) && 
                    obtenerStock(i) >= c }
            POST:{res =obs vender(p, a, i, c)} donde res === p.vender(a,i,c), p === self
            Aliasing: No genera.
        */
        void vender(Persona a, Producto i, Nat c);
        
        /*
            Dado un producto i devuelve true si el item es parte del menu del puesto.
            Complejidad: O(log(I))
            PRE: {true}
            POST: {res === i pertenece menu(p)} donde p === self, res === p.existeItem(i)
            Aliasing: Sin aliasing
        */
        bool existeItem(Producto i) const;

        /*
            Dado un producto i y una persona a, le suma ese item al stock del local y se 
            lo resta de la compra de la persona.
            Complejidad: O(log(P)+log(I))
            PRE: {  i pertenece menu(p) &&
                    consumioSinPromo?(p,a,i) }
            POST: {res =obs olvidarItem(p,a,i)} donde res === p.devolverItem(a,i), p === self
            Aliasing: No genera.
        */
        void devolverItem(Persona a, Producto i);


    private:
        using Compra = pair<Nat, Nat>;                          // [ Precio, Cantidad ]
        using Producto2Compras = map<Producto, list<Compra>>;   // Diccionario { Producto -> Secuencia de compras}
    
        Stock stock;
        Menu menu;
        Promociones promociones;
        map<Persona, pair<Nat, Producto2Compras>> gastosPorPersona; // Diccionario { Pesrona -> [Dinero gastado, Secuencias de compra por producto] }

};

#endif // PUESTO_H_