#include "../std_inc.hpp"
#include "../boost_asio.h"
#include <boost/ref.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace boost::asio;

void client(io_service &ios)
    try {
        std::cout << "client starting." << std::endl;

        ip::tcp::socket sock(ios);
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 6688);
        sock.connect(ep);

        std::vector<char> str(100, 0);
        sock.read_some(buffer(str));
        std::cout << "receive from: " << sock.remote_endpoint().address() << std::endl;
        std::cout << &str[0] << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

class a_timer
{
    private:
        int count, count_max;
        boost::function<void()> f;
        boost::asio::deadline_timer t;

    public:
        template<typename F>
            a_timer(io_service &ios, int x, F func): f(func), count_max(x), count(0),
            t(ios, boost::posix_time::millisec(500)) {
                t.async_wait(boost::bind(&a_timer::call_func, this, boost::asio::placeholders::error));                
            }

        void call_func(const boost::system::error_code&)
        {
            if (count >= count_max) {
                return;
            }
            ++count;
            f();
            t.expires_at(t.expires_at() + boost::posix_time::millisec(500));
            t.async_wait(boost::bind(&a_timer::call_func, this, boost::asio::placeholders::error));
        }

};

int main()
{
    io_service ios;
    a_timer at(ios, 5, boost::bind(client, boost::ref(ios)));

    ios.run();
}
