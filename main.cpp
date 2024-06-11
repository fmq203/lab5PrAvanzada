#include "stdio.h"
#include <string>
#include <iostream>
#include <map>
#include "fabrica/fabrica.h"

using namespace std;

bool isNumber(const string& str) {
  for (char const& c : str) {
    if (std::isdigit(c) == 0) return false;
  }
  return true;
}

bool correcto(string ci){
   if(!isNumber(ci) || ci.length() < 8 || ci.length() > 8)
      return false;
   return true;
}

int main(){
   bool valido = false;
   Fabrica* f;
   IIniciarSesion* iSesion;
   IAltaDiagnostico* iAD;
   IAltaUsuario* iAU;
   ICerrarSesion* ICS;
   IDevolucionReserva* iDR;
   IListarRepresentaciones* iLR;
   IObtenerHistorial* iOH;
   IRegisConsulta* iRG;

   Usuario* usuarioSesion = new Usuario();
   map<string, Usuario*> usersCollection;
   Fecha fecha = Fecha(2001, 10, 22);
   Usuario* pruebaU = new Usuario("contrasena", "Nicolas", "Marquez", "51467384", "masculino", fecha, true);
   usersCollection.insert({pruebaU->getCedula(), pruebaU});

   f = Fabrica::getInstancia();
   iSesion = f->getIIniciarSesion();
   iAD = f->getIAltaDiagnostico();
   iAU = f->getIAltaUsuario();
   ICS = f->getICerrarSesion();
   iDR = f->getIDevolucionReserva();
   iLR = f->getIListarRepresentaciones();
   iOH = f->getIObtenerHistorial();
   iRG = f->getIRegisConsulta();
   string cedula;
   string pass;
   printf("\t\tBIENVENIDO\n\n");
   printf("Iniciar sesion\n");
   printf("Ingrese su cedula: ");
   while (!valido){
      cin >> cedula;
      valido = correcto(cedula);
      if(!valido){
         cout << "cedula invalida\n";
      }
   }

   auto it = usersCollection.find(cedula);
      if (it != usersCollection.end()) {
         Usuario* u = it->second;
         cout << "\nIngrese su contrasena: ";
         cin >> pass;
         if(u->getActivo() == false && u->getContrasena() == " "){
            u->setContrasena(pass);
            u->setActivo(true);
         } else if(u->getActivo() == true){
            if(u->esContrasena(pass)){
               usuarioSesion = u;
            }
         }
      } else {
         cout << "Usuario no encontrado" << endl;
      }
   
   if(usuarioSesion->getCedula() != "11111111"){
      bool salir = false;
      int option = 0;
      while (!salir){
         cout << "\nBienvenido " << usuarioSesion->getNombre() << endl;
         cout << "¿Que desea hacer?" << endl;
         cout << "1 - " << endl;
         cout << "2 - " << endl;
         cout << "3 - " << endl;
         cout << "4 - " << endl;
         cout << "5 - Salir" << endl;
         cin >> option;
         switch(option){
         case 5:
            salir = true;
            break;
         
         default:
            break;
         }
      }
   }
   
   iAD->agregarDescripcion("descripcion");
   iAU->salir();
   ICS->cerrarSesion();
   return 0;
}