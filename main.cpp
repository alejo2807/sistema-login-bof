#include <fstream>
#include <iostream>
#include <string>
#include <sstream> //to use stringstream
#include <vector>
#include <map> //para usar map
#include "Usuario.h" // Asegúrate de incluir el archivo Usuario.h
#include "SistemaLogin.h"

//para el algoritmo de criptografia bcrypt (hashear contrasena)
#include "libbcrypt/include/BCrypt.hpp"  // Now points to the correct path!

using namespace std;


int main()
{
	string nombreComp;
	string nombreUser;
	string emailUser;
	string numeroUser;
	string password;
	
	cout<< "------------Bienvenido a Vibe City :)------------ "<<endl;
	cout<< "---------------Menu de registro---------------"<<endl;
	cout<< "Nombre Completo: " <<endl;
	getline(cin, nombreComp);
	cout<< "Nombre de Usuario: " <<endl;
	getline(cin, nombreUser);
	cout<< "Email: " <<endl;
	getline(cin, emailUser);
	cout<< "Numero Telefonico: " <<endl;
	getline(cin, numeroUser);
	cout<< "Contrasena: " <<endl;
	getline(cin, password);
	
	Usuario* nuevoUsuarioPrueba = new Usuario(nombreComp, nombreUser, emailUser, numeroUser, password);
	SistemaLogin sistema;
	
	if(sistema.registrarUsuario("users.txt", nombreUser, nuevoUsuarioPrueba))
	{
		sistema.parseFile("users.txt");
		sistema.mostrarInformacionUsuarios();

	};
	sistema.eliminarInformacionDelMap();
	
	//g++ main.cpp Usuario.cpp SistemaLogin.cpp -o ap
	return 0;
	
}




/*
	//ejemplo de hash con bcrypt
	std::string password = "password123";
	std::string hash = BCrypt::generateHash(password, 12);
	std::cout << "Hashed: " << hash << std::endl;

	bool isValid = BCrypt::validatePassword(password, hash);
	std::cout << "Valid? " << (isValid ? "YES" : "NO") << std::endl;
*/