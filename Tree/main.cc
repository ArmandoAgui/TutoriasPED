#include <iostream>
using namespace std;

// Definición del nodo del árbol binario
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
};

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->valor = valor;
    nuevoNodo->izquierdo = nullptr;
    nuevoNodo->derecho = nullptr;
    return nuevoNodo;
}

// Función para insertar un nuevo valor en el árbol binario
Nodo* insertar(Nodo* nodo, int valor) {
    if (nodo == nullptr) {
        return crearNodo(valor);
    }

    if (valor < nodo->valor) {
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    }
    else if (valor > nodo->valor) {
        nodo->derecho = insertar(nodo->derecho, valor);
    }

    return nodo;
}

// Función para realizar el recorrido inorden (izquierdo, raíz, derecho)
void inorden(Nodo* nodo) {
    if (nodo != nullptr) {
        inorden(nodo->izquierdo);
        cout << nodo->valor << " ";
        inorden(nodo->derecho);
    }
}

// Función para realizar el recorrido preorden (raíz, izquierdo, derecho)
void preorden(Nodo* nodo) {
    if (nodo != nullptr) {
        cout << nodo->valor << " ";
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }
}

// Función para realizar el recorrido postorden (izquierdo, derecho, raíz)
void postorden(Nodo* nodo) {
    if (nodo != nullptr) {
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        cout << nodo->valor << " ";
    }
}

int main() {
    Nodo* raiz = nullptr;

    // Insertar valores en el árbol binario
    raiz = insertar(raiz, 50);
    insertar(raiz, 30);
    insertar(raiz, 20);
    insertar(raiz, 40);
    insertar(raiz, 70);
    insertar(raiz, 60);
    insertar(raiz, 80);

    // Realizar los distintos recorridos
    cout << "Recorrido Inorden: ";
    inorden(raiz);
    cout << endl;

    cout << "Recorrido Preorden: ";
    preorden(raiz);
    cout << endl;

    cout << "Recorrido Postorden: ";
    postorden(raiz);
    cout << endl;

    return 0;
}
