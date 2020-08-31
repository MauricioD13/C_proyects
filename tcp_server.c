#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
// For windows
#include <WinSock2.h>
#include <windows.h>
#include <winsock.h>
#include <ws2tcpip.h>
// For linux BSD
// #include <sys/socket.h>
// #include <netinet/in.h> -> Manipulacion de headers, tiene la informacion de los headers para la ip y el puerto del otro socket


int main(){

    const char *server_response="Hello";
    
    //Crear socket del servidor
    SOCKET server_socket;
    server_socket= socket(AF_INET,SOCK_STREAM,0);
    
    // Definir direccion del servidor
    struct sockaddr_in server_address;
    server_address.sin_family=  AF_INET;
    server_address.sin_port=    htons(8080);
    server_address.sin_addr.s_addr= INADDR_LOOPBACK;

    // Funcion bind -> Similar a connect en el client
    //Esta funcion hata el socket a una direccion y puerto para poder escuchar conexiones
    bind(server_socket,(struct sockaddr *) &server_address,sizeof(server_address));
    int client_socket=-1;
    while(client_socket==-1){
    listen(server_socket,5); //EL primer parametro es el socket y el segundo la cantidad de conexiones que se esperan
    
    //Aceptar conexion 
    
    client_socket=accept(server_socket,NULL,NULL);
    if(client_socket==0){
        printf("Hubo conexion");
    }
    //Funcion accept:
    //EL primer parametro es el socket que acepta conexion}
    //Segundo parametro es una estructura que se llena con la informacion del socket que se esta conectando
    //Tercer parametro informacion del client_socket

    //Enviar mensaje  
    send(client_socket,server_response,sizeof(server_response),0);
    //Funcion send
    //Primer parametro: socket al que queremos enviar
    //Segundo parametro: mensaje (apuntador)
    //Tercer parametro: banderas
    
    }
    //Cerrar el socket
    closesocket(server_socket);
    return 0;
}