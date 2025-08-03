# tcp-client-server

This is a simple TCP client-server program written in C to demonstrate the basic concepts of socket programming. It's part of my learning journey into the basics of computer networks.

## Functions

- Accepts server IP address and port number as command-line arguments.
- Sends and receives messages over a TCP connection.
- Handles connection errors and disconnections gracefully.
- Exits cleanly when the user types `exit`.

## How to run locally on your machine?

### Requirements
- Unix like OS (Linux, BSD, MacOS), NOT Windows but it'll work if you use WSL.
- Basic understanding of C language and `gcc`.

### Step 1: Compile the Client Program

```
gcc client.c -o client
```

This will generate an executable named `client`.

### Step 2: Start a TCP Server

Since we don’t have a `server.c` yet, we are going to simulate a TCP server using `netcat` (`nc`):

```
# In Terminal 1 (acts as the server)
nc -l 8080
```

This listens for incoming TCP connections on port 8080.

### Step 3: Run the Client

In a second terminal, run the compiled client and pass the server IP and port as command-line arguments:

```
./client <SERVER_IP> <PORT>
```

#### Example

  ```
  ./client 127.0.0.1 8080
  ```

## How It Works?

1. The client creates a TCP socket.
2. It connects to the server using the provided IP address and port.
3. The user types a message and presses Enter.
4. The message is sent to the server.
5. The client waits for and displays the server's response.
6. The user can type `exit` to end the session.

## Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Linux man pages for info on network syscalls like `socket` `connect` etc](https://man7.org/linux/man-pages/)

