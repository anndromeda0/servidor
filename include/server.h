#ifndef SERVER_H
#define SERVER_H
#include "correo.h"
#include <array>
#define size2 500

using namespace std;

class server
{
    public:
        server();
        virtual ~server();
        array<correo,size2> getCorreo(string path); //Obtiene los correos desde el archivo.txt
        int getCantidadCorreos(); //Obtiene el numero de cuantos correos almacenados hay
        array<int,size2> buscarCorreoRemitente(string remitente, array<correo,size2> correos); //Busca x Remitente en todos los correos cargados
        array<int,size2> buscarCorreoId(string id, array<correo,size2> correos); //Busca x ID en todos los correos cargados
        bool capturarCorreoNuevo(correo &correoNuevo); //Captura de correo nuevo
        int getUltimoCorreo(); //Obtener la posicion del ultimo correo
        int getTamanio();
        void guardarCorreo(array<correo,size2> &correos); //Almacena los correos de la estructura en el archivo.txt
        void setUltimoCorreo(int ultimoCorreo); //establece la posicion del ultimo correo
        bool eliminarCorreoId(string id, array<correo,size2> &correos); //Elimina correo x id
        bool eliminarCorreoRemitente(string remitente, array<correo,size2> &correos); //Elimina correo x remitente
        void generarCopiaSeguridad(array<correo,size2> &correos); //Genera copia de seguridad
        void generarCopiaSeguridadCifrada(array<correo,size2> &correos, string password);
        void generarCopiaSeguridadDescifrada(array<correo,size2> &correos, string password);
        void exportarCorreos(array<correo,size2> &correos); //Exporta correos en fecha.txt
        bool eliminarCorreoIdCopiaSeguridad(string id, array<correo,size2> &correos); //elimina correo x id en copia de seguridad
        string cifradoCesar(string password, string palabra); //Funcion para cifrar informacion de todos los correos
        string descifradoCesar(string password, string palabra); //Descifrado por metodo cesar mediante una clave

    protected:

    private:
        int ultimoCorreo;
        int tamanio;
};

#endif // SERVER_H
