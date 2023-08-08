template<typename T>
string_map<T>::string_map(): _raiz(nullptr), _size(0) {

}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    // obtengo las claves en d, las agrego a este nuevo
    this->_size = d.size();
    for (int i = 0; i < d.claves.size(); ++i) {
        insert(make_pair(d.claves[i].first, d.claves[i].second));
    }
    return *this;
}

template<typename T>
string_map<T>::~string_map() {
    vector<string> str;
    for (int i = 0; i < this->claves.size(); ++i) {
        str.push_back(this->claves[i].first);
    }
    for (string s: str) {
        erase(s);
    }

    if(_raiz != nullptr) {
        delete _raiz;
        _raiz = nullptr;
    }
}


template<typename T>
T &string_map<T>::operator[](const string &clave) {

}


template<typename T>
int string_map<T>::count(const string &clave) const {
    // apariciones de una clave, devuelve (0 o 1)
    if (_raiz == nullptr)
        return 0;
    Nodo *act = _raiz;
    for (char i: clave) {
        if (act->siguientes[int(i)] == nullptr) // char
            return 0;
        else
            act = act->siguientes[int(i)]; // char
    }
    return act->definicion != nullptr ? 1 : 0;
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *act = _raiz;
    for (char i: clave)
        act = act->siguientes[int(i)];

    return *act->definicion;
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    Nodo *act = _raiz;
    for (char i: clave)
        act = act->siguientes[int(i)];

    return *act->definicion;
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    Nodo *act = _raiz;
    Nodo *ult = _raiz;
    Nodo** punteroAUlt = &_raiz;

    // si tengo casa y cas definidos, y me iden borrar casa, tengo que borrar solo a.
    for (char c: clave) {

        // entonces busco en este caso "s" como el último con un solo hijo.
        // y borro a.
        // en el caso donde tengo que borrar cas;
        // voy de c->a->s y borro su significado.
        int hijosAct = 0;
        for (int i = 0; i < 256; ++i) {
            if (act->siguientes[i] != nullptr)
                hijosAct++;
        }

        if (hijosAct > 1 || act->definicion != nullptr) { //
            ult = act->siguientes[c];
            punteroAUlt = &act->siguientes[c];
        }

        act = act->siguientes[c];
    }

    bool actHijos = false;
    for (int i = 0; i < 256; i++) {
        if (act->siguientes[i] != nullptr)
            actHijos = true;
    }

    for (int i = 0; i < claves.size(); ++i) {
        const pair<string, T> &edge = claves[i];
        if (edge.first == clave)
            claves.erase(claves.begin() + i);
    }

    if (actHijos) {
        delete act->definicion;
        act->definicion = nullptr;
        return;
    }

    *punteroAUlt = nullptr;

    for (char c: clave) {
        if (ult->siguientes[c] != nullptr) {
            Nodo *temp = ult->siguientes[int(c)];
            delete ult;
            ult = temp;
        }
    }
    _size = _size - 1;

    delete act->definicion;
    delete act;
}


template<typename T>
void string_map<T>::insert(const pair<string, T> &key) {
    // Dada que está es la definición para el proyecto de apariciones,
    // Asumo que la defición de los nodos solo está definida al final.
    // Para insertar un nodo, necesitaria que count(key.first) = 0 ^ inserto al final de el string T.

    if (_raiz == nullptr)
        _raiz = new Nodo();

    string cl = key.first;

    if (count(cl) == 0)
        _size++;

    Nodo *act = this->_raiz;

    for (char c: cl) { // c-a-s
        if (act->siguientes[int(c)] == nullptr) {
            Nodo *n = new Nodo();
            act->siguientes[int(c)] = n;
            act = n;
        } else
            act = act->siguientes[int(c)];
    }

    T *val = new T(key.second);
    if (act->definicion != nullptr) {
        delete act->definicion;
    }

    act->definicion = val;

    for (pair<string, T> a: claves) {
        if (a.first == key.first)
            return;
    }

    claves.push_back(key);
}

template<typename T>
int string_map<T>::size() const {
    return this->_size;
}

template<typename T>
bool string_map<T>::empty() const {
    return this->_size == 0;
}
