#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map> 
#include <fstream> // Para manejar archivos, usamos ifstream y ofstream
#include <sstream> // Para usar stringstream
using namespace std;

void SistemaLogin::parseFile(string &filename)
{
	std::ifstream miArchivo(filename);
	if (miArchivo.is_open()) 
	{
		cout << "El archivo se ha abierto correctamente." << endl;
		string line;
		while (getline(miArchivo, line)) 
		{
			Usuario usuarioInicial;
			Usuario *userPtr = &usuarioInicial; // Puntero al usuario actual
			if (parseLine(line, usuarioInicial)) 
			{
				(guardarAlMapa(usuarioInicial, userPtr ));
			} 
			else cerr << "Error al parsear la línea: " << line << endl;
		}
		miArchivo.close(); // Cerrar el archivo después de leer
	} 
	else 
	{
		cout << "No se pudo abrir el archivo." << endl;
	}
}

bool SistemaLogin::parseLine(string &LineaDondeEstoy, Usuario &user)
{
	string token;
	stringstream dispenser(LineaDondeEstoy);
	size_t index = 0; // Usado para saber en qué parte (en qué token) de la línea estamos
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

bool SistemaLogin::guardarAlMapa(const Usuario &user, Usuario *ptrUsu)
{
	if(usuarios.find(user.getNombreUsuario()) != usuarios.end()) 
	{
		cout << "El usuario " << user.getNombreUsuario() << " ya existe. No se agregará nuevamente." << endl;
		return false; // Si el usuario ya existe, no lo agregamos de nuevo
	}
	else
	{
		usuarios[user.getNombreUsuario()] = ptrUsu; // Agregar el usuario al mapa
	}
}


void SistemaLogin::mostrarInformacionUsuarios(map<string, Usuario *> &usuariosRef) const
{
	
	if (!usuariosRef.empty()) 
	{
		for (const auto &par : usuariosRef) 
		{
		cout << "Usuario: " << par.first << endl;
		cout << "Nombre Completo: " << par.second->getNombreCompleto() << endl;
		cout << "Email: " << par.second->getEmail() << endl;
		cout << "Numero de Telefono: " << par.second->getNumeroTelefono() << endl;
		cout << "------------------------" << endl;
		}
	}
	
	else cout << "No hay usuarios registrados." << endl;
	
}

void SistemaLogin::eliminarInformacionDelMap(map<string, Usuario *> &usuariosRef)
{
	for (auto& pair : usuariosRef) 
	{
		usuariosRef.clear(); // Limpiar el mapa
	}
	cout << "Todos los usuarios han sido eliminados." << endl;	
}