#include "server.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "correo.h"
#include <cstdlib>
#include <ctime>

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

array<correo,1000> server::getCorreo(string path){
string texto;
ifstream archivoplano(path);
array<correo,1000> correos;
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




void server::guardarCorreo(array<correo,1000> &correos){
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

void server::generarCopiaSeguridad(array <correo, 1000> &correos){
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

array<int,1000> server::buscarCorreoRemitente(string remitente, array<correo,1000> correos){
    array<int,1000> indiceCorreos;
    for(int j=0;j<1000;j++){
        indiceCorreos[j] = -1;
    }
    int indice = 0;
    for(int i=0; i<1000;i++){
        if(correos[i].getRemitente() == remitente){
            indiceCorreos[indice] = i;
            indice++;
        }
    }
    return indiceCorreos;
}

array<int,1000> server::buscarCorreoId(string id, array<correo,1000> correos){
    array<int,1000> indiceCorreos;
    for(int j=0;j<1000;j++){
        indiceCorreos[j] = -1;
    }
    int indice = 0;
    for(int i=0; i<1000;i++){
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

bool server::eliminarCorreoId(string id, array<correo, 1000> &correos){
    int indiceCorreoBuscado = -1;
    for(int i=0;i<1000;i++){
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

bool server::eliminarCorreoIdCopiaSeguridad(string id, array<correo, 1000> &correos){
    int indiceCorreoBuscado = -1;
    for(int i=0;i<1000;i++){
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

bool server::eliminarCorreoRemitente(string remitente, array<correo, 1000> &correos){
    int indiceCorreoBuscado = -1;
    for(int i=0;i<1000;i++){
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
