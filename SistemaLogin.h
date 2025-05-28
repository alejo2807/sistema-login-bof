#ifndef SISTEMALOGIN_H
#define SISTEMALOGIN_H
#include <string>
using namespace std;




class SistemaLogin {

    private:
        string username;
        string password;
        bool isLoggedIn;
    
    public:
        SistemaLogin();

        //funciones 
        bool iniciarSesion();
        bool verificarCredenciales(const string& user, const string& pass) const;
        bool cerrarSesion();
        bool estaConectado(const bool& estaActivo) const;
        bool cambiarContrasena(const string& oldPass, const string& newPass);
        bool restablecerContrasena(const string& user, const string& newPass);
        bool hashContrasena(const string& pass) const;

        // Getters
        string getUsername() const;
        string getPassword() const;


        //setters
        void setUsername( string& user);
        void setPassword( string& pass);

};


#endif // SISTEMALOGIN_H