template <class T>
void swap(vector<T> xs, x, y) {
    const T& aux = xs[x];
    xs[x] = xs[y];
    elementos[y] = aux;
}

minHeap::minHeap() : elementos() {};

template <class T>
T& minHeap::proximo() {
    return elementos[0];
}

void minHeap::encolar(const T& elemento) {
    elementos.push_back(elemento);
    int i = elementos.size() - 1;
    while (elementos[(i-1)/2] > elementos[i] && i != 0) {
        swap(elementos, i, (i-1)/2);
        i = (i-1)/2;
    }
}


void minHeap::desencolar(){
    swap(elementos, 0, elementos.size() - 1);
    elementos.pop_back();

    int i = 0;
    while(( elementos[i] > elementos[2*i+1]     ||
            elementos[i] > elementos[2*i+2] )   &&
            i < elementos.size() ) {
            
            if (elementos[2*i+1] < elementos[2*i+2]) {
                swap(elementos, i, 2*i + 1);
                i = 2*i + 1;
            } else {
                swap(elementos, i, 2*i + 2);
                i = 2*i + 2;
            }
        }
}