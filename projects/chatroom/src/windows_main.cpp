#include <WS2tcpip.h>
#include <winsock2.h>

#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

// Entry point
int main() {
  cout << "socket programming" << endl;

  WSADATA wsaData;

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    cerr << "WSAStartup failed.\n";
    exit(1);
  }

  if ((LOBYTE(wsaData.wVersion) != 2) || HIBYTE(wsaData.wVersion != 2)) {
    cerr << "Version 2.2 is not available.\n";
    WSACleanup();
    exit(2);
  }

  return 0;
}
