
template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr), _size(0) {}

template <class T>
Conjunto<T>::~Conjunto() {
    while(_raiz != nullptr){
        remover(_raiz->valor);
    }
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual = _raiz;
    bool res = false;
    while(actual != nullptr && !res) {
        if (clave == actual->valor) {
            res = true;

        } else {
            if (clave < actual->valor) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (!pertenece(clave)) {
        Nodo* actual = _raiz;
        Nodo* padre = nullptr;
        while(actual != nullptr){
            padre = actual;
            if(clave < actual->valor){
                actual = actual->izq;
            } else{
                actual = actual->der;
            }
        }
        Nodo* nuevo = new Nodo(clave);
        if(padre == nullptr){
            _raiz = nuevo;
        } else{
            if(clave < padre->valor){
                padre->izq = nuevo;
            } else{
                padre->der = nuevo;
            }
        }
        _size++;
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (pertenece(clave)) {
        Nodo *aBorrar = buscar(clave);
        Nodo *padre = buscarPadre(aBorrar);

        // Aquí van los casos en que el que quiero borrar es la raíz
        if(aBorrar == _raiz){
            // Me fijo si no tiene hijos
            if(aBorrar->izq == nullptr && aBorrar->der == nullptr){
                delete aBorrar;
                _size--;
                _raiz = nullptr;
                return;
            }
            // Me fijo si el que quiero borrar tiene 1 hijo (el derecho)
            if(aBorrar->izq == nullptr){
                _raiz = aBorrar->der;
                delete aBorrar;
                _size--;
                return;
            }
            // Me fijo si el que quiero borrar tiene 1 hijo (el izquierdo)
            if(aBorrar->der == nullptr){
                _raiz = aBorrar->izq;
                delete aBorrar;
                _size--;
                return;
                // Este es el caso de que la raíz tenga dos hijos
            } else {
                Nodo *sucesor = buscarSucesor(clave);
                Nodo *padreSucesor = buscarPadre(sucesor);

                aBorrar->valor = sucesor->valor;

                if (padreSucesor->izq == sucesor) {
                    padreSucesor->izq = sucesor->der;
                } else {
                    padreSucesor->der = sucesor->der;
                }

                delete sucesor;
                _size--;
                return;
            }

        }
        // Desde aquí son los casos en que no quiero borrar la raíz

        // Aquí me fijo si el que quiero borrar es una hoja
        if (aBorrar->izq == nullptr && aBorrar->der == nullptr) {
            if (padre != nullptr) {
                if (padre->izq == aBorrar) {
                    padre->izq = nullptr;
                } else {
                    padre->der = nullptr;
                }
            }
            delete aBorrar;
            _size--;
            return;
        }
        // Me fijo si el que quiero borrar tiene 1 hijo (el derecho)
        if (aBorrar->izq == nullptr) {
            if (padre->izq == aBorrar) {
                padre->izq = aBorrar->der;
            } else {
                padre->der = aBorrar->der;
            }
            delete aBorrar;
            _size--;
            return;
        }
        // Me fijo si el que quiero borrar tiene 1 hijo (el izquierdo)
        if (aBorrar->der == nullptr) {
            if (padre->izq == aBorrar) {
                padre->izq = aBorrar->izq;
            } else {
                padre->der = aBorrar->izq;
            }
            delete aBorrar;
            _size--;
            return;
        // Este es el caso si tiene dos hijos
        } else {
            Nodo *sucesor = buscarSucesor(clave);
            Nodo *padreSucesor = buscarPadre(sucesor);

            aBorrar->valor = sucesor->valor;

            if (padreSucesor->izq == sucesor) {
                padreSucesor->izq = sucesor->der;
            } else {
                padreSucesor->der = sucesor->der;
            }
            delete sucesor;
            _size--;
            return;
        }
    }
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscar(const T &clave) const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    while(actual->valor != clave){
        padre = actual;
        actual = actual->valor < clave ? actual->der : actual->izq;
    }
    return actual;
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscarPadre(Conjunto::Nodo* nodo) const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;
    while(actual != nodo){
        padre = actual;
        actual = actual->valor < nodo->valor ? actual->der : actual->izq;
    }
    return padre;
}

template<class T>
typename Conjunto<T>::Nodo *Conjunto<T>::buscarSucesor(const T &clave) const {
    Nodo* actual = buscar(clave);
    Nodo* sucesor = actual->der;
    while(sucesor->izq != nullptr){
        sucesor = sucesor->izq;
    }
    return sucesor;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = buscar(clave);
    Nodo* sucesor = nullptr;
    if(actual->der != nullptr){
        sucesor = actual->der;
        while(sucesor->izq != nullptr){
            sucesor = sucesor->izq;
        }
    } else{
        sucesor = buscarPadre(actual);
    }
    return sucesor->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;

    while(actual->izq != nullptr){
        padre = actual;
        actual = actual->izq;
    }
    return actual->valor;

}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual = _raiz;
    Nodo* padre = nullptr;

    while(actual->der != nullptr){
        padre = actual;
        actual = actual->der;
    }
    return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_size;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

