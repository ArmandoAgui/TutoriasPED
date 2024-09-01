#include <iostream>

using namespace std;

struct Personaje
{
    string nombre;
    int nivel;
    int vida;

};

void mostrarDatos(Personaje *p);
void subirNivel(struct Personaje &p);
void Danio(Personaje *personaje);

int main(){
    Personaje personaje [2];
    personaje [0].nombre = "Juan";
    personaje [0].nivel = 1;
    personaje [0].vida = 100;
    personaje [1].nombre = "Carlos";
    personaje [1].nivel = 1;
    personaje [1].vida = 100;

    
    mostrarDatos(personaje);
    return 0;
}



void subirNivel(struct Personaje &p){
    p.nivel++;
}


void Danio(Personaje *personaje){

personaje[0].vida = 90;
personaje[1].vida = 50;

}

void mostrarDatos(Personaje *p){
    cout << "Bienvenido, tu vida y nivel son : "<<endl; 
    for (int i = 0; i < 2; i++)
    {
        cout<<p[i].nombre<<endl;
        cout<<p[i].nivel<<endl;
        cout<<p[i].vida<<endl;
        cout<<"--------------"<<endl;
    }
    cout << "A juan le cayo una roca en la mano, ha presentado un danio." << endl;
    cout << "A calor le mordio un tigre, ha presentado un danio." << endl;
    Danio(p) ;
    cout<<"La vida de Juan es : " << p[0].vida<<endl;
    cout<<"La vida de Carlos es : " << p[1].vida<<endl;
    subirNivel(p[0]);
    cout<<"Juan tomo una posion, su nivel actual es: " << p[0].nivel << endl;
    subirNivel(p[1]);
    cout<<"Carlos mato un ogros, su nivel " << p[1].nivel << endl;
}