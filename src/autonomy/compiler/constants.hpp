//! \file
//! \brief Information shared between more than one autonomy::compiler file.
//!
//! Constants, typedefs, etc shared across the autonomy::compiler namespace.

#ifndef AUTONOMY_COMPILER_CONSTANTS_HPP
#define AUTONOMY_COMPILER_CONSTANTS_HPP

#include <string>

//#include <boost/spirit/iterator/position_iterator.hpp>
//#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>

namespace autonomy 
{
    namespace compiler
    {
        typedef std::string
            parse_input_t;
        typedef boost::spirit::position_iterator< parse_input_t::iterator >
            parse_input_iterator_t;
        typedef char parse_input_unit_t;

#if 0
        typedef boost::spirit::node_iter_data_factory< parse_node_attributes >
            parse_tree_node_factory_t;
        typedef boost::spirit::tree_match< parse_input_iterator_t,
                                           parse_tree_node_factory_t >
                parse_tree_match_t;
#endif
    }
}
#endif
