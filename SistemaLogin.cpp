#include "SistemaLogin.h"
#include <iostream>
#include <string>
#include <map> 
#include <fstream> // Para manejar archivos, usamos ifstream y ofstream
#include <sstream> // Para usar stringstream, istringstream y ostringstream 
//stringstream es el dispensador, istringstream es la cajita de dulces parecida al dispensador
//y ostringstream es como el constructor que une palabras en una misma linea
#include <vector>

#include <cstdlib>// para rand() y srand()
#include <ctime>// para time()

#include <filesystem> // libreria que agregue para  hacer la linea 300 mas moderna y simple

//para el algoritmo de criptografia bcrypt (hashear contrasena)
#include "libbcrypt/include/BCrypt.hpp"  // Now points to the correct path!
using namespace std;



bool SistemaLogin::verificarArchivo()
{
	std::ifstream miArchivo("users.csv");
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
	std::ofstream nuevoArchivo("users.csv");
	if (!nuevoArchivo.is_open()) {
		//vamos a dar mas informacion al usuario si no se pudo crear el archivo
		std::cerr<< "Error al crear el archivo users.csv.\n Asegúrate de tener permisos de escritura en el directorio." << std::endl;
		return false; // Si no se pudo abrir el archivo, retornar false

	}

	nuevoArchivo.close(); // Cerrar el archivo después de crearlo
	cout << "Base de datos creada correctamente." << endl;
	return true; // Archivo creado exitosamente
	
}

