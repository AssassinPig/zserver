#include "../std_inc.hpp"
#include "../boost_asio.h"
#include <boost/asio.hpp>

using namespace boost::asio;

int main()
try {
    io_service ios;
    ip::address addr;
     
    addr = addr.from_string("127.0.0.1");
    std::cout << "server starting."  << std::endl;
    ip::tcp::acceptor acceptor(ios, ip::tcp::endpoint(addr, 6688));
    std::cout << acceptor.local_endpoint().address() << ":" << acceptor.local_endpoint().port() << std::endl;
     
    while (true) {
        ip::tcp::socket sock(ios);
        acceptor.accept(sock);

        std::cout << "client: " << sock.remote_endpoint().address() << std::endl;

        sock.write_some(buffer("hello asio"));
    }
} catch (std::exception& e) {
    std::cout << e.what() << std::endl;
}

