#include <iostream>
#include "lib/funciones.h"

using namespace std;

int main()
{
    int opc = 1;
    string user, pwd;
    do
    {
        cout << "Ingrese un 1 para acceder al sistema o un 0 para salir" << endl;
        cin >> opc;
        if (opc != 0)
        {
            cout << "Ingrese el nombre del usuario" << endl;
            cin >> user;
            cout << "Ingrese la contrasenia del usuario" << endl;
            cin >> pwd;
            login(user, pwd);
        }
    } while (opc != 0);
    return 0;
}