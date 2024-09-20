#include <iostream>
// Libreria para administrar ficheros
#include <fstream>
// Libreria para funciones con variables string
#include <string>
// Libreria para crear carpetas
#include <direct.h>
// Librerias para cambiar el nombre de las carpetas
#include <cstdlib>
#include <cstdio>
// Libreria para cerrar el programa
#include <stdlib.h>
// Validar informacion de usuario
#include <cstring>
#include <cctype>
// Libreria para convertir un int a string
#include <sstream>
// Libreria para verificar un int no sea otro tipo de dato
#include <limits>

using namespace std;
// Cantidad de mesas Disponibles
const int CantMesas = 25;
// Estructura con la informacion de una reservacion
struct Reserva
{
    string mesa;
    string ubicacion;
    string tipo;
    string capacidad;
    // Guarda que empleado realizo la reservacion
    string empleado;
};

// Estructura de Nodo2 para la listaReserva doblemente enlazada
struct Nodo2
{
    Reserva Data;
    Nodo2 *prev;
    Nodo2 *next;
};
// Estructira de informacion de un usuario
struct Data
{
    string user;
    string pwd;
    string userLevel;
};

// Estructura de nodo para la listaUsuario doblemente enlazada
struct Nodo
{
    Data Data;
    Nodo *prev;
    Nodo *next;
};
// Variables globales, que facilitan el acceso a cierta informacion recurrente
int intentos = 1;
string nivelUsuario, nombreUsuario;

// Variable global, donde se establece que la listaUsuario esta vacia
struct Nodo2 *listaReservas = nullptr;

// Funciones para la gestion de Reservaciones
void llenadoListaReservas(string);
void insertarFinalReserva(const string &, const string &, const string &, const string &, const string &);
void imprimirReservasParametrizada(string);
void imprimirReservas();
void envioParametros();
void editarNodoReserva(string, int, string);
void editarReserva(int, string);
bool estaLibre(string);
void eliminarReserva(int);
void menuReservacion();
bool verificarNumero(int);

// Variable global, donde se establece que la listaUsuario esta vacia
struct Nodo *listaUsuario = nullptr;

// Funciones para la gestion de Usuarios
bool validarUsuario(const char *);
bool validarContrasena(string);
void llenadoListaUsuarios();
void insertarFinal(const string &, const string &, const string &);
void login(string, string);
void agregarUsuario();
void editarUsuario(string);
void editarNodo(string, int, string);
void eliminarUsuario();
void menuUsuarios();
void imprimir();
void verificacion(int, int, string, string, string, string);

// ----------------------------------------------------------------------------------
bool verificarNumero(int num)
{
    // Verificar si es un número negativo
    if (num < 0)
    {
        cout << "El numero es negativo." << endl;
        return false;
    }
    // Verificar si no es un número
    if (cin.fail())
    {
        cin.clear();                                         // Limpiar el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
        cout << "La entrada no es un numero valido." << endl;
        return false;
    }
    return true;
}

// Funcion para lectura de los txt de reservaciones y llenado de la lista doblemente enlazada
void llenadoListaReservas(string user)
{
    struct Nodo *temporal = listaUsuario;
    string direccion = user + "/reservaciones.txt";
    ifstream inputFile(direccion.c_str());
    if (!inputFile)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    string info, mesa, ubicacion, tipo, capacidad, empleado;
    int i = 1;
    while (getline(inputFile, info))
    {
        switch (i)
        {
        case 1:
            mesa = info;
            i++;
            break;
        case 2:
            ubicacion = info;
            i++;
            break;
        case 3:
            tipo = info;
            i++;
            break;
        case 4:
            capacidad = info;
            i++;
            break;
        case 5:
            empleado = info;
            i = 1;
            insertarFinalReserva(mesa, ubicacion, tipo, capacidad, empleado);
            break;
        }
    }
    inputFile.close();
}

