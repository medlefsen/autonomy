//!
//! \file  lex.hpp
//! \brief contains Boost::Spirit rules for lexical analysis of the
//!        drone language of Autonomy
//!
#ifndef AUTONOMY_COMPILER_LEX_HPP
#define AUTONOMY_COMPILER_LEX_HPP

//#include <boost/spirit/core.hpp>
//#include <boost/spirit/utility/confix.hpp>
//#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>

#include <autonomy/compiler/lexer_ids.hpp>
#include <autonomy/compiler/parse_node_attributes.hpp>

namespace autonomy
{
    namespace compiler
    {
        namespace lex
        {
            namespace bsp = boost::spirit;


            /* Lexer rules */
            template < typename ScannerT >
            struct lex_rules
            {
                lex_rules()
                {
                    // reserved words //
                    reserved
                        = bsp::lexeme_d[ 
                            bsp::strlit<>("if") 
                            | bsp::strlit<>("elseif")
                            | bsp::strlit<>("else")
                            | bsp::strlit<>("and")
                            | bsp::strlit<>("not")
                            | bsp::strlit<>("or")
                            | bsp::strlit<>("while")
                            ];

                    /* symbols */
                    id_tok
                    =  bsp::token_node_d[
                            bsp::chlit<>('$')
                            >>  +(bsp::alnum_p | bsp::chlit<>('_'))
                            //>>  bsp::leaf_node_d[+(bsp::alnum_p | bsp::chlit<>('_'))]
                      ];

                    type_tok
                    = bsp::token_node_d[
                           bsp::alpha_p 
                           >>  *(bsp::alnum_p | bsp::chlit<>('_'))
                        ] - reserved;

                    cmd_tok
                    =  bsp::token_node_d[
                            bsp::alpha_p
                            >> *(bsp::alnum_p | bsp::chlit<>('_'))
                        ] - reserved;

                    /* keywords */
                    if_tok
                    = bsp::token_node_d[
                            bsp::strlit<>("if")
                        ];

                    elseif_tok
                    = bsp::token_node_d[
                        bsp::strlit<> ("elseif")
                      ];

                    else_tok
                    = bsp::token_node_d[
                        bsp::strlit<> ("else")
                      ];

                    while_tok
                        = bsp::token_node_d[
                        bsp::strlit<> ("while")
                        ];

                    /* grouping */
                    lbr
                    =
                        bsp::chlit< > ('{');
                    rbr
                    =
                        bsp::chlit< > ('}');

                    lgrp
                    =
                        bsp::chlit< > ('(');

                    rgrp
                    =
                        bsp::chlit< > (')');

                    /* composition/sequencing */
                    stmtterm
                    =
                        bsp::chlit< > (';')
                    ;

                    argsep
                    =
                        bsp::chlit< > (',')
                    ;


                    /* operators */
                    asgnop
                    =
                        bsp::strlit< >(":=")
                    ;

                    /* mathematical */
                    addop
                    = bsp::token_node_d[
                            (bsp::chlit<>('+') | bsp::chlit<>('-'))
                        ];

                    multop
                    = bsp::token_node_d[
                            (bsp::chlit<>('*') | bsp::chlit<>('/'))
                        ];

                    expop
                    = bsp::token_node_d[
                            bsp::chlit<>('^')
                        ];

                    /* relational */
                    relop
                    = bsp::token_node_d[
                            ( bsp::chlit<> ('<')
                              | bsp::chlit<> ('=')
                            )
                        ];

                    /* logical */
                    notop =
                        bsp::token_node_d[bsp::strlit<>
                                                        ("not")];
                    orop  =
                        bsp::token_node_d[bsp::strlit<>
                                                        ("or")];
                    andop =
                        bsp::token_node_d[bsp::strlit<>
                                                        ("and")];

                    /* literals */
                    litc = bsp::token_node_d[bsp::uint_p];
                }

                // reserved words //
                bsp::rule< ScannerT, bsp::parser_context< >,
                    bsp::parser_tag< RESERVED_ID > > reserved; 

                /* symbols */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ID_TOK_ID > > id_tok;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< TYPE_TOK_ID > > type_tok;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< CMD_TOK_ID > > cmd_tok;

                /* keywords */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< IF_TOK_ID > > if_tok;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ELSEIF_TOK_ID > > elseif_tok;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ELSE_TOK_ID > > else_tok;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< WHILE_TOK_ID > > while_tok;

                /* grouping */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< LBR_ID > > lbr;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< RBR_ID > > rbr;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< LGRP_ID > > lgrp;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< RGRP_ID > > rgrp;

                /* composition/sequencing */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< STMTTERM_ID > > stmtterm;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ARGSEP_ID > > argsep;

                /* operators */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ASGNOP_ID > > asgnop;

                /* mathematical */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ADDOP_ID > > addop;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< MULTOP_ID > > multop;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< EXPOP_ID > > expop;

                /* relational */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< RELOP_ID > > relop;

                /* logical */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< NOTOP_ID > > notop;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< OROP_ID > > orop;
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< ANDOP_ID > > andop;

                /* literals */
                bsp::rule< ScannerT, bsp::parser_context< >,
                          bsp::parser_tag< LITC_ID > > litc;
            };
        }
    }
}
#endif