bool SistemaLogin::parseFile(const string &filename)
{
		
	//Esto lo comento porque ya esta creado el archivo users.csv (ofstream recibe filename)
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

bool SistemaLogin::guardarAlMapa(Usuario *usuarioActivo)
{
	
	string username = usuarioActivo->getNombreUsuario(); 
	
	if(usuarios.find(username) != usuarios.end()) 
	{
		cout << "El usuario " << username << " ya existe. No se agregará nuevamente." << endl;
		return false; // Si el usuario ya existe, no lo agregamos de nuevo
	}
	else
	{
		//usuario vive en el heap, por lo que debemos usar un puntero a Usuario
		usuarios[username] = usuarioActivo; // Agregar el usuario al mapa
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

string SistemaLogin::maskEmail(const string& email) {
	
	//si no se encuentra se retorna los 3 asterisctos
	if (email.empty()) return "***";
	size_t atPos = email.find('@');
	
	//string::npos sirve para tener una posicion "no encontrada"
	//aqui tambien, si no se encuentra se retorna los 3 asterisctos
	if (atPos == string::npos) return "***";
	
	//extrae, de la cadena, la posicion 0, con una longitud de 1 caracter
	//luego le suma 3 asteriscos al correo, "escondiendolo"
	//finalmente, de la cadena email, extrea la cadena desde un caracter antes del '@', hasta el final.
	// Turns "margaret@gmail.com" → "m***t@gmail.com" (example)
	return email.substr(0, 1) + "***" + email.substr(atPos - 1);
	
	
	//substr(pos, len);
	//Parameters:
	//pos: Index of the first character to be copied.
	//len: Length of the sub-string.
	//if len is not specified, it takes all from the start position "pos" till the end
}

bool SistemaLogin::verificarUsuarioNoRepetidoDataBase(const string &filename, Usuario *usuarioActivo)
{
	//variable para medir si la funcion es exitosa o no
	//se retorna al final, ya que toda funcion booleana debe retorna algo al final
	//(incluso si no es booleana, con que NO sea void, debe retornar algo)
	bool success;
	string searchUsername = usuarioActivo->getNombreUsuario();


	// Intentamos leer el archivo y lo parseamos.
	// (esta es la verificacion para evitar nombres de usuario repetidos en la base de datos)
	ifstream archivoLeido(filename);
	string line;
	
	if(!archivoLeido.is_open())
	{
		cerr <<"error en la base de datos"<<endl;
		success = false;
	}
	while(getline(archivoLeido, line)) {
		// Saltar líneas vacías/comentarios
		if(line.empty() || line[0] == '/') continue;

		// Extraer solo el nombre de usuario (segundo campo entre comas)
		size_t posInicio = line.find(',') + 1;
		size_t posFin = line.find(',', posInicio);
		string usuarioEnArchivo = line.substr(posInicio, posFin - posInicio);

		// Eliminar espacios alrededor si los hay
		usuarioEnArchivo.erase(0, usuarioEnArchivo.find_first_not_of(" \t"));
		usuarioEnArchivo.erase(usuarioEnArchivo.find_last_not_of(" \t") + 1);

		// Comparación exacta
		if(usuarioEnArchivo == searchUsername) {
			archivoLeido.close();
			cerr << "Error. Usuario '" << searchUsername << "' no disponible.\n";
			return false;
		}
	}
	
	archivoLeido.close();
	return true;
}

void SistemaLogin::overwriteSpecificLineInFileActiveUser(const string &filename, const string &username)
{
	ifstream inFile(filename);
	ofstream outFile("temp.csv");
	string line;
	
	std::ostringstream oss;
	oss << usuarioActivo->getNombreCompleto()
		<< "," << usuarioActivo->getNombreUsuario()
		<< "," << usuarioActivo->getEmail()
		<< "," << usuarioActivo->getNumeroTelefono()
		<< "," << usuarioActivo->getHashContrasena();

	string newContent = oss.str();

	while (getline(inFile, line)) {
		
		// Extract username from CSV line
		size_t firstComma = line.find(',');
		size_t secondComma = line.find(',', firstComma + 1);
		string fileUsername = line.substr(firstComma + 1, secondComma - firstComma - 1);
		
		if (fileUsername == username) {
			outFile << newContent << endl; // Replace the line
		} 
		else {
			outFile << line << endl;
		}
	}

	inFile.close();
	outFile.close();

	//aqui usaremos la libreria filesystem porque es mas moderna
	std::filesystem::remove(filename); // Elimina el archivo original
	std::filesystem::rename("temp.csv", filename); // Renombra el archivo temporal al nombre original

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
		cout << "Hash: " << par.second->getHashContrasena() << endl;
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


bool SistemaLogin::registrarUsuarioAlArchivo(const string& filename, const string& username, const string& plainPassword, Usuario* usuarioActivo)
{

	bool success;
	
	if(verificarUsuarioNoRepetidoDataBase(filename,usuarioActivo))
	{
		// Se abre el archivo con ofstream en modo edicion, 
		// y para escribir en la ultima linea usamos ios::app
		std::ofstream archivoCambiado(filename, ios::app);
		
		if(!archivoCambiado.is_open())
		{
			cerr << "No se pudo abrir el archivo" <<endl;
			success = false;
		}

		//hasheamos la contrasena en registrar usuario, de tal modo que el metodo es privado
		string hash = hashContrasena(plainPassword);
		usuarioActivo->setHashContrasena(hash);

		//el contra-slash n se usa para escribir en la linea mas abajo del archivo
		archivoCambiado <<"\n"<< usuarioActivo->getNombreCompleto() 
		<< "," << usuarioActivo->getNombreUsuario() 
		<< "," << usuarioActivo->getEmail() 
		<< "," << usuarioActivo->getNumeroTelefono() 
		<< "," << usuarioActivo->getHashContrasena() << endl;
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

	string hashTemporal = usuarioActivo->getHashContrasena();
	if(BCrypt::validatePassword(oldPass,hashTemporal))
	{
		string hashNuevo = BCrypt::generateHash(newPass);
		usuarioActivo->setHashContrasena(hashNuevo);
		
		overwriteSpecificLineInFileActiveUser("users.csv", usuarioActivo->getNombreUsuario());
		cout << "✓ Contraseña cambiada exitosamente.\n";
		return true;
	}
	return false;
}

bool SistemaLogin::restablecerContrasena() 
{
	if (usuarioActivo) {
		cout << "Cierra sesión primero para restablecer contraseña.\n";
		return false;
	}

	string username, email;
	
	// Step 1: Verify user exists
	cout << "Ingrese su nombre de usuario: ";
	getline(cin, username);
	
	auto it = usuarios.find(username);
	if (it == usuarios.end()) {
		cerr << "Usuario no encontrado.\n";
		return false;
	}

	// Step 2: Verify email/phone (professional touch)
	Usuario* user = it->second;
	string storedEmail = user->getEmail();
	string maskedEmail = maskEmail(storedEmail);
	
	cout << "Ingrese el email registrado (" << maskedEmail << "): ";
	getline(cin, email);
	
	if (email != storedEmail) {
		cerr << "Email no coincide.\n";
		return false;
	}
	
	srand(time(0)); // Seed for random number generation
	int randNum = rand() % 1000; // Random number for temporary password

	// Step 3: Generate temporary password (simple approach)
	string tempPassword = "temp_" + to_string(randNum);
	cout << "\nTu contraseña temporal es: " << tempPassword
		<< "\nCámbiala inmediatamente después de iniciar sesión.\n\n";

	// Step 4: Update password (using existing cambiarContrasena)
	user->setHashContrasena(hashContrasena(tempPassword));
	
	//revisar este pedazo, porque no se si funciona. 
	//En caso de que funcione, tendria las 3 ultimas funciones completas :)
	//overwriteSpecificLineInFile("users.csv", username);

	
	cout << "✓ Contraseña restablecida. Inicia sesión con la temporal.\n";
	return true;
}