// Insertar Nodo2s al final de la listaUsuario
void insertarFinalReserva(const string &mesa, const string &ubicacion, const string &tipo, const string &capacidad, const string &empleado)
{
    struct Nodo2 *nuevoNodo2 = new Nodo2;
    struct Nodo2 *temporal = listaReservas;

    nuevoNodo2->Data.mesa = mesa;
    nuevoNodo2->Data.ubicacion = ubicacion;
    nuevoNodo2->Data.tipo = tipo;
    nuevoNodo2->Data.capacidad = capacidad;
    nuevoNodo2->Data.empleado = empleado;
    nuevoNodo2->next = nullptr;
    nuevoNodo2->prev = nullptr;

    // Si la listaUsuario esta vacia
    if (listaReservas == nullptr)
    {
        listaReservas = nuevoNodo2;
    }
    else
    {
        while (temporal->next != nullptr)
        {
            temporal = temporal->next;
        }
        // conexiones de nuevoNodo2 a temporal
        temporal->next = nuevoNodo2;
        nuevoNodo2->prev = temporal;
    }
}

// Funcion que imprime la informacion de una reservacion mediante parametros
void imprimirReservasParametrizada(string mesaparam)
{
    int i = 1;
    struct Nodo2 *temporal = listaReservas;
    if (temporal != nullptr)
    {
        // Imprimir cuando se inserta al final de la lista
        while (temporal != nullptr)
        {
            if (mesaparam == temporal->Data.mesa)
            {
                cout << "---------------------------------------" << endl;
                cout << "Mesa: #" << temporal->Data.mesa << endl
                     << "Ubicacion -> " << temporal->Data.ubicacion << endl
                     << "Tipo -> " << temporal->Data.tipo << endl
                     << "Capacidad-> " << temporal->Data.capacidad << endl
                     << "Reservado por: -> " << temporal->Data.empleado << endl;
                return;
            }
            temporal = temporal->next;
        }
        cout << "Reservacion no encontrada" << endl;
    }
    else
    {
        cout << "Lista vacia";
    }
}

// Funcion que imprime todas las reservaciones
void imprimirReservas()
{
    int i = 1;
    struct Nodo2 *temporal = listaReservas;
    if (temporal != nullptr)
    {
        // Imprimir cuando se inserta al final de la lista
        while (temporal != nullptr)
        {
            cout << "---------------------------------------" << endl;
            cout << i << ". Mesa: #" << temporal->Data.mesa << endl
                 << "Ubicacion -> " << temporal->Data.ubicacion << endl
                 << "Tipo -> " << temporal->Data.tipo << endl
                 << "Capacidad-> " << temporal->Data.capacidad << endl
                 << "Reservado por -> " << temporal->Data.empleado << endl;
            temporal = temporal->next;
            i++;
        }
    }
    else
    {
        cout << "Lista vacia";
    }
}

// Funcion que envia el nombre de cada usuarios para buscar por cada una de sus carpetas y acceder al txt de reservaciones
void envioParametros()
{
    struct Nodo *temporal = listaUsuario;
    if (temporal != nullptr)
    {
        while (temporal != nullptr)
        {
            llenadoListaReservas(temporal->Data.user);
            temporal = temporal->next;
        }
    }
    else
    {
        cout << "Lista vacia" << endl;
    }
}

