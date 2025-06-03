#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map> 
#include <fstream> // Para manejar archivos, usamos ifstream y ofstream
#include <sstream> // Para usar stringstream
using namespace std;



bool SistemaLogin::verificarArchivo()
{
	std::ifstream miArchivo("users.txt");
	if (miArchivo.is_open()) 
	{ 
		miArchivo.close(); // Cerrar el archivo después de verificar
		return true; // El archivo existe
	}
	return false;
}

bool SistemaLogin::crearArchivo()
{
	if(verificarArchivo()) {
		return true; // si ya existe el archivo, no es necesario crearlo
	}

	// Si el archivo no existe, lo creamos
	std::ofstream nuevoArchivo("users.txt");
	if (!nuevoArchivo.is_open()) {
		//vamos a dar mas informacion al usuario si no se pudo crear el archivo
		std::cerr<< "Error al crear el archivo users.txt.\n Asegúrate de tener permisos de escritura en el directorio." << std::endl;
		return false; // Si no se pudo abrir el archivo, retornar false

	}

	nuevoArchivo.close(); // Cerrar el archivo después de crearlo
	cout << "Base de datos creada correctamente." << endl;
	return true; // Archivo creado exitosamente
	
}



void SistemaLogin::parseFile(string& filename)
{

	//usaremos el mapa para almacenar los usuarios de nuestra clase SistemaLogin
	// Se deja comentado para recordar la estructura map<string, Usuario*> usuarios;
	
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
			string nombreCompletoBaseDatos, nombreUsuarioBaseDatos, emailBaseDatos, numeroTelefonoBaseDatos, hashContrasenaBaseDatos;

			size_t index = 0; //(lo usaremos para saber en qué parte (en que token) de la línea estamos)
			while(std::getline(dispenser, token, ',')) {
				if (index == 0) {
					nombreCompletoBaseDatos = token; 
				} else if (index == 1) {
					nombreUsuarioBaseDatos = token; 
				} else if (index == 2) {
					emailBaseDatos = token; 
				}
				else if(index == 3)
				{
					numeroTelefonoBaseDatos = token;
				}
				else if(index == 4)
				{
					hashContrasenaBaseDatos = token; 
				}
				
				index++; // Incrementar el índice para la siguiente iteración
			}
			// Ahora tenemos los datos extraídos de la línea
			// Los datos estan en el mapa usuarios, donde la clave es el nombre de usuario y el valor es un puntero a un objeto Usuario
			
			
			//se agrega solo si se han extraído los 5 datos necesarios
			if (index == 5 && !nombreCompletoBaseDatos.empty() && !nombreUsuarioBaseDatos.empty() 
			&& !emailBaseDatos.empty() && !numeroTelefonoBaseDatos.empty() && !hashContrasenaBaseDatos.empty())
			{
				// Verificar si el usuario ya existe en el mapa
				if (usuarios.find(nombreUsuarioBaseDatos) != usuarios.end()) {
					cout << "El usuario " << nombreUsuarioBaseDatos << " ya existe. No se agregará nuevamente." << endl;
					continue; // Si el usuario ya existe, no lo agregamos de nuevo
				}
				
				// Crear un nuevo objeto Usuario y agregarlo al mapa
				// Usamos el nombre de usuario como clave y el objeto Usuario como valor
				// Esto nos permite acceder fácilmente a los usuarios por su nombre de usuario
			
				//se puede hacer de las 2 formas, pero esta es mas clara y concisa
				usuarios[nombreUsuarioBaseDatos] = new Usuario(nombreCompletoBaseDatos, nombreUsuarioBaseDatos, emailBaseDatos,
																numeroTelefonoBaseDatos, hashContrasenaBaseDatos);
				//aun asi, dejo la forma anterior comentada por motivos de aprendizaje
				// usuarios.insert(pair<string, Usuario*>(nombreUsuarioBaseDatos, new Usuario(nombreCompletoBaseDatos, nombreUsuarioBaseDatos, 
				//                                                                 		... ,hashContrasenaBaseDatos)));
			}
			
		miArchivo.close(); // Cerrar el archivo después de leer	
		
		// Imprimir los usuarios almacenados en el mapa
		for(auto& par : usuarios) {
			//usamos par como variable de iteración del mapa, porque cada elemento del mapa es un par clave-valor
			//par.first es la clave (nombre de usuario) y par.second es el valor (puntero a Usuario)
			cout << "Usuario: " << par.first << endl;
			cout << "Nombre Completo: " << par.second->getNombreCompleto() << endl;
			cout << "Email: " << par.second->getEmail() << endl;
			cout << "Numero de Telefono: " << par.second->getNumeroTelefono() << endl;
			// No imprimimos la contraseña por razones de seguridad
			cout << "------------------------" << endl;
		}
		
		// Liberar la memoria de los objetos Usuario
			for(auto& pair : usuarios) {
			// se elimina el valor del mapa, que es un objeto Usuario en memoria dinámica
			// el puntero vive en la stack, pero el objeto vive en el heap, por lo que debemos liberar la memoria
			delete pair.second; 
			}
		// Limpiar el mapa. 
		//Se elimina los nombres de usuario (strings)
		//Se eliminan los punteros a los objetos Usuario, que viven en la stack
		usuarios.clear();
		
		} //llave que cierra el while de cada linea leida en el archivo
		
	} //lave que cierra el if de si se pudo abrir el archivo
	
	
	else {
		cerr << "Error al abrir el archivo." << endl;
	}
	
}

////////////////////////////////////////////////////////////////


SistemaLogin::SistemaLogin()
{
	if(verificarArchivo()) {cout << "Archivo de usuarios encontrado." << endl;} 

	else {
		cout << "Archivo de usuarios no encontrado. Creando uno nuevo..." << endl;
		crearArchivo();
	}

}


