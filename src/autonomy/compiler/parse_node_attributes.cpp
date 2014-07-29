//! \file 
//! \brief Implementations of helper functions for parse_node_attributes
//!        objects.

#include <autonomy/compiler/parse_node_attributes.hpp>

namespace autonomy
{
	namespace compiler
	{
        void set_value(boost::spirit::tree_node <
					   boost::spirit::node_iter_data <
					   parse_input_iterator_t,
					   parse_node_attributes > >& root_node,
					   parse_input_iterator_t first,
					   parse_input_iterator_t last)
		{

            parse_node_attributes tmp(root_node.value.value());
            tmp.value() = parse_node_attributes::value_t(first,last);
            root_node.value.value(tmp);
        }

	}
}
