#include "stdio.h"
#include <string>
#include <iostream>
#include "IIniciarSesion.h"

using namespace std;

int main(){
   string cedula;
   string pass;
   printf("\t\tBIENVENIDO\n\n");
   printf("Iniciar sesion\n");
   printf("Ingrese su cedula: ");
   cin >> cedula;
   cout << "\nIngrese su contrasena: ";
   cin >> pass;
   
   return 0;
}