#ifndef LOLLAPATUZA_H
#define LOLLAPATUZA_H

// Usa: Nat, Producto, Persona
#include "tipos.h"

// Usa: PuestoDeComida
#include "puestoDeComida.h"

/*
    Constantes:
    - A: Cantidad de personas.
    - I: Cantidad total de ítems en todo el festival.
    - P: Cantidad de puestos.
*/

class Lollapatuza
{
    public:

        /*
            Constructor.
            Complejidad: O(#as + #ps * copy(puesto))
        */
        Lollapatuza(map<IdPuesto, aed2_Puesto> ps, set<Persona> as);

        /*
            Destructor.
            Complejidad: *****
        */
        ~Lollapatuza();

        /*
            Dada una persona a, un IdPuesto pi  un Producto i, y una cantidad c registra una compra.
            Complejidad: O(log(A) + log(I) + log(P) + log(c))
            PRE: {a pertenece peronas(l) & def?(pi, puestos(l)) &l haySuficiente?(obtener(pi, puestos(l)), i, c)}
            POST:{res =obs vender(l, pi, a, i, c)} donde res === l.vender(pi, a,i,c), l === self
            Aliasing: No genera
        */
        void vender(Persona a, IdPuesto pi, Producto i, Nat c);

        /*
            Dada una persona a y un Producto i, hackea el puesto de menor ID en el
            que esa persona haya consumido ese Producto sin promoción.
            Complejidad: O(log(A) + log(I) + log(P))
            PRE: {ConsumioSinPromoEnAlgunPuesto(l, a, i)} donde l === self
            POST: {res =obs hackear(l,a,i)} donde res === l.hackear(a,i), l === self
            Aliasing: No genera
        */
        void hackear(Persona a, Producto i);

        /*
            Dada una persona a devuelve el gasto total que haya realizado.
            Complejidad: O(log(A))
            PRE: { a pertenece personas(l)}  donde l === self
            POST:{res = gastoTotal(l, a)}
            Aliasing: No genera.
        */
        Nat gastoTotal(Persona a) const;

        /*
            Devuelve la persona con mayor gasto total.
            Complejidad: O(1)
            PRE: {true}
            POST: {res = masGasto(l)}  donde l === self
            Aliasing: No genera.
        */
        Persona masGasto() const;

        /*
            Dado un Producto i devuelve el IdPuesto del puesto cuyo stock sea menor o igual a los demas y tenga el menor ID.
            Complejidad: (P*log(I))
            PRE: {true}
            POST: {res = menorStock(l, i)} donde l === self
            Aliasing: No genera
        */
        IdPuesto menorStock(Producto i) const;

        /* 
            Devuelve el conjunto de personas.
            Complejidad: O(1)
            PRE: {true}
            POST: {res = personas(l)} donde l === self
            Aliasing: Se obtiene una referencia modificable al conjunto de personas.
        */
        const set<Persona>& personas() const;

        /*
            Devuelve un diccionario IdPuesto->PuestoDeComida.
            Complejidad: O(1)
            PRE: {true}
            POST: {res = puestos(l)} donde l === self
            Aliasing: Se obtiene una referencia modificable al dicc de puestos
        */
        const map<IdPuesto, PuestoDeComida>& puestos() const;


    private:

        using PuestosHackeables = map<IdPuesto, Nat>; // Diccionario { IdPuesto -> veces a hackear}
        using Hackeables2Puesto = map<Producto, PuestosHackeables>;         // Diccionario { Producto -> Puestos donde se puede hackear ese producto }
        
        set<Persona> _personas;
        map<IdPuesto, PuestoDeComida> _puestos;                 // Diccionario { IdPuesto -> Puesto}
        map<Persona, Nat> _gastos;                              // Diccionario { Persona -> Dinero gastado }
        map<Nat, set<Persona>> _gasto2personas;                 // Diccionario { Dinero gastado -> Conjunto de personas que hayan gastado esa cantidad}
        map<Persona, Hackeables2Puesto> _persona2hackeables;    // Diccionario { Persona -> Productos hackeables y donde hackearlos }
};

#endif // LOLLAPATUZA_H