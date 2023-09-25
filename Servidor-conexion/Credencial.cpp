#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <string>

using namespace std;

struct Credencial {
    string usuario;
    string contra;
    string rol;
    int bloqueos;
};

list<Credencial> FuncionArchivoEnEstructura() {
    list<Credencial> credenciales;
    ifstream file("credenciales.txt");

    if (!file) {
        cerr << "Error al abrir el archivo de credenciales." << endl;
        return credenciales;
    }

    string linea;
    while (getline(file, linea)) {
        istringstream iss(linea);
        string usuario, contrasenia, rol, bloqueosStr;

        if (getline(iss, usuario, '|') &&
            getline(iss, contrasenia, '|') &&
            getline(iss, rol, '|') &&
            getline(iss, bloqueosStr, '|')) {
            // Intenta convertir bloqueosStr a entero, con manejo de errores
            int bloqueos;
            bloqueos = stoi(bloqueosStr);

            Credencial credencial;
            credencial.usuario = usuario;
            credencial.contra = contrasenia;
            credencial.rol = rol;
            credencial.bloqueos = bloqueos;

            credenciales.push_back(credencial);
        } else {
            cerr << "Error al analizar la l�nea: " << linea << endl;
        }
    }

    file.close();
    return credenciales;
}

bool buscadorDeUsuario(list<Credencial> credenciales, string usuario) {
    bool valor = false;
    for (Credencial credencial : credenciales) {
        if (credencial.usuario == usuario) {
            valor = true;
        }
    }
    return valor;
}

bool verificarContrasenia(list<Credencial> credenciales, string usuario, string contra) {
    bool valor = false;
    for (Credencial credencial : credenciales) {
        if (credencial.usuario == usuario) {
            if (credencial.contra == contra) {
                valor = true;
            }
        }
    }
    return valor;
}

/*
int main() {
    list<Credencial> credenciales = FuncionArchivoEnEstructura();

    for (Credencial credencial : credenciales) {
        cout << "Usuario: " << credencial.usuario << endl;
        cout << "Contrasenia: " << credencial.contra << endl;
        cout << "Rol: " << credencial.rol << endl;
        cout << "Bloqueos: " << credencial.bloqueos << endl;
        cout << "-----------------------" << endl;
    }

    return 0;
}
*/
