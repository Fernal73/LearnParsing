/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for summing a comma-separated list of numbers using phoenix.
//
//  [ JDG June 28, 2002 ]   spirit1
//  [ JDG March 24, 2007 ]  spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
//[tutorial_adder_includes
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <string>
//]

namespace client {
//[tutorial_adder_using
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using ascii::space;
using phoenix::ref;
using qi::_1;
using qi::double_;
//]

///////////////////////////////////////////////////////////////////////////
//  Our adder
///////////////////////////////////////////////////////////////////////////

//[tutorial_adder
template <typename Iterator>
bool adder(Iterator first, Iterator last, double &n) {
  bool r = qi::phrase_parse(
      first, last,

      //  Begin grammar
      (double_[ref(n) = _1] >> *(',' >> double_[ref(n) += _1])),
      //  End grammar

      space);

  if (first != last) // fail if we did not get a full match
    return false;
  return r;
}
//]
} // namespace client

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int main() {
  using namespace std;
  cout << "/////////////////////////////////////////////////////////\n\n";
  cout << "\t\tA parser for summing a list of numbers...\n\n";
  cout << "/////////////////////////////////////////////////////////\n\n";

  cout << "Give me a comma separated list of numbers.\n";
  cout << "The numbers are added using Phoenix.\n";
  cout << "Type [q or Q] to quit\n\n";

  string str;
  while (getline(cin, str)) {
    if (str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    double n;
    if (client::adder(str.begin(), str.end(), n)) {
      cout << "-------------------------\n";
      cout << "Parsing succeeded\n";
      cout << str << " Parses OK: " << endl;
      cout << "sum = " << n;
      cout << "\n-------------------------\n";
    } else {
      cout << "-------------------------\n";
      cout << "Parsing failed\n";
      cout << "-------------------------\n";
    }
  }
  cout << "Bye... :-) \n\n";
  return 0;
}
