#ifndef CORREO_H
#define CORREO_H
#include <string>

using namespace std;

class correo
{
    public:
        correo();
        virtual ~correo();

        //setters
        void setId(string id);
        void setFecha_envio(string fecha_envio);
        void setHora_envio(string hora_envio);
        void setRemitente(string remitente);
        void setDestinatario(string destinatario);
        void setCopia_carbon(string copia_carbon);
        void setCopia_carbon_ciega(string copia_carbon_ciega);
        void setAsunto(string asunto);
        void setContenido(string contenido);

        //Getters
        string getId();
        string getFecha_envio();
        string getHora_envio();
        string getRemitente();
        string getDestinatario();
        string getCopia_carbon();
        string getCopia_carbon_ciega();
        string getAsunto();
        string getContenido();

    protected:

    private:
        string id;
        string fecha_envio;
        string hora_envio;
        string remitente;
        string destinatario;
        string copia_carbon;
        string copia_carbon_ciega;
        string asunto;
        string contenido;

};

#endif // CORREO_H
