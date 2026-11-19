#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void mostrarMenu();
void mostrarEntradas();
void mostrarBebidas();
void mostrarPostres();

float precioPlatillo = 0;
float precioEntradas = 0;
float precioBebida = 0;
float precioPostre = 0;
float total = 0;

string platillo = "";
string entradas = "";
string bebida = "";
string postre = "";

int opcion=0;
int mesa=0;


void mostrarMenu() {
    cout << "===========================" << endl;
    cout << "MENU PARA ORDENAR" << endl;
    cout << "===========================" << endl;
    cout << "1. Hamburguesa precio: $3.50" << endl;
    cout << "2. Pizza precio: $5.00" << endl;
    cout << "3. Hot Dog precio: $2.50" << endl;
    cout << "4. Pupusas precio: $1.00" << endl;
    cout << "5. Panini de pollo precio: $4.50" << endl;
}
void mostrarEntradas() {
    cout << "===========================" << endl;
    cout << "   ENTRADAS   " << endl;
    cout << "===========================" << endl;
    cout << "1. Papas fritas precio: $1.50" << endl;
    cout << "2. Ensalada precio: $2.00" << endl;
    cout << "3. Pan con Ajo precio: $1.00" << endl;
}
void mostrarBebidas() {
    cout << "===========================" << endl;
    cout << "Bebidas" << endl;
    cout << "===========================" << endl;
    cout << "1. Agua precio: $1.00" << endl;
    cout << "2. Refresco precio: $2.00" << endl;
    cout << "3. Jugo precio: $2.50" << endl;
    cout << "4. Coca-Cola precio: $1.00" << endl;
    cout << "5. Té frio precio: $1.00" << endl;
    cout << "6. Café precio: $1.50" << endl;
    cout << "7. Frozen precio: $2.50" << endl;
    cout << "8. Licuado precio: $2.00" << endl;
}
void mostrarPostres() {
    cout << "===========================" << endl;
    cout << "Postres" << endl;
    cout << "===========================" << endl;
    cout << "1. Pastel precio: $3.00" << endl;
    cout << "2. Helado precio: $2.00" << endl;
    cout << "3. Brownie precio: $1.50" << endl;
    cout << "4. Galletas precio: $1.00" << endl;
}
int main(){
    cout<< "Ingrese el numero de mesa: ";
    cin>>mesa;
    cout<< "me regalas tu nombre: ";
    cin>>nombre;
    cout<< "Bienvenido " << nombre << " a nuestro restaurante" << endl;
    mostrarMenu();
    

}