#include "Lista.h"
#include <cassert>
#include <iostream>

Lista::Lista(): _prim(nullptr), _ult(nullptr) { }

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    destruirNodos();
}

void Lista::destruirNodos(){
        if(_prim != nullptr){
        Nodo* actual = _prim;

        while(actual->sig != nullptr){
            actual = actual->sig;
            delete(actual->ant);
        }

        delete(_ult);

        _ult = nullptr;
        _prim = nullptr;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {

    destruirNodos();


    Nodo* actual = aCopiar._prim;

    while(actual != nullptr){
        agregarAtras(actual->valor);
        actual = actual->sig;
    }

    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    
    if(_prim == nullptr){
        Nodo* agregar = new Nodo(elem, nullptr, nullptr);
        _prim = agregar;
        _ult = agregar;
    }else{
        Nodo* agregar = new Nodo(elem, _prim, nullptr);
        _prim->ant = agregar;
        _prim = agregar;
    }    
}

void Lista::agregarAtras(const int& elem) {

    if(_prim == nullptr){
        Nodo* agregar = new Nodo(elem, nullptr, nullptr);
        _prim = agregar;
        _ult = agregar;
    }else{
        Nodo* agregar = new Nodo(elem, nullptr, _ult);
        _ult->sig = agregar;
        _ult = agregar;
    }
}

void Lista::eliminar(Nat i) {
    

    if(i==0)
    {   
        if(longitud() == 1)
        {
            Nodo* actual = _prim;
            delete(actual);
            _prim = nullptr;
            _ult = nullptr;
        }
        else{
            Nodo* actual = _prim;
            actual->sig->ant = nullptr;
            _prim = actual->sig;

            delete(actual);
        }

    }
    else if(i == longitud() -1)
    {
        Nodo* actual = _ult;
        actual->ant->sig = nullptr;
        _ult = actual->ant;

        delete(actual);
    }
    else{
        Nodo* actual = _prim;

          
        for(int pos = 0 ; pos < i; pos++){
            actual = actual->sig;
        }

        actual->ant->sig = actual->sig;
        actual->sig->ant = actual->ant;

        delete(actual);
    }
}


int Lista::longitud() const {
    if(_prim == nullptr){
        return 0;
    }
    
    Nodo* actual = _prim;
    int cantidad = 1;

    while(actual->sig != nullptr){
        actual = actual->sig;
        cantidad ++;
    }
    
    return cantidad;
}

const int& Lista::iesimo(Nat i) const {
    if(i==0){
        return _prim->valor;
    }

    if(i==longitud()){
        return _ult->valor;
    }

    Nodo* actual = _prim;
    
    int pos = 0;

    if(actual != nullptr){   
        while(pos<i){    
            actual = actual->sig;
            pos++;
        }
    }


    return actual->valor;
}

int& Lista::iesimo(Nat i) {
      if(i==0){
        return _prim->valor;
    }

    if(i==longitud()){
        return _ult->valor;
    }

    Nodo* actual = _prim;
    
    int pos = 0;

    if(actual != nullptr){   
        while(pos<i){    
            actual = actual->sig;
            pos++;
        }
    }


    return actual->valor;
}

void Lista::mostrar(ostream& o) {
    // Completar
}
