#include <iostream>
#include <winsock2.h>
#include <vector>
#include <fstream>   // Agrega esta l�nea
#include <sstream>
#include <list>
#include "Credencial.h"
#include <algorithm> // Necesario para std::transform

using namespace std;

class Servidor{
public:
    WSADATA WSAData;
    SOCKET server,client;
    SOCKADDR_IN serverAddr,clientAddr;
    char buffer[1024];
    //string buffer;
    Servidor(){

    WSAStartup(MAKEWORD(2,0),&WSAData);
    server=socket(AF_INET,SOCK_STREAM,0);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(5555);

    bind(server,(SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server,0);
    cout <<"ESCUCHANDO CONEXIONES ENTRANTES."<<endl;
    int clientAddrSize=sizeof(clientAddr);
    if((client=accept(server,(SOCKADDR *)&clientAddr,&clientAddrSize)) != INVALID_SOCKET){
        cout<< "Cliente conectado!" << endl;
    }

    }
/*
    void Recibir(){
    recv(client,buffer,sizeof(buffer),0);
    cout<< "EL CLIENTE DICE : "<< buffer <<endl;
    memset(buffer,0,sizeof(buffer));

    }
    void Enviar(){
    cout<<"Escribe el mensaje a enviar";
    cin>>this->buffer;
    send(client,buffer,sizeof(buffer),0);
   memset(buffer,0,sizeof(buffer));
    //return buffer;
    cout<< "Mensaje enviado!"<<endl;
    }


    void CerrarSocket(){
    closesocket(client);
    cout<<"Socket cerrado,cliente desconectado."<<endl;
    }
*/
  void Credenciales(Servidor* servidor) {
     list<Credencial> credencial=FuncionArchivoEnEstructura();
      bool valor=false;
  bool valor2=false;
    int intentos=0;
    //while(valor!=true){
   send(client,"Nombre Usuario?",sizeof(buffer),0);
    memset(buffer,0,sizeof(buffer));
 cout << "Mensaje enviado!" << endl;
    // -----------recibo-----------
    recv(servidor->client, servidor->buffer, sizeof(servidor->buffer), 0);
    cout << "EL CLIENTE DICE : " << servidor->buffer << endl;
 valor=buscadorDeUsuario(credencial,buffer);//busca dentro de la lista string  al usuario
    printf("VALOR : %d",valor);

printf("QUE BUSCO: %s", servidor->buffer);
   memset(servidor->buffer, 0, sizeof(servidor->buffer)); // borra el buffer

    if(valor==true){//verifica y avisa
    send(client,"Usuario Encontrado!",sizeof(buffer),0);
    }else{
        send(client,"Usuario  no Encontrado! :( ",sizeof(buffer),0);
    }

/*
    //--------contrase�a--------------------
    //agregar condicion de intentos &&

  //  if (valor == true) {
  string buscar;
            while(valor2!=true ){
        send(client,"Contrasenia?",sizeof(buffer),0);
    memset(buffer,0,sizeof(buffer));
        cout << "Mensaje enviado!" << endl;
        // -----------recibo-----------
        recv(servidor->client, servidor->buffer, sizeof(servidor->buffer), 0);
        cout << "EL CLIENTE DICE : " << servidor->buffer << endl;
      valor2= verificarContrasenia(credencial,"persona1","potasio");
      printf("VALOR : %d",valor2);

printf("QUE BUSCO: %s", servidor->buffer);
        memset(servidor->buffer, 0, sizeof(servidor->buffer)); // borra el buffer
    }
*/
}






    //TRADUCCION-----------------------------------------------------------
void Traductor(const std::string& palabra) {
    std::ifstream file("traductor.txt");

    if (!file) {
        std::cerr << "Error al abrir el archivo de traductor." << std::endl;
        return;
    }

    std::string linea;
    bool encontrada = false;
    while (std::getline(file, linea)) {
        std::istringstream iss(linea);
        std::string palaEspa;
        std::string palaIngles;

        if (std::getline(iss, palaIngles, ':') && std::getline(iss, palaEspa)) {
            if (palaEspa == palabra||palabra==palaIngles) {
                encontrada = true;
               string mensaje="\nPalabra recibida en ingles: "+palaIngles+"\nPalabra traducida al espaniol: "+palaEspa;
                send(client, mensaje.c_str(), mensaje.size(), 0);
            }
        }
    }

    if (!encontrada) {
        std::cout << "No fue posible encontrar la traducci�n para: " << palabra << std::endl;
    }
}


void TraductorCliente(){

 // ---- Interacci�n ----
    const char* mensaje = "Escribe el mensaje a enviar a traducir\n";
    send(client, mensaje, strlen(mensaje), 0);

    // --------- Recepci�n -----------
   // char buffer[1024];
    int bytesRecibidos = recv(client, buffer, sizeof(buffer) - 1, 0);

    if (bytesRecibidos == -1) {
        std::cerr << "Error al recibir el mensaje del cliente." << std::endl;
        return;
    }

    buffer[bytesRecibidos] = '\0'; // A�ade el car�cter nulo al final del mensaje recibido

    std::cout << "Palabra a Traducir: " << buffer << std::endl;
    std::cout << "Traduzco entonces..." << std::endl;

//    Traductor(buffer);
      Traductor(ConvertirAMinusculas(buffer));//se convierte el texto antes de buscar
}





std::string ConvertirAMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);
    return resultado;
}





  //INSERTAR TRADUCCIONNN

    void InsertarTraduccion() {

        FILE *puntero;
        puntero = fopen ("traductor.txt", "a");

        string palabraTraduccion;

        char aux[50];
        string pala;
        const char* mensaje = "Escribe la nueva traduccion, separado las palabras con un ( : )\n";
    send(client, mensaje, strlen(mensaje), 0);
        int bytesRecibidos = recv(client, aux, sizeof(aux), 0);
pala=aux;

        // Verificar que las palabras no est�n vac�as
    if (pala.empty() ) {
       mensaje= "\nError: Las palabras deben tener contenido.";
        send(client, mensaje, strlen(mensaje), 0);
        return;
    }

    // Verificar que las palabras no contengan ':' para cumplir con el formato
    if (pala.find(':')==std::string::npos ) {

        mensaje= "\nError: Las palabras deben tener el caracter ':'.\n";
        send(client, mensaje, strlen(mensaje), 0);
        return;
    }else{

        if (bytesRecibidos <= 0) {
            std::cout << "ERROR" << std::endl; //me da este error revisar!
            } else {
            aux[bytesRecibidos] = '\0'; // A�adir terminador nulo para convertirlo en una cadena de C v�lida
            // Ahora 'aux' contiene los datos recibidos desde el socket
            }

            std::cout << aux << std::endl;

            //escribe
            mensaje= "\nMENSAJE AGREGADO CORRECTAMEN AL ARCHIVO DE TRADUCCIONES!!\n";
        send(client, mensaje, strlen(mensaje), 0);
           // Agrega un car�cter de nueva l�nea al final del arreglo aux
        fprintf(puntero,"\n");
       aux= ConvertirAMinusculas(aux);
            fprintf(puntero, "%s", aux);
    }
            fclose(puntero);

    }};









    int main(){

 Servidor *Servidorr =new Servidor();
//Servidorr->InsertarTraduccion();

     Servidorr->TraductorCliente();
    // Cargar las credenciales desde el archivo


    // Imprimir las credenciales cargadas (solo como ejemplo)
list<Credencial> credencial = FuncionArchivoEnEstructura();

   // Servidorr->Credenciales(Servidorr);
       // Servidorr->Recibir();
        //Servidorr->Enviar();

    return 0;
    }

