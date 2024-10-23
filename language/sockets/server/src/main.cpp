#include <winsock2.h>
#include <WS2tcpip.h>

#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

/*
  Server Functions
  1. Initialize WSA - WSAStartup()
  2. Create a socket - socket()
  3. Bind the socket - bind()
  4. Listen on the socket - listen()
  5. Accept & establish a connection - accept(), connect()
  6. Send & Receive data - recv(), send(), recvfrom(), sendto()
  7. Disconnect - closesocket()

  Client Functions
  1. Initialize WSA - WSAStartup()
  2. Create a socket - socket()
  3. Connect to the server - connect()
  4. Send & Receive data - recv(), send(), recvfrom(), sendto()
  5. Disconnect - closesocket()
*/

// Server: 1. Initialize WSA
void initialize_wsa() {
  WSADATA wsaData;
  int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

  if (wsaResult != 0) {
    cerr << "WSAStartup failed: " << wsaResult << "\n";
    exit(1);
  }

  cout << "WSA initialized. Status: " << wsaData.szSystemStatus << "\n";

  if ((LOBYTE(wsaData.wVersion) != 2) || (HIBYTE(wsaData.wVersion) != 2)) {
    cerr << "Winsock version 2.2 is not available.\n";
    WSACleanup();
    exit(2);
  }
}

// Server 2: Create a socket, and return it
SOCKET create_socket() {
  SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (server_socket == INVALID_SOCKET) {
    cerr << "Error at socket(): " << WSAGetLastError() << "\n";
    WSACleanup();
    exit(2);
  }

  cout << "Socket created successfully.\n";
  return server_socket;
}

// Close a given socket and Cleanup WSA
void close_socket(SOCKET socket) {
  cout << "Closing the socket\n";
  closesocket(socket);
  WSACleanup();
}

// Bind the IPAddress & Port to the socket
void bind_ip_and_port(SOCKET socket, const string& ip_address, int port) {
  cout << "Binding Socket\n";

  sockaddr_in service;
  service.sin_family = AF_INET;

  // Convert IP address string to binary form
  int result = InetPton(AF_INET, ip_address.c_str(), &service.sin_addr.s_addr);
  if (result != 1) {
    cerr << "Error with InetPton: " << WSAGetLastError() << "\n";
    close_socket(socket);
    WSACleanup();
    exit(2);
  }

  // Set the port
  service.sin_port = htons(port);

  // Bind the socket to the address and port
  int bind_result = bind(socket, (SOCKADDR*)&service, sizeof(service));

  if (bind_result != 0) {
    cerr << "Error binding socket: " << WSAGetLastError() << "\n";
    close_socket(socket);
    WSACleanup();
    exit(2);
  }

  cout << "Binding Successful\n";
}

// Server 3: Listen for incoming connections
void listen_for_connections(SOCKET server_socket) {
  cout << "Listening on the socket...\n";
  if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
    cerr << "Listen Failed: " << WSAGetLastError() << "\n";
    close_socket(server_socket);
    WSACleanup();
    exit(3);
  }
}

// Server 4: Accept and handle connections
void accept_connections(SOCKET server_socket) {
  sockaddr_in client_addr;
  int client_addr_size = sizeof(client_addr);

  // Infinite loop to keep the server running
  while (true) {
    cout << "Waiting for a client to connect...\n";
    SOCKET client_socket =
        accept(server_socket, (sockaddr*)&client_addr, &client_addr_size);
    if (client_socket == INVALID_SOCKET) {
      cerr << "Error accepting connection: " << WSAGetLastError() << "\n";
      WSACleanup();
      exit(4);
    }

    // Convert client IP to string
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    cout << "Client connected from IP: " << client_ip << "\n";

    // Receive data from the client
    char recv_buf[512];
    int recv_result = recv(client_socket, recv_buf, sizeof(recv_buf), 0);

    if (recv_result > 0) {
      cout << "Received Message: " << string(recv_buf, 0, recv_result) << "\n";
      // Send response to the client
      string reply = "Message received";
      send(client_socket, reply.c_str(), reply.length(), 0);
    } else if (recv_result < 0) {
      cerr << "Receive failed: " << WSAGetLastError() << "\n";
    }

    // Close the client connection
    close_socket(client_socket);
  }
}

int main() {
  initialize_wsa();

  // Create the server socket
  SOCKET server_socket = create_socket();

  // Bind the socket to the IP address and port
  bind_ip_and_port(server_socket, "127.0.0.1", 8080);

  // Start listening for incoming connections
  listen_for_connections(server_socket);

  // Accept and handle connections indefinitely
  accept_connections(server_socket);

  // Clean up WSA resources
  WSACleanup();

  return 0;
}
