#include <stdio.h> 
#include <cstdint>
#include <string.h>

namespace { 

    constexpr uint32_t address = 0xC0A80076; // <-- As the sender, this is the reciever address
    constexpr uint16_t port = 8000; // <-- As the sender, this is the reciever port 

    void OnRecieve(const std::string& message) { 
        printf("Received message: %s\n", message.c_str()); 
    } 
    
}

int main(int argc, char* argv[]) { 
    //Create a Socekt Object 
    Sockets::DatagramSocket sender; 


}