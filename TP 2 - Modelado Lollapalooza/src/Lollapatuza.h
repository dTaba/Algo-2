// Usa: Nat, Item, Dinero, Persona
#include "otrosTADS.h"

// Usa: PuestoDeComida
#include "PuestoDeComida.h"

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
        Lollapatuza(Dicc<PuestoID, Puesto> ps, Conj<Persona> as);

        /*
            Destructor.
            Complejidad: *****
        */
        ~Lollapatuza();

        /*
            Dada una persona a, un puestoID pi  un item i, y una cantidad c registra una compra.
            Complejidad: O(log(A) + log(I) + log(P) + log(c))
            PRE: {a pertenece peronas(l) & def?(pi, puestos(l)) &l haySuficiente?(obtener(pi, puestos(l)), i, c)}
            POST:{res =obs vender(l, pi, a, i, c)} donde res === l.vender(pi, a,i,c), l === self
            Aliasing: No genera
        */
        void vender(Persona a, PuestoID pi, Item i, Nat c);

        /*
            Dada una persona a y un item i, hackea el puesto de menor ID en el
            que esa persona haya consumido ese Item sin promoción.
            Complejidad: O(log(A) + log(I) + log(P))
            PRE: {ConsumioSinPromoEnAlgunPuesto(l, a, i)} donde l === self
            POST: {res =obs hackear(l,a,i)} donde res === l.hackear(a,i), l === self
            Aliasing: No genera
        */
        void hackear(Persona a, Item i);

        /*
            Dada una persona a devuelve el gasto total que haya realizado.
            Complejidad: O(log(A))
            PRE: { a pertenece personas(l)}  donde l === self
            POST:{res = gastoTotal(l, a)}
            Aliasing: No genera.
        */
        Dinero gastoTotal(Persona a);

        /*
            Devuelve la persona con mayor gasto total.
            Complejidad: O(1)
            PRE: {true}
            POST: {res = masGasto(l)}  donde l === self
            Aliasing: No genera.
        */
        Persona masGasto();

        /*
            Dado un item i devuelve el PuestoID del puesto cuyo stock sea menor o igual a los demas y tenga el menor ID.
            Complejidad: (P*log(I))
            PRE: {true}
            POST: {res = menorStock(l, i)} donde l === self
            Aliasing: No genera
        */
        PuestoID menorStock(Item i);

        /* 
            Devuelve el conjunto de personas.
            Complejidad: O(1)
            PRE: {true}
            POST: {res = personas(l)} donde l === self
            Aliasing: Se obtiene una referencia modificable al conjunto de personas.
        */
        Conj<Persona>& personas();

        /*
            Devuelve un diccionario PuestoID->PuestoDeComida.
            Complejidad: O(1)
            PRE: {true}
            POST: {res = puestos(l)} donde l === self
            Aliasing: Se obtiene una referencia modificable al dicc de puestos
        */
        Dicc<PuestoID, PuestoDeComida>& puestos();


    private:
        Conj<Persona> personas;
        Dicc<PuestoID, PuestoDeComida> puestos;
        Dicc<Persona, Dinero> gastos;
        Dicc<Dinero, Conj<Persona>> maxGastador;

        Dicc<Personas, Dicc<Item, Dicc<PuestoID, tupla<Puesto, Nat>>>> ItemsHackeables; // Prioridad sobre PuestoID, el nat es la cantidad del item hackeable
};

bool tupla<Dinero, Persona>::operator<(const tupla<Dinero, Persona>& b) {
    return this.Dinero > b.Dinero;
}
