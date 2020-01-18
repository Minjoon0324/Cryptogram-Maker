#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	//connection build, 입력된 IP로 연결 시도 
	char rcv_msg[1000];
	int strLen;
	if(argc!=3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) !=0)
		ErrorHandling("WSAStartup() errer!");

	hSocket=socket(PF_INET, SOCK_STREAM, 0);
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("hSocketet() error!");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=inet_addr(argv[1]);
	servAddr.sin_port=htons(atoi(argv[2]));

	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("connect() error!");


	// connection build finish, when receive message recv function activate 
	strLen=recv(hSocket, rcv_msg, sizeof(rcv_msg)-1, 0);
	if(strLen==-1)
		ErrorHandling("read() error!");
	printf("Message from server: %s \n", rcv_msg);
	/*
	char send_msg[1000];
	while(1){
		memset(send_msg,'\0', sizeof(send_msg));
		memset(rcv_msg, '\0', sizeof(rcv_msg));
		printf("보낼 메세지를입력하세요:");

		scanf("%s",send_msg);
		send(hSocket, send_msg, sizeof(send_msg),0);
		strLen=recv(hSocket, rcv_msg, sizeof(rcv_msg)-1, 0);
		if(strLen==-1)
			ErrorHandling("read() error!");
		printf("Message from server: %s \n", rcv_msg);		
	}
	*/
	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