// Funcion que imprime las mesas disponibles
void imprimirMesasLibres()
{
    int j = 1;
    bool estaLibre = true;
    struct Nodo2 *temporal = listaReservas;
    cout << "---------------Mesas Disponibles---------------" << endl;
    for (int i = 1; i <= CantMesas; i++)
    {
        // Convertimos el número de iterador (representa el numero de la mesa) de int a string
        stringstream stream;
        stream << i;
        string mesaString;
        stream >> mesaString;
        // Imprimir cuando se inserta al final de la lista
        while (temporal != nullptr)
        {
            int res = temporal->Data.mesa.compare(mesaString);
            if (res == 0)
            {
                estaLibre = false;
            }
            temporal = temporal->next;
        }
        if (estaLibre)
        {
            cout << j << "-> Mesa #" << i << endl;
            j++;
        }
        estaLibre = true;
        temporal = listaReservas;
    }
    estaLibre = true;
    j = 1;
    cout << "---------------Mesas no Disponibles---------------" << endl;
    for (int i = 1; i <= CantMesas; i++)
    {
        // Convertimos el número de iterador (representa el numero de la mesa) de int a string
        stringstream stream;
        stream << i;
        string mesaString;
        stream >> mesaString;
        // Imprimir cuando se inserta al final de la lista
        while (temporal != nullptr)
        {
            int res = temporal->Data.mesa.compare(mesaString);
            if (res == 0)
            {
                estaLibre = false;
            }
            temporal = temporal->next;
        }
        if (!estaLibre)
        {
            cout << j << "-> Mesa #" << i << endl;
            j++;
        }
        estaLibre = true;
        temporal = listaReservas;
    }
}

// Funcion que verifica si una mesa esta disponible o no
bool estaLibre(string mesa)
{
    struct Nodo2 *temporal = listaReservas;
    // Imprimir cuando se inserta al final de la lista
    while (temporal != nullptr)
    {
        int res = temporal->Data.mesa.compare(mesa);
        if (res == 0)
        {
            return false;
        }
        temporal = temporal->next;
    }
    int numMesa = 0;
    istringstream(mesa) >> numMesa;
    if (numMesa <= 0 || numMesa > 25)
    {
        return false;
    }
    return true;
}

// Funcion que edita la informacion la lista de reserva
void editarNodoReserva(string mesaParam, int opc, string valorEditado)
{
    struct Nodo2 *aux = listaReservas;
    string url, user;
    while (aux != nullptr && aux->Data.mesa != mesaParam)
    {
        aux = aux->next;
    }
    if (aux != nullptr)
    {
        switch (opc)
        {
        case 1:
            aux->Data.mesa = valorEditado;
            break;
        case 2:
            aux->Data.ubicacion = valorEditado;
            break;
        case 3:
            aux->Data.tipo = valorEditado;
            break;
        case 4:
            aux->Data.capacidad = valorEditado;
            break;
        default:
            break;
        }
        user = aux->Data.empleado;
        url = "c:" + user + "/reservaciones.txt";
    }
    else
    {
        cout << "No se encontro";
        system("pause");
    }
    ofstream fichero(url.c_str(), ios::out | ios::ate);
    struct Nodo2 *temporal = listaReservas;
    // Imprimir cuando se inserta al final de la listaUsuario
    while (temporal != nullptr)
    {
        if (temporal->Data.empleado == user)
        {
            fichero << temporal->Data.mesa << endl;
            fichero << temporal->Data.ubicacion << endl;
            fichero << temporal->Data.tipo << endl;
            fichero << temporal->Data.capacidad << endl;
            fichero << temporal->Data.empleado << endl;
        }
        temporal = temporal->next;
    }
    fichero.close();
}

// Funcion que solicita la informacion a editar en la lista de reservaciones
void editarReserva(int opc, string mesaParam)
{
    string valorCambiado;
    switch (opc)
    {
    case 1:
        system("cls");
        imprimirMesasLibres();
        cout << "Ingrese el nuevo numero de mesa (es el numero que esta de ultimo Ejemplo: 'Mesa #34')" << endl;
        cin >> valorCambiado;
        if (!estaLibre(valorCambiado))
        {
            cout << "Mesa no disponible" << endl;
            system("pause");
            return;
        }
        break;
    case 2:
        system("cls");
        cout << "Ingrese la nueva ubicacion" << endl;
        cin >> valorCambiado;
        break;
    case 3:
        system("cls");
        cout << "Ingrese el nuevo tipo de mesa" << endl;
        cin >> valorCambiado;
        break;
    case 4:
        system("cls");
        cout << "Ingrese la nueva capacidad" << endl;
        cin >> valorCambiado;
        break;
    default:
        break;
    }
    editarNodoReserva(mesaParam, opc, valorCambiado);
}

