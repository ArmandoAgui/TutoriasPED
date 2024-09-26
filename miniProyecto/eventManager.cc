#include <iostream>
#include <string>

const int MAX_EVENTS = 5;      // Máximo de eventos
const int MAX_PERSONAS = 10;   // Máximo de personas por evento

// Estructura para una persona
struct Person {
    std::string nombre;
};

// Estructura para un evento
struct Event {
    std::string nombre;
    std::string fecha_inicio;
    std::string fecha_fin;
    int capacidad_maxima;
    Person personas[MAX_PERSONAS]; // Lista de personas inscritas en el evento
    int total_personas;            // Contador de personas inscritas
};

// Función para crear un nuevo evento
void createEvent(Event* eventos, int* total_eventos) {
    if (*total_eventos >= MAX_EVENTS) {
        std::cout << "No se pueden crear más eventos, límite alcanzado.\n";
        return;
    }

    std::string nombre, fecha_inicio, fecha_fin;
    int capacidad_maxima;

    std::cout << "Ingrese el nombre del evento: ";
    std::cin.ignore();
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la fecha de inicio (dd/mm/aaaa): ";
    std::getline(std::cin, fecha_inicio);

    std::cout << "Ingrese la fecha de fin (dd/mm/aaaa): ";
    std::getline(std::cin, fecha_fin);

    std::cout << "Ingrese la capacidad máxima de personas: ";
    std::cin >> capacidad_maxima;

    eventos[*total_eventos].nombre = nombre;
    eventos[*total_eventos].fecha_inicio = fecha_inicio;
    eventos[*total_eventos].fecha_fin = fecha_fin;
    eventos[*total_eventos].capacidad_maxima = capacidad_maxima;
    eventos[*total_eventos].total_personas = 0; // Inicializa en cero el número de inscritos
    (*total_eventos)++;

    std::cout << "Evento '" << nombre << "' creado con éxito.\n";
}

// Función para listar todos los eventos
void listEvents(const Event* eventos, const int* total_eventos) {
    if (*total_eventos == 0) {
        std::cout << "No hay eventos creados.\n";
        return;
    }

    for (int i = 0; i < *total_eventos; i++) {
        std::cout << "Evento: " << eventos[i].nombre << ", Fecha Inicio: " << eventos[i].fecha_inicio
                  << ", Fecha Fin: " << eventos[i].fecha_fin << ", Capacidad: " << eventos[i].capacidad_maxima 
                  << ", Inscritos: " << eventos[i].total_personas << "\n";
    }
}

// Función para registrar una persona en un evento
void registerPerson(Event* eventos, int* total_eventos) {
    std::string nombreEvento, nombrePersona;

    std::cout << "Ingrese el nombre del evento para registrar una persona: ";
    std::cin.ignore();
    std::getline(std::cin, nombreEvento);

    for (int i = 0; i < *total_eventos; i++) {
        if (eventos[i].nombre == nombreEvento) {
            if (eventos[i].total_personas >= eventos[i].capacidad_maxima) {
                std::cout << "El evento " << nombreEvento << " ha alcanzado su capacidad máxima.\n";
                return;
            }

            std::cout << "Ingrese el nombre de la persona: ";
            std::getline(std::cin, nombrePersona);

            eventos[i].personas[eventos[i].total_personas].nombre = nombrePersona;
            eventos[i].total_personas++;
            std::cout << "Persona '" << nombrePersona << "' registrada en el evento '" << nombreEvento << "'.\n";
            return;
        }
    }

    std::cout << "Evento '" << nombreEvento << "' no encontrado.\n";
}

// Función para listar las personas registradas en un evento
void listRegisteredPersons(const Event* eventos, const int* total_eventos) {
    std::string nombreEvento;

    std::cout << "Ingrese el nombre del evento para ver las personas registradas: ";
    std::cin.ignore();
    std::getline(std::cin, nombreEvento);

    for (int i = 0; i < *total_eventos; i++) {
        if (eventos[i].nombre == nombreEvento) {
            if (eventos[i].total_personas == 0) {
                std::cout << "No hay personas registradas en el evento '" << nombreEvento << "'.\n";
                return;
            }

            std::cout << "Personas registradas en el evento '" << nombreEvento << "':\n";
            for (int j = 0; j < eventos[i].total_personas; j++) {
                std::cout << eventos[i].personas[j].nombre << "\n";
            }
            return;
        }
    }

    std::cout << "Evento '" << nombreEvento << "' no encontrado.\n";
}

// Función para eliminar una persona de un evento
void deletePersonFromEvent(Event* eventos, int* total_eventos) {
    std::string nombreEvento, nombrePersona;

    std::cout << "Ingrese el nombre del evento: ";
    std::cin.ignore();
    std::getline(std::cin, nombreEvento);

    for (int i = 0; i < *total_eventos; i++) {
        if (eventos[i].nombre == nombreEvento) {
            std::cout << "Ingrese el nombre de la persona a eliminar: ";
            std::getline(std::cin, nombrePersona);

            for (int j = 0; j < eventos[i].total_personas; j++) {
                if (eventos[i].personas[j].nombre == nombrePersona) {
                    eventos[i].total_personas--;
                    std::cout << "Persona '" << nombrePersona << "' eliminada del evento '" << nombreEvento << "'.\n";
                    return;
                }
            }
            std::cout << "Persona '" << nombrePersona << "' no encontrada en el evento '" << nombreEvento << "'.\n";
            return;
        }
    }

    std::cout << "Evento '" << nombreEvento << "' no encontrado.\n";
}

// Función para mostrar el menú
void showMenu() {
    std::cout << "\n------ Menú de Gestión de Eventos ------\n";
    std::cout << "1. Crear un nuevo evento\n";
    std::cout << "2. Listar todos los eventos\n";
    std::cout << "3. Registrar una persona en un evento\n";
    std::cout << "4. Listar personas registradas en un evento\n";
    std::cout << "5. Eliminar una persona de un evento\n";
    std::cout << "6. Salir\n";
    std::cout << "Seleccione una opción: ";
}

// Función principal
int main() {
    // Arreglo estático para los eventos
    Event eventos[MAX_EVENTS];
    int total_eventos = 0;
    int opcion;

    do {
        showMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                createEvent(eventos, &total_eventos);
                break;
            case 2:
                listEvents(eventos, &total_eventos);
                break;
            case 3:
                registerPerson(eventos, &total_eventos);
                break;
            case 4:
                listRegisteredPersons(eventos, &total_eventos);
                break;
            case 5:
                deletePersonFromEvent(eventos, &total_eventos);
                break;
            case 6:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida, por favor intente de nuevo.\n";
                break;
        }
    } while (opcion != 6);

    return 0;
}
