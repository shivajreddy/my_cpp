#pragma once

// Bind the IPAddress & Port to the socket
void bind_ip_and_port(SOCKET* socket) {
  cout << "Binding socket\n";

  const sockaddr* sockAddrName{
      AF_INET,

  };

  int bind_result = bind(*socket, sockAddrName, 8);

  if (bind_result != 0) {
    cerr << "Error binding socket\n";
    exit(2);
  }
}
