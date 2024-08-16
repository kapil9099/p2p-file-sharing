This project is a basic Peer-to-Peer (P2P) file-sharing system implemented in C/C++. The system allows users to share files directly between peers without the need for a central server. The project includes both a server and a client component. The server listens for incoming file requests from clients, and upon receiving a request, it sends the requested file to the client.

Features

File Sharing: Allows clients to request and download files from the server.
TCP Sockets: Utilizes TCP sockets for reliable communication between the server and clients.
Cross-Platform: The code is designed to run on both Windows and Unix-like systems (with modifications).
Logging: Basic logging of file requests and transfers.

Technologies Used

C/C++: The core programming languages used for developing the server and client.
GCC: The GNU Compiler Collection, used for compiling the C/C++ code.
Winsock2: Used on Windows for socket programming.
POSIX Sockets: Used on Unix-like systems for socket programming.
