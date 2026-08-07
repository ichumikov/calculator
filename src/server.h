#pragma once
#include <atomic>
#include <boost/asio.hpp>

namespace calculator {

    class Server {
    public:
        Server(boost::asio::io_context& io, int port, std::atomic<bool>& running);
        void run();

    private:
        boost::asio::ip::tcp::acceptor acceptor_;
        std::atomic<bool>& running_;
    };
} //namespace calculator