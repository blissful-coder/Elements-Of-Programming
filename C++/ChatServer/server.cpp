#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>

std::vector<int> clients;
std::mutex clientMutex;
std::atomic<int> clientCount(0);
std::condition_variable clientJoinCV;

void broadcastMessage(int senderSocket, const std::string& message) {
    std::lock_guard<std::mutex> lock(clientMutex);
    for (int clientSocket : clients) {
        if (clientSocket != senderSocket) {
            std::string senderName = "Client #" + std::to_string(senderSocket);
            std::string broadcastMessage = senderName + ": " + message;
            send(clientSocket, broadcastMessage.c_str(), broadcastMessage.size(), 0);
        }
    }
    
    // Print the message on the server
    std::string senderName = "Client #" + std::to_string(senderSocket);
    std::string serverMessage = senderName + ": " + message;
    std::cout << serverMessage << std::endl;
}

void updateClientCount() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Update every 1 second.
        std::lock_guard<std::mutex> lock(clientMutex);
        std::cout << "Online clients: " << clientCount << std::endl;
    }
}

void clientHandler(int clientSocket) {
    std::string welcomeMessage = "Welcome to the chat server!\n";
    send(clientSocket, welcomeMessage.c_str(), welcomeMessage.size(), 0);

    {
        std::unique_lock<std::mutex> lock(clientMutex);
        clients.push_back(clientSocket);
        clientCount++;
        clientJoinCV.notify_all();
    }

    char buffer[1024];
    int bytesRead;

    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {

        buffer[bytesRead] = '\0';
        std::string message(buffer);

        // Broadcast the message to all clients
        broadcastMessage(clientSocket, message);
    }

    // Remove the client from the list and update the count
    {
        std::lock_guard<std::mutex> lock(clientMutex);
        clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
        clientCount--;
    }

    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket" << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket" << std::endl;
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on server socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    std::thread countThread(updateClientCount);

    while (true) {
        socklen_t clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);

        std::thread clientThread(clientHandler, clientSocket);
        clientThread.detach();
    }

    close(serverSocket);

    return 0;
}
