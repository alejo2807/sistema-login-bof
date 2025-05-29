#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map> 
#include <fstream> // Para manejar archivos, usamos ifstream y ofstream
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


