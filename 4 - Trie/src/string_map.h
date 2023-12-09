#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    INSERT 
    * Inserta un par clave, valor en el diccionario
    **/
    void insert(const pair<string, T>&);

    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /** OPTATIVO
    * operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &key);

private:
    // Estructura de datos del diccionario - Trie
    
    struct Nodo {
        vector<Nodo*> siguientes;
        
        // Puntero a ese significado genérico, definición de la palabra
        T* definicion;

        Nodo() {
            for(int i = 0; i < 256 ; i++){
                this->siguientes.push_back(nullptr);
            }
            this->definicion = nullptr;
        };
    };
    
    Nodo* _raiz;
    int _size;

    // Funciones auxiliares hpp
    
    void auxDestructor(Nodo* nodoActual){
        // Caso base
        if(nodoActual == nullptr){
            return;
        }
        
        // Si no

        // Tengo que recorrer todo el vector, caracter por caracter, siempre son 256
        
        for(int i = 0 ; i < (nodoActual->siguientes).size() ; i++){
            auxDestructor((nodoActual->siguientes)[i]);
        }
        
        // Si tiene una definición la borro tambien
        
        if(nodoActual->definicion != nullptr){
            // Tiene una definición que tengo que borrar
            // Ya conseguiste la clave recorriendo el trie
            // Ahora tenes el significado, el cual es T*
            delete(nodoActual->definicion);
        }

        delete(nodoActual);
    }

    void auxInsert(Nodo* nodoActual, string clave, T significado){
    
        // Caso base
        
        if(clave == ""){
            // Puede darse el caso de que ya este definida
            // y no crearias otro nodo
            
            if(nodoActual->definicion == nullptr)
            {
                nodoActual->definicion = new T(significado);
                _size ++;
                return;
            }

            delete(nodoActual->definicion);
            nodoActual->definicion = new T(significado);
            
            return;
        }

        // Caso ya está la letra 
        if(nodoActual->siguientes[int(clave.at(0))] != nullptr){
            return auxInsert(nodoActual->siguientes[int(clave.at(0))], clave.substr(1), significado);
        }

        // Caso la letra no está
        if(nodoActual->siguientes[int(clave.at(0))] == nullptr){
            //Agrego la letra al trie
            nodoActual->siguientes[int(clave.at(0))] = new Nodo();
            

            return auxInsert(nodoActual->siguientes[int(clave.at(0))], clave.substr(1), significado);
        }

        
    }

    int auxCount(Nodo* nodoActual, const string& clave)const{
        
        if(nodoActual == nullptr){
            return 0;
        }
        
        
        // Ya lo encontre tamo 
        if(clave == ""){
            return nodoActual->definicion != nullptr;
        }


        // Esta la letra de la palabra, prosiga
        return auxCount(nodoActual->siguientes[(clave.at(0))], clave.substr(1));   
        
    }


    //La clave está definida

    T* auxAt(Nodo* nodoActual, const string& clave)const{
        

        // Llegaste a la definición
        if(clave == ""){
            return nodoActual->definicion;
        }

        // Tenés que seguir recorriendo
        if(nodoActual->siguientes[int(clave.at(0))] != nullptr){
            return auxAt(nodoActual->siguientes[int(clave.at(0))], clave.substr(1));
        }
    }
    
    Nodo* auxCopiar(const Nodo* aCopiar){
        
        if(aCopiar == nullptr){
            return nullptr;
        }
        
        Nodo* nodoActual = new Nodo();
        nodoActual->definicion = aCopiar->definicion ? new T(*(aCopiar->definicion)) : nullptr;

        for (int i = 0; i < 256; i++)
        {
            nodoActual->siguientes[i] = auxCopiar(aCopiar->siguientes[i]);
        }

        return nodoActual;
    }

    Nodo* auxErase(Nodo* nodoActual,const string& clave){
        if(clave == ""){
            // Borrar, llegue xd

            delete(nodoActual->definicion);
            nodoActual->definicion = nullptr;

        } else {
            nodoActual->siguientes[clave.at(0)] = auxErase(nodoActual->siguientes[clave.at(0)], clave.substr(1));
        }
        //Tiene hijos
        
        for (Nodo* p: nodoActual->siguientes)
        {
            if(p != nullptr) return nodoActual;
        }
        
        //Aca ya no
        
        //Tiene significado
        delete(nodoActual);
        return nullptr;
    }
};

#include "string_map.hpp"

#endif // STRING_MAP_H_
