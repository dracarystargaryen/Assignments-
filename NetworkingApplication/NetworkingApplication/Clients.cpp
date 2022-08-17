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
#include "Server.cpp"
#include <iostream>
#define MAX_LEN 200
#define NUM_COLORS 6

using namespace std;

bool exit_flat = false;
thread thr_send, thr_recv;
int client_socket;
string def_color = "\033[0m";
string color[] = { "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m" };

void catch_ctrl_c(int signal);
string color(int code);
int deleteText(int cnt);
void send(int client_socket);
void recv(int client_socket);

int main()
{
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket: ");
		exit(-1);
	}

	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(10000);
	client.sin_addr.s_addr = INADDR_ANY;
	bzero(&client.sin_zero, 0);

	if ((connect(client_socket, (struct sockaddr*)&client, sizeof(struct sockaddr_in))) == -1)
	{
		perror("Connect: ");
		exit(-1);
	}

	signal(SIGINT, catch_ctrl_c);
	char name[MAX_LEN];
	cout << "Enter your name: ";
	cin.getLine(name, MAX_LEN);
	send(client_socket, name, sizeof(name), 0);

	cout << colors[NUM_COLORS - 1] << "\n\t --------Welcome to the Chat Room-------" << endl << def_color;

	thread thr1(send, client_socket);
	thread thr2(recv, client_socket);

	thr_send = move(thr1);
	thr_recv = move(thr2);

	thr_send = move(thr1);
	thr_recv = move(thr2);

	if (thr_send.joinable())
		thr_send.join();
	if (thr_recv.joinable())
		thr_recv.join();

	return 0;
}

void catch_ctrl_c(int signal)
{
	char str[MAX_LEN] = "#exit";
	send(client_socket, str, sizeof(str), 0);
	exit_flag = true;
	thr_send.detach();
	thr_recv.detach();
	close(client_socket);
	exit(signal);

}

string color(int code)
{
	return colors[code % NUM_COLORS];

}

int deleteText(int cont)
{
	char back_space = 8;
	for (int x = 0; x < cont; x++)
	{
		cout << back_space;
	}
}

void send(int client)
{
	while (1)
	{
		cout << colors[1] << "You : " << def_col;
		char str[MAX_LEN];
		cin.getline(str, MAX_LEN);
		send(client_socket, str, sizeof(str), 0);
		if (strcmp(str, "#exit") == 0)
		{
			exit_flag = true;
			thr_recv.detach();
			close(client_socket);
			return;
		}
	}
}

void recv(int client_socket)
{
	while (1)
	{
		if (exit_flag)
			return;
		char name[MAX_LEN], str[MAX_LEN];
		int color_code;
		int bytes = recv(client_socket, name, sizeof(name), 0);
		if (bytes <= 0)
			continue;
		recv(client_socket, &color_code, sizeof(color_code), 0);
		recv(client_socket, str, sizeof(str), 0);
		deleteText(6);
		if (strcmp(name, "#NULL") != 0)
			cout << color(color_code) << str << endl;

		cout << colors[1] << "You: " << def_col;
		fflush(stdout);
	}
}