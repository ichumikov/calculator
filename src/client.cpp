#include <boost/asio.hpp>
#include <iostream>
#include <string>

int main()
{
    boost::asio::io_context io;
    boost::asio::ip::tcp::socket socket(io);

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080);
    socket.connect(endpoint);

    std::string request = "{\"a\": 5, \"op\": \"+\", \"b\": 3}\n";
    boost::asio::write(socket, boost::asio::buffer(request));

    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, '\n');
    std::string response = boost::asio::buffer_cast<const char*>(buf.data());
    std::cout<< "Result: " << response;

    return 0;
}