#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	//connection build
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	if(argc!=2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!");

	hServSock=socket(PF_INET, SOCK_STREAM, 0);
	if(hServSock==INVALID_SOCKET)
		ErrorHandling("socket() error");

		memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(atoi(argv[1]));

	if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
		ErrorHandling("bind() error");

	if(listen(hServSock, 5)==SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr=sizeof(clntAddr);
	hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if(hClntSock==INVALID_SOCKET)
		ErrorHandling("accept() error");

	// connection build finish. Let's send own message
	char message[]="Hello World!";

	send(hClntSock, message, sizeof(message), 0);
	/*
	char send_msg[1000];
	char rcv_msg[1000];
	int strLen;
	while(1){
		strLen=recv(hClntSock, rcv_msg, sizeof(rcv_msg)-1, 0);
		if(strLen==-1)
			ErrorHandling("read() error!");
		printf("Message from client: %s \n", rcv_msg);
		memset(send_msg,'\0', sizeof(send_msg));
		memset(rcv_msg, '\0', sizeof(rcv_msg));
		printf("보낼 메세지를 입력하세요 : ");
		scanf("%s",send_msg);
		send(hClntSock, send_msg, sizeof(send_msg),0);		
	}
	*/
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
