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

bool SistemaLogin::parseFile(const string &filename)
{
	//lo comento porque ya esta creado el archivo users.txt (ofstream recibe filename)
	//std::ofstream nuevoArchivo(filename);
	//nuevoArchivo.close();
	
	// Intentamos abrir el archivo para leer
	//si no se pudo abrir, retornamos falso
	std::ifstream miArchivo(filename);
	if (!miArchivo.is_open()) 
	{
		cerr << "No se pudo abrir el archivo." << endl;
		return false; 
	} 

	string line;
	bool success;
	while (getline(miArchivo, line)) 
	{
		// Saltar líneas vacías o comentarios
		if (line.empty() || line.find("/") == 0) continue; 
		
		Usuario* userPtr = new Usuario(); // Crear un nuevo objeto Usuario para cada línea
		
		if (parseLine(line, *userPtr)) 
		{
			if(guardarAlMapa(userPtr)) 
			{
				// Si se pudo guardar el usuario, retornar true en success
				success = true;
			} 
			
			else
			{
				cerr << "Error al guardar el usuario "<< endl;
				delete userPtr; // Si no se pudo guardar, liberar memoria y retonar false en success
				success = false;
			}
			
		} 
		else 
		{
			cerr << "Error al parsear la línea: " << line << endl;
			delete userPtr; // Liberar memoria si no se pudo parsear correctamente
			success = false;
		}
	}
	
	miArchivo.close(); // Cerrar el archivo después de leer
	return success;
}

bool SistemaLogin::parseLine(const string &LineaDondeEstoy, Usuario &user)
{
	
	//creamos un stringstream a partir de la línea leída (es como el dispensador de dulces del cual extraemos los dulces (datos))
	// Esto nos permite procesar la línea de manera más flexible.
	// Por ejemplo, como la línea contiene datos separados por comas, podemos usar stringstream para extraerlos.
	stringstream dispenser(LineaDondeEstoy);
	
	//los tokens son las partes de la línea que están separadas por comas
	string token;

	size_t index = 0; // Usado para saber en qué parte (en qué token) de la línea estamos
	
	// Leemos el archivo línea por línea (por eso recibe una línea como parámetro)
	// Usamos getline para leer cada línea del archivo
	// Esto nos permite procesar cada línea de manera individual.
	while(getline(dispenser, token, ',')) 
	{
		switch(index) 
		{
			case 0:
				user.setNombreCompleto(token);
				break;
			case 1:
				user.setNombreUsuario(token);
				break;
			case 2:
				user.setEmail(token);
				break;
			case 3:
				user.setNumeroTelefono(token);
				break;
			case 4:
				user.setHashContrasena(token);
				break;
			default:
				break; // Si hay más de 5 tokens, ignorar
		}
		index++; // Incrementar el índice para la siguiente iteración
	}
	if(index == 5 
		&& !user.getNombreCompleto().empty() 
		&& !user.getNombreUsuario().empty() 
		&& !user.getEmail().empty() 
		&& !user.getNumeroTelefono().empty() 
		&& !user.getHashContrasena().empty()) 
	{
		return true; // Si se han extraído los 5 datos necesarios, retornar true
	}
	
	else return false; // Si no, retornar false
	
}

bool SistemaLogin::guardarAlMapa(Usuario *nuevoUsuario)
{
	
	string username = nuevoUsuario->getNombreUsuario(); 
	
	if(usuarios.find(username) != usuarios.end()) 
	{
		cout << "El usuario " << username << " ya existe. No se agregará nuevamente." << endl;
		return false; // Si el usuario ya existe, no lo agregamos de nuevo
	}
	else
	{
		//usuario vive en el heap, por lo que debemos usar un puntero a Usuario
		usuarios[username] = nuevoUsuario; // Agregar el usuario al mapa
		return true;
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

//implementacion del destructor y cambios, de priv a public mostrar info y eliminar info
SistemaLogin::~SistemaLogin()
{
	//como la funcion es de la misma clase, tiene acceso a la variable privada original
	//entonces le pasamos el mapa como parametro a la funcion eliminarInfoDelMap.
	eliminarInformacionDelMap(); 
}

void SistemaLogin::mostrarInformacionUsuarios() const
{
	
	if (!usuarios.empty()) 
	{
		for (const auto &par : usuarios) 
		{
		//usamos par como variable de iteración del mapa, porque cada elemento del mapa es un par clave-valor
		//par.first es la clave (nombre de usuario) y par.second es el valor (puntero a Usuario)
		cout << "Usuario: " << par.first << endl;
		cout << "Nombre Completo: " << par.second->getNombreCompleto() << endl;
		cout << "Email: " << par.second->getEmail() << endl;
		cout << "Numero de Telefono: " << par.second->getNumeroTelefono() << endl;
		// No imprimimos la contraseña por razones de seguridad
		cout << "------------------------" << endl;
		}
	}
	
	else cout << "No hay usuarios registrados." << endl;
	
}

void SistemaLogin::eliminarInformacionDelMap()
{
	for (auto& pair : usuarios) 
	{
		// se elimina el valor del mapa, que es un objeto Usuario en memoria dinámica
		// el puntero vive en la stack, pero el objeto vive en el heap, por lo que debemos liberar la memoria
		delete pair.second; 
	}
	
	// Limpiar el m// Limpiar el mapaapa. 
	//Se elimina los nombres de usuario (strings)
	//Se eliminan los punteros a los objetos Usuario, que viven en la stack
	usuarios.clear(); 
	cout << "Todos los usuarios han sido eliminados." << endl;	
}
