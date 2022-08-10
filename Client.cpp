#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <signal.h>
#include <mutex>
#define MAX_LEN 200


using namespace std;

bool exit_flag = false;
thread t_send, t_recv;
int client_socket;

void catch_ctrl_c(int signal);
int eraseText(int cnt);
void send_message(int client_socket);
void recv_message(int client_socket);

int main()
{
    //Client socket call function
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket: ");
        exit(-1);
    }
    struct socaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(10000);
    client.sin_addr.s_addr = INADDR_ANY;
    bzero(&client.sin_zero, 0);

    if((connect(client_socket,(struct sockaddr *)&client, sizeof(struct sockaddr_in))) == -1)
    {
        perror("connect: ");
        exit(-1);
    }

    //Prompting user for their name
    signal(SIGNIT, catch_ctrl_c);
    char name(MAX_LEN);
    cout << "Enter your name: ";
    cin.getline(name, MAX_LEN);
    send(client_socket, name, sizeof(name), 0);

    thread thr1(send_message, client_socket);
    thread thr2(recv_message, client_socket);

    t_send = move(thr1);
    t_recv = move(thr2);

    if(t_send.joinable())
        t_send.join();
    if(t_recv.joinable())
        r_recv.join();

    return 0;

}


//Using CTRL C to stop the connection
void catch_ctrl_c(int signal)
{
    char str[MAX_LEN] = "#exit";
    send(client_socket, str, sizeof(str), 0);
    exit_flag = true;
    t_send.detach();
    t_recv.detach();
    close(client_socket);
    exit(signal);
}

//Erasing text from prompt
int textErase(int cnt)
{
    char backspace = 0;
    for (int x = 0; x < cnt; x++)
    {
        cout << backspace;
    }
}

//Sending message
void send_message(int client_socket)
{
    while(1)
    {
        cout << "You :" << endl;
        char str[MAX_LEN];
        cin.getline(str, MAX_LINE);
        send(client_socket, str, sizeof(str), 0);
        if(strcmp(str, "#exit") == 0)
        {
            exit_flat = true;
            t_recv.detach();
            close(client_socket);
            return;
        }
    }
}

//Recieving messages
void recv_message(int client_socket)
{
    while(1)
    {
        if(exit_flag)
            return;
        char name[MAX_LEN], str[MAX_LEN];
        int bytes_received = recv(client_socket, name, sizeof(name),0);
        if(bytes_received <= 0)
            continue;
        recv(client_socket, str, sizeof(str), 0);
        textErase(6);
        if(strcmp(name, "#NULL") != 0)
            cout << name << "You: " << endl;
        else
            cout << str << endl;
        cout << "You: " << endl;
        fflush(stdout);
    }
}
