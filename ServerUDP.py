from socket import *

serverPort = 12000

serverSocket = socket(AF_INET, SOCK_DGRAM)

serverSocket.bind(("127.0.0.1", serverPort))

print("The server is ready to receive")

while True:

    sentence, clientAddress = serverSocket.recvfrom(2048)

    fileName = sentence.decode("utf-8")

    try:
        file = open(fileName, "r")

        fileContents = file.read(2048)

        serverSocket.sendto(
            fileContents.encode("utf-8"),
            clientAddress
        )

        print("Sent back to client")

        file.close()

    except FileNotFoundError:

        message = "File not found"

        serverSocket.sendto(
            message.encode("utf-8"),
            clientAddress
        )