
template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() { 
    auxDestructor(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if(auxPertenece(_raiz, clave) == nullptr){
        return false;
    }else{
        return true;
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    _raiz = auxInsertar(_raiz, clave);
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    _raiz = auxRemover(_raiz, clave);
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    return auxSiguiente(clave);
}

template <class T>
const T& Conjunto<T>::minimo() const {
    return auxMinimo(_raiz)->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return auxMaximo(_raiz)->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    auxCardinal(_raiz);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

