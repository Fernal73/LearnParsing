/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for arbitrary tuples. This example presents a parser
//  for an employee structure.
//
//  [ JDG May 9, 2007 ]
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

#include <complex>
#include <iostream>
#include <string>

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
using std::string;
///////////////////////////////////////////////////////////////////////////
//  Our employee struct
///////////////////////////////////////////////////////////////////////////
//[tutorial_employee_struct
struct employee {
  int age;
  string surname;
  string forename;
  double salary;
};
//]
} // namespace client

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

//[tutorial_employee_adapt_struct
BOOST_FUSION_ADAPT_STRUCT(client::employee,
                          (int, age)(std::string, surname)(std::string,
                                                           forename)(double,
                                                                     salary))
//]

namespace client {
///////////////////////////////////////////////////////////////////////////////
//  Our employee parser
///////////////////////////////////////////////////////////////////////////////
//[tutorial_employee_parser
template <typename Iterator>
struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type> {
  employee_parser() : employee_parser::base_type(start) {
    using ascii::char_;
    using qi::double_;
    using qi::int_;
    using qi::lexeme;
    using qi::lit;

    quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

    start %= lit("employee") >> '{' >> int_ >> ',' >> quoted_string >> ',' >>
             quoted_string >> ',' >> double_ >> '}';
  }

  qi::rule<Iterator, string(), ascii::space_type> quoted_string;
  qi::rule<Iterator, employee(), ascii::space_type> start;
};
//]
} // namespace client

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int main() {
  using namespace std;
  cout << "/////////////////////////////////////////////////////////\n\n";
  cout << "\t\tAn employee parser for Spirit...\n\n";
  cout << "/////////////////////////////////////////////////////////\n\n";

  cout << "Give me an employee of the form :"
            << "employee{age, \"surname\", \"forename\", salary } \n";
  cout << "Type [q or Q] to quit\n\n";

  using boost::spirit::ascii::space;
  typedef string::const_iterator iterator_type;
  typedef client::employee_parser<iterator_type> employee_parser;

  employee_parser g; // Our grammar
  string str;
  while (getline(cin, str)) {
    if (str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    client::employee emp;
    string::const_iterator iter = str.begin();
    string::const_iterator end = str.end();
    bool r = phrase_parse(iter, end, g, space, emp);

    if (r && iter == end) {
      cout << boost::fusion::tuple_open('[');
      cout << boost::fusion::tuple_close(']');
      cout << boost::fusion::tuple_delimiter(", ");
      cout << "-------------------------\n";
      cout << "Parsing succeeded\n";
      cout << "got: " << boost::fusion::as_vector(emp) << endl;
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
