#include "Lista.h"
#include <cassert>

Lista::Lista()  {
    // Completar
    prim = nullptr;
    ult = nullptr;
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

void Lista::destruirNodos() {
    Nodo* actual = prim;
    while(actual != nullptr) {
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    prim = nullptr;
    ult = nullptr;
}

void Lista::copiarNodos(const Lista &o) {
    Nodo* actual = o.prim;
    while(actual != nullptr) {
        agregarAtras(actual->valor);
        actual = actual->sig;
    }
}

Lista::~Lista() {
    // Completar
    //Nodo* actual = prim;
    //int contador = 0;
    //while(actual != nullptr) {
    //    Nodo* siguiente = actual->sig;
    //    delete actual;
    //    actual = siguiente;
    //}
    destruirNodos();
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    destruirNodos();
    copiarNodos(aCopiar);
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem, nullptr, prim);
    if(prim == nullptr) {
        prim = nuevo;
        ult = nuevo;
        return;
    } else {
        prim->ant = nuevo;
        prim = nuevo;
    }

}

void Lista::agregarAtras(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem, ult, nullptr);
    if(prim == nullptr) {
        prim = nuevo;
        ult = nuevo;
        return;
    } else {
        ult->sig = nuevo;
        nuevo->ant = ult;
        ult = nuevo;
    }
    //ult->sig = nuevoNodo;
    //ult = nuevoNodo;

}

void Lista::eliminar(Nat i) {
    // Completar
    if(longitud() == 1) {
        delete prim;
        prim = nullptr;
        ult = nullptr;
    } else if(i == 0) {
        Nodo* actual = prim->sig;
        actual->ant = nullptr;
        delete prim;
        prim = actual;
    } else if(i == longitud() - 1) {
        Nodo* actual = ult->ant;
        delete ult;
        actual->sig = nullptr;
        ult = actual;
    } else {
        Nodo* actual = prim;
        int contador = 0;
        while(contador < i) {
            contador++;
            actual = actual->sig;
        }
        (actual->ant)->sig = actual->sig;
        (actual->sig)->ant = actual->ant;
        delete actual;
    }
}

int Lista::longitud() const {
    // Completar
    Nodo* actual = prim;
    int contador = 0;
    while(actual != nullptr) {
        contador++;
        actual = actual->sig;
    }
    return contador;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    Nodo* actual = prim;
    int contador = 0;
    while(contador < i) {
        contador++;
        actual = actual->sig;
    }
    return actual->valor;
    assert(false);
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* actual = prim;
    int contador = 0;
    while(contador < i) {
        actual = actual->sig;
        contador++;
    }
    return actual->valor;
    assert(false);
}

void Lista::mostrar(ostream& o) {
    // Completar
}
