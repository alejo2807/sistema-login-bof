#include <string>
#include "Usuario.h" 
#include "SistemaLogin.h"

using namespace std;


int main()
{
	
	
	string nombreComp;
	string nombreUser;
	string emailUser;
	string numeroUser;
	string password;
	
	cout<< "------------Bienvenido a Vibe City :)------------ "<<endl;
	cout<< "---------------Menu---------------"<<endl;
	//cout<< "Nombre Completo: " <<endl;
	//getline(cin, nombreComp);
	cout<< "Nombre de Usuario: " <<endl;
	getline(cin, nombreUser);
	//cout<< "Email: " <<endl;
	//getline(cin, emailUser);
	//cout<< "Numero Telefonico: " <<endl;
	//getline(cin, numeroUser);
	cout<< "Contrasena: " <<endl;
	getline(cin, password);
	
	//COMPILO CON ESTE COMANDO:
	//g++ main.cpp Usuario.cpp SistemaLogin.cpp libbcrypt/src/*.c -Ilibbcrypt/include -o a

	
	
	SistemaLogin sistema;
	
	//se le pasan los parametros al usuario creado en la heap
	Usuario* nuevoUsuarioPrueba = new Usuario(nombreComp, nombreUser, emailUser, numeroUser, password);

	//NOTAS;
	/*
	-AGREGAR IMPLEMENTACION DE API PARA VALIDACION DE NUMEROTELEFONICO Y CORREO
	(REVISAR EL CURSO DE APIS DE FREECODEORG EN INGLES)

	-VERIFICAR QUE RESTABLECER CONTRASENA 
	FUNCIONEN CORRECTAMENTE (LA TERMINO MANANA PORQUE HOY LA EMPECE)
	
	//en la funcion registrarUsuario(...) nos encargamos de hashear la contrasena
	if(sistema.registrarUsuarioAlArchivo("users.csv", nombreUser, password,  nuevoUsuarioPrueba))
	{
		sistema.parseFile("users.csv");
		sistema.mostrarInformacionUsuarios();
		if(sistema.iniciarSesion(nombreUser, password))
		{
			cout<<"Inicio Correcto"<<endl;
		}
	
		else cerr<<"Hubo una falla"<<endl;	
	
	};
	*/
	
	sistema.parseFile("users.csv");

	if(sistema.iniciarSesion(nombreUser, password))
	{
		cout<<"Inicio Correcto"<<endl;
		//1.probaremos cerrar sesion  (si funciona, goat)
		//2. probaremos cambiar contrasena (si funciona, goat)
		//3. probaremos restablecer contrasena
		int opc = 0;
		string nuevaContrasena;
		while(opc != 2)
		{
			cout << "Selecciona una opcion: " << endl;
			cout << "1. Cambiar contrasena" << endl;
			cout << "2. Salir" << endl;
			cin >> opc;
			cin.ignore(); // Clear newline left in input buffer

			switch(opc)
			{
				case 1:
					cout<<"Ahora cambiaremos la contrasena"<<endl;
					cout<<"Ingresa la nueva contrasena: "<<endl;
					getline(cin, nuevaContrasena);
		
					if(sistema.cambiarContrasena(password, nuevaContrasena))
					{
						cout<<"OK. Puedes ingresar con la nueva contrasena"<<endl;
					}
					else cerr<<"Hubo una falla al cambiar la contrasena"<<endl;
					break;
				case 2:
					cout << "Saliendo del sistema..." << endl;
					opc = 2; // Exit the loop
					sistema.cerrarSesion();
					break;
				default:
					cout<<"Seleccionaste una opcion no valida. Intenta de nuevo." << endl;
					break;
			}
		}
		
		
		//sistema.cerrarSesion();
		//sistema.restablecerContrasena();
		

		
	}
	
	else cerr<<"Hubo una falla"<<endl;

	cout<<"Olvidaste tu contrasena? No hay problema, puedes restablecerla."<<endl;
	sistema.restablecerContrasena();

	sistema.eliminarInformacionDelMap();
	
	return 0;
	
}
