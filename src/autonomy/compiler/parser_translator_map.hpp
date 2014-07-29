//! \file parser_translator_map.hpp
//! \brief Declaration of map between parsers and translators.

#ifndef AUTONOMY_COMPILER_PARSER_TRANSLATOR_MAP_HPP
#define AUTONOMY_COMPILER_PARSER_TRANSLATOR_MAP_HPP

#include <map>
#include <limits>
#include <utility>

#include <boost/shared_ptr.hpp>
#include <boost/spirit/core.hpp>
#include <boost/integer_traits.hpp>

#include <autonomy/compiler/parser_ids.hpp>
#include <autonomy/compiler/lexer_ids.hpp>
#include <autonomy/compiler/parse_node_attributes.hpp>
#include <autonomy/compiler/symbol_table.hpp>
#include <autonomy/compiler/translator_exceptions.hpp>
#include <autonomy/compiler/translator_functors.hpp>

namespace autonomy
{
    namespace compiler
    {

        typedef std::auto_ptr<translator_base> 
        (*construct_translator_ptr)(parser_id_t parser,
                                    parse_node_attributes const& node_attr,
                                    symbol_table & st,
                                    const command_registry & cr);
        typedef std::map < int, construct_translator_ptr > internal_map_t;

        template < typename TranslatorT >
        std::auto_ptr<translator_base> 
        construct_translator(parser_id_t parser,
                             parse_node_attributes const& node_attr,
                             symbol_table & st,
                             const command_registry & cr )
        {
            return std::auto_ptr<translator_base>((translator_base*)(new TranslatorT(parser, node_attr, st, cr)));
        }

        const int DEFAULT_ID (boost::integer_traits< int >::const_max);
        const int NIL_ID (boost::integer_traits< int >::const_min);
        const construct_translator_ptr NIL_TRANSLATOR (NULL);

        //! \class parser_translator_map
        //! \brief Implements map between parsers and translators, for the semantic
        //!        translator.
        class parser_translator_map
        {
            public:

                parser_translator_map();

                template < parser_id_t ParserID, typename TranslatorT >
                void register_translator()
                {
                    if ( ParserID == DEFAULT_ID )
                    {
                        _default_translator
                        = &construct_translator< TranslatorT >;
                    }
                    else
                    {
                        _pt_map.insert(std::make_pair(ParserID,
                                                      &construct_translator<
                                                                            TranslatorT >));
                    }
                }

                construct_translator_ptr translator(parser_id_t parser) throw (
                    translator_exception);

                size_t num_translators ()
                {
                    return _pt_map.size();
                }

            protected:
                internal_map_t _pt_map;
                construct_translator_ptr _default_translator;
        };

    }
}
#endif
