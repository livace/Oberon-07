#include <iostream>
#include <parser/driver.hh>

int main(int argc, char **argv) {
  Driver driver;
  int res = 0;
  for (int i = 1; i < argc; ++i) {
      if (argv[i] == std::string("-p")) {
          driver.trace_parsing = true;
      } else if (argv[i] == std::string("-s")) {
          driver.trace_scanning = true;
      } else if (!driver.parse(argv[i])) {
          std::cout << "Ok" << '\n';
      } else {
          res = 1;
      }
  }

  return res;
}