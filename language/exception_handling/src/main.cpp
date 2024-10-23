#include <exception>
#include <iostream>
#include <string>

using std::cout;
using std::string;

class MyError : public std::exception {
public:
  string message = "default error message";
  MyError(string message) { this->message = message; }
};

int read_file(int x) {
  try {
    if (x % 2 == 1) {
      // throw("ERR_ODD_GIVEN");
      // throw(402);
      MyError err = MyError{"odd num given"};
      throw(err);
    }
    cout << x << "\n";
    return x;

  } catch (const char *ex) {
    std::cerr << ex << "\n";
  } catch (int ex) {
    std::cerr << "ex_num: " << ex << "\n";
  } catch (MyError err) {
    std::cerr << err.message << "\n";
  } catch (...) {
    std::cerr << "default catch\n";
  }
  return -1;
}

int main() {
  // cout << "Exception Handling\n";
  read_file(2);
  read_file(3);
  read_file(2);
  return 0;
}
