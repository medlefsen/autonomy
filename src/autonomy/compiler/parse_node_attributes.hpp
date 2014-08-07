#ifndef AUTONOMY_COMPILER_PARSE_NODE_ATTRIBUTES_HPP
#define AUTONOMY_COMPILER_PARSE_NODE_ATTRIBUTES_HPP

#include <string>

//#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>

#include <autonomy/compiler/constants.hpp>
#include <autonomy/compiler/type.hpp>

namespace autonomy 
{
    namespace compiler
    {
        const int INVALID_INSTRUCTION ( -1 );

        class parse_node_attributes
        {
            public:
                typedef parse_input_t value_t;
                typedef int instruction_location_t;

                parse_node_attributes()
                        :_loc ( INVALID_INSTRUCTION )
                {}

                ~parse_node_attributes()
                {}

                type::type_t s_type() const
                {
                    return _s_type;
                }
                type::type_t & s_type()
                {
                    return _s_type;
                }

                type::type_t i_type() const
                {
                    return _i_type;
                }
                type::type_t & i_type()
                {
                    return _i_type;
                }

                value_t value() const
                {
                    return _val;
                }
                value_t & value()
                {
                    return _val;
                }

                void value(const value_t& val)
                {
                    _val = val;
                }

                instruction_location_t loc() const
                {
                    return _loc;
                }
                instruction_location_t & loc()
                {
                    return _loc;
                }

            private:
                type::type_t _s_type;
                type::type_t _i_type;

                value_t _val;

                instruction_location_t _loc;
        };
        
        void set_value ( boost::spirit::tree_node <boost::spirit::node_iter_data<parse_input_iterator_t, 
                        parse_node_attributes > >& root_node,
                        parse_input_iterator_t first,
                        parse_input_iterator_t last );

    }
}
#endif
