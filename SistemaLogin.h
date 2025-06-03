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

		//funciones que se encargan de parsear el archivo de usuarios
		// y guardar los usuarios en el mapa
		bool parseFile(string& filename); //1. the file to load users into the map
		bool parseLine(string& LineaDondeEstoy, Usuario& user); //2.parses a line from the file to create a Usuario object
		bool guardarAlMapa(Usuario* nuevoUsuario); //3. saves the user to the map
		void mostrarInformacionUsuarios() const; //4. shows the user information
		void eliminarInformacionDelMap(); //5. deletes a user from the map
		
		//falta hash contrasena y funciones publicas
		string hashContrasena(string pass); //retornara la contraseña hasheada

	public:
		SistemaLogin();
		~SistemaLogin();
		
		//funciones 
		bool registrarUsuario(const string& user, const string& pass);
		bool iniciarSesion();
		bool verificarCredenciales(const string& user, const string& pass) const;
		bool cerrarSesion();
		bool estaConectado(const bool& estaActivo) const;
		bool cambiarContrasena(const string& oldPass, const string& newPass);
		bool restablecerContrasena(const string& user, const string& newPass);

};


#endif // SISTEMALOGIN_H