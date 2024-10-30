// main.cc
#include <iostream>
#include <string>

using namespace std;

const int MAX_CLUBS = 10;   // Capacidad máxima de clubes
const int MAX_MEMBERS = 50; // Capacidad máxima de miembros por club

struct Member
{
    string first_name;
    string last_name;
    int age;
};

struct Club
{
    string name;
    string creation_date;
    int max_capacity;
    Member *members[MAX_MEMBERS];
    int member_count = 0;
};

// Función para crear un nuevo club
void CreateClub(Club clubs[], int &num_clubs, int max_clubs)
{
    if (num_clubs >= max_clubs)
    {
        cout << "No se pueden agregar más clubes. Capacidad máxima alcanzada." << endl;
        return;
    }

    Club new_club;
    cout << "Ingrese el nombre del club: ";
    cin >> ws; // Limpia el espacio en blanco
    getline(cin, new_club.name);
    cout << "Ingrese la fecha de creación (dd/mm/aaaa): ";
    getline(cin, new_club.creation_date);
    cout << "Ingrese la capacidad máxima de miembros: ";
    cin >> new_club.max_capacity;

    new_club.member_count = 0; // Inicializa sin miembros
    clubs[num_clubs++] = new_club;

    cout << "Club creado exitosamente." << endl;
}

// Función para listar todos los clubes
void ListClubs(const Club clubs[], int num_clubs)
{
    if (num_clubs == 0)
    {
        cout << "No hay clubes registrados." << endl;
        return;
    }

    for (int i = 0; i < num_clubs; ++i)
    {
        cout << "Club " << i + 1 << ": " << clubs[i].name << " - Creado en: "
             << clubs[i].creation_date << " - Capacidad máxima: "
             << clubs[i].max_capacity << endl;
    }
}

// Función para registrar un miembro en un club
void RegisterMember(Club &club)
{
    if (club.member_count >= club.max_capacity)
    {
        cout << "No se pueden agregar más miembros. Capacidad máxima alcanzada." << endl;
        return;
    }

    Member *new_member = new Member;
    cout << "Ingrese el nombre del miembro: ";
    cin >> ws; // Limpia el espacio en blanco
    getline(cin, new_member->first_name);
    cout << "Ingrese el apellido del miembro: ";
    getline(cin, new_member->last_name);
    cout << "Ingrese la edad del miembro: ";
    cin >> new_member->age;

    club.members[club.member_count++] = new_member;

    cout << "Miembro registrado exitosamente en el club " << club.name << "." << endl;
}

// Función para listar todos los miembros de un club
void ListMembers(const Club &club)
{
    if (club.member_count == 0)
    {
        cout << "No hay miembros registrados en este club." << endl;
        return;
    }

    cout << "Miembros del club " << club.name << ":" << endl;
    for (int i = 0; i < club.member_count; ++i)
    {
        cout << "Miembro " << i + 1 << ": " << club.members[i]->first_name << " "
             << club.members[i]->last_name << ", Edad: " << club.members[i]->age << endl;
    }
}

// Función para contar el total de miembros en un club
void TotalMembers(const Club &club)
{
    cout << "Total de miembros en el club " << club.name << ": " << club.member_count << endl;
}

// Función principal
int main()
{
    Club clubs[MAX_CLUBS];
    int num_clubs = 0;
    int option;

    do
    {
        cout << "\nMenú de Gestión de Clubes" << endl;
        cout << "1. Crear un nuevo club" << endl;
        cout << "2. Listar todos los clubes" << endl;
        cout << "3. Registrar un miembro en un club" << endl;
        cout << "4. Listar miembros de un club" << endl;
        cout << "5. Calcular el total de miembros en un club" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> option;

        switch (option)
        {
        case 1:
            CreateClub(clubs, num_clubs, MAX_CLUBS);
            break;
        case 2:
            ListClubs(clubs, num_clubs);
            break;
        case 3:
        {
            int club_index;
            cout << "Ingrese el índice del club (1 - " << num_clubs << "): ";
            cin >> club_index;
            if (club_index < 1 || club_index > num_clubs)
            {
                cout << "Índice inválido." << endl;
            }
            else
            {
                RegisterMember(clubs[club_index - 1]);
            }
            break;
        }
        case 4:
        {
            int club_index;
            cout << "Ingrese el índice del club (1 - " << num_clubs << "): ";
            cin >> club_index;
            if (club_index < 1 || club_index > num_clubs)
            {
                cout << "Índice inválido." << endl;
            }
            else
            {
                ListMembers(clubs[club_index - 1]);
            }
            break;
        }
        case 5:
        {
            int club_index;
            cout << "Ingrese el índice del club (1 - " << num_clubs << "): ";
            cin >> club_index;
            if (club_index < 1 || club_index > num_clubs)
            {
                cout << "Índice inválido." << endl;
            }
            else
            {
                TotalMembers(clubs[club_index - 1]);
            }
            break;
        }
        case 6:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (option != 6);

    // Liberar memoria de miembros en cada club
    for (int i = 0; i < num_clubs; ++i)
    {
        for (int j = 0; j < clubs[i].member_count; ++j)
        {
            delete clubs[i].members[j];
        }
    }

    return 0;
}
