/*
    Faibanx Camera
    RgNetwork.c
    Copyright (c) 2016 Robert MacGregor
*/

#include "RgNetwork.h"

// Current Socket Set
RgSocket *CurrentSocket = 0;

//! Sets the currently active RgSocket
/** Sockets are created from the establish connection function
 \param Socket: The socket to use
*/
void RgSetSocket(RgSocket *Socket)
{
    CurrentSocket = Socket;
}

//! Sends data through the currently active socket.
/** If there is no active socket, nothing happens.
 \param Data: The data to send.
*/
void RgSendData(char *Data)
{
    if (CurrentSocket == 0)
        return;
    send(CurrentSocket->Socket, Data, strlen(Data), 0);
}

//! Retrieves data from the currently active socket.
/** This function waits (halting execution) until data is returned.
 \return A pointer to a NULL terminated char* array with data.
*/
char *RgGetData(void)
{
    if (CurrentSocket == 0)
        return 0;
    // Malloc some space for our response
    char *szResponse = (char*)malloc(10);
    memset(szResponse,0,10); // Write 0x00 to the whole thing
    int retVal = recv(CurrentSocket->Socket, szResponse, 9, 0);

    if(retVal == SOCKET_ERROR)
    {
        printf("SOCKET HERE\n");
        WSACleanup();
        return 0;
    }
    else
        return szResponse;
}

//! Establishes a connection to a foreign host.
/** May crash if the host is invalid!!!!!!
 \param host: A pointer to a char* array specifying the host
 \param port: A pointer to a char* array specifying the port
 \return Returns an RgSocket if the connection is successful.
*/
RgSocket *RgEstablishConnection(char *host, char *port)
{
    WSADATA wsaData;
    SOCKET tSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

    WSAStartup(MAKEWORD(2,2), &wsaData);

	if (getaddrinfo(host,port, &hints, &result) != 0)
    {
		WSACleanup();
		return 0;
	}

    ptr=result;
	tSocket = socket(ptr->ai_family,
			ptr->ai_socktype,
			ptr->ai_protocol);

	if (tSocket == INVALID_SOCKET) {
		freeaddrinfo(result);
		WSACleanup();
		return 0;
	}

    if (connect(tSocket,
		ptr->ai_addr,
		(int)ptr->ai_addrlen) == SOCKET_ERROR)
	{
		closesocket(tSocket);
		tSocket = INVALID_SOCKET;
		freeaddrinfo(result);
		WSACleanup();
		return 0;
	}
	else
        printf("Connection successfully established to %s:%s.\n",host,port);

    // Allocate our simple struct now
    RgSocket *Socket = (RgSocket*)malloc(sizeof(RgSocket));
    memset(Socket,0,sizeof(RgSocket));
    Socket->Socket = tSocket;
    return Socket;
}

//! Closes the current connection.
/** Nothing happens if there is no socket set currently.
*/
void RgClose(void)
{
    if(CurrentSocket == 0)
        return;
    closesocket(CurrentSocket->Socket);
    free(CurrentSocket);
    CurrentSocket = 0;
}
