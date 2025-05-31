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

void SistemaLogin::parseFile()
{
	//TRABAJE LA FUNCION PARSE FILE, QUE SE ENCARGA DE LEER EL ARCHIVO Y PARSEARLO.
	//SUBIR COMMITS DE ESTO, Y LUEGO SEGUIR CON EL PROYECTO.
	//EN SISTEMA LOGIN SOLO AGREGUE LA FUNCION PERO NO HICE NADA CON ELLA AUN.
	//HARE COMMIT DE ESO TAMBIEN
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
			std::stringstream stream(line);
			//los tokens son las partes de la línea que están separadas por comas
			std::string token;
			//variables para almacenar los datos (tokens) extraídos de la línea
			string nombreCompletoBaseDatos, nombreUsuarioBaseDatos, hashContrasenaBaseDatos;

			size_t index = 0; //(lo usaremos para saber en qué parte de la línea estamos)
			while(std::getline(stream, token, ',')) {
				if (index == 0) {
					nombreCompletoBaseDatos = token; // Guardar el nombre completo
				} else if (index == 1) {
					nombreUsuarioBaseDatos = token; // Guardar el nombre de usuario
				} else if (index == 2) {
					hashContrasenaBaseDatos = token; // Guardar el hash de la contraseña
				}
				index++; // Incrementar el índice para la siguiente iteración
			}
			cout<<nombreCompletoBaseDatos << " | " 
					<< nombreUsuarioBaseDatos << " | " 
					<< hashContrasenaBaseDatos << endl; // Imprimir los datos extraídos
		}
		miArchivo.close(); // Cerrar el archivo después de leer		
	} 
	else {
		cout << "Error al abrir el archivo." << endl;
		return; 
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

	cargarUsuariosDesdeArchivo(); // Cargar usuarios desde el archivo al iniciar el sistema
}


