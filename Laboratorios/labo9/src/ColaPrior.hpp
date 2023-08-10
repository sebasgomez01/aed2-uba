
template<class T>
ColaPrior<T>::ColaPrior() {
	_tam = 0;
	v.push_back(0);
}

template<class T>
int ColaPrior<T>::tam() const {
	// COMPLETAR
	return _tam;
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
	// COMPLETAR
	_tam++;
	v.push_back(elem);
	int padre = v.size() / 2;
	int indice = v.size() - 1;
	while(v[indice] > v[padre] and indice != 1) {
		// Realizo el swap
		v[padre] = v[padre] + v[indice];
		v[indice] = v[padre] - v[indice];
		v[padre] = v[padre] - v[indice]; 
		indice = padre;
		padre = indice / 2;
	}

}

template<class T>
const T& ColaPrior<T>::proximo() const {
	// COMPLETAR
	return v[1];
}

template<class T>
void ColaPrior<T>::sink(int k, std::vector<int> &v) {
	while(2*k < v.size()) {
		int hijoMayor = 2*k;
		if(hijoMayor < v.size() and v[hijoMayor] < v[hijoMayor + 1]) {
			hijoMayor = hijoMayor + 1;
		}
		if(v[k] < v[hijoMayor]) {
			v[k] = v[k] + v[hijoMayor];
			v[hijoMayor] = v[k] - v[hijoMayor];
			v[k] = v[k] - v[hijoMayor];
			k = hijoMayor;
		}
	}
} 

template<class T>
void ColaPrior<T>::desencolar() {
	_tam--;
	// Primero intercambio la raíz con la "última hoja"
	v[1] = v[1] + v[v.size() - 1];
	v[v.size() - 1] = v[1] - v[v.size() - 1];
	v[1] = v[1] - v[v.size() - 1];
	// Ahora elimino la última hoja
	v.pop_back();
	// Y ahora tengo que "bajar" el elemento de la raíz al lugar que le corresponede intercambiandolo
	// por el hijo más grande
	sink(1, v);
} 

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems) {
	// COMPLETAR
}

