#include "server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "correo.h"
#include <cstdlib>
#include <ctime>
#define size 500

using namespace std;

server::server()
{
    ultimoCorreo = 0;
    tamanio = 1000;
}

server::~server()
{
    //dtor
}

array<correo,size> server::getCorreo(string path){
string texto;
ifstream archivoplano(path);
array<correo,size> correos;
int contadorRegistros = 0;

while(getline(archivoplano, texto)){
    string word = "";
    int contadorCadena;
    contadorCadena = 0;
    for(auto x : texto){
        if (x == ','){ //Delimitador ","
            //Introduccion de registros en archivo a clases
            if(contadorCadena==0){
                correos[contadorRegistros].setId(word);
            }

            if(contadorCadena==1){
                correos[contadorRegistros].setFecha_envio(word);
            }
            if(contadorCadena == 2){
                correos[contadorRegistros].setHora_envio(word);
            }
            if(contadorCadena == 3){
                correos[contadorRegistros].setRemitente(word);
            }
            if(contadorCadena == 4){
                correos[contadorRegistros].setDestinatario(word);
            }
            if(contadorCadena == 5){
                correos[contadorRegistros].setCopia_carbon(word);
            }
            if(contadorCadena == 6){
                correos[contadorRegistros].setCopia_carbon_ciega(word);
            }
            if(contadorCadena == 7){
                correos[contadorRegistros].setAsunto(word);
            }
            if(contadorCadena == 8){
                correos[contadorRegistros].setAsunto(word);
            }

            word = "";
            contadorCadena++;
        }else{
            word = word + x;
            correos[contadorRegistros].setContenido(word);
        }
    }
    contadorRegistros++;
    ultimoCorreo = contadorRegistros;
}

archivoplano.close();
return correos;
}




void server::guardarCorreo(array<correo,size> &correos){
    //Fecha
    time_t now = time(0);
    string fecha;
    string hora;

    tm *ltm = localtime(&now);
    fecha = to_string(ltm->tm_mday) + "-" + to_string((ltm->tm_mon)+1) + "-" + to_string(1900 + ltm->tm_year);
    hora = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);

    //Guardar en Documento txt los correos
    ofstream Doc;
    Doc.open("archivo.txt");
    if(!Doc.is_open()){
        Doc.open("archivo.txt",ios::out);
        if(!Doc.good()){
            cout << "Error al crear el archivo..." <<endl;
            return;
        }
    }

    for(int i=0;i<ultimoCorreo; i++ ){
        Doc << correos[i].getId() << "," ;
        //Doc << correos[i].getFecha_envio() << "," ;
        Doc << fecha  << "," ;
        Doc << hora << "," ;
        Doc << correos[i].getRemitente() << "," ;
        Doc << correos[i].getDestinatario() << "," ;
        Doc << correos[i].getCopia_carbon() << "," ;
        Doc << correos[i].getCopia_carbon_ciega()<< "," ;
        Doc << correos[i].getAsunto() << ",";
        Doc << correos[i].getContenido() << endl;
    }
    Doc.close();
}

void server::generarCopiaSeguridad(array <correo, size> &correos){
   //Guardar en Documento txt los correos
    ofstream Doc;
    Doc.open("CopiaSeguridad.txt");
    if(!Doc.is_open()){
        Doc.open("CopiaSeguridad.txt",ios::out);
        if(!Doc.good()){
            cout << "Error al crear el archivo..." <<endl;
            return;
        }
    }

    //for(int i=0;i<ultimoCorreo; i++ ){
    for(int i=0;i<ultimoCorreo; i++ ){
        Doc << correos[i].getId() << "," ;
        //Doc << correos[i].getFecha_envio() << "," ;
        Doc << "2023-10-28" << "," ;
        Doc << correos[i].getHora_envio() << "," ;
        Doc << correos[i].getRemitente() << "," ;
        Doc << correos[i].getDestinatario() << "," ;
        Doc << correos[i].getCopia_carbon() << "," ;
        Doc << correos[i].getCopia_carbon_ciega()<< "," ;
        Doc << correos[i].getAsunto() << ",";
        Doc << correos[i].getContenido() << endl;
    }
    Doc.close();
}

void server::generarCopiaSeguridadCifrada(array <correo, size> &correos, string password){
   //Guardar en Documento txt los correos
    ofstream Doc;
    Doc.open("CopiaSeguridadCifrada.txt");
    if(!Doc.is_open()){
        Doc.open("CopiaSeguridadCifrada.txt",ios::out);
        if(!Doc.good()){
            cout << "Error al crear el archivo..." <<endl;
            return;
        }
    }

    //for(int i=0;i<ultimoCorreo; i++ ){
    /// *******************************************
    for(int i=0;i<ultimoCorreo; i++ ){
        Doc << correos[i].getId() << "," ;
        //Doc << correos[i].getFecha_envio() << "," ;
        Doc << "2023-10-28" << "," ;
        Doc << correos[i].getHora_envio() << "," ;
        //Doc << correos[i].getRemitente() << "," ;
        Doc << cifradoCesar(password,correos[i].getRemitente()) << ",";
        Doc << cifradoCesar(password,correos[i].getDestinatario()) << "," ;
        Doc << cifradoCesar(password,correos[i].getCopia_carbon()) << "," ;
        Doc << cifradoCesar(password,correos[i].getCopia_carbon_ciega())<< "," ;
        Doc << cifradoCesar(password,correos[i].getAsunto()) << ",";
        Doc << cifradoCesar(password,correos[i].getContenido()) << endl;
    }
    /// *******************************************
    Doc.close();
}

