template <typename T>
string_map<T>::string_map(){
    _raiz = nullptr;
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // De lo que necesito traer datos es D


    // Llamar al destructor, lo que tenga mi diccionario ya no me sirve (Tal vez sí pero es un caso muy borde)

    auxDestructor(_raiz);

    // Crear el diccionario que sea igual al que te pasan por párametro

    _raiz = auxCopiar(d._raiz);
    _size = d._size;
}

template <typename T>
string_map<T>::~string_map(){
    // Voy por cada nodo haciendo delete, importante poner la raíz como nullptr tambien
    auxDestructor(_raiz);
    _raiz = nullptr;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& value_type){
    
    string clave = value_type.first;
    T significado = value_type.second;

    if(_raiz == nullptr) _raiz = new Nodo();

    auxInsert(_raiz, clave, significado);
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    return auxCount(_raiz, clave);
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    return auxAt(_raiz, clave);
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    return *auxAt(_raiz, clave);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    _raiz = auxErase(_raiz, clave);
    _size--;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    if(_raiz == nullptr){
        return true;
    }

    return false;
}