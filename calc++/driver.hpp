#ifndef DRIVER_HPP
#define DRIVER_HPP
#include "parser.hpp"
#include <map>
#include <string>

class driver {
public:
  driver();
  virtual ~driver();
  // Run the parser on file F.  Return 0 on success.
  int parse(const std::string &f);
  // Handling the scanner.
  void scan_begin();
  void scan_end();
  // The name of the file being parsed.
  std::string file;
  std::map<std::string, int> variables;
  int result;
  // Whether to generate parser debug traces.
  bool trace_parsing;
  // Whether to generate scanner debug traces.
  bool trace_scanning;
  // The token's location used by the scanner.
  yy::location location;

private:
};
#endif /* end of include guard DRIVER_HPP */
