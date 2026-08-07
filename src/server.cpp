#include "server.h"
#include "app.h"
#include <nlohmann/json.hpp>
#include <string>

namespace calculator {
    
    using boost::asio::ip::tcp;

    Server::Server(boost::asio::io_context& io, int port, std::atomic<bool>& running)
        : acceptor_(io, tcp::endpoint(tcp::v4(), port))
        , running_(running)
    {
        acceptor_.set_option(tcp::acceptor::reuse_address(true));        
    }

    void Server::run()
    {
        while (running_) {
            tcp::socket socket(acceptor_.get_executor());
            acceptor_.accept(socket);

            boost::asio::streambuf buf;
            boost::asio::read_until(socket, buf, '\n');
            std::string request = boost::asio::buffer_cast<const char*>(buf.data());

            Task task;
            auto j = nlohmann::json::parse(request);
            task.firstValue = j["a"];
            std::string op = j["op"];
            task.operation = op[0];
            if(j.contains("b")) {
                task.secondValue = j["b"];
            }

        Application::calculate(task);

        nlohmann::json result;
        result["result"] = task.result;
        std::string response = result.dump() + "\n";
        boost::asio::write(socket, boost::asio::buffer(response));
            
        }
    }

} //namespace calculator