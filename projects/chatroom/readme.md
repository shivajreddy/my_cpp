Goal: simple cli chat tool using sockets

When you run the tool
  - if not already running, it starts the server
  - if already running, connects to existing server

- 1 single chat room

- client when can connect only when server is running
- ask for username, 
- they can chat realtime

Further improvements/thoughts:
- make sure this is unique for every client
- user is typing... when someone is typing
- colored messages on the terminal

```bash
find src/ -name '*.cpp' | entr -c sh -c 'g++ -std=c++17 src/main.cpp -o chatroom && ./chatroom'
```

