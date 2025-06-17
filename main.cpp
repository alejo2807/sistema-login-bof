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
	//Usuario* nuevoUsuarioPrueba = new Usuario(nombreComp, nombreUser, emailUser, numeroUser, password);

	//NOTAS;
	/*
	-FALTAN UN PAR DE FUNCIONES PUBLCIAS COMO CAMBIAR CONTRASENA, CERRAR SESION
		Y RESTABLECLER CONTRASENA
	-CORREGIR TAMBIEN, PARA QUE NO SE ME BORREN LAS LINEAS DE LOS ESPACIOS 
		O LOS COMENTARIOS EN LA BASE DE DATOS 
	-VERIFICAR QUE NO SE PUEDAN AGREGAR 2 USUARIOS CON EL MISMO NOMBRE 
		A LA BASE DE DATOS
	-CREAR NUEVA RAMA PARA EL PROPOSITO DE ARRIBA (QUE NO SE PUEDAN AGREGAR 2 USERS
		CON MISMO NOMBR A LA BASE DE DATOS)
	
	//en la funcion registrarUsuario(...) nos encargamos de hashear la contrasena
	if(sistema.registrarUsuario("users.txt", nombreUser, password,  nuevoUsuarioPrueba))
	{
		sistema.parseFile("users.txt");
		sistema.mostrarInformacionUsuarios();
		if(sistema.iniciarSesion(nombreUser, password))
		{
			cout<<"Inicio Correcto"<<endl;
		}
	
		else cerr<<"Hubo una falla"<<endl;	
	
	};
	*/
	

	sistema.parseFile("users.txt");
	
	if(sistema.iniciarSesion(nombreUser, password))
	{
		cout<<"Inicio Correcto"<<endl;
	}
	
	else cerr<<"Hubo una falla"<<endl;	
	
	
	sistema.eliminarInformacionDelMap();
	
	return 0;
	
}
