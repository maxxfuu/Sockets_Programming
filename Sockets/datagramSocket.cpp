#include "Abstractions.hpp"
#include "datagramSocket.hpp" 

#include <list> 
#include <mutex> 
#include <stdio.h> 
#include <thread> 
#include <vector> 
#include <string.h> 
#include <stddef.h> 
#include <stdint.h> 


namespace { 
    constexpr size_t maximumReadSize = 65536; 
} 

namespace Sockets { 
    struct DatagramSocket::Impl { 
        struct datagram { 
            std::string message; 
            uint32_t address; 
            uint16_t port; 
            OnSent onSent; 
        }; 

        // Properties 
        std::list< datagram > datagramsToSend; 
        bool error = false; 
        std::mutex mutex; 
        uint8_t receieveBuffer[maximumReadSize];

        SOCKET socket = INVALID_SOCKET; // Operating System Socket Itself  
        SocketEventLoop socketEventLoop; 

        ~Impl() noexcept { 
            if (!IS_INVALID_SOCKET(socket)) { 
                (void)closesocket(socket); 
            }
        }

        Impl(const Impl&) = delete;
        Impl(Impl&&) noexcept = delete;
        Impl& operator=(const Impl&) = delete;
        Impl& operator=(Impl&&) noexcept = delete;





    };


}