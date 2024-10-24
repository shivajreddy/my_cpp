#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/system_error.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>

using boost::asio::ip::tcp;

using std::cerr;
using std::cout;

int main(int argc, char *argv[]) {
  cout << "Sockets - Server\n";

  if (argc != 2) {
    std::cerr << "Usage: server port\n";
    return 1;
  }

  try {
    boost::asio::io_context io_context;

    tcp::endpoint tcp_endpoint = tcp::endpoint(tcp::v4(), std::atoi(argv[1]));

    tcp::acceptor acceptor(io_context, tcp_endpoint, std::atoi(argv[1]));

    cout << "Server is listening on port " << argv[1] << "\n";

    for (;;) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      cout << "Client connected: " << socket.remote_endpoint() << "\n";

      boost::system::error_code error;

      while (true) {
        char data[1024];
        size_t length = socket.read_some(boost::asio::buffer(data), error);
        if (error == boost::asio::error::eof) {
          cout << "Client disconnected\n";
          break;
        } else if (error) {
          throw boost::system::system_error(error);
        }
        // Echo back the received data
        boost::asio::write(socket, boost::asio::buffer(data, length));
      }
    }
  } catch (std::exception &e) {
    cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
