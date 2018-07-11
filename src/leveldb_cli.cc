#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "db.h"
#include "util.h"

int main(int argc, char* argv[]) {
  std::cout << "leveldb-cli v0.0.1" << std::endl;

  DB db;
  std::string dbname;

  if (argc > 1 && argc < 3) {
    dbname = argv[1];
  } else {
    std::cerr << "Please Input DB name." << std::endl;
    return -1;
  }

  db.Create(dbname);

  while (1) {
    // Check Ctrl-D
    if (std::cin.eof()) {
      break;
    }

    // Read input
    std::cout << ">>> ";
    std::string input;

    std::getline(std::cin, input);

    // Lexer
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(), back_inserter(tokens));

    for (auto i = 0; i < tokens.size(); ++i) {
      if (iequals(tokens[0], "PUT")) {
        if (tokens.size() != 3) {
          std::cerr << "Format Error" << std::endl;
          break;
        }
        std::string key = tokens[1];
        std::string value = tokens[2];
        auto s = db.Put(key, value);
        if (!s.ok()) {
          std::cerr << s.ToString() << std::endl;
        }
        break;
      } else if (iequals(tokens[i], "GET")) {
        if (tokens.size() < 2) {
          std::cerr << "Format Error" << std::endl;
          break;
        } else if (tokens.size() > 2) {
          // TODO: get multi key
          std::cerr << "Just support get one key!" << std::endl;
          break;
        }

        std::string key = tokens[1];
        std::string value;
        auto s = db.Get(key, &value);
        if (!s.ok()) {
          std::cerr << s.ToString() << std::endl;
        }
        std::cout << value << std::endl;
        break;
      } else if (iequals(tokens[i], "DELETE")) {
        if (tokens.size() < 2) {
          std::cerr << "Format Error" << std::endl;
          break;
        } else if (tokens.size() > 2) {
          // TODO: delete multi key-value
          std::cerr << "Just support delete one key-value!" << std::endl;
          break;
        }

        std::string key = tokens[1];
        auto s = db.Delete(key);
        if (!s.ok()) {
          std::cerr << s.ToString() << std::endl;
        }
        break;
      } else {
        std::cout << "Not supported!" << std::endl;
      }
    }
  }

  return 0;
}