// Funcion que elimina una reservacion de la lista de reservaciones
void eliminarReserva(int pos)
{
    string nameuser;
    struct Nodo2 *aux = listaReservas;

    // Verificar si la lista esta vacia
    if (aux == nullptr)
    {
        cout << "La lista esta vacia." << endl;
        return;
    }

    // Si pos es 1, eliminar el primer nodo
    if (pos == 1)
    {
        nameuser = listaReservas->Data.empleado;
        listaReservas = aux->next;
        delete aux;
        aux = nullptr;
        listaReservas->prev = nullptr;
        cout << "Reservacion eliminado exitosamente." << endl;
        system("pause");
    }

    int i = 1;
    while (aux != nullptr && i < pos)
    {
        aux = aux->next;
        i++;
    }

    if (aux != nullptr)
    {
        if (aux->next != nullptr)
        {
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
        }
        else
        {
            // Si pos es el último nodo
            aux->prev->next = nullptr;
        }
        nameuser = aux->Data.empleado;
        delete aux;
        cout << "Usuario eliminado exitosamente." << endl;
        system("pause");
    }
    else
    {
        cout << "No se encontro el usuario en la posicion especificada." << endl;
        system("pause");
        return;
    }
    string url = "c:" + nameuser + "/reservaciones.txt";
    ofstream fichero(url, ios::out | ios::ate);
    aux = listaReservas;
    while (aux != nullptr)
    {
        if (nameuser == aux->Data.empleado)
        {
            fichero << aux->Data.mesa << endl;
            fichero << aux->Data.ubicacion << endl;
            fichero << aux->Data.tipo << endl;
            fichero << aux->Data.capacidad << endl;
            fichero << aux->Data.empleado << endl;
        }
        aux = aux->next;
    }
    fichero.close();
}

// Funcion que solicita la informacion de una reservacion para agregarla a la lista
void agregarReserva()
{
    string numMesa, ubicacion, tipo, capacidad, url;
    cout << "Ingresa el numero de mesa: #" << endl;
    cin >> numMesa;
    if (!estaLibre(numMesa))
    {
        cout << "Mesa no disponible" << endl;
        system("pause");
        return;
    }
    cout << "Ingrese la ubicacion de la mesa" << endl;
    cin >> ubicacion;
    cout << "Ingrese el tipo de mesa" << endl;
    cin >> tipo;
    cout << "Ingrese el numero de personas de la reservacion" << endl;
    cin >> capacidad;
    insertarFinalReserva(numMesa, ubicacion, tipo, capacidad, nombreUsuario);
    try
    {
        url = "c:" + nombreUsuario + "/reservaciones.txt";
        ofstream fichero(url, ios::out | ios::trunc);
        struct Nodo2 *temporal = listaReservas;
        // Imprimir cuando se inserta al final de la listaUsuario
        while (temporal != nullptr)
        {
            if (nombreUsuario == temporal->Data.empleado)
            {
                fichero << temporal->Data.mesa << endl;
                fichero << temporal->Data.ubicacion << endl;
                fichero << temporal->Data.tipo << endl;
                fichero << temporal->Data.capacidad << endl;
                fichero << temporal->Data.empleado << endl;
            }
            temporal = temporal->next;
        }
        fichero.close();
    }
    catch (const std::exception &e)
    {
        cout << "Ocurrio un error, llama a soporte tecnico" << endl;
    }
}
// Funcion menú para mostrar las opciones de gestion de reservaciones
void menuReservacion()
{
    listaReservas = nullptr;
    delete listaReservas;
    system("cls");
    envioParametros();
    string mesaBusqueda;
    int numMesa = 0;
    int opc = 0, selecion = 0;
    cout << "-------------------------------------------------------------------------------------"
         << "\n"
         << "-----------------------------------BIENVENIDO----------------------------------------"
         << "\n"
         << "Seleccione la opcion que desea realizar "
         << "\n"
         << "1. Desea agregar una reserva de mesa"
         << "\n"
         << "2. Desea eliminar una reservacion de mesa "
         << "\n"
         << "3. Desea buscar una reservacion de mesa"
         << "\n"
         << "4. Desea buscar una mesa libre"
         << "\n"
         << "5. Desea editar una reservacion de mesa"
         << "\n"
         << "6. Desea salir"
         << "\n"
         << "-------------------------------------------------------------------------------------"
         << "\n";
    cin >> opc;
    switch (opc)
    {
    case 1:
        agregarReserva();
        break;

    case 2:
        system("cls");
        imprimirReservas();
        cout << "Ingrese el indice de la reservacion a eliminar" << endl;
        cin >> selecion;
        if (!verificarNumero(selecion))
        {
            system("pause");
            break;
        }
        eliminarReserva(selecion);
        break;
    case 3:
        system("cls");
        cout << "Ingrese el numero de la mesa de la cual desea encontrar la reservacion" << endl;
        cin >> mesaBusqueda;
        imprimirReservasParametrizada(mesaBusqueda);
        system("pause");
        break;
    case 4:
        system("cls");
        imprimirMesasLibres();
        system("pause");
        break;
    case 5:
        system("cls");
        imprimirReservas();
        cout << "Ingrese el numero de mesa a la cual desea editar (es el numero que esta de ultimo Ejemplo: 'Mesa #34')" << endl;
        cin >> mesaBusqueda;
        istringstream(mesaBusqueda) >> numMesa;
        if (numMesa <= 0 || numMesa > 25)
        {
            cout << "Numero de mesa no registrado" << endl;
            system("pause");
            break;
        }
        cout << "Que dato desea editar: 1. Numero de mesa, 2. Ubicacion, 3. Tipo, 4. Capacidad" << endl;
        cin >> selecion;
        editarReserva(selecion, mesaBusqueda);
        system("pause");
        break;
    case 6:
        system("cls");
        return;
    default:
        cout << "La opcion no esta disponible "
             << "\n";
        break;
    }
    menuReservacion();
}

