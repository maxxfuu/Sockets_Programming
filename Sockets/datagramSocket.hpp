#ifndef DATAGRAM_SOCKET 
#define DATAGRAM_SOCKET 

#include <functional> 
#include <string> 

namespace Sockets { 
    class DatagramSocket { 

        private: 
            struct Impl; 
            std::shared_ptr< Impl > impl_;  

        public: 
            using OnReceived = std::function<void(const std::string&) >; 
            using OnSet = std::function<void() >; 

            DatagramSocket(); 

            bool Bind(uint16_t port = 0); 
            void sendMessage(const std::string& message, uint32_t address, uint16_t port, OnSet onSent = nullptr); 
            void start(OnReceived onReceived); 

            

    }; 
}

#endif 

// std::functions are wrapppers that lets you store callable objects. 
// A callable object is anything that we can call like a function. 