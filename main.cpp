// formato del archivo users.txt:
//nombreCompleto,nombreUsuario,hashContrasena (mini base de datos)



//SE HACE UNA REESTRUCTURACION DEL CODIGO DE TODO EL PROYECTO:
//ahora hay 2 clases, SistemaLogin y Usuario, y se implementa un sistema de login básico.


//vamos a hacer un intento de leer y parsear el archivo de usuarios

#include <fstream>
#include <iostream>
#include <string>
#include <sstream> //to use stringstream
#include <vector>
#include <map> //para usar map
#include "Usuario.h" // Asegúrate de incluir el archivo Usuario.h
using namespace std;


int main()
{
	map<string, Usuario*> usuarios; // Mapa para almacenar usuarios

	//DESPUES DE PARSEAR EL ARCHIVO, Y EXTRAER LOS TOKENS, DEBO ALMACENARLOS EN UNA ESTRUCTURA DE DATOS
	//USARE MAP PARA PRACTICAR PUNTEROS TMB, Y PODER USARLOS MAS ADELANTE.
	//lo comento porque ya esta creado el archivo users.txt
	//std::ofstream nuevoArchivo("users.txt");
	//nuevoArchivo.close();
	
	// Intentamos abrir el archivo para leer
	std::ifstream miArchivo("users.txt");
	if(miArchivo.is_open()) 
	{
		cout << "El archivo se ha abierto correctamente." << endl;
		string line;
		
		// Leemos el archivo línea por línea
		// Usamos getline para leer cada línea del archivo
		// Esto nos permite procesar cada línea de manera individual.
		while(std::getline(miArchivo, line))
		{	
			if(line.empty() || line.find("/") == 0) {
				continue; // Saltar líneas vacías o comentarios
			}
			//creamos un stringstream a partir de la línea leída (es como el dispensador de dulces del cual extraemos los dulces (datos))
			// Esto nos permite procesar la línea de manera más flexible.
			// Por ejemplo, como la línea contiene datos separados por comas, podemos usar stringstream para extraerlos.
			std::stringstream dispenser(line);
			//los tokens son las partes de la línea que están separadas por comas
			std::string token;
			//variables para almacenar los datos (tokens) extraídos de la línea
			string nombreCompletoBaseDatos, nombreUsuarioBaseDatos, hashContrasenaBaseDatos;

			size_t index = 0; //(lo usaremos para saber en qué parte de la línea estamos)
			while(std::getline(dispenser, token, ',')) {
				if (index == 0) {
					nombreCompletoBaseDatos = token; // Guardar el nombre completo
				} else if (index == 1) {
					nombreUsuarioBaseDatos = token; // Guardar el nombre de usuario
				} else if (index == 2) {
					hashContrasenaBaseDatos = token; // Guardar el hash de la contraseña
				}
				index++; // Incrementar el índice para la siguiente iteración
			}
			// Ahora tenemos los datos extraídos de la línea
			// Los datos estan en el mapa usuarios, donde la clave es el nombre de usuario y el valor es un puntero a un objeto Usuario
			usuarios.insert(pair<string, Usuario*>(nombreUsuarioBaseDatos, new Usuario(nombreCompletoBaseDatos, nombreUsuarioBaseDatos, hashContrasenaBaseDatos)));
			
			for(auto & username : usuarios) {
				cout << "Usuario: " << username.first <<  endl;
				cout << "Informacion:" << endl;
				cout << "Nombre Completo: " << username.second->getNombreCompleto() << endl;
				//g++ main.cpp Usuario.cpp -o p
			}
			
		}
		miArchivo.close(); // Cerrar el archivo después de leer		
	} 
	else {
		cout << "Error al abrir el archivo." << endl;
		return 1; 
	}
	
	
	
}

