#include "Usuario.h"
#include <iostream>
#include <string>
using namespace std;


Usuario::Usuario(string nombreCompleto, string nombreUsuario, string email, string NumeroTelefono, string hashContrasena) 
	:	nombreCompleto(nombreCompleto), 
		nombreUsuario(nombreUsuario),
		emailUsuario(email),
		numeroTelefono(NumeroTelefono),
		hashContrasena(hashContrasena){}

Usuario::Usuario(){}

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
	return emailUsuario;
}

string Usuario::getNumeroTelefono() const
{
	return numeroTelefono;
}

string Usuario::getHashContrasena() const
{
	return hashContrasena;
}

void Usuario::setNombreCompleto(const string& nombre)
{
	nombreCompleto = nombre;
}

void Usuario::setNombreUsuario(const string& usuario)
{
	nombreUsuario = usuario;
}

void Usuario::setEmail(const string& email)
{
	emailUsuario = email;
}

void Usuario::setNumeroTelefono(const string& telefono)
{
	numeroTelefono = telefono;
}

void Usuario::setHashContrasena(const string& hash)
{
	hashContrasena = hash;
}

