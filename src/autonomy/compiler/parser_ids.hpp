//! \file parser_ids.hpp
//!  Static parser identifiers.

#ifndef AUTONOMY_COMPILER_PARSE_PARSER_IDS
#define AUTONOMY_COMPILER_PARSE_PARSER_IDS

namespace autonomy
{
    namespace compiler
    {
        typedef int parser_id_t;

        namespace parse
        {
            const parser_id_t PROG_ID       ( 1 ) ;
            const parser_id_t STMTLST_ID    ( 2 ) ;
            const parser_id_t BLOCK_ID      ( 8 ) ;
            const parser_id_t STMT_ID       ( 3 ) ;
            const parser_id_t CMD_ID        ( 4 ) ;
            const parser_id_t BEXPR_ID      ( 6 ) ;
            const parser_id_t EXPR_ID       ( 7 ) ;

            const parser_id_t COND_ID       ( 5 ) ;
            const parser_id_t CONDCONT_ID   ( 13  ) ;
            const parser_id_t WHILE_ID      ( 45 );

            const parser_id_t ASGN_ID       ( 9  ) ;

            const parser_id_t DECL_ID       ( 10  ) ;
            const parser_id_t DECLCONT_ID   ( 12  ) ;

            const parser_id_t ARGLST_ID     ( 15  ) ;

            const parser_id_t BEXPRCONT_ID  ( 18  ) ;
            const parser_id_t CONJ_ID       ( 19  ) ;
            const parser_id_t CONJCONT_ID   ( 20  ) ;
            const parser_id_t LLIT_ID       ( 21  ) ;
            const parser_id_t REL_ID        ( 22 ) ;
            const parser_id_t RELCONT_ID    ( 23 ) ;

            const parser_id_t EXPRCONT_ID   ( 25 ) ;
            const parser_id_t TERM_ID       ( 26 ) ;
            const parser_id_t TERMCONT_ID   ( 27 ) ;
            const parser_id_t FACTOR_ID     ( 28 ) ;
            const parser_id_t FACTORCONT_ID ( 29 ) ;
            const parser_id_t BASE_ID       ( 30 ) ;
        }
    }
}
#endif
