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
        array<correo,size2> getCorreo(string path);
        int getCantidadCorreos();
        array<int,size2> buscarCorreoRemitente(string remitente, array<correo,size2> correos);
        array<int,size2> buscarCorreoId(string id, array<correo,size2> correos);
        bool capturarCorreoNuevo(correo &correoNuevo);
        int getUltimoCorreo();
        int getTamanio();
        void guardarCorreo(array<correo,size2> &correos);
        void setUltimoCorreo(int ultimoCorreo);
        bool eliminarCorreoId(string id, array<correo,size2> &correos);
        bool eliminarCorreoRemitente(string remitente, array<correo,size2> &correos);
        void generarCopiaSeguridad(array<correo,size2> &correos);
        void exportarCorreos(array<correo,size2> &correos);
        bool eliminarCorreoIdCopiaSeguridad(string id, array<correo,size2> &correos);


    protected:

    private:
        int ultimoCorreo;
        int tamanio;
};

#endif // SERVER_H
