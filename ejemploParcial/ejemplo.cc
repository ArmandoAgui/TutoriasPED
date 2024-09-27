#include <iostream>
#include <string>

const int MAX_PERSONAS = 100; // Constante para el tamaño máximo del arreglo

struct Persona {
    std::string nombre;
    int edad;
};

// Prototipos de funciones
void menu(Persona* personas, int* tam);
void crearPersona(Persona* personas, int* tam);
void listarPersonas(const Persona* personas, int tam);
void actualizarPersona(Persona* personas, int tam);
void eliminarPersona(Persona* personas, int* tam);
bool validarIndice(int tam, int indice);

int main() {
    Persona personas[MAX_PERSONAS];  // Arreglo estático de personas
    int tam = 0;  // Tamaño actual del arreglo
    menu(personas, &tam);  // Llamar al menú principal, pasando el arreglo y el tamaño por referencia
    return 0;
}

// Función principal del menú
void menu(Persona* personas, int* tam) {
    int opcion;

    do {
        std::cout << "\n--- Menu CRUD ---\n";
        std::cout << "1. Crear persona\n";
        std::cout << "2. Listar personas\n";
        std::cout << "3. Actualizar persona\n";
        std::cout << "4. Eliminar persona\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                crearPersona(personas, tam);
                break;
            case 2:
                listarPersonas(personas, *tam);
                break;
            case 3:
                actualizarPersona(personas, *tam);
                break;
            case 4:
                eliminarPersona(personas, tam);
                break;
            case 5:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion invalida, intente de nuevo.\n";
        }
    } while (opcion != 5);
}

// Función para crear una nueva persona
void crearPersona(Persona* personas, int* tam) {
    if (*tam >= MAX_PERSONAS) {
        std::cout << "Error: no se puede agregar más personas, el límite ha sido alcanzado.\n";
        return;
    }

    Persona* nuevaPersona = &personas[*tam];  // Apuntamos al siguiente espacio disponible en el arreglo
    std::cout << "Ingrese el nombre: ";
    std::cin.ignore();
    std::getline(std::cin, nuevaPersona->nombre);
    std::cout << "Ingrese la edad: ";
    std::cin >> nuevaPersona->edad;

    (*tam)++;  // Incrementamos el tamaño del arreglo
    std::cout << "Persona " << nuevaPersona->nombre << " ha sido agregada exitosamente.\n";
}

// Función para listar todas las personas
void listarPersonas(const Persona* personas, int tam) {
    if (tam == 0) {
        std::cout << "No hay personas en la lista.\n";
        return;
    }

    std::cout << "\n--- Lista de personas ---\n";
    for (int i = 0; i < tam; i++) {
        std::cout << i + 1 << ". Nombre: " << personas[i].nombre << ", Edad: " << personas[i].edad << std::endl;
    }
}

// Función para actualizar los datos de una persona
void actualizarPersona(Persona* personas, int tam) {
    int indice;
    listarPersonas(personas, tam);
    std::cout << "Seleccione el índice de la persona a actualizar: ";
    std::cin >> indice;

    if (!validarIndice(tam, indice - 1)) {
        std::cout << "Índice inválido.\n";
        return;
    }

    Persona* persona = &personas[indice - 1];  // Apuntamos a la persona que se va a actualizar
    std::cout << "Ingrese el nuevo nombre: ";
    std::cin.ignore();
    std::getline(std::cin, persona->nombre);
    std::cout << "Ingrese la nueva edad: ";
    std::cin >> persona->edad;

    std::cout << "Persona actualizada exitosamente.\n";
}

// Función para eliminar una persona
void eliminarPersona(Persona* personas, int* tam) {
    int indice;
    listarPersonas(personas, *tam);
    std::cout << "Seleccione el índice de la persona a eliminar: ";
    std::cin >> indice;

    if (!validarIndice(*tam, indice - 1)) {
        std::cout << "Índice inválido.\n";
        return;
    }

    for (int i = indice - 1; i < *tam - 1; i++) {
        personas[i] = personas[i + 1];  // Mover las personas hacia la izquierda
    }
    (*tam)--;  // Reducir el tamaño
    std::cout << "Persona eliminada exitosamente.\n";
}

// Función para validar si el índice está dentro del rango
bool validarIndice(int tam, int indice) {
    return indice >= 0 && indice < tam;
}
