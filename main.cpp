#include <fstream>
#include <iostream>
#include <string>
#include <sstream> //to use stringstream
#include <vector>
#include <map> //para usar map
#include "Usuario.h" // Asegúrate de incluir el archivo Usuario.h

//para el algoritmo de criptografia bcrypt (hashear contrasena)
#include "libbcrypt/include/BCrypt.hpp"  // Now points to the correct path!

using namespace std;


int main()
{
	//ejemplo de hash con bcrypt
	std::string password = "password123";
	std::string hash = BCrypt::generateHash(password, 12);
	std::cout << "Hashed: " << hash << std::endl;

	bool isValid = BCrypt::validatePassword(password, hash);
	std::cout << "Valid? " << (isValid ? "YES" : "NO") << std::endl;
	return 0;
	
}

