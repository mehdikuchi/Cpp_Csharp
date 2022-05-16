//#define timer_sync 0
//#define timer_async 1
//#define timer_async2 2 // counter timer
//#define timer_async3 3 //counter timer with class
//#define timer_async4 4   //two timers with different callback synchronized using strand
//#define daytime1 5   // Client side of a day time server
#ifdef timer_sync
#endif
#ifdef timer_async
#    include <iostream>
#    include <boost/asio.hpp>

void print(const boost::system::error_code & /*e*/) { std::cout << "Hello, world!" << std::endl; }

int main() {
    boost::asio::io_context io;

    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    boost::asio::steady_timer t2(io, boost::asio::chrono::seconds(10)); // you can bind as many object as you want to the io_context object
    t.async_wait(&print);
    t2.async_wait(&print);
    io.run();

    return 0;
}
#endif
#ifdef timer_async2
#    include <iostream>
#    include <boost/asio.hpp>

void print(const boost::system::error_code & /*e*/, boost::asio::steady_timer *timer, int *count) { //
    std::cout << "Hello, world! number:" << *count << std::endl;
    ++(*count);
    timer->expires_after(boost::asio::chrono::seconds(1));
    if (*count < 6)
        timer->async_wait(
            std::bind(print, std::placeholders::_1, timer, count)); //while there is task to do, the run method of the context will not return
    else
        return;
    return;
}

int main() {
    boost::asio::io_context   io;
    int                       number { 0 };
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.async_wait(std::bind(print, std::placeholders::_1, &t, &number));
    io.run();

    return 0;
}
#endif

#ifdef timer_async3
#    include <iostream>
#    include <boost/asio.hpp>
#    include <boost/bind/bind.hpp>

class printer {
public:
    printer(boost::asio::io_context &io)
        : timer_(io, boost::asio::chrono::seconds(1))
        , count_(0) {
        timer_.async_wait(boost::bind(&printer::print, this));
    }

    ~printer() { std::cout << "Final count is " << count_ << std::endl; }

    void print() {
        if (count_ < 5) {
            std::cout << count_ << std::endl;
            ++count_;

            timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this));
        }
    }

private:
    boost::asio::steady_timer timer_;
    int                       count_;
};

int main() {
    boost::asio::io_context io;
    printer                 p(io);
    io.run();

    return 0;
}
#endif

#ifdef timer_async4
#    include <iostream>
#    include <boost/asio.hpp>
#    include <boost/thread/thread.hpp>
#    include <boost/bind/bind.hpp>

class printer {
public:
    printer(boost::asio::io_context &io)
        : strand_(boost::asio::make_strand(io))
        , timer1_(io, boost::asio::chrono::seconds(1))
        , timer2_(io, boost::asio::chrono::seconds(1))
        , count_(0) {
        timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1, this)));

        timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
    }

    ~printer() { std::cout << "Final count is " << count_ << std::endl; }

    void print1() {
        if (count_ < 10) {
            std::cout << "Timer 1: " << count_ << std::endl;
            ++count_;

            timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

            timer1_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print1, this)));
        }
    }

    void print2() {
        if (count_ < 10) {
            std::cout << "Timer 2: " << count_ << std::endl;
            ++count_;

            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

            timer2_.async_wait(boost::asio::bind_executor(strand_, boost::bind(&printer::print2, this)));
        }
    }

private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer                                   timer1_;
    boost::asio::steady_timer                                   timer2_;
    int                                                         count_;
};

int main() {
    boost::asio::io_context io;
    printer                 p(io);
    boost::thread           t(boost::bind(&boost::asio::io_context::run, &io));
    io.run();
    t.join();

    return 0;
}
#endif

#ifdef daytime1
#    include <iostream>
#    include <boost/array.hpp>
#    include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;

        tcp::resolver               resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        for (;;) {
            boost::array<char, 128>   buf;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            std::cout.write(buf.data(), len);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#endif

#include <cassert>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <atomic>
#include <memory>
#include <functional>
#include <utility>

int main() {
    std::unique_ptr<std::deque<std::string>> queue { new std::deque<std::string> {  } };
    //queue.release();
    while (queue->empty()) {
        std::cout << "Print Hello" << std::endl;
    }
}