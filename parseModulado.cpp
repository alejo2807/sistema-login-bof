#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map> 
#include <fstream> // Para manejar archivos, usamos ifstream y ofstream
#include <sstream> // Para usar stringstream
using namespace std;

void SistemaLogin::parseFile(string &filename)
{
	
}

bool SistemaLogin::parseLine(string &LineaDondeEstoy, Usuario &user)
{
	return false;
}

bool SistemaLogin::guardarAlMapa(const Usuario &user)
{
	return false;
}

void SistemaLogin::mostrarInformacionUsuarios(map<string, Usuario *> &usuariosRef) const
{
}

void SistemaLogin::eliminarUsuarios(map<string, Usuario *> &usuariosRef)
{
}