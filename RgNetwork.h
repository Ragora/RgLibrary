/*
    Faibanx Camera
    RgNetwork.h
    Copyright (c) 2016 Robert MacGregor
*/

#ifndef _INCLUDE_RGNETWORK_H_
#define _INCLUDE_RGNETWORK_H_

#define _WIN32_WINNT 0x0501 // Apparently required for this to compile correctly
#include <stdio.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>

// Include RgString
#include "RgString.h"

//! A struct containing a Win32 socket...
typedef struct
{
    SOCKET Socket;
} RgSocket;

//! Sets the currently active RgSocket
/** Sockets are created from the establish connection function
 \param Socket: The socket to use
*/
void RgSetSocket(RgSocket*);

//! Sends data through the currently active socket.
/** If there is no active socket, nothing happens.
 \param Data: The data to send.
*/
void RgSendData(char *Data);

//! Retrieves data from the currently active socket.
/** This function waits (halting execution) until data is returned.
 \return A pointer to a NULL terminated char* array with data.
*/
char *RgGetData(void);

//! Establishes a connection to a foreign host.
/** May crash if the host is invalid!!!!!!
 \param host: A pointer to a char* array specifying the host
 \param port: A pointer to a char* array specifying the port
 \return Returns an RgSocket if the connection is successful.
*/
RgSocket *RgEstablishConnection(char *host, char *port);

//! Closes the current connection.
/** Nothing happens if there is no socket set currently.
*/
void RgClose(void);
#endif
