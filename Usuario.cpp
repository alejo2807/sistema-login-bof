#include "Usuario.h"
#include <iostream>
#include <string>
using namespace std;

//correcion del constructor de Usuario. 
// Antes, el constructor no inicializaba hashContrasena correctamente,
//(Lo tenia como hashContrasena = "";) lo cual no es correcto.
Usuario::Usuario(string nombreCompleto, string nombreUsuario, string email, string NumeroTelefono, string hashContrasena) 
	:	nombreCompleto(nombreCompleto), 
		nombreUsuario(nombreUsuario),
		email(email),
		numeroTelefono(NumeroTelefono),
		hashContrasena(hashContrasena){}


bool Usuario::verificarContrasena(string contrasena) const
{

	// Aquí deberías implementar la lógica para verificar la contraseña
	// Por ejemplo, comparar el hash de la contraseña ingresada con el hash almacenado
	// En este caso, simplemente retornamos true para simular una verificación exitosa
	return true; // Simulación de verificación exitosa
}




string Usuario::getNombreCompleto() const
{
	return nombreCompleto;
}

string Usuario::getNombreUsuario() const
{
	return nombreUsuario;
}

string Usuario::getEmail() const
{
	return email;
}

string Usuario::getNumeroTelefono() const
{
	return numeroTelefono;
}
