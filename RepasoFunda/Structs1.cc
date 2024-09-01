#include <iostream>
#include <string>

// Estructura para almacenar la informacion de una pelicula
struct Pelicula
{
    std::string titulo;
    std::string director;
    int anio;
    std::string genero;
    static int contador;  // Contador estatico para el numero de peliculas
};

int Pelicula::contador = 0;  // Inicializacion del contador estatico

// Funcion para mostrar todas las peliculas almacenadas
void mostrarPeliculas(Pelicula peliculas[], int cantidad) {
    if (cantidad == 0) {
        std::cout << "No hay peliculas almacenadas." << std::endl;
        return;
    }

    std::cout << "\nLista de peliculas:\n";
    for(int i = 0; i < cantidad; i++) {
        std::cout << "\nPelicula " << i + 1 << ":\n";
        std::cout << "Titulo: " << peliculas[i].titulo << std::endl;
        std::cout << "Director: " << peliculas[i].director << std::endl;
        std::cout << "Anio: " << peliculas[i].anio << std::endl;
        std::cout << "Genero: " << peliculas[i].genero << std::endl;
    }
}

// Funcion para buscar una pelicula por su nombre
void buscarPelicula(Pelicula peliculas[], int cantidad) {
    std::cin.ignore();  // Limpiar el buffer del cin

    std::string tituloBusqueda;
    std::cout << "Ingrese el titulo de la pelicula que desea buscar: ";
    std::getline(std::cin, tituloBusqueda);

    bool encontrada = false;
    for(int i = 0; i < cantidad; i++) {
        if(peliculas[i].titulo == tituloBusqueda) {
            std::cout << "\nPelicula encontrada:\n";
            std::cout << "Titulo: " << peliculas[i].titulo << std::endl;
            std::cout << "Director: " << peliculas[i].director << std::endl;
            std::cout << "Anio: " << peliculas[i].anio << std::endl;
            std::cout << "Genero: " << peliculas[i].genero << std::endl;
            encontrada = true;
            break;
        }
    }

    if (!encontrada) {
        std::cout << "Pelicula no encontrada." << std::endl;
    }
}

// Funcion principal que incluye un menu para interactuar con el usuario
int main(int argc, char *argv[])
{
    // Verifica si el argumento de cantidad de peliculas fue pasado correctamente
    if (argc != 2)
    {
        std::cerr << "Uso: " << argv[0] << " <numero>" << std::endl;
        return 1;
    }

    int cantidad = std::atoi(argv[1]);  // Convertir argumento a entero
    Pelicula peliculas[cantidad];  // Array de structs estaticos para almacenar peliculas

    // Ciclo para ingresar la informacion de cada pelicula
    for (int i = 0; i < cantidad; i++)
    {
        std::cout << "\nIngrese la informacion de la pelicula " << i + 1 << ":\n";

        std::cin.ignore();  // Limpiar el buffer del cin

        std::cout << "Titulo: ";
        std::getline(std::cin, peliculas[i].titulo);

        std::cout << "Director: ";
        std::getline(std::cin, peliculas[i].director);

        std::cout << "Anio: ";
        std::cin >> peliculas[i].anio;

        std::cin.ignore();  // Limpiar el buffer del cin nuevamente

        std::cout << "Genero: ";
        std::getline(std::cin, peliculas[i].genero);

        Pelicula::contador++;
    }

    // Menu de opciones para el usuario
    int opcion;
    do {
        std::cout << "\n--- Menu de opciones ---\n";
        std::cout << "1. Mostrar todas las peliculas\n";
        std::cout << "2. Buscar una pelicula por su nombre\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarPeliculas(peliculas, cantidad);
                break;
            case 2:
                buscarPelicula(peliculas, cantidad);
                break;
            case 3:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Por favor intente nuevamente." << std::endl;
        }

    } while(opcion != 3);

    return 0;
}