void server::generarCopiaSeguridadDescifrada(array <correo, size> &correos, string password){
   //Guardar en Documento txt los correos
    ofstream Doc;
    Doc.open("CopiaSeguridadCifrada.txt");
    if(!Doc.is_open()){
        Doc.open("CopiaSeguridadCifrada.txt",ios::out);
        if(!Doc.good()){
            cout << "Error al crear el archivo..." <<endl;
            return;
        }
    }

    //for(int i=0;i<ultimoCorreo; i++ ){
    /// *******************************************
    for(int i=0;i<ultimoCorreo; i++ ){
        Doc << correos[i].getId() << "," ;
        //Doc << correos[i].getFecha_envio() << "," ;
        Doc << "2023-10-28" << "," ;
        Doc << correos[i].getHora_envio() << "," ;
        //Doc << correos[i].getRemitente() << "," ;
        Doc << descifradoCesar(password,correos[i].getRemitente()) << ",";
        Doc << descifradoCesar(password,correos[i].getDestinatario()) << "," ;
        Doc << descifradoCesar(password,correos[i].getCopia_carbon()) << "," ;
        Doc << descifradoCesar(password,correos[i].getCopia_carbon_ciega())<< "," ;
        Doc << descifradoCesar(password,correos[i].getAsunto()) << ",";
        Doc << descifradoCesar(password,correos[i].getContenido()) << endl;
    }
    /// *******************************************
    Doc.close();
}

void server::exportarCorreos(array <correo, size> &correos){
    time_t now = time(0);
    string fecha;
    string hora;
    string fechaExportacion;
    tm *ltm = localtime(&now);
    fecha = to_string(ltm->tm_mday) + "-" + to_string((ltm->tm_mon)+1) + "-" + to_string(1900 + ltm->tm_year);
    hora = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);
    fechaExportacion = fecha + ".txt";
   //Guardar en Documento txt los correos
    ofstream Doc;
    Doc.open(fechaExportacion);
    if(!Doc.is_open()){
        Doc.open(fechaExportacion,ios::out);
        if(!Doc.good()){
            cout << "Error al crear el archivo..." <<endl;
            return;
        }
    }

    //for(int i=0;i<ultimoCorreo; i++ ){
    for(int i=0;i<ultimoCorreo; i++ ){
        Doc << correos[i].getId() << "," ;
        //Doc << correos[i].getFecha_envio() << "," ;
        Doc << "2023-10-28" << "," ;
        Doc << correos[i].getHora_envio() << "," ;
        Doc << correos[i].getRemitente() << "," ;
        Doc << correos[i].getDestinatario() << "," ;
        Doc << correos[i].getCopia_carbon() << "," ;
        Doc << correos[i].getCopia_carbon_ciega()<< "," ;
        Doc << correos[i].getAsunto() << ",";
        Doc << correos[i].getContenido() << endl;
    }
    Doc.close();
}

int server::getCantidadCorreos(){
    ifstream archivoplano("archivo.txt");
    string texto;
    int contadorRegistros = 0;
    while(getline(archivoplano, texto)){
    string word = "";
    for(auto x : texto){
        if (x == ','){ //Delimitador ","
            word = "";

        }else{
            word = word + x;
        }
        }
        contadorRegistros++;
        ultimoCorreo ++;
    }

archivoplano.close();
return contadorRegistros;
}

array<int,size> server::buscarCorreoRemitente(string remitente, array<correo,size> correos){
    array<int,size> indiceCorreos;
    for(int j=0;j<size;j++){
        indiceCorreos[j] = -1;
    }
    int indice = 0;
    for(int i=0; i<size;i++){
        if(correos[i].getRemitente() == remitente){
            indiceCorreos[indice] = i;
            indice++;
        }
    }
    return indiceCorreos;
}

array<int,size> server::buscarCorreoId(string id, array<correo,size> correos){
    array<int,size> indiceCorreos;
    for(int j=0;j<size;j++){
        indiceCorreos[j] = -1;
    }
    int indice = 0;
    for(int i=0; i<size;i++){
        if(correos[i].getId() == id){
            indiceCorreos[indice] = i;
            indice++;
        }
    }
    return indiceCorreos;
}

