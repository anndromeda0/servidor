#ifndef SERVER_H
#define SERVER_H
#include "correo.h"
#include <array>

using namespace std;

class server
{
    public:
        server();
        virtual ~server();
        array<correo,1000> getCorreo(string path);
        int getCantidadCorreos();
        array<int,1000> buscarCorreoRemitente(string remitente, array<correo,1000> correos);
        array<int,1000> buscarCorreoId(string id, array<correo,1000> correos);
        bool capturarCorreoNuevo(correo &correoNuevo);
        int getUltimoCorreo();
        int getTamanio();
        void guardarCorreo(array<correo,1000> &correos);
        void setUltimoCorreo(int ultimoCorreo);
        bool eliminarCorreoId(string id, array<correo,1000> &correos);
        bool eliminarCorreoRemitente(string remitente, array<correo,1000> &correos);
        void generarCopiaSeguridad(array<correo,1000> &correos);
        bool eliminarCorreoIdCopiaSeguridad(string id, array<correo,1000> &correos);


    protected:

    private:
        int ultimoCorreo;
        int tamanio;
};

#endif // SERVER_H
