#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:

        /**
         * Completar con lo que sea necesario...
         **/

        struct Nodo
        {
            T valor;
            Nodo* izq;
            Nodo* der; 
            Nodo(const T& v) : valor(v), izq(nullptr), der(nullptr) {}
        };

        Nodo* _raiz;

        void auxDestructor(Nodo* nodoActual) { 
            if(nodoActual != nullptr)
            {
                Nodo* izq = nodoActual->izq;
                Nodo* der = nodoActual->der;

                delete(nodoActual);
                nodoActual = nullptr;
    
                auxDestructor(izq);
                auxDestructor(der);
            }
        }
        
        Nodo* auxMaximo(Nodo* nodoActual) const {
            if(nodoActual == nullptr){
                return nullptr;
            }

            if(nodoActual->der == nullptr)
            {
                return nodoActual;
            }

            return auxMaximo(nodoActual->der);
        }

        Nodo* auxMinimo(Nodo* nodoActual) const {
            if(nodoActual == nullptr){
                return nullptr;
            }

            if(nodoActual->izq == nullptr)
            {
                return nodoActual;
            }

            return auxMinimo(nodoActual->izq);       
        }

        unsigned int auxCardinal(Nodo* nodoActual) const { 
            if(nodoActual != nullptr){
                Nodo* izq = nodoActual->izq;
                Nodo* der = nodoActual->der;
                return (1 + auxCardinal(izq) + auxCardinal(der));
            }
            else{
                return 0;
            }
        }

        Nodo* auxPertenece(Nodo* nodoActual, const T& clave) const{
            if(nodoActual == nullptr){
                return nullptr;
            }

            if(nodoActual->valor == clave){
                return nodoActual;
            }
            
            if(clave > nodoActual->valor){
                return auxPertenece(nodoActual->der, clave);
            }
            
            if(clave < nodoActual->valor){
                return auxPertenece(nodoActual->izq, clave);
            }

        }

        Nodo* auxInsertar(Nodo* nodoActual, const T& clave){
            if(nodoActual == nullptr) return new Nodo(clave);

            if(clave > nodoActual->valor){
                nodoActual->der = auxInsertar(nodoActual->der, clave);
            }

            if(clave < nodoActual->valor){
                nodoActual->izq = auxInsertar(nodoActual->izq, clave);
            }
            
            return nodoActual;
        }

        Nodo* auxRemover(Nodo* nodoActual, const T& clave){
            if(nodoActual == nullptr) {
                return nullptr;
            }
            
            if(nodoActual->valor != clave){
                
                if(clave > nodoActual->valor){
                    nodoActual->der = auxRemover(nodoActual->der, clave);
                }

                if(clave < nodoActual->valor){
                    nodoActual->izq = auxRemover(nodoActual->izq, clave);
                }

                return nodoActual;
            }


            // A partir de acá solo entra si no es nullptr y si es la clave

            Nodo* posibleHijo;
            
            // En este punto puede tener un hijo izquierdo o ningun hijo
            if(nodoActual->der == nullptr){
                //Verifico si tiene un hijo
                
                posibleHijo = nodoActual->izq;
                
                delete(nodoActual);
                
                return posibleHijo;
            }


            // Acá entro si el der no es nullptr, es decir hay un hijo derecho 
            if(nodoActual->izq == nullptr)
            {
                posibleHijo = nodoActual->der;

                delete(nodoActual);

                return posibleHijo;
            }
            

            //Si sigo ejecutando significa que el nodo actual(clave) tiene 2 hijos

            nodoActual->valor = auxMinimo(nodoActual->der)->valor;
            
            //La parte izquierda se conserva igual, lo importante es la parte derecha
            nodoActual->der = auxRemover(nodoActual->der, nodoActual->valor);


            return nodoActual;            
        }

        const T& auxSiguiente(const T& clave){
            Nodo* nodo = buscarNodoPorClave(clave, _raiz);
            Nodo* padreSucesor;
            
            if(nodo->der == nullptr){
                return buscarPadre(nodo, _raiz)->valor;
            }
            else{
                Nodo* padreSucesor = buscarPadreSucesor(nodo->der);

                if(padreSucesor == nullptr){
                    return nodo->der->valor;
                }
                else{
                    return padreSucesor->izq->valor;
                }
            }           
        }

        Nodo* buscarPadre(Nodo* clave, Nodo* nodoActual){
            if(nodoActual->der == clave)
            {
                return nodoActual;
            }
            else if(nodoActual->izq == clave){
                return nodoActual;
            }
            else if(clave->valor > nodoActual->valor){
                buscarPadre(clave, nodoActual->der);
            }
            else if(clave->valor < nodoActual->valor){
                buscarPadre(clave, nodoActual->izq);
            }
        }

        Nodo* buscarNodoPorClave(const T& clave, Nodo* nodoActual)
        {
            if(nodoActual->valor == clave){
                return nodoActual;
            }
            else if(clave > nodoActual->valor){
                buscarNodoPorClave(clave, nodoActual->der);
            }
            else if(clave < nodoActual->valor){
                buscarNodoPorClave(clave, nodoActual->izq);
            }
        }

        Nodo* buscarPadreSucesor(Nodo* nodoActual){
            if(nodoActual->izq == nullptr){
                    return nullptr; 
            }
            else{
                if(nodoActual->izq->izq == nullptr){
                    return nodoActual;
                }
                else{
                    buscarPadreSucesor(nodoActual->izq);
                }
            }
        }
};  

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
