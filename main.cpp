#include "stdio.h"
#include <string>
#include <iostream>
#include <map>
#include "fabrica/fabrica.h"
#include "../headers/socio.h"
#include "../headers/medico.h"
#include "../headers/administrativo.h"

using namespace std;

bool isNumber(const string& str) {
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool correcto(string ci) {
    if (!isNumber(ci) || ci.length() != 8)
        return false;
    return true;
}

int main() {
   Fabrica* f;
   IIniciarSesion* iSesion;
   IAltaDiagnostico* iAD;
   IAltaUsuario* iAU;
   ICerrarSesion* ICS;
   IDevolucionReserva* iDR;
   IListarRepresentaciones* iLR;
   IObtenerHistorial* iOH;
   IRegisConsulta* iRG;
   IUsuario* IU;
   Fecha fecha = Fecha(2001, 10, 22);

   DtUsuario usuarioSesion = DtUsuario();
   map<string, Usuario*> usersCollection;
   Socio* catS = new Socio();
   Medico* catM = new Medico();
   Administrativo* catA = new Administrativo();
   Usuario* pruebaU = new Usuario("contrasena", "Nicolas", "Marquez", "51467384", "masculino", fecha, true, catS);
   Usuario* pruebaM = new Usuario("medico", "medico", "medicoAp", "12345678", "femenino", fecha, true, catM);
   Usuario* pruebaA = new Usuario("admin", "admin", "adminAp", "87654321", "masculino", fecha, true, catA);
   usersCollection.insert({pruebaU->getCedula(), pruebaU});
   usersCollection.insert({pruebaM->getCedula(), pruebaM});
   usersCollection.insert({pruebaA->getCedula(), pruebaA});

   f = Fabrica::getInstancia();
   iSesion = f->getIIniciarSesion();
   iAD = f->getIAltaDiagnostico();
   iAU = f->getIAltaUsuario();
   ICS = f->getICerrarSesion();
   iDR = f->getIDevolucionReserva();
   iLR = f->getIListarRepresentaciones();
   iOH = f->getIObtenerHistorial();
   iRG = f->getIRegisConsulta();
   IU = f->getIUsuario();

   string cedula = "-1";
   string pass;
   bool salir = false;
   bool cedulaValida = false;
   bool passCorrecto = false;
   int opcion = -1;
   cout << "\t\tBIENVENIDO\n\n";
   while (!salir){
      cout << "Que desea hacer?\n";
      cout << "0- Cargar datos\n";
      cout << "1- Iniciar sesion\n";
      cout << "2- Salir\n";
      cin >> opcion;
      switch (opcion){
      case  0:
         IU->cargarDatos(usersCollection);
         break;
      
      case 1:
         cout << "Ingrese su cedula: ";
         while (!cedulaValida) {
            cin >> cedula;
            cedulaValida = correcto(cedula);
            if (!cedulaValida) {
               cout << "cedula invalida\n";
            }
         }
         usuarioSesion = IU->ingresarCedula(cedula);

         if (usuarioSesion.getContrasena() == " ") {
            cout << "Ingrese su contrsena" << endl;
            while (!passCorrecto && pass != "-1") {
               cin >> pass;
               passCorrecto = IU->registrarContrasena(pass);
               if (!passCorrecto && pass != "-1")
                     cout << "Contrasena invalida" << endl;
            }
         } else {
            cout << "Ingrese su contrsena (ingrese -1 si desea cancelar)" << endl;
            while (!passCorrecto && pass != "-1") {
               cin >> pass;
               passCorrecto = IU->ingresarContrasena(pass);
               if (!passCorrecto && pass != "-1")
                     cout << "Contrasena incorrecta" << endl;
            }
         }
         break;
      
      case 2:
         salir = true;
         break;

      default:
         cout << "\nOpcion invalida\n\n";
         break;
      }

      if (usuarioSesion.getCedula() != "11111111") {
         bool salirSesion = false;
         int option = 0;
         while (!salirSesion) {
            cout << "\nBienvenido " << usuarioSesion.getNombre() << endl;
            if (dynamic_cast<Socio*>(usuarioSesion.getCategoria())) {
               cout << "Que desea hacer socio?" << endl;
               cout << "1 - Realizar reserva" << endl;
               cout << "2 - Cancelar reserva" << endl;
               cout << "3 - Salir" << endl;
               cin >> option;
               switch (option) {
                  case 1:
                     cout << "Realizar reserva" << endl;
                     break;
                  case 2:
                     cout << "Cancelar reserva" << endl;
                     break;
                  case 3:
                     cedula = "-1";
                     usuarioSesion = DtUsuario();
                     cedulaValida = false;
                     passCorrecto = false;
                     salirSesion = true;
                     break;
                  default:
                     break;
               }
            } else if (dynamic_cast<Medico*>(usuarioSesion.getCategoria())) {
               cout << "Que desea hacer medico?" << endl;
               cout << "1 - " << endl;
               cout << "2 - " << endl;
               cout << "3 - " << endl;
               cout << "4 - " << endl;
               cout << "5 - Salir medico" << endl;
               cin >> option;
               switch (option) {
                  case 1:
                     cout << "Realizar reserva" << endl;
                     break;
                  case 2:
                     cout << "Cancelar reserva" << endl;
                     break;
                  case 5:
                     cedula = "-1";
                     usuarioSesion = DtUsuario();
                     cedulaValida = false;
                     passCorrecto = false;
                     salirSesion = true;
                     break;
                  default:
                     break;
               }
            } else if (dynamic_cast<Administrativo*>(usuarioSesion.getCategoria())) {
               string input;
               cout << "Que desea hacer admin?" << endl;
               cout << "1 - Alta/Reactivacion de usuario" << endl;
               cout << "2 - " << endl;
               cout << "3 - " << endl;
               cout << "4 - " << endl;
               cout << "5 - Salir admin" << endl;
               cin >> option;

               string nombre, apellido, sexo, categoria;
               int anio, mes, dia;
               DtUsuario user = DtUsuario();
               switch (option) {
                  case 1:
                     while (input != "-1") {
                           cout << "Ingrese una cedula (ingrese -1 si desea salir): ";
                           cin >> input;
                           if (input == "-1"){
                              break;
                           }                           
                           user = IU->ingresarCedulaAlta(input);
                           if (user.getCedula() == "11111111") {
                              cout << "ingrese el nombre del usuario: ";
                              cin >> nombre;
                              cout << "\ningrese el apellido del usuario: ";
                              cin >> apellido;
                              cout << "\ningrese el sexo del usuario: ";
                              cin >> sexo;
                              cout << "\ningrese el anio, mes y dia de nacimiento del usuario: ";
                              cin >> anio >> mes >> dia;
                              cout << "\ningrese la categoria del usuario: ";
                              cin >> categoria;

                              Fecha fecha(anio, mes, dia);
                              if (categoria == "socio")
                                 IU->ingresarDatos(nombre, apellido, sexo, fecha, catS);
                              else if (categoria == "medico")
                                 IU->ingresarDatos(nombre, apellido, sexo, fecha, catM);
                              else
                                 IU->ingresarDatos(nombre, apellido, sexo, fecha, catA);
                           } else {
                              cout << "\n Nombre: " << user.getNombre();
                              cout << "\n Apellido:" << user.getApellido();
                              cout << "\n Sexo: " << user.getSexo();
                              cout << "\n Edad: " << user.getEdad();
                              cout << "\n Activo: " << user.getActivo();
                              if(dynamic_cast<Administrativo*>(user.getCategoria())){
                                 cout << "\n Categoria: Administrativo";
                              } else if(dynamic_cast<Socio*>(user.getCategoria())){
                                 cout << "\n Categoria: Socio";
                              } else if(dynamic_cast<Medico*>(user.getCategoria())){
                                 cout << "\n Categoria: Medico";
                              }

                              if(user.getActivo() == false){
                                 cout << "desea reactivar el usuario?" << endl;
                                 cout << "1- SI\t\t2- NO";
                                 cin >> option;

                                 if(option == 1){
                                    IU->activarUsuario(user.getCedula());
                                    cout << "Usuario reactivado";
                                 }
                              }
                           }
                     }
                     IU->salir();
                     break;
                  case 2:
                     cout << "Cancelar reserva" << endl;
                     break;
                  case 5:
                     cedula = "-1";
                     usuarioSesion = DtUsuario();
                     cedulaValida = false;
                     passCorrecto = false;
                     salirSesion = true;
                     break;
                  default:
                     break;
               }
            }
         }
      }
   }
   cout << "\n\nsalgo\n\n";

   iAD->agregarDescripcion("descripcion");
   iAU->salir();
   ICS->cerrarSesion();
   return 0;
}