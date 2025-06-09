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
	
	//COMPILO CON ESTE COMANDO:
	//g++ main.cpp Usuario.cpp SistemaLogin.cpp libbcrypt/src/*.c -Ilibbcrypt/include -o ap

	
	
	SistemaLogin sistema;
	
	//se le pasan los parametros al usuario creado en la heap
	Usuario* nuevoUsuarioPrueba = new Usuario(nombreComp, nombreUser, emailUser, numeroUser, password);

	//en la funcion registrarUsuario() nos encargamos de hashear la contrasena
	if(sistema.registrarUsuario("users.txt", nombreUser, password,  nuevoUsuarioPrueba))
	{
		sistema.parseFile("users.txt");
		sistema.mostrarInformacionUsuarios();

	};
	sistema.eliminarInformacionDelMap();
	
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