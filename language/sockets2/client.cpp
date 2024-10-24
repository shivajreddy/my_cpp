// client.cpp
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: client <host> <port>\n";
    return 1;
  }

  try {
    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(argv[1], argv[2]);
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    std::cout << "Connected to server. Type messages to send:\n";

    for (std::string line; std::getline(std::cin, line);) {
      boost::asio::write(socket, boost::asio::buffer(line + "\n"));

      char reply[1024];
      boost::system::error_code error;
      size_t reply_length = socket.read_some(boost::asio::buffer(reply), error);

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout << "Reply: ";
      std::cout.write(reply, reply_length);
      std::cout << "\n";
    }
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
