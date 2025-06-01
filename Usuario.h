#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
using namespace std;

class Usuario {

	// se agrego el email y el numero de telefono como atributos privados
	private:
		string nombreCompleto;
		string nombreUsuario;
		string email;
		string numeroTelefono;
		string hashContrasena;
	
	public:
		Usuario(string nombreCompleto, string nombreUsuario, string email, 
				string numeroTelefono, string hashContrasena);
		bool verificarContrasena(string contrasena) const;

		// Getters
		string getNombreCompleto() const;
		string getNombreUsuario() const;
		string getEmail() const;
		string getNumeroTelefono() const;

};


#endif // USUARIO_H