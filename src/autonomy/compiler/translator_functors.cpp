//! \file translator_functors.cpp
//! \brief Translator functor implementations.
#include <boost/lexical_cast.hpp>

#include <autonomy/script_builtins.hpp>

#include <autonomy/compiler/translator_functors.hpp>
#include <autonomy/compiler/parser_translator_map.hpp>
#include <autonomy/compiler/parser_ids.hpp>
#include <autonomy/compiler/lexer_ids.hpp>

namespace autonomy 
{
    namespace compiler
    {
        //! \class translator_base
        std::pair < bool, instruction_list >
        translator_base::operator () (instruction_list const &ins,
                                      parser_id_t prev_node_type,
                                      parse_node_attributes const
                                      &prev_node_attr)
        throw (translator_exception)
        {
            return (std::make_pair(true, ins));
        }


        //! \class base_translator
        std::pair < bool, instruction_list >
        base_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::FACTOR_ID )
            {
                return (std::make_pair(true, ins));
            }
            else if ( prev_node_type == lex::ADDOP_ID )
            {
                if ( prev_node_attr.value() == "-" )
                {
                    _negate = true;
                }
                return (std::make_pair(true, ins));
            }
            else if ( prev_node_type == lex::LITC_ID )
            {
                int val = boost::lexical_cast< int >(prev_node_attr.value());
                if ( _negate )
                {
                    val *= -1;
                }
                return (std::make_pair(true,
                                       ins
                                       + new literal(val)));
            }
            else if ( prev_node_type == lex::ID_TOK_ID )
            {
                symbol_table::location_t loc =
                    (_st.lookup_symbol(prev_node_attr.value()));
                if ( loc == symbol_table::ID_EXCEPTIONAL )
                {
                    throw (undeclared_variable(prev_node_attr.value()));
                }
                return (std::make_pair(true, ins
                                       + new literal(
                                           static_cast< int >(loc))
                                       + new load));
            }
            else if ( prev_node_type == parse::CMD_ID )
            {
                return (std::make_pair(true, ins));
            }
            else if ( prev_node_type == parse::BEXPR_ID )
            {
                return (std::make_pair(true, ins));
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class factorcont_translator
        std::pair < bool, instruction_list > factorcont_translator::
        operator()(
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const& prev_node_attr) throw (
            translator_exception)
        {
            if ( prev_node_type == parse::FACTOR_ID )
            {
                if ( !(_left.size() > 0)  )
                {
                    // factor as parent
                    _left = ins;
                    return (std::make_pair(true,
                                           instruction_list()));
                }
                else
                {
                    // factor as right-most child
                    return (std::make_pair(true,
                                           _left + ins + new power));
                }
            }
            else if ( prev_node_type == lex::EXPOP_ID )
            {
                return (std::make_pair(true, ins));
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class termcont_translator
        std::pair < bool, instruction_list >
        termcont_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::TERM_ID )
            {
                _left = ins;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == lex::MULTOP_ID )
            {
                if ( prev_node_attr.value() == "/" )
                {
                    _op = boost::shared_ptr< script_instruction >(
                        new divide);
                }
                else
                {
                    _op = boost::shared_ptr< script_instruction >(
                        new multiply);
                }
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::FACTOR_ID )
            {
                return std::make_pair(true, _left + ins + _op);
            }
            else if ( prev_node_type == parse::TERMCONT_ID )
            {
                if ( !(_left.size() > 0) )
                {
                    // termcont as child of termcont
                    _left = ins;
                    return std::make_pair(true, instruction_list());
                }
                else
                {
                    // termcont as parent of termcont
                    return std::make_pair(true, ins);
                }
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class exprcont_translator
        std::pair < bool, instruction_list >
        exprcont_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::EXPR_ID )
            {
                _left = ins;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == lex::ADDOP_ID )
            {
                if ( prev_node_attr.value() == "-" )
                {
                    _op = boost::shared_ptr< script_instruction >(
                        new sub);
                }
                else
                {
                    _op = boost::shared_ptr< script_instruction >(
                        new add);
                }
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::TERM_ID )
            {
                return std::make_pair(true, _left + ins + _op);
            }
            else if ( prev_node_type == parse::EXPRCONT_ID )
            {
                if ( !(_left.size() > 0) )
                {
                    // exprcont as child of exprcont
                    _left = ins;
                    return std::make_pair(true, instruction_list());
                }
                else
                {
                    // exprcont as parent of exprcont
                    return std::make_pair(true, ins);
                }
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class relcont_translator
        std::pair < bool, instruction_list >
        relcont_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::REL_ID )
            {
                _left = ins;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == lex::RELOP_ID )
            {
                if ( prev_node_attr.value() == "<" )
                {
                    _op = boost::shared_ptr< script_instruction >
                          ( new less_than );
                }
                else if ( prev_node_attr.value() == "=" )
                {
                    _op = boost::shared_ptr< script_instruction >
                          ( new equals );
                }
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::EXPR_ID )
            {
                return std::make_pair(true, _left + ins + _op);
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class llit_translator
        std::pair < bool, instruction_list >
        llit_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::CONJ_ID )
            {
                _2nd_visit = true;
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == parse::CONJCONT_ID )
            {
                _2nd_visit = true;
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == parse::REL_ID )
            {
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == lex::NOTOP_ID )
            {
                _negate = true;
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == parse::LLIT_ID )
            {
                if ( !_2nd_visit )
                {
                    _2nd_visit = true;
                    return std::make_pair(true, ins);
                }
                else
                {
                    if ( _negate )
                    {
                        return std::make_pair(true,
                                              ins
                                              + new logical_not);
                    }
                    else
                    {
                        return std::make_pair(true, ins);
                    }
                }
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class conjcont_translator
        std::pair < bool, instruction_list >
        conjcont_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::CONJ_ID )
            {
                _left = ins;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::CONJCONT_ID )
            {
                if ( _left.size() <= 0 )
                {
                    _left = ins;
                    // previous node was parent
                    return std::make_pair(true, instruction_list());
                }
                else
                {
                    // previous node was child
                    return std::make_pair(true, ins);
                }
            }
            else if ( prev_node_type == lex::ANDOP_ID )
            {
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::LLIT_ID )
            {
                return std::make_pair(
                           true,
                           _left + ins +
                           new logical_and);
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class bexprcont_translator
        std::pair < bool, instruction_list >
        bexprcont_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::BEXPR_ID )
            {
                _left = ins;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::BEXPRCONT_ID )
            {
                if ( _left.size() <= 0 )
                {
                    _left = ins;
                    // previous node was parent
                    return std::make_pair(true, instruction_list());
                }
                else
                {
                    // previous node was child
                    return std::make_pair(true, ins);
                }
            }
            else if ( prev_node_type == lex::OROP_ID )
            {
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::CONJ_ID )
            {
                return std::make_pair(
                           true,
                           _left + ins +
                           new logical_or);
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class cmd_translator
        std::pair < bool, instruction_list >
        cmd_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::STMT_ID )
            {
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == parse::BASE_ID )
            {
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == lex::CMD_TOK_ID )
            {
                command_registry::command_ptr_t command(_cr.get_command(
                                                            prev_node_attr.
                                                            value()));
                if ( command != command_registry::command_ptr_t() )
                {
                    _command = command;
                    return std::make_pair(true, ins);
                }
                else
                {
                    throw (undefined_command(prev_node_attr.value()));
                }
            }
            else if ( prev_node_type == parse::ARGLST_ID )
            {
                return std::make_pair(true, ins +  _command);
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class asgn_translator
        std::pair < bool, instruction_list >
        asgn_translator::operator () (
            instruction_list const &ins,
            parser_id_t prev_node_type,
            parse_node_attributes const &
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::STMT_ID )
            {
                return (std::make_pair(true, ins));
            }
            else if ( prev_node_type == lex::ID_TOK_ID )
            {
                symbol_table::location_t loc = _st.lookup_symbol(
                    prev_node_attr.
                    value());
                if (loc == symbol_table::ID_EXCEPTIONAL)
                {
                    throw (undeclared_variable(prev_node_attr.value()));
                }
                // TODO:  add type checking here

                // at this point the variable is known to be declared and of the
                // right type
                return std::make_pair(true, ins + new literal(loc));
            }
            else if ( prev_node_type == parse::EXPR_ID )
            {
                return (std::make_pair(true, ins + new store));
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        #ifdef TESTING1
        std::string test_asgn_translator_operator_parens()
        {
            parse_node_attributes attr;
            symbol_table st;
            instruction_list il;
            parse_node_attributes prev_attr;
            prev_attr.value() = "$prev";
            st.add_symbol("$prev");

            asgn_translator at (parse::ASGN_ID, attr, st);
            std::pair < bool, instruction_list > result_pair = at(
                il,
                lex::ID_TOK_ID,
                prev_attr);

            if(!(result_pair.first)
               || (result_pair.second !=
                   (il + new literal(st.lookup_symbol("$prev")))))
            {
                return "Error 1";
            }

            return "";
        }
        #endif

        //! \class decl_translator
        std::pair < bool, instruction_list >
        decl_translator::operator ()( instruction_list const &ins,
                                     parser_id_t prev_node_type,
                                     parse_node_attributes const
                                     &prev_node_attr)
        throw (translator_exception)
        {
            if (prev_node_type == lex::TYPE_TOK_ID)
            {
                // check if we have a valid type, there will be more to do later
                if (type::exists(prev_node_attr.value()))
                {
                    return (std::make_pair(true, ins));
                }
                else
                {
                    throw translator_exception(std::
                                               string
                                               ("reference to undefined type: ")
                                               + prev_node_attr.value());
                }
            }
            else if (prev_node_type == lex::ID_TOK_ID)
            {
                _mem_loc_first = (_st.add_symbol(prev_node_attr.value()));
                return (std::make_pair(true, ins));
            }
            else if (prev_node_type == parse::DECLCONT_ID)
            {
                if ( ins.size() == 0  )
                {
                    return std::make_pair(true, _pre_decl
                                          + new literal(
                                              _mem_loc_first)
                                          + ins
                                          + new store);
                }
                else
                {
                    return std::make_pair(true,
                                          _pre_decl
                                          + new literal(
                                              _mem_loc_first)
                                          + ins
                                          + new store );
                }
            }
            else if (prev_node_type == parse::STMT_ID)
            {
                _pre_decl = ins;
                return (std::make_pair(true, instruction_list()));
            }
            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class cond_translator
        std::pair < bool, instruction_list >
        cond_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::BLOCK_ID )
            {
                    _left = ins;
                    return(std::make_pair(true, instruction_list()));
            }
            else if ( prev_node_type == lex::IF_TOK_ID )
            {
                return(std::make_pair(true, ins));
            }
            else if ( prev_node_type == parse::BEXPR_ID )
            {
                _left = _left + ins + new logical_not;
                return(std::make_pair(true, instruction_list()));
            }
            else if ( prev_node_type == parse::STMTLST_ID )
            {
                _body = ins;
                return(std::make_pair(true, instruction_list()));
            }
            else if ( prev_node_type == parse::CONDCONT_ID )
            {
                if ( ins.size() == 0 )
                {
                    // a slight optimization for empty continuations
                    return std::make_pair(true, _left 
                                              + new literal(_body.size()+1)
                                              + new cond_rel_jump
                                              + _body );
                }
                else
                {
                    return(std::make_pair(true, _left
                                          + new literal(_body.size()+3)
                                          + new cond_rel_jump
                                          + _body
                                          // we must add one because we want to be
                                          // one _past_ the final instruction of
                                          // the following block
                                          + new literal(ins.size()
                                                                     +1)
                                          + new rel_jump
                                          + ins));
                }
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class condcont_translator
        std::pair < bool, instruction_list >
        condcont_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( ( prev_node_type == parse::CONDCONT_ID )
                 || ( prev_node_type   == parse::COND_ID ) )
            {
                if ( !_2nd_visit )
                {
                    _2nd_visit = true;
                    return std::make_pair(true, instruction_list());
                }
                else
                {
                    if ( ins.size() == 0 )
                    {
                        // a slight optimization for empty continuations
                        return std::make_pair(true, _left 
                                + new literal(_body.size()+1)
                                + new cond_rel_jump
                                + _body );
                    }
                    else
                    {
                        instruction_list neg_jump
                            = inst_list(new literal(_body.size()+3))
                                + new cond_rel_jump;
                        instruction_list pos_jump
                            = inst_list(new literal(ins.size()+1))
                            + new rel_jump;

                        return(std::make_pair(true, _left
                                    + neg_jump 
                                    + _body
                                    + pos_jump 
                                    + ins));
                    }
                }
            }
            else if ( prev_node_type == lex::ELSEIF_TOK_ID )
            {
                _else = false;
                return(std::make_pair(true, ins));
            }
            else if ( prev_node_type == parse::BEXPR_ID )
            {
                _left = ins + new logical_not;
                return(std::make_pair(true, instruction_list()));
            }
            else if ( prev_node_type == lex::ELSE_TOK_ID )
            {
                _else = true;
                return(std::make_pair(true, ins));
            }
            else if ( prev_node_type == parse::STMTLST_ID )
            {
                if ( _else )
                {
                    return std::make_pair(true, ins);
                }
                _body = ins;
                return std::make_pair(true, instruction_list());
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        //! \class while_translator
        std::pair < bool, instruction_list >
        while_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == parse::BLOCK_ID )
            {
                _left = ins;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == parse::BEXPR_ID )
            {
                _condition = ins + new logical_not;
                return std::make_pair(true, instruction_list());
            }
            else if ( prev_node_type == lex::RBR_ID )
            {
                return std::make_pair(true, _left 
                        + _condition
                        + new literal(_body.size()+3)
                        + new cond_rel_jump
                        + _body
                        + new literal((_body.size()+_condition.size()+3)*(-1))
                        + new rel_jump);
            }
            else if ( prev_node_type == parse::STMTLST_ID )
            {
                _body = ins;
                return std::make_pair( true, instruction_list() );
            }
            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }


        std::pair < bool, instruction_list >
        prog_translator::operator () (
            instruction_list const& ins,
            parser_id_t prev_node_type,
            parse_node_attributes const&
            prev_node_attr)
        throw (translator_exception)
        {
            if ( prev_node_type == NIL_ID )
            {
                // very first symbol, just keep going
                return std::make_pair(true, ins);
            }
            else if ( prev_node_type == parse::STMTLST_ID )
            {
                return std::make_pair(true, ins
                                            // go to script start
                                            + new literal(0)
                                            + new jump );
            }

            throw (corrupted_parse_tree(_node_type, prev_node_type));
        }

        std::pair < bool, instruction_list >
            stmt_translator::operator () (instruction_list const& ins,
                                          parser_id_t prev_node_type,
                                          parse_node_attributes const& prev_node_attr)
            throw (translator_exception)
            {
                if ( prev_node_type == parse::CMD_ID )
                {
                    return std::make_pair(true, (ins + new pop));
                }
                else
                {
                    return std::make_pair(true, ins);
                }
            }

    }
}
