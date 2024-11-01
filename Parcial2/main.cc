#include <iostream>
#include <string>

using namespace std;

// Estructura de miembro (Pila de miembros)
struct Miembro {
    string nombre;
    string apellido;
    int edad;
    Miembro* siguiente;
};

// Estructura de club (Lista doblemente enlazada de clubes)
struct Club {
    string nombre;
    string fecha;
    Miembro* miembros; // Puntero a la pila de miembros
    Club* siguiente;
    Club* anterior;
};

// Punteros a la lista doble de clubes
Club* listaClubes = nullptr;

// Declaración de funciones
void mostrarMenu();
void agregarClub(Club*& lista, const string& nombre, const string& fecha);
void agregarMiembro(Club*& club, const string& nombre, const string& apellido, int edad);
void listarClubes(const Club* lista);
void eliminarClub(Club*& lista, const string& nombre);
int contarMiembros(const Club* club);
void verMiembros(const Club* club);
void modificarMiembro(Club*& club, const string& nombre);
void eliminarMiembro(Club*& club, const string& nombre);

int main() {
    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                string nombre, fecha;
                cout << "Ingrese el nombre del club: ";
                getline(cin, nombre);
                cout << "Ingrese la fecha de creación del club: ";
                getline(cin, fecha);
                agregarClub(listaClubes, nombre, fecha);
                break;
            }
            case 2: {
                string nombreClub, nombreMiembro, apellido;
                int edad;
                cout << "Ingrese el nombre del club: ";
                getline(cin, nombreClub);
                Club* temp = listaClubes;
                while (temp && temp->nombre != nombreClub) temp = temp->siguiente;
                if (temp) {
                    cout << "Ingrese el nombre del miembro: ";
                    getline(cin, nombreMiembro);
                    cout << "Ingrese el apellido del miembro: ";
                    getline(cin, apellido);
                    cout << "Ingrese la edad del miembro: ";
                    cin >> edad;
                    agregarMiembro(temp, nombreMiembro, apellido, edad);
                } else {
                    cout << "Club no encontrado.\n";
                }
                break;
            }
            case 3:
                listarClubes(listaClubes);
                break;
            case 4: {
                string nombre;
                cout << "Ingrese el nombre del club a eliminar: ";
                getline(cin, nombre);
                eliminarClub(listaClubes, nombre);
                break;
            }
            case 5: {
                string nombre;
                cout << "Ingrese el nombre del club para contar sus miembros: ";
                getline(cin, nombre);
                Club* temp = listaClubes;
                while (temp && temp->nombre != nombre) temp = temp->siguiente;
                if (temp) {
                    cout << "Cantidad de miembros en el club " << temp->nombre << ": " << contarMiembros(temp) << endl;
                } else {
                    cout << "Club no encontrado.\n";
                }
                break;
            }
            case 6: {
                string nombreClub;
                cout << "Ingrese el nombre del club para ver sus miembros: ";
                getline(cin, nombreClub);
                Club* temp = listaClubes;
                while (temp && temp->nombre != nombreClub) temp = temp->siguiente;
                if (temp) {
                    verMiembros(temp);
                } else {
                    cout << "Club no encontrado.\n";
                }
                break;
            }
            case 7: {
                string nombreClub, nombreMiembro;
                cout << "Ingrese el nombre del club: ";
                getline(cin, nombreClub);
                Club* temp = listaClubes;
                while (temp && temp->nombre != nombreClub) temp = temp->siguiente;
                if (temp) {
                    cout << "Ingrese el nombre del miembro a modificar: ";
                    getline(cin, nombreMiembro);
                    modificarMiembro(temp, nombreMiembro);
                } else {
                    cout << "Club no encontrado.\n";
                }
                break;
            }
            case 8: {
                string nombreClub, nombreMiembro;
                cout << "Ingrese el nombre del club: ";
                getline(cin, nombreClub);
                Club* temp = listaClubes;
                while (temp && temp->nombre != nombreClub) temp = temp->siguiente;
                if (temp) {
                    cout << "Ingrese el nombre del miembro a eliminar: ";
                    getline(cin, nombreMiembro);
                    eliminarMiembro(temp, nombreMiembro);
                } else {
                    cout << "Club no encontrado.\n";
                }
                break;
            }
            case 0:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 0);

    return 0;
}

