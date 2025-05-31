#include "Usuario.h"
#include <iostream>
#include <string>
using namespace std;

Usuario::Usuario(string nombreCompleto, string nombreUsuario, string hashContrasena)
{
    this->nombreCompleto = nombreCompleto;
    this->nombreUsuario = nombreUsuario;
    hashContrasena = ""; // Inicializar hashContrasena como una cadena vacía
}


bool Usuario::verificarContrasena(string contrasena) const
{

    // Aquí deberías implementar la lógica para verificar la contraseña
    // Por ejemplo, comparar el hash de la contraseña ingresada con el hash almacenado
    // En este caso, simplemente retornamos true para simular una verificación exitosa
    return true; // Simulación de verificación exitosa
}




string Usuario::getNombreCompleto() const
{
    return nombreCompleto;
}

string Usuario::getNombreUsuario() const
{
    return nombreUsuario;
}
