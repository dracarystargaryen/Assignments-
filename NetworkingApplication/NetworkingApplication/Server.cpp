#include <iostream>
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
#define NUM_COLORS 6

using namespace std;

struct terminal
{
	int ID;
	string name;
	int socket;
	thread thr;
};

vector<terminal> clients;
string def_col = "\033[0m";
string colors[] = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m","\033[36m" };
int seeding = 0;
mutex cout_mt, clients_mtx;

string color(int code);
void set_name(int ID, char name[]);
void shared_message(string str, bool endMessage);
int broadcast(string message, int send_id);
int broadcast(int num, int send_id);
void connectionEnd(int ID);
void clientHandle(int client_socket, int ID);

int main()
{
	int server_socket;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket: ");
		exit(-1);
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 0);

	if ((bind(server_socket, (struct sockaddr*)&server, sizeof(struct sockaddr_in))) == -1)
	{
		perror("Bind error: ");
		exit(-1);
	}

	if ((listen(server_socket, 8)) == -1)
	{
		perror("Listen error: ");
		exit(-1);
	}

	struct sockaddr_in client;
	int client_socket;
	unsigned int len = sizeof(sockaddr_in);

	cout << color[NUM_COLORS - 1] << "\n\t -------Welcome to the Chat Room-------    " << endl << def_col;

	while (1)
	{
		if ((client_socket = accept(server_socket, (struct sockaddr*)&client, &len)) == -1)
		{
			perror("Accept error: ");
			exit(-1);
		}
		seed++;
		thread thr(handle_client, client_socket, seed);
		lock_guard<mutex> guard(clients_mtx);
		clients.push_back({ seed, string("Anonymous"), client_socket,(move(t))});
	}

	for (int x = 0; x < clients.size(); x++)
	{
		if (clients[x].thr.joinable())
			clients[x].thr.join();
	}

	close(server_socket);
	return 0;
}

string color(int code)
{
	return colors[code % NUM_COLORS];
}

void set_name(int ID, char name[])
{
	for (int x = 0; x < clients.size(); x++)
	{
		if (clients[x].ID == ID)
		{
			clients[x].name = string(name);
		}
	}
}

void shared_message(string str, bool endMessage = true)
{
	lock_guard<mutex> guard(cout_mtx);
	cout << str;
	if (endMessage)
		cout << endl;
}

int broadcast(string message, int send)
{
	char temp(MAX_LEN);
	strcpy(temp, message.c_str());
	for (int x = 0; x < clients.size(); x++)
	{
		if (clients[x].id != sender_ID)
		{
			send(clients[x].socket, temp, sizeof(temp), 0);
		}
	}
}

int broadcast(int num, int send)
{
	for (int x = 0; x < clients.size(); x++)
	{
		if (clients[x].ID != sender_ID)
		{
			send(clients[x].socket, &num, sizeof(num), 0);
		}
	}
}

void connectionEnd(int ID)
{
	for (int x = 0; x < clients.size(); x++)
	{
		if (clients[x].ID == ID)
		{
			lock_guard<mutex> guard(clients_mtx);
			clients[x].thr.detach();
			clients.erase(clients.begin() + x);
			close(clients[x].socket);
			break;

		}
	}
}

void clientHandle(int client_socket, int ID)
{
	char name[MAX_LEN], str[MAX_LEN];
	recv(client_socket, name, sizeof(name), 0);
	set_name(ID, name);

	string welcome = string(name) + string(" has joined the chat.");
	broadcast("NULL", ID);
	broadcast(ID, ID);
	broadcast(welcome, ID);
	shared_message(color(ID) + welcome + def_col);

	while (1)
	{
		int bytes = recv(client_socket, str, sizeof(str), 0);
		if (bytes <= 0)
			return;
		if (strcmp(str, "#exit") == 0)
		{
			string message = string(name) + string(" has left the chat.");
			broadcast("#NULL", ID);
			broadcast(ID, ID);
			broadcast(message, ID);
			shared_print(color(ID) + message + def_color);
			end_broadcast(ID);
		}
		broadcast(string(name), ID);
		broadcast(ID, ID);
		broadcast(string(str), ID);
		shared_print(color(ID) + name + " : " + def_col + str);
	}
}