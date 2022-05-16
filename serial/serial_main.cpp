#include <iostream>
#include <boost/asio.hpp>
#include <thread>

//char buff[1000];

std::array<char, 1000> buff {};
class Serial {

    public:
    void sercb(boost::system::error_code ec,std::size_t size) { 
        std::cout << std::string(buff.data()) << "\t"<< size<<std::endl;
    }


};

int  main() { 
    boost::asio::io_service io {};
    boost::asio::serial_port ser { io, "COM10" };
    std::thread { [&] { io.run(); } }.detach();
    auto obj { Serial {} };
    auto                             baud = boost::asio::serial_port_base::baud_rate { 9600 };
    ser.set_option(baud);
    
    std::string msg { "printing something" };
    ser.write_some(boost::asio::buffer(msg.data(),msg.length()));
    ser.async_read_some(boost::asio::buffer(buff, 1000),
        //std::bind(&Serial::sercb,obj,std::placeholders::_1,std::placeholders::_2)
        [](auto ec, auto size) { std::cout << std::string(buff.data()) << "\t" << size << std::endl;
        }
    );
    std::cin.get();
    ser.close();
    return 0;
}