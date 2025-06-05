#ifndef SISTEMALOGIN_H
#define SISTEMALOGIN_H
#include "Usuario.h" // Asegúrate de incluir el archivo Usuario.h
#include <string>
#include <iostream>
#include <map> //para el uso de maps
using namespace std;




class SistemaLogin {

	private:

		// Atributos (usaremos un map para almacenar usuarios y hashes de contraseñas)
		//Ademas, la idea es practicar con los maps, porque nunca los he usado.
		map<string, Usuario*> usuarios; // usamos un puntero a Usuario para  no tener que copiar todo el objeto Usuario
		Usuario* usuarioActivo; // Puntero al usuario actualmente conectado

		//funciones privadas. No nos interesa que sean accesibles desde fuera de la clase.
		bool verificarArchivo(); //verifica si el archivo de usuarios existe. TRUE si existe, FALSE si no existe.
		bool crearArchivo(); //crea el archivo de usuarios si no existe

		
		bool parseLine(const string& LineaDondeEstoy, Usuario& user); //parses a line from the file to create a Usuario object
		bool guardarAlMapa(Usuario* nuevoUsuario); //saves the user to the map
		
		
		//falta hash contrasena y funciones publicas
		string hashContrasena(string pass); //retornara la contraseña hasheada

	public:
		SistemaLogin();
		~SistemaLogin();
		
		//funciones  sobre el archivo y el mapa
		bool parseFile(const string& filename); // parses the file to load users into the map
		void mostrarInformacionUsuarios() const; //4. shows the user information
		void eliminarInformacionDelMap(); //5. deletes a user from the map
		
		//funciones del sistema
		bool registrarUsuario(const string& user, const string& pass);
		bool iniciarSesion();
		bool verificarCredenciales(const string& user, const string& pass) const;
		bool cerrarSesion();
		bool estaConectado(const bool& estaActivo) const;
		bool cambiarContrasena(const string& oldPass, const string& newPass);
		bool restablecerContrasena(const string& user, const string& newPass);

};


#endif // SISTEMALOGIN_H