//--------------------------------------------------------------------------------------

// Funcion para validar caracteres especiales en el nombre de usuario
bool validarUsuario(const char *usuario)
{
    while (*usuario)
    {
        if (!isalnum(*usuario))
        {
            return false; // Caracter especial encontrado
        }
        ++usuario;
    }
    return true; // No se encontraron caracteres especiales
}

// Funcion para validar la longitud de la contrasena
bool validarContrasena(string contrasena)
{
    if (contrasena == "12345678" || contrasena == "87654321" || contrasena == "contrasena")
    {
        return false;
    }

    return strlen(contrasena.c_str()) >= 8;
}

// Funcion que lee el txt usuario y llena la lista usuarios
void llenadoListaUsuarios()
{
    ifstream inputFile("usuarios.txt");

    if (!inputFile)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    string info, user, pwd, level;
    int i = 1;
    while (getline(inputFile, info))
    {
        switch (i)
        {
        case 1:
            user = info;
            i++;
            break;
        case 2:
            pwd = info;
            i++;
            break;
        case 3:
            level = info;
            insertarFinal(user, pwd, level);
            i = 1;
            break;
        }
    }
    inputFile.close();
}

// Funcion que imprime todos los usuarios
void imprimir()
{
    int i = 1;
    struct Nodo *temporal = listaUsuario;
    if (temporal != nullptr)
    {
        // Imprimir cuando se inserta al final de la lista
        while (temporal != nullptr)
        {
            cout << i << ". " << temporal->Data.user << endl;
            if (temporal->Data.userLevel == "1")
            {
                cout << " -> Tipo Usuario: Admin" <<endl;
            }else{
                cout<<" -> Tipo Usuario: Empleado "<<endl;
            }
            
            
            temporal = temporal->next;
            i++;
        }
    }
    else
    {
        cout << "Lista vacia";
    }
}
// Insertar nodos al final de la listaUsuario
void insertarFinal(const string &user, const string &pwd, const string &level)
{
    struct Nodo *nuevoNodo = new Nodo;
    struct Nodo *temporal = listaUsuario;

    nuevoNodo->Data.user = user;
    nuevoNodo->Data.pwd = pwd;
    nuevoNodo->Data.userLevel = level;
    nuevoNodo->next = nullptr;
    nuevoNodo->prev = nullptr;

    // Si la listaUsuario esta vacia
    if (listaUsuario == nullptr)
    {
        listaUsuario = nuevoNodo;
    }
    else
    {
        while (temporal->next != nullptr)
        {
            temporal = temporal->next;
        }
        // conexiones de nuevonodo a temporal
        temporal->next = nuevoNodo;
        nuevoNodo->prev = temporal;
    }
}
// Funcion que permite gestionar que menú mostrar segun el tipo de usuario que accede
void seleccionMenu()
{
    int opc = 0;
    if (nivelUsuario == "1")
    {
        cout << "Que menu desea ingresar: 1. Gestion de Usuarios, 2. Gestion de reservaciones" << endl;
        cin >> opc;
        if (opc == 1)
        {
            menuUsuarios();
        }
        else
        {
            menuReservacion();
        }
    }
    else
    {
        menuReservacion();
    }
}
// Funcion Login, verifica las credenciales del usuario y brinda o no acceso a las demas funciones
void login(string userparam, string pwdparam)
{
    llenadoListaUsuarios();
    struct Nodo *temporal = listaUsuario;
    if (intentos > 3)
    {
        cout << "Demasiados intentos" << endl;
        exit(0);
    }

    if (temporal != nullptr)
    {
        // Imprimir cuando se inserta al final de la listaUsuario
        while (temporal != nullptr)
        {

            if (userparam == temporal->Data.user && pwdparam == temporal->Data.pwd)
            {
                intentos = 1;
                cout << "--------------------" << endl
                     << "Bienvenido" << endl
                     << "--------------------" << endl;
                nivelUsuario = temporal->Data.userLevel;
                nombreUsuario = temporal->Data.user;
                seleccionMenu();
                return;
            }
            temporal = temporal->next;
        }
        intentos++;
        cout << "No Bienvenido" << endl;
    }

    else
    {
        cout << "listaUsuario vacia";
    }
}
// Funcion que solicita la informacion del nuevo usuario
void agregarUsuario()
{
    string nuser, pwd, level;
    cout << " -> Recuerde que su contrasena y usuario no puede ser con los siguientes literales: " << endl
         << " -> La contrasena debe contener por lo menos 8 caracteres " << endl
         << " -> Evitar usar datos personales " << endl
         << " -> No signos especiales en el usuario" << endl
         << " -> Evita contrasenas como (12345678, 87654321, contrasena) " << endl;
    system("pause");
    cin.ignore();
    cout << "Ingrese el nombre del usuario" << endl;
    getline(cin, nuser);
    cout << "Ingrese la contrasenia del usuario" << endl;
    getline(cin, pwd);
    cout << "Ingrese el nivel del usuario" << endl;
    cin >> level;
    if (level != "1" && level != "2")
    {
        cout << "Tipo de usuarion invalido" << endl;
        system("pause");
        menuUsuarios();
    }
    verificacion(1, 0, "", nuser, pwd, level);
    insertarFinal(nuser, pwd, level);
    try
    {
        mkdir(nuser.c_str());
        string url = "c:" + nuser + "/reservaciones.txt";
        ofstream fichero2(url, ios::out);
        ofstream fichero("usuarios.txt", ios::out | ios::trunc);
        struct Nodo *temporal = listaUsuario;
        // Imprimir cuando se inserta al final de la listaUsuario
        while (temporal != nullptr)
        {
            fichero << temporal->Data.user << endl;
            fichero << temporal->Data.pwd << endl;
            fichero << temporal->Data.userLevel << endl;
            temporal = temporal->next;
        }
        fichero.close();
    }
    catch (const std::exception &e)
    {
        cout << "Ocurrio un error, llama a soporte tecnico" << endl;
    }
}
// Funcion que solicita la informacion a editar de un usuario
void editarUsuario(string userparam)
{
    int answer;
    string valorCambiado;
    cout << "Que dato desea cambiar 1.Nombre de usuario, 2. Contrasenia, 3. Tipo de Usuario" << endl;
    cin >> answer;
    cout << " -> Recuerde que su contrasena y usuario no puede ser con los siguientes literales: " << endl
         << " -> La contrasena debe contener por lo menos 8 caracteres " << endl
         << " -> Evitar usar datos personales " << endl
         << " -> No signos especiales en el usuario" << endl
         << " -> Evita contrasenas como (12345678, 87654321, contrasena) " << endl;
    system("pause");
    switch (answer)
    {
    case 1:
        cout << "Ingrese el nuevo nombre de usuario" << endl;
        cin >> valorCambiado;
        verificacion(2, 1, valorCambiado, "", "", "");
        break;
    case 2:
        cout << "Ingrese la nueva contrasenia de usuario" << endl;
        cin >> valorCambiado;
        verificacion(2, 2, valorCambiado, "", "", "");
        break;
    case 3:
        cout << "Ingrese el nuevo tipo de usuario 1. Gerente, 2. Empleado" << endl;
        cin >> valorCambiado;
        if (valorCambiado != "1" && valorCambiado != "2")
        {
            cout << "Tipo de usuarion invalido" << endl;
            system("pause");
            menuUsuarios();
        }
        break;
    default:
        cout << "Opcion incorrecta" << endl;
        break;
    }
    editarNodo(userparam, answer, valorCambiado);
}
// Funcion que edita la informacion de la lista de usuarios y guarda los cambios
void editarNodo(string userparam, int opc, string valorCambioParam)
{
    struct Nodo *aux = listaUsuario;
    while (aux != nullptr && aux->Data.user != userparam)
    {
        aux = aux->next;
    }
    if (aux != nullptr)
    {
        switch (opc)
        {
        case 1:
            aux->Data.user = valorCambioParam;
            userparam = "c:" + userparam;
            rename(userparam.c_str(), valorCambioParam.c_str());
            break;
        case 2:
            aux->Data.pwd = valorCambioParam;
            break;
        case 3:
            aux->Data.userLevel = valorCambioParam;
            break;
        }
    }
    else
    {
        cout << "No se encontro";
    }
    ofstream fichero("usuarios.txt", ios::out | ios::ate);
    struct Nodo *temporal = listaUsuario;
    // Imprimir cuando se inserta al final de la listaUsuario
    while (temporal != nullptr)
    {
        fichero << temporal->Data.user << endl;
        fichero << temporal->Data.pwd << endl;
        fichero << temporal->Data.userLevel << endl;
        temporal = temporal->next;
    }
    fichero.close();
}
// Funcion que solicita que usuarios se eliminara del sistema
void eliminarUsuario()
{
    string nameuser;
    int pos = 0;
    imprimir();
    cout << "Ingrese el indice del usuario que desea eliminar" << endl;
    cin >> pos;
    if (!verificarNumero(pos))
    {
        system("pause");
        return;
    }
    struct Nodo *aux = listaUsuario;

    // Verificar si la lista esta vacia
    if (aux == nullptr)
    {
        cout << "La lista esta vacia." << endl;
        return;
    }

    // Si pos es 1, eliminar el primer nodo
    if (pos == 1)
    {
        nameuser = listaUsuario->Data.user;
        listaUsuario = aux->next;
        delete aux;
        aux = nullptr;
        listaUsuario->prev = nullptr;
        cout << "Usuario eliminado exitosamente." << endl;
    }

    int i = 1;
    while (aux != nullptr && i < pos)
    {
        aux = aux->next;
        i++;
    }

    if (aux != nullptr)
    {
        if (aux->next != nullptr)
        {
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
        }
        else
        {
            // Si pos es el último nodo
            aux->prev->next = nullptr;
        }
        nameuser = aux->Data.user;
        delete aux;
    }
    else
    {
        cout << "No se encontro el usuario en la posicion especificada." << endl;
        system("pause");
        return;
    }
    ofstream fichero("usuarios.txt", ios::out | ios::ate);
    aux = listaUsuario;
    while (aux != nullptr)
    {
        fichero << aux->Data.user << endl;
        fichero << aux->Data.pwd << endl;
        fichero << aux->Data.userLevel << endl;
        aux = aux->next;
    }
    fichero.close();
    nameuser = "c:" + nameuser + "/reservaciones.txt";
    try
    {
        remove(nameuser.c_str());
        cout << "Usuario eliminado exitosamente." << endl;
        system("pause");
    }
    catch (const std::exception &e)
    {
        cout << "No se pudo eliminar" << '\n';
    }
}
// Funcion que muestra todas las acciones disponibles de la gestion de Usuarios
void menuUsuarios()
{
    system("cls");
    listaUsuario = nullptr;
    llenadoListaUsuarios();
    int opc = 0;
    string nameUser;
    cout << "-------------------------------------------------------------------------------------"
         << "\n";
    cout << "-----------------------------------BIENVENIDO----------------------------------------"
         << "\n";
    cout << "Seleccione la opcion que desea realizar:"
         << "\n";
    cout << "1. crear usuario"
         << "\n";
    cout << "2. Editar usuario"
         << "\n";
    cout << "3. Borrar usuario"
         << "\n";
    cout << "4. Imprimir lista de usuarios"
         << "\n";
    cout << "5. Salir"
         << "\n";
    cout << "-------------------------------------------------------------------------------------"
         << "\n";
    cin >> opc;
    switch (opc)
    {
    case 1:
        agregarUsuario();
        break;
    case 2:
        imprimir();
        cout << "Ingrese el nombre del usuario a editar" << endl;
        cin >> nameUser;
        editarUsuario(nameUser);
        break;
    case 3:
        eliminarUsuario();
        break;
    case 4:
        imprimir();
        system("pause");
        break;
    case 5:
        system("cls");
        return;
    default:
        cout << "Opcion no valida" << endl;
        break;
    }
    menuUsuarios();
}
// Funcion que verifica la informacion de un usuarios sea correcta para el sistema
void verificacion(int accion, int opcEditar, string valorParam, string nombreU, string pass, string tipo)
{
    struct Nodo *temporal = listaUsuario;
    if (accion == 1)
    {
        if (!validarContrasena(pass) || !validarUsuario(nombreU.c_str()))
        {
            cout << "Informacion del usuario invalida" << endl;
            system("pause");
            menuUsuarios();
        }
        if (temporal != nullptr)
        {
            // Imprimir cuando se inserta al final de la listaUsuario
            while (temporal != nullptr)
            {

                if (nombreU == temporal->Data.user)
                {
                    cout << "Nombre de usuario ya existente" << endl;
                    system("pause");
                    menuUsuarios();
                }
                temporal = temporal->next;
            }
        }
    }
    else if (accion == 2)
    {
        if (opcEditar == 1)
        {
            if (!validarUsuario(valorParam.c_str()))
            {
                cout << "Informacion del usuario invalida" << endl;
                system("pause");
                menuUsuarios();
            }
            if (temporal != nullptr)
            {
                // Imprimir cuando se inserta al final de la listaUsuario
                while (temporal != nullptr)
                {

                    if (valorParam == temporal->Data.user)
                    {
                        cout << "Nombre de usuario ya existente" << endl;
                        system("pause");
                        menuUsuarios();
                    }
                    temporal = temporal->next;
                }
            }
        }
        else if (opcEditar == 2)
        {
            if (!validarContrasena(valorParam))
            {
                cout << "Informacion del usuario invalida" << endl;
                system("pause");
                menuUsuarios();
            }
        }
    }
}