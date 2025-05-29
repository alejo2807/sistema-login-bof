#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
using namespace std;

class Usuario {

    private:
        string nombreCompleto;
        string nombreUsuario;
        string hashContrasena;
    
    public:
        Usuario(string nombreCompleto, string nombreUsuario, string hashContrasena);
        bool verificarContrasena(string contrasena) const;

        // Getters
        string getNombreCompleto() const;
        string getNombreUsuario() const;

};


#endif // USUARIO_H