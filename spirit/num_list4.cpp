/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers.
//  The numbers are inserted in a vector using phoenix.
//
//  [ JDG May 10, 2002 ]    spirit1
//  [ JDG March 24, 2007 ]  spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using std::vector;

    ///////////////////////////////////////////////////////////////////////////
    //  Our number list compiler
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_numlist4
    template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, vector<double>& v)
    {
        using qi::double_;
        using qi::phrase_parse;
        using qi::_1;
        using ascii::space;

        bool r = phrase_parse(first, last,

            //  Begin grammar
            (
                double_ % ','
            )
            ,
            //  End grammar

            space, v);

        if (first != last) // fail if we did not get a full match
            return false;
        return r;
    }
    //]
}

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int main()
{
  using namespace std;
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tA comma separated list parser for Spirit...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";

    cout << "Give me a comma separated list of numbers.\n";
    cout << "The numbers will be inserted in a vector of numbers\n";
    cout << "Type [q or Q] to quit\n\n";

    string str;
    while (getline(cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;

        vector<double> v;
        if (client::parse_numbers(str.begin(), str.end(), v))
        {
            cout << "-------------------------\n";
            cout << "Parsing succeeded\n";
            cout << str << endl << "Parses OK: " << endl;

            for (vector<double>::size_type i = 0; i < v.size(); ++i)
                cout << i << ": " << v[i] << " ";
            cout << endl;

            cout << "\n-------------------------\n";
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Parsing failed\n";
            cout << "-------------------------\n";
        }
    }
    cout << "Bye... :-) \n\n";
    return 0;
}
