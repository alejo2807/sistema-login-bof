#ifndef SISTEMALOGIN_H
#define SISTEMALOGIN_H
#include "Usuario.h" 
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
		string limpiarToken(string& str); //limpia espacios en blanco, tabulaciones o contra slash-n de los tokens
		
		//funciones especiales privadas
		string hashContrasena(const string& password); 
		//esconder el email con asteriscos. Por ejemplo margaret@gmail.com
		//con maskEmail seria m***t@gmail.com
		string maskEmail(const string& email); 
		
		//verificar que el usuario no este repetido en la base de datos
		bool verificarUsuarioNoRepetidoDataBase(const string& filename, Usuario* nuevoUsuario);
		
		//esta fn sobreescribe una linea especifica del archivo.
  		//Por ejemplo, si el usuario cambia su contrasena, se sobreescribe la
  		//linea del usuario en el archivo, con la nueva contrasena.
  		//Esto se hace para que no se creen lineas repetidas en el archivo.
		void overwriteSpecificLineInFileUserOn(const string& filename, const string& username);

		// funcion que hace lo mismo de arriba, pero para usuarios inactivos
		// o sea, usuarios que cerraron sesion y olvidaron su contrasena
		void overwriteSpecificLineInFileUserOff(const string& filename, const string& username, const string& hashContrasenaTemporal);

	public:
		SistemaLogin();
		
		~SistemaLogin();
		
		//funciones  sobre el archivo y el mapa
		bool parseFile(const string& filename); // parses the file to load users into the map
		void mostrarInformacionUsuarios() const; //4. shows the user information
		void eliminarInformacionDelMap(); // deletes all users from the map
		
		//funciones del sistema
		bool registrarUsuarioAlArchivo(const string& filename, const string& username, const string& plainPassword, Usuario* nuevoUsuario);
		bool iniciarSesion(const string& user, string& pass);
		bool verificarCredenciales(const string& user, string& pass);
		bool cerrarSesion();
		//elimine la fn bool estaConectado. No la vi necesaria, pues el mensaje lo dejo en iniciarSesion()
		bool cambiarContrasena(const string& oldPass, const string& newPass);
		//en restablecler contrasena usamos el email escondido (maskEmail)
		//esta funcion se realiza desde afuera del sistema
		bool restablecerContrasena();

};


#endif // SISTEMALOGIN_H