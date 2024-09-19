#include <iostream>
#include <string>

using namespace std;

// Estructura que representa una persona
struct Persona {
    int id;
    string nombre;
    string apellido;
    int edad;
};

// Estructura que representa un nodo de la lista enlazada
struct Nodo {
    Persona persona; // Datos de la persona
    Nodo* siguiente; // Puntero al siguiente nodo
};

// Función para agregar una persona a la lista enlazada
void agregarPersona(Nodo*& cabeza, int id, string nombre, string apellido, int edad) {
    // Crear un nuevo nodo con los datos proporcionados
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->persona.id = id;
    nuevoNodo->persona.nombre = nombre;
    nuevoNodo->persona.apellido = apellido;
    nuevoNodo->persona.edad = edad;
    nuevoNodo->siguiente = nullptr; // El nuevo nodo apunta a nullptr, es el último nodo por ahora

    // Si la lista está vacía, el nuevo nodo será la cabeza
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        // Si la lista no está vacía, recorrer hasta el último nodo
        Nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        // Enlazar el último nodo con el nuevo nodo
        temp->siguiente = nuevoNodo;
    }
    cout << "Persona agregada con exito!" << endl;
}

// Función para mostrar todas las personas en la lista enlazada
void mostrarPersonas(Nodo* cabeza) {
    // Si la lista está vacía
    if (cabeza == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    // Recorrer la lista e imprimir los datos de cada persona
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << "ID: " << temp->persona.id << ", Nombre: " << temp->persona.nombre 
             << ", Apellido: " << temp->persona.apellido << ", Edad: " << temp->persona.edad << endl;
        temp = temp->siguiente;
    }
}

// Función para actualizar los datos de una persona en la lista
void actualizarPersona(Nodo* cabeza, int id) {
    // Buscar la persona en la lista por su ID
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        if (temp->persona.id == id) {
            // Solicitar los nuevos datos
            cout << "Ingrese el nuevo nombre: ";
            cin >> temp->persona.nombre;
            cout << "Ingrese el nuevo apellido: ";
            cin >> temp->persona.apellido;
            cout << "Ingrese la nueva edad: ";
            cin >> temp->persona.edad;
            cout << "Persona actualizada con exito!" << endl;
            return;
        }
        temp = temp->siguiente;
    }
    // Si no se encontró el ID
    cout << "Persona con ID " << id << " no encontrada." << endl;
}

// Función para eliminar una persona de la lista enlazada por su ID
void eliminarPersona(Nodo*& cabeza, int id) {
    // Si la lista está vacía
    if (cabeza == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    // Si la persona a eliminar está en la cabeza de la lista
    if (cabeza->persona.id == id) {
        Nodo* aEliminar = cabeza;
        cabeza = cabeza->siguiente; // Mover la cabeza al siguiente nodo
        delete aEliminar;            // Liberar la memoria
        cout << "Persona eliminada con exito!" << endl;
        return;
    }

    // Buscar la persona en el resto de la lista
    Nodo* temp = cabeza;
    while (temp->siguiente != nullptr && temp->siguiente->persona.id != id) {
        temp = temp->siguiente;
    }

    // Si no se encontró el ID
    if (temp->siguiente == nullptr) {
        cout << "Persona con ID " << id << " no encontrada." << endl;
        return;
    }

    // Eliminar el nodo de la lista
    Nodo* aEliminar = temp->siguiente;
    temp->siguiente = temp->siguiente->siguiente;
    delete aEliminar;
    cout << "Persona eliminada con exito!" << endl;
}

// Función principal que ejecuta el CRUD mediante un menú
int main() {
    Nodo* lista = nullptr;  // Puntero que apunta al primer nodo de la lista enlazada
    int opcion, id, edad;
    string nombre, apellido;

    // Menú para realizar las operaciones CRUD
    do {
        cout << "\nMenu CRUD\n";
        cout << "1. Agregar persona\n";
        cout << "2. Mostrar personas\n";
        cout << "3. Actualizar persona\n";
        cout << "4. Eliminar persona\n";
        cout << "5. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Solicitar datos para agregar una persona
            cout << "Ingrese ID: ";
            cin >> id;
            cout << "Ingrese nombre: ";
            cin >> nombre;
            cout << "Ingrese apellido: ";
            cin >> apellido;
            cout << "Ingrese edad: ";
            cin >> edad;
            agregarPersona(lista, id, nombre, apellido, edad);
            break;
        case 2:
            mostrarPersonas(lista);
            break;
        case 3:
            cout << "Ingrese ID de la persona a actualizar: ";
            cin >> id;
            actualizarPersona(lista, id);
            break;
        case 4:
            cout << "Ingrese ID de la persona a eliminar: ";
            cin >> id;
            eliminarPersona(lista, id);
            break;
        case 5:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 5);  // Repetir el menú hasta que el usuario elija salir

    return 0;
}
