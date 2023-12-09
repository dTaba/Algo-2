// Usa: Nat, Item, Dinero, Persona
#include "otrosTADS.h"

/*
    Constantes:
    - A: Cantidad de personas.
    - I: Cantidad total de ítems en todo el festival.
    - P: Cantidad de puestos.
*/

class PuestoDeComida
{
    public:

        // Constructor.
        // Complejidad: O((#claves(stockI) + #claves(preciosI) + #claves(descuentosI))
        PuestoDeComida(Dicc<item, nat> stockI, dicc<item, Dinero> preciosI, dicc<item, Dicc<cant, nat> descuentosI);

        // Destructor.
        ~PuestoDeComida();

        /*
            Dado un item i devuelve su Stock
            PRE: {i pertenece menu(p)} donde p === self.
            POST: {res = obtenerStock(p, i)} donde p === self, res === p.obtenerStock(i)
            Complejidad: O(log(I))
            Aliasing: Se obtiene una referencia modificable al stock
        */
        Nat obtenerStock(Item i);

        /*
            Dado un item i y una cantidad c devuelve el descuento a aplicar.
            PRE: {i pertenece menu(p)} donde p === self
            POST: {res = obtenerDescuento(p, i , c)} donde p === self
            Complejidad: O(log(I) + log(cant))
            Aliasing: No genera.
        */
        Nat obtenerDescuento(Item i, Nat c);

        /*
            Dada una persona a devuelve el dinero que gastó en el puesto.
            PRE: {true}
            POST: {res = gastosDe(p, a)} donde p === self, res === p.gastosDe(a)
            Complejidad: O(log(A))
            Aliasing: No genera.
        */
        Dinero gastosDe(Persona a);
        
        /*
            Dado un item devuelve su precio.
            Complejidad: O(log(I))
            PRE: {i pertece menu(p)} donde p === self
            POST: {res = precio(p, i)} donde p === self, res === p.precioDeItem(i) 
            Aliasing: No genera.
        */
        Dinero precioDeItem(Item I);

        /*
            Dada una persona a, un item i, y una cantidad c registra una compra.
            Complejidad: O(log(A) + log(I) + log(c))
            PRE: {  i pertenece menu(p) && 
                    obtenerStock(i) >= c }
            POST:{res =obs vender(p, a, i, c)} donde res === p.vender(a,i,c), p === self
            Aliasing: No genera.
        */
        void vender(Persona a, Item i, Nat c);
        
        /*
            Dado un item i devuelve true si el item es parte del menu del puesto.
            Complejidad: O(log(I))
            PRE: {true}
            POST: {res === i pertenece menu(p)} donde p === self, res === p.existeItem(i)
            Aliasing: Sin aliasing
        */
        bool existeItem(Item i);

        /*
            Dado un item i y una persona a, le suma ese item al stock del local y se 
            lo resta de la compra de la persona.
            Complejidad: O(log(P)+log(I))
            PRE: {  i pertenece menu(p) &&
                    consumioSinPromo?(p,a,i) }
            POST: {res =obs olvidarItem(p,a,i)} donde res === p.devolverItem(a,i), p === self
            Aliasing: No genera.
        */
        void devolverItem(Persona a, Item i);


    private:
    
        Dicc<Item, Nat> stock;

        Dicc<Item, Dinero> precios;

        Dicc<Item, Dicc<Nat,Nat>> descuentos;

        Dicc<Persona, tupla<Dinero, Dicc<Item, ListaEnlazada<Compra>>>> gastos;

};
