#include <iostream>
#include <string>

using namespace std;

// Estructura del nodo del árbol
struct Nodo {
    string pregunta;  // Puede ser una pregunta o una adivinanza
    Nodo* si;         // Nodo para la respuesta 'sí'
    Nodo* no;         // Nodo para la respuesta 'no'

    Nodo(string p) : pregunta(p), si(nullptr), no(nullptr) {}
};

// Función para hacer preguntas
bool hacerPregunta(string pregunta) {
    string respuesta;
    while (true) {
        cout << pregunta << " (si/no): ";
        cin >> respuesta;
        if (respuesta == "si" || respuesta == "SI") {
            return true;
        } else if (respuesta == "no" || respuesta == "NO") {
            return false;
        } else {
            cout << "Por favor, responde 'si' o 'no'.\n";
        }
    }
}

// Función para jugar el juego
void jugar(Nodo* nodo) {
    if (nodo->si == nullptr && nodo->no == nullptr) {  // Nodo hoja
        if (hacerPregunta("¿Estabas pensando en " + nodo->pregunta + "?")) {
            cout << "¡Adiviné correctamente!\n";
        } else {
            cout << "Oh no, no lo adiviné.\n";
            cout << "¿En qué estabas pensando? ";
            string nuevoObjeto;
            cin.ignore();
            getline(cin, nuevoObjeto);

            cout << "Por favor, escribe una pregunta que distinga a " << nodo->pregunta << " de " << nuevoObjeto << ": ";
            string nuevaPregunta;
            getline(cin, nuevaPregunta);

            bool respuestaNueva = hacerPregunta("Para " + nuevoObjeto + ", ¿cuál es la respuesta correcta a tu pregunta?");

            Nodo* nuevoNodo = new Nodo(nuevoObjeto);
            if (respuestaNueva) {
                nodo->no = new Nodo(nodo->pregunta);
                nodo->pregunta = nuevaPregunta;
                nodo->si = nuevoNodo;
            } else {
                nodo->si = new Nodo(nodo->pregunta);
                nodo->pregunta = nuevaPregunta;
                nodo->no = nuevoNodo;
            }

            cout << "¡He aprendido algo nuevo!\n";
        }
    } else {  // Nodo interno (pregunta)
        if (hacerPregunta(nodo->pregunta)) {
            jugar(nodo->si);  // Avanzar por la rama "sí"
        } else {
            jugar(nodo->no);  // Avanzar por la rama "no"
        }
    }
}

// Función para iniciar el juego
void iniciarJuego(Nodo* raiz) {
    cout << "¡Bienvenido al juego de adivinanzas!\n";
    do {
        jugar(raiz);
    } while (hacerPregunta("¿Quieres jugar otra vez?"));
}

int main() {
    // ÁRBOL INICIAL
    Nodo* raiz = new Nodo("¿Es un animal?");
    raiz->si = new Nodo("perro");
    raiz->no = new Nodo("manzana");

    iniciarJuego(raiz);

    // Liberar memoria
    delete raiz->si;
    delete raiz->no;
    delete raiz;

    return 0;
}
