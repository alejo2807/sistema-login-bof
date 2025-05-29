#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
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

    else if (!verificarArchivo()) {
        std::ofstream nuevoArchivo("users.txt");
        nuevoArchivo.close(); // Cerrar el archivo después de crearlo
        cout << "Base de datos creada correctamente." << endl;
        return true; // Archivo creado exitosamente
    }
    return false; // Error al crear el archivo
}


////////////////////////////////////////////////////////////////


SistemaLogin::SistemaLogin(string username, string password)
{
}