bool server::capturarCorreoNuevo(correo &correoNuevo){
    string id;
    string remitente;
    string destinatario;
    string cc;
    string bcc;
    string asunto;
    string contenido;
        //Fecha
    time_t now = time(0);
    string fecha;
    string hora;

    tm *ltm = localtime(&now);
    fecha = to_string(ltm->tm_mday) + "-" + to_string((ltm->tm_mon)+1) + "-" + to_string(1900 + ltm->tm_year);
    hora = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);


    bool confirmacion = false;

    cout << "Ingrese el ID: " <<endl;
    cin >> id;
    cout << "Ingrese el remitente: " <<endl;
    cin >> remitente;
    cout << "Ingrese el destinatario: " <<endl;
    cin >> destinatario;
    cout << "Ingrese la copia carbon: " <<endl;
    cin >> cc;
    cout << "Ingrese la copia carbon ciega: " <<endl;
    cin >> bcc;
    cout << "Ingrese el asunto: " << endl;
    cin >> asunto;
    cout << "Ingrese el contenido: " << endl;
    cin >> contenido;


    correoNuevo.setId(id);
    correoNuevo.setFecha_envio(fecha);
    correoNuevo.setHora_envio(hora);
    correoNuevo.setRemitente(remitente);
    correoNuevo.setDestinatario(destinatario);
    correoNuevo.setCopia_carbon(cc);
    correoNuevo.setCopia_carbon_ciega(bcc);
    correoNuevo.setAsunto(asunto);
    correoNuevo.setContenido(contenido);

    confirmacion = true;

    return confirmacion;
}

int server::getUltimoCorreo(){
    return ultimoCorreo;
}

int server::getTamanio(){
    return tamanio;
}

void server::setUltimoCorreo(int ultimoCorreo){
    this->ultimoCorreo = ultimoCorreo;
}

bool server::eliminarCorreoId(string id, array<correo, size> &correos){
    int indiceCorreoBuscado = -1;
    for(int i=0;i<size;i++){
        if(correos[i].getId() == id){
            indiceCorreoBuscado = i;
        }
    }
    if(indiceCorreoBuscado == -1)
        return false;
    for(int j=indiceCorreoBuscado;j<ultimoCorreo;j++){
        correos[j] = correos[j+1];
    }
    ultimoCorreo--;

   return true;
}

bool server::eliminarCorreoIdCopiaSeguridad(string id, array<correo, size> &correos){
    int indiceCorreoBuscado = -1;
    for(int i=0;i<size;i++){
        if(correos[i].getId() == id){
            indiceCorreoBuscado = i;
        }
    }
    if(indiceCorreoBuscado == -1)
        return false;
    for(int j=indiceCorreoBuscado;j<ultimoCorreo;j++){
        correos[j] = correos[j+1];
    }
    ultimoCorreo--;

   return true;
}

bool server::eliminarCorreoRemitente(string remitente, array<correo, size> &correos){
    int indiceCorreoBuscado = -1;
    for(int i=0;i<size;i++){
        if(correos[i].getRemitente() == remitente){
            indiceCorreoBuscado = i;
        }
    }
    if (indiceCorreoBuscado == -1)
        return false;
    for(int j=indiceCorreoBuscado;j<ultimoCorreo;j++){
        correos[j] = correos[j+1];
    }
    ultimoCorreo--;

   return true;
}

string server::cifradoCesar(string password, string palabra){
    string palabraCodificada="";

    const int largoPassword = password.length();
    char* passArray = new char(largoPassword);
    strcpy(passArray,password.c_str());
    int codificador = 0; //Entero que se utilizara para generar un digito 0-10 para metodo Cesar

    //Obtener numero codificador
    for(int i = 0 ; i<largoPassword; i++){
        codificador+=int(passArray[i]);
    }
    codificador = codificador % 10;
    const int largoPalabra = palabra.length();

    //char* palabraArray = new char(largoPalabra + 1);
    //strcpy(palabraArray,palabra.c_str());

    char palabraArray[palabra.length()+1];
    strcpy(palabraArray, palabra.c_str());

    for(int j=0;j<largoPalabra;j++){
        palabraCodificada = palabraCodificada + char(int(palabraArray[j])+ codificador );
    }

    //cout << "#Codificador cifrado: " << codificador << endl;
return palabraCodificada;
}

string server::descifradoCesar(string password, string palabra){
    string palabraDecodificada="";

    const int largoPassword = password.length();
    char* passArray = new char(largoPassword);
    strcpy(passArray,password.c_str());
    int codificador = 0; //Entero que se utilizara para generar un digito 0-10 para metodo Cesar

    //Obtener numero codificador
    for(int i = 0 ; i<largoPassword; i++){
        codificador+=int(passArray[i]);
    }
    codificador = codificador % 10;
    const int largoPalabra = palabra.length();

    //char* palabraArray = new char(largoPalabra + 1);
    //strcpy(palabraArray,palabra.c_str());

    char palabraArray[palabra.length()+1];
    strcpy(palabraArray, palabra.c_str());

    for(int j=0;j<largoPalabra;j++){
        palabraDecodificada = palabraDecodificada + char(int(palabraArray[j]) - codificador ); //Para descifrar solo hay que restar el decodificador
    }

    //cout << "#Codificador descifrado: " << codificador << endl;
return palabraDecodificada;
}
