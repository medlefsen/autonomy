//! \file parser_translator_map.cpp
//! \brief Implementation of parser translator map class(es).

#include <string>

#include <boost/lexical_cast.hpp>

#include <autonomy/compiler/parser_translator_map.hpp>

namespace autonomy 
{
    namespace compiler
    {
        parser_translator_map::parser_translator_map()
            : _default_translator
              (&construct_translator < translator_base >)
        {}

        construct_translator_ptr parser_translator_map::
        translator(parser_id_t parser) throw (translator_exception)
        {
            internal_map_t::iterator pt_pair(_pt_map.find(parser));
            if (pt_pair == _pt_map.end())
            {
                if (_default_translator != NULL)
                {
                    return _default_translator;
                }
                else
                {
                    throw (translator_exception("no translator for "
                                                + boost::lexical_cast <
                                                                       std::
                                                                       string > (
                                                    parser)));
                }
            }
            else
            {
                return pt_pair->second;
            }
        }
    }
}
