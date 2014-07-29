//! \file symbol_table.cpp
//! Implementation of symbol table class.

#include <autonomy/compiler/symbol_table.hpp>
#include <limits>
#include <utility>
#include <cassert>

namespace autonomy
{
	namespace compiler
	{
		const symbol_table::location_t symbol_table::ID_EXCEPTIONAL =
		   std::numeric_limits < symbol_table::location_t >::max();

		const symbol_table::symbol_t SYMBOL_EXCEPTIONAL = "";

		 symbol_table::symbol_table()
		{
		}

		symbol_table::~symbol_table()
		{
		}

        symbol_table::location_t symbol_table::add_symbol(symbol_table::symbol_t symbol)
		{
			std::pair < symbol_table_forward_t::iterator, bool > result =
			   _forward_table.insert(make_pair(symbol,
				  _reverse_table.size()));
			if (result.second)
			{
				_reverse_table.push_back(symbol);
				return (result.first)->second;
			}
			return ID_EXCEPTIONAL;
		}

		symbol_table::symbol_t symbol_table::
		   lookup_symbol(symbol_table::location_t identifier)
		{
			if (identifier < static_cast<int>(_reverse_table.size()))
			{
				return _reverse_table[identifier];
			}
			return symbol_t("");
		}

        symbol_table::location_t symbol_table::lookup_symbol ( symbol_t symbol   ) 
        {
            symbol_table_forward_t::iterator element(_forward_table.find(symbol));
           if ( element != _forward_table.end() )
           {
                return element->second;
           }
           else
           {
                return ID_EXCEPTIONAL;
           }
        }
	}
}
