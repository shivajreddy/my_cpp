#include <asio.hpp>
#include <iostream>

int main()
{
    try {
        asio::io_context io_context;

        asio::steady_timer timer(io_context, asio::chrono::seconds(3));
        timer.wait();

        std::cout << "Hello, ASIO! Timer expired after 3 seconds." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
