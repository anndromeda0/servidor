#include <iostream>
#include "correo.h"
#include "server.h"
#include <array>
#define size 1000

using namespace std;

int main()
{
    server servidorCorreo;
    //int tamanio = servidorCorreo.getTamanio();
    array<correo,size> correos = servidorCorreo.getCorreo("archivo.txt"); //Arreglo de correos
    array<int,size> busquedaRemitente; //Arreglo de correos buscados x remitente
    array<int,size> busquedaId; //Arreglo de correos buscados x remitente
    array<int,size> busquedaIds; //Arreglo de correos buscados x remitente

    //int registros = servidorCorreo.getCantidadCorreos();
    int menu = 0;
    cout << "cantidad de registros : " << servidorCorreo.getUltimoCorreo() << endl;

    do{
        cout << endl <<"Bienvenido a tu correo electronico!!" <<endl;
        cout << "Selecciona una opcion: "<< endl;
        cout << "1) Ver todos los correos." << endl;
        cout << "2) Buscar correos por remitente." << endl;
        cout << "3) Buscar correos por id." << endl;
        cout << "4) Modificar correo por id." << endl;
        cout << "5) Modificar correo por remitente." <<endl;
        cout << "6) Insertar Correo Nuevo." <<endl;
        cout << "7) Borrar por ID." << endl;
        cout << "8) Borrar por Remitente."<< endl;
        cout << "9) Crear copia de seguridad." << endl;
        cout << "10) Exportar correos electronicos." << endl;
        cout << "11) Importar correos desde archivo csv." << endl;
        cout << "12) Eliminar correo de copia de seguridad." << endl;
        cout << "20) Salir" << endl;
        cin >> menu;
        //system("cls");
        switch(menu){

                case 1:{ //Ver Correos
                    correos = servidorCorreo.getCorreo("archivo.txt");
                    system("cls");
                    cout <<endl<<"Bandeja de entrada:"<<endl <<endl;
                    cout <<"--------------------------------------------------" << endl;
                for(int i= 0 ; i<servidorCorreo.getUltimoCorreo(); i++){
                    cout << "Correo: " <<i <<endl;
                    cout << "ID: "<<correos[i].getId()<< endl;
                    cout << "Fecha de envio: "<<correos[i].getFecha_envio()<< endl;
                    cout << "Hora de envio: "<<correos[i].getHora_envio()<< endl;
                    cout << "Remitente: "<<correos[i].getRemitente()<< endl;
                    cout << "Destinatario: "<<correos[i].getDestinatario()<< endl;
                    cout << "CC: "<<correos[i].getCopia_carbon()<< endl;
                    cout << "BCC: "<<correos[i].getCopia_carbon_ciega()<< endl;
                    cout << "Asunto: "<<correos[i].getAsunto()<< endl;
                    cout << "Contenido: "<<correos[i].getContenido()<< endl<<endl;
                    cout <<"--------------------------------------------------" << endl;
                }
                }
                break;
                case 2:{ //Buscar x Remitente
                    system("cls");
                string remitente = "";
                cout <<"Ingrese el remitente que quiere buscar entre sus correos:"<< endl;
                cin >> remitente;
                system("cls");
                cout << "Correos encontrados con el remitente: "<<remitente<<":"<<endl << endl;
                cout <<"--------------------------------------------------" << endl;
                busquedaRemitente = servidorCorreo.buscarCorreoRemitente(remitente,correos);
                for(int i=0;i<servidorCorreo.getUltimoCorreo();i++){
                    if(busquedaRemitente[i] != -1){
                        cout << "ID: "<<correos[busquedaRemitente[i]].getId()<< endl;
                        cout << "Fecha de envio: "<<correos[busquedaRemitente[i]].getFecha_envio()<< endl;
                        cout << "Hora de envio: "<<correos[busquedaRemitente[i]].getHora_envio()<< endl;
                        cout << "Remitente: "<<correos[busquedaRemitente[i]].getRemitente()<< endl;
                        cout << "Destinatario: "<<correos[busquedaRemitente[i]].getDestinatario()<< endl;
                        cout << "CC: "<<correos[busquedaRemitente[i]].getCopia_carbon()<< endl;
                        cout << "BCC: "<<correos[busquedaRemitente[i]].getCopia_carbon_ciega()<< endl;
                        cout << "Asunto: "<<correos[busquedaRemitente[i]].getAsunto()<< endl;
                        cout << "Contenido: "<<correos[busquedaRemitente[i]].getContenido()<< endl<<endl;
                    }
                }
                cout <<"--------------------------------------------------" << endl;
                }
                break;
                case 3:{ //Buscar x ID
                    system("cls");
                string id = "";
                cout <<"Ingrese el id que quiere buscar entre sus correos:"<< endl;
                cin >> id;
                system("cls");
                cout << "Correos encontrados con el id: "<<id<<":"<<endl << endl;
                cout <<"--------------------------------------------------" << endl;
                busquedaId = servidorCorreo.buscarCorreoId(id,correos);
                for(int i=0;i<servidorCorreo.getUltimoCorreo();i++){
                    if(busquedaId[i] != -1){
                        cout << "ID: "<<correos[busquedaId[i]].getId()<< endl;
                        cout << "Fecha de envio: "<<correos[busquedaId[i]].getFecha_envio()<< endl;
                        cout << "Hora de envio: "<<correos[busquedaId[i]].getHora_envio()<< endl;
                        cout << "Remitente: "<<correos[busquedaId[i]].getRemitente()<< endl;
                        cout << "Destinatario: "<<correos[busquedaId[i]].getDestinatario()<< endl;
                        cout << "CC: "<<correos[busquedaId[i]].getCopia_carbon()<< endl;
                        cout << "BCC: "<<correos[busquedaId[i]].getCopia_carbon_ciega()<< endl;
                        cout << "Asunto: "<<correos[busquedaId[i]].getAsunto()<< endl;
                        cout << "Contenido: "<<correos[busquedaId[i]].getContenido()<< endl<<endl;
                    }
                }
                cout <<"--------------------------------------------------" << endl;

                }
                break;
                case 4:{ //Modificar x ID

                    string id = "";
                    correo correoModificado;
                    int posicionCorreo = -1;
                    cout << "Ingrese el ID del correo que quiere modificar.";
                    cin >> id;
                    busquedaId = servidorCorreo.buscarCorreoId(id,correos);
                    system("cls");
                    servidorCorreo.capturarCorreoNuevo(correoModificado); //Capturar datos nuevos

                    for(int i=0;i<100;i++){
                        if(busquedaId[i] != -1){
                            posicionCorreo = busquedaId[i];
                            cout << posicionCorreo <<endl;
                        }
                    }
                    if(posicionCorreo != -1){
                        correos[posicionCorreo] = correoModificado;
                    }
                    servidorCorreo.guardarCorreo(correos);
                    cout << "Correos: " << servidorCorreo.getUltimoCorreo();
                }
                break;
                case 5:{ //Modificar x Remitente

                    string remitente = "";
                    correo correoModificado;
                    int posicionCorreo = -1;
                    cout << "Ingrese el remitente del correo que quiere modificar.";
                    cin >> remitente;
                    busquedaRemitente = servidorCorreo.buscarCorreoRemitente(remitente,correos);
                    system("cls");
                    servidorCorreo.capturarCorreoNuevo(correoModificado); //Capturar datos nuevos

                    for(int i=0;i<100;i++){
                        if(busquedaRemitente[i] != -1){
                            posicionCorreo = busquedaRemitente[i];
                            cout << posicionCorreo <<endl;
                        }
                    }
                    if(posicionCorreo != -1){
                        correos[posicionCorreo] = correoModificado;
                    }
                    servidorCorreo.guardarCorreo(correos);

                }
                break;
                case 6:{ //Insertar Correo Nuevo
                    correo correoNuevo;
                    servidorCorreo.capturarCorreoNuevo(correoNuevo);
                    correos[servidorCorreo.getUltimoCorreo()] = correoNuevo;
                    //cout << servidorCorreo.getUltimoCorreo();
                    int aumentocontadorcorreo = servidorCorreo.getUltimoCorreo();
                    aumentocontadorcorreo++;
                    servidorCorreo.setUltimoCorreo(aumentocontadorcorreo);
                    servidorCorreo.guardarCorreo(correos);
                    }
                break;
                case 7:{ //Eliminar x ID
                    system("cls");
                    string id = "";
                    bool verificacionEliminacion;
                    cout << "Ingrese el ID del correo que quiere eliminar." << endl;
                    cin >> id;
                    system("cls");
                    verificacionEliminacion = servidorCorreo.eliminarCorreoId(id,correos);

                    if(verificacionEliminacion){
                        servidorCorreo.guardarCorreo(correos);
                        cout << "Correos Eliminado!" << endl;
                    }else{
                        cout << "No hubo correo que eliminar!";
                    }
                }
                break;
                case 8:{ //Eliminar x Remitente
                    system("cls");
                    string remitente = "";
                    bool verificacionEliminacion;
                    cout << "Ingrese el Remitente del correo que quiere eliminar." << endl;
                    cin >> remitente;
                    system("cls");
                    verificacionEliminacion = servidorCorreo.eliminarCorreoRemitente(remitente,correos);

                    if(verificacionEliminacion){
                        servidorCorreo.guardarCorreo(correos);
                        cout << "Correo Eliminado!" << endl;
                    }else{
                        cout <<"No hubo correo que eliminar" << endl;
                    }

                }
                break;
                case 9:{ //Copia de Seguridad
                    system("cls");
                    servidorCorreo.generarCopiaSeguridad(correos);
                    cout << "Copia de seguridad generada"  << endl;
                }
                break;
                case 10:{ //Exportar Correos
                    system("cls");
                    servidorCorreo.exportarCorreos(correos);
                    cout << "Los correos se han exportado en formato csv." << endl;
                }
                break;
                case 11:{ //Importar Correos csv
                }
                break;
                case 12:{ //Eliminar Correo de copia de seguridad
                        system("cls");
                        string id;
                        bool verificacionEliminacion;
                        cout << "Ingrese el ID del correo que quiere eliminar de la copia de seguridad." << endl;
                        cin >> id;
                        //correos = servidorCorreo.getCorreo("CopiaSeguridad.txt");
                        system("cls");
                        //verificacionEliminacion = servidorCorreo.eliminarCorreoId(id,correos);


                        cout << "Correo eliminado de copia de seguridad" << endl;
                    }
                break;
                case 20:{ //Salir
                    cout << "Adios que tengas buen dia!" << endl;
                    return 0;
                }
                break;
                default:
                    cout << "Opcion no disponible!!" <<endl;
                break;
        }

    }while(menu !=20);


}

