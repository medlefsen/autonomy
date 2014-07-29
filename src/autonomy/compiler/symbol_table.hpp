//! \file symbol_table.hpp
//! Declaration of a simple class for constructing symbol tables.

#ifndef AUTONOMY_COMPILER_SYMBOL_TABLE_HPP
#define AUTONOMY_COMPILER_SYMBOL_TABLE_HPP

#include <map>
#include <string>
#include <vector>

namespace autonomy
{
    namespace compiler
    {
       
        class symbol_table
        {
            public:
                typedef std::string symbol_t;
                typedef int    location_t;

                typedef std::map    < symbol_t,location_t > symbol_table_forward_t;
                typedef std::vector < symbol_t        > symbol_table_reverse_t;

                symbol_table();
                
                ~symbol_table();

                location_t add_symbol      ( symbol_t symbol   ) ;

                symbol_t lookup_symbol ( location_t identifier ) ;

                location_t lookup_symbol   ( symbol_t symbol   ) ;

                symbol_table_reverse_t& get() { return _reverse_table; }
                
                static const location_t ID_EXCEPTIONAL;
                static const symbol_t SYMBOL_EXCEPTIONAL;

            private:
                symbol_table_forward_t  _forward_table;
                symbol_table_reverse_t  _reverse_table;
        };
    }
}
#endif
