/*=============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A mini XML-like parser
//
//  [ JDG March 25, 2007 ]   spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/foreach.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace client {
namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Our mini XML tree representation
///////////////////////////////////////////////////////////////////////////
struct mini_xml;

typedef boost::variant<boost::recursive_wrapper<mini_xml>, string>
    mini_xml_node;

struct mini_xml {
  string name;                    // tag name
  vector<mini_xml_node> children; // children
};
} // namespace client

// We need to tell fusion about our mini_xml struct
// to make it a first-class fusion citizen
BOOST_FUSION_ADAPT_STRUCT(client::mini_xml,
                          (std::string,
                           name)(std::vector<client::mini_xml_node>, children))

namespace client {
///////////////////////////////////////////////////////////////////////////
//  Print out the mini xml tree
///////////////////////////////////////////////////////////////////////////
int const tabsize = 4;

void tab(int indent) {
  for (int i = 0; i < indent; ++i)
    cout << ' ';
}

struct mini_xml_printer {
  mini_xml_printer(int indent = 0) : indent(indent) {}

  void operator()(mini_xml const &xml) const;

  int indent;
};

struct mini_xml_node_printer : boost::static_visitor<> {
  mini_xml_node_printer(int indent = 0) : indent(indent) {}

  void operator()(mini_xml const &xml) const {
    mini_xml_printer(indent + tabsize)(xml);
  }

  void operator()(string const &text) const {
    tab(indent + tabsize);
    cout << "text: \"" << text << '"' << endl;
  }

  int indent;
};

void mini_xml_printer::operator()(mini_xml const &xml) const {
  tab(indent);
  cout << "tag: " << xml.name << endl;
  tab(indent);
  cout << '{' << endl;

  BOOST_FOREACH (mini_xml_node const &node, xml.children) {
    boost::apply_visitor(mini_xml_node_printer(indent), node);
  }

  tab(indent);
  cout << '}' << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Our mini XML grammar definition
///////////////////////////////////////////////////////////////////////////
//[tutorial_xml2_grammar
template <typename Iterator>
struct mini_xml_grammar
    : qi::grammar<Iterator, mini_xml(), qi::locals<string>,
                  ascii::space_type> {
  mini_xml_grammar() : mini_xml_grammar::base_type(xml) {
    using ascii::char_;
    using ascii::string;
    using qi::lexeme;
    using qi::lit;
    using namespace qi::labels;

    text %= lexeme[+(char_ - '<')];
    node %= xml | text;

    start_tag %= '<' >> !lit('/') >> lexeme[+(char_ - '>')] >> '>';

    end_tag = "</" >> lit(_r1) >> '>';

    xml %= start_tag[_a = _1] >> *node >> end_tag(_a);
  }

  qi::rule<Iterator, mini_xml(), qi::locals<string>, ascii::space_type>
      xml;
  qi::rule<Iterator, mini_xml_node(), ascii::space_type> node;
  qi::rule<Iterator, string(), ascii::space_type> text;
  qi::rule<Iterator, string(), ascii::space_type> start_tag;
  qi::rule<Iterator, void(string), ascii::space_type> end_tag;
};
//]
} // namespace client

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
  using namespace std;
  char const *filename;
  if (argc > 1) {
    filename = argv[1];
  } else {
    cerr << "Error: No input file provided." << endl;
    return 1;
  }

  ifstream in(filename, ios_base::in);

  if (!in) {
    cerr << "Error: Could not open input file: " << filename << endl;
    return 1;
  }

  string storage;         // We will read the contents here.
  in.unsetf(ios::skipws); // No white space skipping!
  copy(istream_iterator<char>(in), istream_iterator<char>(),
            back_inserter(storage));

  typedef client::mini_xml_grammar<string::const_iterator>
      mini_xml_grammar;
  mini_xml_grammar xml; // Our grammar
  client::mini_xml ast; // Our tree

  using boost::spirit::ascii::space;
  string::const_iterator iter = storage.begin();
  string::const_iterator end = storage.end();
  bool r = phrase_parse(iter, end, xml, space, ast);

  if (r && iter == end) {
    cout << "-------------------------\n";
    cout << "Parsing succeeded\n";
    cout << "-------------------------\n";
    client::mini_xml_printer printer;
    printer(ast);
    return 0;
  } else {
    string::const_iterator some = iter + min(30, int(end - iter));
    string context(iter, (some > end) ? end : some);
    cout << "-------------------------\n";
    cout << "Parsing failed\n";
    cout << "stopped at: \"" << context << "...\"\n";
    cout << "-------------------------\n";
    return 1;
  }
}
