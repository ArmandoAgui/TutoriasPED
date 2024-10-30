#include <iostream>
#include <string>

using namespace std;

struct Member
{
    string first_name;
    string last_name;
    int age;
    Member *next;
};

struct Club
{
    string name;
    string creation_date;
    int max_capacity;
    int member_count;
    Member *member_stack;
    Club *next;
    Club *prev;
};

// Lista doblemente enlazada de Clubes
Club *listaClubes = nullptr;

// Declaración de funciones
void CrearClub();
void ListarClubes();
void RegistrarMiembro();
void ListarMiembros();
void CalcularTotalMiembros();
void MostrarMenu();

int main()
{
    int opcion;
    do
    {
        MostrarMenu();
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            CrearClub();
            break;
        case 2:
            ListarClubes();
            break;
        case 3:
            RegistrarMiembro();
            break;
        case 4:
            ListarMiembros();
            break;
        case 5:
            CalcularTotalMiembros();
            break;
        case 6:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 6);

    return 0;
}

void MostrarMenu()
{
    cout << "\nMenú de Gestión de Clubes" << endl;
    cout << "1. Crear un nuevo club" << endl;
    cout << "2. Listar todos los clubes" << endl;
    cout << "3. Registrar un miembro en un club" << endl;
    cout << "4. Listar miembros de un club" << endl;
    cout << "5. Calcular el total de miembros en un club" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void CrearClub()
{
    Club *nuevoClub = new Club;
    cout << "Ingrese el nombre del club: ";
    cin >> ws;
    getline(cin, nuevoClub->name);
    cout << "Ingrese la fecha de creación (dd/mm/aaaa): ";
    getline(cin, nuevoClub->creation_date);
    cout << "Ingrese la capacidad máxima de miembros: ";
    cin >> nuevoClub->max_capacity;

    nuevoClub->member_count = 0;
    nuevoClub->member_stack = nullptr;
    nuevoClub->next = nullptr;
    nuevoClub->prev = nullptr;

    if (listaClubes == nullptr)
    {
        listaClubes = nuevoClub;
    }
    else
    {
        Club *temporal = listaClubes;
        while (temporal->next != nullptr)
        {
            temporal = temporal->next;
        }
        temporal->next = nuevoClub;
        nuevoClub->prev = temporal;
    }

    cout << "Club '" << nuevoClub->name << "' creado exitosamente." << endl;
}

void ListarClubes()
{
    if (listaClubes == nullptr)
    {
        cout << "No hay clubes registrados." << endl;
        return;
    }

    Club *temporal = listaClubes;
    int index = 1;
    while (temporal != nullptr)
    {
        cout << "Club " << index++ << ": " << temporal->name
             << ", Creación: " << temporal->creation_date
             << ", Capacidad: " << temporal->max_capacity
             << ", Miembros: " << temporal->member_count << endl;
        temporal = temporal->next;
    }
}

void RegistrarMiembro()
{
    if (listaClubes == nullptr)
    {
        cout << "No hay clubes registrados. Primero cree un club." << endl;
        return;
    }

    ListarClubes();
    int club_index;
    cout << "Seleccione el índice del club donde desea registrar al miembro: ";
    cin >> club_index;

    Club *club = listaClubes;
    for (int i = 1; i < club_index && club != nullptr; i++)
    {
        club = club->next;
    }

    if (club == nullptr)
    {
        cout << "Índice de club inválido." << endl;
        return;
    }

    if (club->member_count >= club->max_capacity)
    {
        cout << "Capacidad máxima de miembros alcanzada en el club " << club->name << "." << endl;
        return;
    }

    Member *nuevoMiembro = new Member;
    cout << "Ingrese el nombre del miembro: ";
    cin >> ws;
    getline(cin, nuevoMiembro->first_name);
    cout << "Ingrese el apellido del miembro: ";
    getline(cin, nuevoMiembro->last_name);
    cout << "Ingrese la edad del miembro: ";
    cin >> nuevoMiembro->age;

    nuevoMiembro->next = club->member_stack;
    club->member_stack = nuevoMiembro;
    club->member_count++;

    cout << "Miembro '" << nuevoMiembro->first_name << " " << nuevoMiembro->last_name
         << "' registrado exitosamente en el club " << club->name << "." << endl;
}

void ListarMiembros()
{
    if (listaClubes == nullptr)
    {
        cout << "No hay clubes registrados." << endl;
        return;
    }

    ListarClubes();
    int club_index;
    cout << "Seleccione el índice del club para listar sus miembros: ";
    cin >> club_index;

    Club *club = listaClubes;
    for (int i = 1; i < club_index && club != nullptr; i++)
    {
        club = club->next;
    }

    if (club == nullptr)
    {
        cout << "Índice de club inválido." << endl;
        return;
    }

    if (club->member_stack == nullptr)
    {
        cout << "No hay miembros registrados en el club " << club->name << "." << endl;
        return;
    }

    Member *temporal = club->member_stack;
    int index = 1;
    while (temporal != nullptr)
    {
        cout << "Miembro " << index++ << ": " << temporal->first_name
             << " " << temporal->last_name
             << ", Edad: " << temporal->age << endl;
        temporal = temporal->next;
    }
}

void CalcularTotalMiembros()
{
    if (listaClubes == nullptr)
    {
        cout << "No hay clubes registrados." << endl;
        return;
    }

    ListarClubes();
    int club_index;
    cout << "Seleccione el índice del club para calcular el total de miembros: ";
    cin >> club_index;

    Club *club = listaClubes;
    for (int i = 1; i < club_index && club != nullptr; i++)
    {
        club = club->next;
    }

    if (club == nullptr)
    {
        cout << "Índice de club inválido." << endl;
        return;
    }

    cout << "Total de miembros en el club " << club->name << ": " << club->member_count << endl;
}