// Función para mostrar el menú
void mostrarMenu() {
    cout << "\n--- Gestión de Clubes ---\n";
    cout << "1. Agregar Club\n";
    cout << "2. Agregar Miembro a un Club\n";
    cout << "3. Listar Clubes y Miembros\n";
    cout << "4. Eliminar Club\n";
    cout << "5. Contar Miembros en un Club\n";
    cout << "6. Ver Miembros de un Club\n";
    cout << "7. Modificar Miembro de un Club\n";
    cout << "8. Eliminar Miembro de un Club\n";
    cout << "0. Salir\n";
}

// Función para crear un nuevo club
void agregarClub(Club*& lista, const string& nombre, const string& fecha) {
    Club* nuevoClub = new Club{nombre, fecha, nullptr, nullptr, nullptr};
    if (!lista) {
        lista = nuevoClub;
    } else {
        Club* temp = lista;
        while (temp->siguiente) temp = temp->siguiente;
        temp->siguiente = nuevoClub;
        nuevoClub->anterior = temp;
    }
}

// Función para agregar un miembro a la pila de un club
void agregarMiembro(Club*& club, const string& nombre, const string& apellido, int edad) {
    Miembro* nuevoMiembro = new Miembro{nombre, apellido, edad, nullptr};
    nuevoMiembro->siguiente = club->miembros;
    club->miembros = nuevoMiembro;
}

// Función para imprimir todos los clubes y sus miembros
void listarClubes(const Club* lista) {
    const Club* temp = lista;
    while (temp) {
        cout << "Club: " << temp->nombre << ", Fecha: " << temp->fecha << endl;
        verMiembros(temp);
        temp = temp->siguiente;
    }
}

// Función para eliminar un club
void eliminarClub(Club*& lista, const string& nombre) {
    Club* temp = lista;
    while (temp && temp->nombre != nombre) temp = temp->siguiente;
    if (!temp) return;
    if (temp->anterior) temp->anterior->siguiente = temp->siguiente;
    if (temp->siguiente) temp->siguiente->anterior = temp->anterior;
    if (temp == lista) lista = temp->siguiente;
    delete temp;
}

// Función para contar miembros en un club
int contarMiembros(const Club* club) {
    int contador = 0;
    const Miembro* temp = club->miembros;
    while (temp) {
        contador++;
        temp = temp->siguiente;
    }
    return contador;
}

// Función para ver miembros de un club
void verMiembros(const Club* club) {
    const Miembro* miembroTemp = club->miembros;
    while (miembroTemp) {
        cout << "  Miembro: " << miembroTemp->nombre << " " << miembroTemp->apellido << ", Edad: " << miembroTemp->edad << endl;
        miembroTemp = miembroTemp->siguiente;
    }
}

// Función para modificar un miembro
void modificarMiembro(Club*& club, const string& nombre) {
    Miembro* temp = club->miembros;
    while (temp && temp->nombre != nombre) temp = temp->siguiente;
    if (temp) {
        cout << "Ingrese el nuevo nombre: ";
        getline(cin, temp->nombre);
        cout << "Ingrese el nuevo apellido: ";
        getline(cin, temp->apellido);
        cout << "Ingrese la nueva edad: ";
        cin >> temp->edad;
        cin.ignore();
    } else {
        cout << "Miembro no encontrado.\n";
    }
}

// Función para eliminar un miembro de un club
void eliminarMiembro(Club*& club, const string& nombre) {
    Miembro* temp = club->miembros;
    Miembro* anterior = nullptr;
    while (temp && temp->nombre != nombre) {
        anterior = temp;
        temp = temp->siguiente;
    }
    if (temp) {
        if (anterior) anterior->siguiente = temp->siguiente;
        else club->miembros = temp->siguiente;
        delete temp;
    } else {
        cout << "Miembro no encontrado.\n";
    }
}
