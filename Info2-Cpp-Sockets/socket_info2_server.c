#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
 
//the thread function
void *connection_handler(void *);
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , Tamanio_sockaddr;
    struct sockaddr_in server , client;
     
    //Creacion del socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        perror("No se puede crear el socket:");
    }
    puts("Socket ok");
     
    //Se prepara la estructura sockaddr_in
    server.sin_family = AF_INET;                        //A pair (host, port) is used for the AF_INET address family, where host is a string representing either a hostname in Internet domain notation like 'daring.cwi.nl' or an IPv4 address like '100.50.200.5', and port is an integer. Used to communicate between processes over the Internet.
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons( 8080 );        // Puerto
     
    //Bind
    if( bind(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Bind Error");
        return 1;
    }
    puts("Bind ok");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Esperando conexiones entrantes...");
    
    // Vamos a guardar en 
    Tamanio_sockaddr = sizeof(struct sockaddr_in);
         
    pthread_t thread_id;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&Tamanio_sockaddr)) )
    {
        puts("Conexion aceptada");
         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            puts("Thread Error");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Thread Nuevo Ok");
    }
     
    if (client_sock < 0)
    {
        puts("Accept Error");
        return 1;
    }
     
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
char Html[] = "<!DOCTYPE html><html><body><h2>HTML Forms</h2><form action=\"/action_page.php\"><label for=\"fname\">First name:</label><br><input type=\"text\" id=\"fname\" name=\"fname\" value=\"John\"><br><label for=\"lname\">Last name:</label><br><input type=\"text\" id=\"lname\" name=\"lname\" value=\"Doe\"><br><br><input type=\"submit\" value=\"Submit\"></form><p>If you click the \"Submit\" button, the form-data will be sent to a page called \"/action_page.php\".</p></body></html>";

char Html2[] = "<!DOCTYPE html><html><body><p>Click the button to get your coordinates %s.</p><button onclick=\"getLocation()\">Try It</button><p id=\"demo\"></p><script>var x = document.getElementById(\"demo\");function getLocation() {  if (navigator.geolocation) {    navigator.geolocation.getCurrentPosition(showPosition);  } else {     x.innerHTML = \"Geolocation is not supported by this browser.\";  }}function showPosition(position) {  x.innerHTML = \"Latitude: \" + position.coords.latitude +   \"<br>Longitude: \" + position.coords.longitude;}</script></body></html>";

char reply[] = 
{
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"\r\n"
};

void *connection_handler(void *socket_desc)
{
    char Temporal[2000];

    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
     
           //usleep(100);
    //Send some messages to the client
    //message = "Greetings! I am your connection handler\n";
    write(sock , reply , strlen(reply));
     
    usleep(1000);
    sprintf(Temporal, Html, "Gustavo");
    write(sock , Temporal , strlen(Temporal));

    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
       
        //end of string marker
		client_message[read_size] = '\0';
		
		puts(client_message);
		
		//Send the message back to client
        //write(sock , client_message , strlen(client_message));
		
		//clear the message buffer
		//memset(client_message, 0, 2000);
                close(sock);
                return 0;
    }
     
    if(read_size == 0)
    {
        puts("Cliente desconectado");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv Error");
    }
         
    return 0;
} 
