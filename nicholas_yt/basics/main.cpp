#include <ctime>
#include <iostream>

using namespace std;

int main() {

  std::time_t rawtime;

  struct tm timeinfo;

  std::time_t(&rawtime);

  std::localtime(&timeinfo, &rawtime);

  return 0;
}
