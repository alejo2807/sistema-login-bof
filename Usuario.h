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
		string emailUsuario;
		string numeroTelefono;
		string hashContrasena;
	
	public:
		Usuario(); // Constructor por defecto
		Usuario(string nombreCompleto, string nombreUsuario, string email, 
				string numeroTelefono, string hashContrasena);

		// Getters
		string getNombreCompleto() const;
		string getNombreUsuario() const;
		string getEmail() const;
		string getNumeroTelefono() const;
		string getHashContrasena() const;
		
		// Setters
		void setNombreCompleto(const string& nombre); 
		void setNombreUsuario(const string& usuario);
		void setEmail(const string& email); 
		void setNumeroTelefono(const string& telefono); 
		void setHashContrasena(const string& hash);

};


#endif // USUARIO_H