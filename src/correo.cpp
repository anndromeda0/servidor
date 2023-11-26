#include "correo.h"

correo::correo()
{
    //ctor
}

correo::~correo()
{
    //dtor
}

//Setters
void correo::setId(string id){
    this -> id = id;
}

void correo::setFecha_envio(string fecha_envio){
    this -> fecha_envio = fecha_envio;
}

void correo::setHora_envio(string hora_envio){
    this -> hora_envio = hora_envio;
}

void correo::setRemitente(string remitente){
    this -> remitente = remitente;
}

void correo::setDestinatario(string destinatario){
    this -> destinatario = destinatario;
}

void correo::setCopia_carbon(string copia_carbon){
    this -> copia_carbon = copia_carbon;
}

void correo::setCopia_carbon_ciega(string copia_carbon_ciega){
    this -> copia_carbon_ciega = copia_carbon_ciega;
}

void correo::setAsunto(string asunto){
    this -> asunto = asunto;
}

void correo::setContenido(string contenido){
    this -> contenido = contenido;
}

//Getters
string correo::getId(){
    return id;
}

string correo::getFecha_envio(){
    return fecha_envio;
}

string correo::getHora_envio(){
    return hora_envio;
}

string correo::getRemitente(){
    return remitente;
}

string correo::getDestinatario(){
    return destinatario;
}

string correo::getCopia_carbon(){
    return copia_carbon;
}

string correo::getCopia_carbon_ciega(){
    return copia_carbon_ciega;
}

string correo::getAsunto(){
    return asunto;
}

string correo::getContenido(){
    return contenido;
}
