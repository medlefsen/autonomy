//! \file lexer_ids.hpp
//!  Static lexer identifiers.

#ifndef AUTONOMY_COMPILER_LEXER_PARSER_IDS
#define AUTONOMY_COMPILER_LEXER_PARSER_IDS

namespace autonomy
{
    namespace compiler
    {
        namespace lex
        {
            const int RESERVED_ID        ( 100 ) ;
            const int ID_TOK_ID          ( 101 ) ;
            const int TYPE_TOK_ID        ( 102 ) ;
            const int CMD_TOK_ID         ( 103 ) ;

            /* keywords */
            const int IF_TOK_ID          ( 106 ) ;
            const int ELSEIF_TOK_ID      ( 107 ) ;
            const int ELSE_TOK_ID        ( 108 ) ;
            const int WHILE_TOK_ID       ( 109 ) ;

            /* grouping */
            const int LBR_ID             ( 111 ) ;
            const int RBR_ID             ( 112 ) ;
            const int LGRP_ID            ( 113 ) ;
            const int RGRP_ID            ( 114 ) ;

            /* composition/sequencing */
            const int STMTTERM_ID        ( 117 ) ;
            const int ARGSEP_ID          ( 118 ) ;

            /* operators */
            const int ASGNOP_ID          ( 121 ) ;

            /* mathematical */
            const int ADDOP_ID           ( 124 ) ;
            const int MULTOP_ID          ( 125 ) ;
            const int EXPOP_ID           ( 126 ) ;

            /* relational */
            const int RELOP_ID           ( 129 ) ;

            /* logical */
            const int NOTOP_ID           ( 132 ) ;
            const int OROP_ID            ( 133 ) ;
            const int ANDOP_ID           ( 134 ) ;

            /* literals */
            const int LITC_ID            ( 137 ) ;
        }
    }
}
#endif
