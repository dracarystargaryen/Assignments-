#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#define MAX_LEN 200

using namespace std;

struct terminal
{
    int id;
    string user;
    int socket;
    thread thr;
}

//Threading to different clients
vector<terminal> clients;
int seed = 0;
mutex cout_mtx, clients_mtx;

void set_name(int id, char user[]);
void shared_print(string str, bool endLine);
int broadcast_message(string message, int sender_id);
int broadcast_message(int num, int sender_id);
void end_connection(int id);
void handle_client(int client_socket, int id);

int main(){
    //Calling for the socket
    int server_socket;
    if((server_socket=socket(AF_INET, SOCK_STREAM,0))==-1)
    {
        perror("socket: ");
        exit(-1);
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 0);

    if((bind(server_socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in))) == -1)
    {
        perror("bind error: ");
        exit(-1);
    }

    if((listen(server_socket)) == -1)
    {
        perror("listen error: ");
        exit(-1);
    }

    //Client-socket address
    struct sockaddr_in client;
    int client_socket;
    unsigned int len = sizeof(sockaddr_in);

    cout << "Network chat" << endl;

    while (1)
    {
        if ((client_socket = accept(server_socket,(struct sockaddr *)&client, &len)) == -1)
        {
            perror("accept error: ");
            exit(-1);
        }
        //Threading through the clients
        seed++;
        thread thr(handle_client, client_socket, seed);
        lock_guard<mutex> guard(clients_mtx);
        clients.push_back({seed, stirng("Anonymous"), client_socket,(move(t))});
    }

    for (int x = 0; x < clients.size(); x++)
    {
        if (clients[x].thr.joinable())
            clients[x].thr.join();
    }
    close(server_socket);
    return 0;
}

//Getting name of server
void set_name(int id, char user[])
{
    for (int x = 0; x < clietns.size(); x++)
    {
        if(clients[x].id == id)
        {
            clients[x].name = string(name);
        }
    }
}

void shared_print(string str, bool endLine = true)
{
    lock_guard<mutex> guard(cout_mtx);
    cout << str;
    if(endLine)
        cout << endl;
}

//Announce that the client recieved message
int broadcast_message(string message, int sender_id)
{
    char temp[MAX_LEN];
    strcpy(temp, message.c_str());
    for (int x = 0; x < clients.size(); x++)
    {
        if(clients[x].id != sender_id)
        {
            send(clients[x].socket, &num, sizeof(num),0);
        }
    }
}

//Ending connection
void end_connection(int id)
{
    for (int x = 0; x < clients.size(); x++)
    {
        if (clients[x].id == id)
        {
            lock_guard<mutex> guard(clients.mtx);
            clients[x].thr.detach();
            clients.erase(clients.begin() + x);
            close(clients[x].socket);
            break;
        }
    }
}

//Calling from client socket
void handle_client(int client_socket, int id)
{
    char name[MAX_LEN], str[MAX_LEN];
    recv(client_socket, name, sizeof(name), 0);
    set_name(id, name);
    string welcome_message = string(name) + string(" has joined the chat.");
    broadcast_message("#NULL", id);
    broadcast_message(id, id);
    broadcast_message(welcome_message,id);
    
    while (1)
    {
        int bytes_received = recv(client_socket, str, sizeof(str), 0);
        if(bytes_received <= 0)
            return;
        if(strcmp(str, "#exit") == 0)
        {
            string message = string(name) + string(" has left");
            broadcast_message("#NULL", id);
            broadcast_message(id, id);
            broadcast_message(message, id);
            end_connection(id);
            return;
        }
        broadcast_message(string(name),id);
        broadcast_message(id, id);
        broadcast_message(string(str),id);
    }

}
