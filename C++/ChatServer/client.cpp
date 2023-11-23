#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket" << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Use the server's IP address.

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        return 1;
    }

    char buffer[1024];
    int bytesRead;

    while (true) {
        std::string message;
        std::cout << "You: ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        send(clientSocket, message.c_str(), message.size(), 0);

        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the received data.
            std::cout << "Server: " << buffer << std::endl;
        }
    }

    close(clientSocket);

    return 0;
}




