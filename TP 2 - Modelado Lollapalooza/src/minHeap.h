#ifndef MINHEAP_H_
#define MINHEAP_H_

// Se explica con Cola de Prioridad(T).
template <class T>
class minHeap
{
    public:

        // Constructor.
        // Pre: {true}
        // Post: {res =obs vacia()}
        // Complejidad: O(1)
        minHeap();

        // Destructor.
        ~minHeap();

        // Devuelve una referencia al elemento con maxima prioridad
        // Complejidad: O(1)
        // Pre: {not vacia?(h)} donde h === self.
        // Post: {res =obs proximo(h)} donde h === self.
        // Aliasing: Genera. La referencia es modificable.
        T& proximo();

        // Agrega un elemento.
        // Complejidad: O(log(n)) siendo n la cantidad de elementos ya en el heap.
        // Pre: {not pertenece(h,elemento)} donde h === self.
        // Post: {h_post =obs encolar(h, elemento)} donde h_post === self.encolar(elemento), h === self.
        // Aliasing: no genera.
        void encolar(const T& elemento);

        // Elimina el primer elemento.
        // Complejidad: O(log(n))
        // Pre: {not vacia?(h)} donde h === self.
        // Post: {h_post === desencolar(h)} donde h_post === self.desencolar, h === self.
        void desencolar();


    private:
        /*
            Estructura:
            estr = vector(T)
        */

        vector<T> elementos;
};

#endif // MINHEAP_H_
