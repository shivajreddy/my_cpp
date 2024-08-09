#include <iostream>
#include <string>

using std::cout;
using std::string;

enum LogLevel { INFO, WARNING, ERROR };

class Log {
 public:
  LogLevel log_level;

 public:
  void send(const char *message, LogLevel level = LogLevel::INFO) {
    cout << std::to_string(level) << " TIME NOW: \n";
    cout << message << "\n";
  }
};

int main() {
  Log logger = Log();

  logger.send("testing");
  logger.send("hello?", LogLevel::ERROR);

  return 0;
}

class Node {
 public:
  int val;
  Node *next;
};

class LinkedList {
 public:
  Node *head;
  int size;

 public:
  void push(Node &node) {}
  void pop() {}
};
