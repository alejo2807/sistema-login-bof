#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map> 
#include <fstream> // Para manejar archivos, usamos ifstream y ofstream
#include <sstream> // Para usar stringstream, istringstream y ostringstream 
//sringstream es el dispensador, istringstream es la cajita de dulces parecida al dispensador
//y ostringstream es como el constructor que une palabras en una misma linea
#include <vector>

//para el algoritmo de criptografia bcrypt (hashear contrasena)
#include "libbcrypt/include/BCrypt.hpp"  // Now points to the correct path!
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
		
	//Esto lo comento porque ya esta creado el archivo users.txt (ofstream recibe filename)
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
				limpiarToken(token);
				user.setNombreCompleto(token);
				break;
			case 1:
				limpiarToken(token);
				user.setNombreUsuario(token);
				break;
			case 2:
				limpiarToken(token);
				user.setEmail(token);
				break;
			case 3:
				limpiarToken(token);
				user.setNumeroTelefono(token);
				break;
			case 4:
				limpiarToken(token);			
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

string SistemaLogin::limpiarToken(string &str)
{
	size_t inicio = str.find_first_not_of(" \t\n\r");
	size_t fin = str.find_last_not_of(" \t\n\r");
	return (inicio == string::npos || fin == string::npos) ? "" : str.substr(inicio, fin - inicio + 1);
}



string SistemaLogin::hashContrasena(const string& password)
{
	std::string hash = BCrypt::generateHash(password, 12);
	return hash;
}

////////////////////////////////////////////////////////////////


SistemaLogin::SistemaLogin()
{
	//inicializacion del puntero usuarioActivo, como null
	usuarioActivo=nullptr;
	if(verificarArchivo()) {cout << "Archivo de usuarios encontrado." << endl;} 

	else {
		cout << "Archivo de usuarios no encontrado. Creando uno nuevo..." << endl;
		crearArchivo();
	}

}

SistemaLogin::~SistemaLogin()
{
	eliminarInformacionDelMap(); 
	cout << "Todos los usuarios han sido eliminados." << endl;	
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
	
	//Se elimina los nombres de usuario (strings)
	//Se eliminan los punteros a los objetos Usuario, que viven en la stack
	usuarios.clear(); 
}


bool SistemaLogin::registrarUsuario(const string& filename, const string& username, const string& plainPassword, Usuario* nuevoUsuario)
{
	std::ofstream archivoCambiado(filename, ios::app);
	
	if(!archivoCambiado.is_open())
	{
		cerr << "No se pudo abrir el archivo" <<endl;
		return false;
	}
	
	//variable para medir si la funcion es exitosa o no
	//se retorna al final, ya que toda funcion booleana debe retorna algo al final
	//(incluso si no es booleana, con que NO sea void, debe retornar algo)
	bool success;
	
	//hasheamos la contrasena en registrar usuario, de tal modo que el metodo es privado
	string hash = hashContrasena(plainPassword);
	nuevoUsuario->setHashContrasena(hash);
	
	string searchUsername = nuevoUsuario->getNombreUsuario();
	// .find() devuelve un puntero(iterador) que apunta al nombre de usuario encontrado
	auto it = usuarios.find(searchUsername);
	
	// .end() devuelve un puntero (iterador) que apunta al ultimo objeto + 1 posicion,
	// tecnicamente .end() es una posicion que no existe en el mapa
	//por lo que, la comparacion es que si it es diferente a usuarios.end()
	// eso significa que si ha sido encontrado en el mapa, el usuario X
	if (it != usuarios.end())
	{
		cerr << "El usuario: " << nuevoUsuario->getNombreUsuario()<< " ya existe.\nNo se puede agregar" <<endl;
		success = false;
	}
	
	else
	{
		//el contra-slash n se usa para escribir en la linea mas abajo del archivo
		archivoCambiado <<"\n"<< nuevoUsuario->getNombreCompleto() 
		<< "," << nuevoUsuario->getNombreUsuario() 
		<< "," << nuevoUsuario->getEmail() 
		<< "," << nuevoUsuario->getNumeroTelefono() 
		<< "," << nuevoUsuario->getHashContrasena() << endl;
		
		success = true;
	}

	return success;
	
}
////////////////////////////////////////////////////////////////////////////////////
// funciones del sistema


bool SistemaLogin::iniciarSesion(const string& user, string& pass)
{
	if(verificarCredenciales(user, pass)) 
	{
		cout<<"Has iniciado sesion como " << user <<endl;
		return true;
	}
	
	else return false;
}

bool SistemaLogin::verificarCredenciales(const string& user,  string& pass)
{
	bool success;
	
	//recordar que le debo poner el auto porque es un iterador,
	//asi el copilador lo reconoce automaticamente, y no funciona con string it = ...
	//porque no puedo asignar el resultado de buscar con la funcion.find() a un string,
	//pues es un iterador
	auto it = usuarios.find(user);
	
	//si encontro el usuario, que se cumplan las instrucciones siguientes
	if (it != usuarios.end())
	{
		//esta linea de it->second, nos sirve para acceder al puntero desde el iterador
		//it->first seria el username, it->second, el puntero de ese username
		Usuario* userTemporal = it->second;
		string hashEnMap = userTemporal->getHashContrasena();
		
		//usamos un metodo de la libreria Bcrypt para verificar la contrasena
		//no podia directamente comparar con el hash hecho aqui y el guardado
		//porque bcrypt siempre hace hashes diferentes por el componente del salt
		if(BCrypt::validatePassword(pass, hashEnMap))
		{
			cout << "Bienvenido " << user << " a Vibe-City" << endl;
			cout << "Tu plataforma de musica favorita :)" << endl;
			success = true;
			usuarioActivo = userTemporal;
		}
		else
		{
			cerr << "Contrasena incorrecta" << endl;
			cerr << "Intentalo de nuevo" <<endl;
			success = false;
		}
		
	}
	
	else 
	{
		cerr << "Usuario no encontrado"<<endl;
		cout << "Registrate para empezar a disfrutar de la buena musica :)" << endl;
		success = false;
	}

	return success;
}

// Probar implementacion de cerrarSesion()  y cambiarContrasena()
bool SistemaLogin::cerrarSesion()
{
	if (usuarioActivo) {
		cout << "Goodbye, " << usuarioActivo->getNombreUsuario() << endl;
		usuarioActivo = nullptr;
		return true;
	}
	return false;
}

bool SistemaLogin::cambiarContrasena(const string &oldPass, const string &newPass)
{	
	string nuevaContrasena;
	
	
	Usuario* user2;
	string hashEnMap = user2->getHashContrasena();
	if(BCrypt::validatePassword(oldPass,hashEnMap))
	{
		cout<<"Ingresa la nueva contrasena: "<<endl;
		getline(cin, nuevaContrasena);
		string hashNuevo = BCrypt::generateHash(nuevaContrasena);
		user2->setHashContrasena(hashNuevo);
		
	}
	return false;
}
