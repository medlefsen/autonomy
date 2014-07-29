//!
//! \file  prog_structure.hpp
//! \brief Defines structural elements of the Autonomy drone language grammar.
//!
//! The structural elements are statements and mechanisms for composing them
//! (sequencing).


#ifndef AUTONOMY_COMPILER_PARSE_PARSE_HPP
#define AUTONOMY_COMPILER_PARSE_PARSE_HPP

//#include <boost/spirit/core.hpp>
//#include <boost/spirit/tree/ast.hpp>
//#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>

#include <autonomy/compiler/lex.hpp>
#include <autonomy/compiler/parser_ids.hpp>
#include <autonomy/compiler/constants.hpp>
#include <autonomy/compiler/parse_node_attributes.hpp>

namespace autonomy
{
    namespace compiler
    {
        typedef boost::spirit::node_iter_data_factory< parse_node_attributes >
            parse_tree_node_factory_t;
        typedef boost::spirit::tree_match< parse_input_iterator_t,
                                           parse_tree_node_factory_t >
            parse_tree_match_t;
        
        namespace parse
        {
            namespace bsp = boost::spirit;

            struct program
                : bsp::grammar < program >
            {

                template < typename ScannerT >
                struct definition
                {

                    lex::lex_rules< ScannerT > lexer;

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< ASGN_ID > > asgn;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< DECL_ID > > decl;

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< DECLCONT_ID > > declcont;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< CONDCONT_ID > > condcont;

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< ARGLST_ID > > arglst;

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< BEXPRCONT_ID > > bexprcont;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< CONJ_ID > > conj;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< CONJCONT_ID > > conjcont;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< LLIT_ID > > llit;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< REL_ID > > rel;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< RELCONT_ID > > relcont;

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< EXPRCONT_ID > > exprcont;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< TERM_ID > > term;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< TERMCONT_ID > > termcont;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< FACTOR_ID > > factor;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< FACTORCONT_ID > > factorcont;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< BASE_ID > > base;

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< PROG_ID > > prog;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< STMTLST_ID > > stmtlst;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< STMT_ID > > stmt;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< CMD_ID > > cmd;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< BLOCK_ID > > block;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< COND_ID > > cond;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< WHILE_ID > > loop_while;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< BEXPR_ID > > bexpr;
                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< EXPR_ID > > expr;

                    definition( program const& self )
                    {
                        prog
                        = (stmtlst >> bsp::end_p);

                        stmtlst
                            = *((stmt >> bsp::discard_node_d[lexer.stmtterm])
                                | block); 

                        stmt = (asgn | decl | cmd);

                        asgn =
                            ( bsp::access_node_d[lexer.id_tok][&set_value]
                              >> bsp::discard_node_d[lexer.asgnop]
                              >> expr);

                        decl =
                            (bsp::access_node_d[lexer.type_tok][&set_value]
                             >> bsp::access_node_d[lexer.id_tok][&set_value]
                             >> bsp::access_node_d[declcont][&set_value]);

                        declcont   = ((  bsp::discard_node_d[lexer.lgrp]
                                         >> expr
                                         >> bsp::discard_node_d[lexer.rgrp])
                                      | bsp::epsilon_p);

                        cmd =
                            ( bsp::access_node_d[lexer.cmd_tok][&set_value]
                              >> arglst);

                        arglst = ( bsp::discard_node_d[lexer.lgrp]
                                   >> !(expr
                                        >> *(bsp::discard_node_d[lexer.argsep]
                                             >> expr))
                                   >> bsp::discard_node_d[lexer.rgrp])
                        ;

                        block = cond | loop_while;

                        cond = ( lexer.if_tok
                                  >> bexpr
                                  >> bsp::discard_node_d[lexer.lbr]
                                  >> stmtlst
                                  >> condcont
                                );

                        condcont = bsp::discard_node_d[lexer.rbr] >>
                                    !((  lexer.elseif_tok
                                      >> bexpr
                                      >> bsp::discard_node_d[lexer.lbr]
                                      >> stmtlst
                                      >> condcont
                                   )
                                   | ( lexer.else_tok
                                       >> bsp::discard_node_d[lexer.lbr]
                                       >> stmtlst
                                       >> bsp::discard_node_d[lexer.rbr]
                                     ) 
                                   )
                                   ;

                        loop_while = bsp::discard_node_d[lexer.while_tok]
                                      >> bexpr
                                      >> bsp::discard_node_d[lexer.lbr]
                                      >> stmtlst
                                      >> lexer.rbr
                                      ;

                        bexpr     = ( conj >> bexprcont );
                        bexprcont =
                            ( bsp::access_node_d[lexer.orop][&set_value]
                              >> conj
                              >> bexprcont
                            )
                            | bsp::no_node_d[bsp::epsilon_p];

                        conj     = ( llit >> conjcont);
                        conjcont =
                            ( bsp::access_node_d[lexer.andop][&set_value]
                              >> llit
                              >> conjcont
                            )
                            | bsp::no_node_d[bsp::epsilon_p];

                        llit =
                            ( bsp::access_node_d[lexer.notop][&set_value]
                              >> llit )
                            | rel;

                        rel     = ( expr >> relcont );
                        relcont =
                            (bsp::access_node_d[lexer.relop][&set_value]
                             >> expr
                            )
                            | bsp::no_node_d[bsp::epsilon_p] ;

                        expr       = term >> exprcont;
                        exprcont   =
                            (bsp::access_node_d[lexer.addop][&set_value] >>
                             term >>
                             exprcont)
                            | bsp::no_node_d[bsp::epsilon_p];

                        term       = factor >> termcont;
                        termcont   =
                            (bsp::access_node_d[lexer.multop][&set_value]
                             >>
                             factor >> termcont)
                            | bsp::no_node_d[bsp::epsilon_p];

                        factor     = base >> factorcont;
                        factorcont =
                            (bsp::access_node_d[lexer.expop][&set_value] >>
                             factor)
                            | bsp::no_node_d[bsp::epsilon_p];

                        base       =
                            bsp::access_node_d[lexer.litc][&set_value]
                            | bsp::access_node_d[lexer.addop][&
                                                              set_value] >>
                            bsp::access_node_d[lexer.litc][&set_value]
                            | bsp::access_node_d[lexer.id_tok][&
                                                               set_value]
                            | cmd
                            | bsp::discard_node_d[lexer.lgrp] >>
                            bexpr >> bsp::discard_node_d[lexer.rgrp];
                    }

                    bsp::rule< ScannerT, bsp::parser_context< >,
                              bsp::parser_tag< PROG_ID > > const& start()
                    const
                    {
                        return prog;
                    }

                };

            };

            struct skipper : bsp::grammar < skipper >
            {
                template < typename ScannerT >
                struct definition
                {
                    definition(const skipper & self)
                    {
                        skip 
                            = bsp::lexeme_d[
                            bsp::longest_d[bsp::space_p
                            | bsp::comment_p("#")
                            | bsp::comment_nest_p("(#", "#)") ]];
                    }

                    bsp::rule< ScannerT, bsp::parser_context< > > skip;

                    bsp::rule< ScannerT, bsp::parser_context< > > const & start() const
                    {
                        return skip;
                    }
                        
                };

            };

        }
    }
}
#endif
