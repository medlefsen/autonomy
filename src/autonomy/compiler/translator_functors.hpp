//! \file translator_functors.hpp
//! \brief Translator functor declarations.

#ifndef AUTONOMY_COMPILER_TRANSLATOR_FUNCTORS_HPP
#define AUTONOMY_COMPILER_TRANSLATOR_FUNCTORS_HPP

#include <string>
#include <utility>

//#include <boost/spirit/core.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/shared_ptr.hpp>

#include <autonomy/instruction_list.hpp>

#include <autonomy/command_registry.hpp>
#include <autonomy/compiler/symbol_table.hpp>
#include <autonomy/compiler/parse_node_attributes.hpp>
#include <autonomy/compiler/translator_exceptions.hpp>

namespace autonomy 
{
    namespace compiler
    {
        //! \class translator_base
        //! \brief Base class for all translator functors.
        class translator_base
        {
            public:
                translator_base(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : _node_type(node_type),
                      _node_attr(node_attr),
                      _st(st), _cr(cr)
                {}

                virtual ~translator_base(){}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

                parse_node_attributes const& attributes() const
                {
                    return _node_attr;
                }
            protected:
                parser_id_t _node_type;
                parse_node_attributes _node_attr;
                symbol_table & _st;
                const command_registry & _cr;
        };

        //! \class base_translator
        //! \brief Translator for the "base" of an expression (a single unit).
        class base_translator
            : public translator_base
        {
            public:
                base_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr), 
                      _negate(false)
                {}

                virtual ~base_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                bool _negate;
        };

        //! \class factorcont_translator
        //! \brief Translator for exponent in expressions.
        class factorcont_translator
            : public translator_base
        {
            public:
                factorcont_translator(parser_id_t node_type,
                                      parse_node_attributes const& node_attr,
                                      symbol_table & st,
                                      const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}

                virtual ~factorcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
        };

        //! \class termcont_translator
        //! \brief Translator for multiplier/dividend of experessions.
        class termcont_translator
            : public translator_base
        {
            public:
                termcont_translator(parser_id_t node_type,
                                    parse_node_attributes const& node_attr,
                                    symbol_table & st,
                                    const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}

                virtual ~termcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
                boost::shared_ptr< script_instruction > _op;
        };

        //! \class exprcont_translator
        //! \brief Translator for addend/subtend of expressions.
        class exprcont_translator
            : public translator_base
        {
            public:
                exprcont_translator(parser_id_t node_type,
                                    parse_node_attributes const& node_attr,
                                    symbol_table & st,
                                    const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~exprcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
                boost::shared_ptr< script_instruction > _op;
        };

        //! \class relcont_translator
        //! \brief Translator for relational operators.
        class relcont_translator
            : public translator_base
        {
            public:
                relcont_translator(parser_id_t node_type,
                                   parse_node_attributes const& node_attr,
                                   symbol_table & st,
                                   const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~relcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
                boost::shared_ptr< script_instruction > _op;
        };

        //! \class llit_translator
        //! \brief Translator for boolean "literals".
        class llit_translator
            : public translator_base
        {
            public:
                llit_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr),
                      _2nd_visit(false), _negate(false)
                {}


                virtual ~llit_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                bool _2nd_visit;
                bool _negate;
        };

        //! \class conjcont_translator
        //! \brief Translator for conjoined boolean expressions.
        class conjcont_translator
            : public translator_base
        {
            public:
                conjcont_translator(parser_id_t node_type,
                                    parse_node_attributes const& node_attr,
                                    symbol_table & st,
                                    const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~conjcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
        };

        //! \class bexprcont_translator
        //! \brief Translator for disjoint boolean expressions.
        class bexprcont_translator
            : public translator_base
        {
            public:
                bexprcont_translator(parser_id_t node_type,
                                     parse_node_attributes const& node_attr,
                                     symbol_table & st,
                                     const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~bexprcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
        };

        //! \class cmd_translator
        //! \brief Translator for module commands.
        class cmd_translator
            : public translator_base
        {
            public:
                cmd_translator(parser_id_t node_type,
                               parse_node_attributes const& node_attr,
                               symbol_table & st,
                               const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}



                virtual ~cmd_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                command_registry::command_ptr_t _command;
        };

        //! \class asgn_translator
        //! \brief Translator for assignment statements.
        class asgn_translator
            : public translator_base
        {
            public:
                asgn_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~asgn_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);
        };

        #ifdef TESTING
        std::string test_asgn_translator_operator_parens();
        #endif

        //! \class decl_translator
        //! \brief Translator for variable delcarations.
        class decl_translator
            : public translator_base
        {
            public:
                decl_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~decl_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                symbol_table::location_t _mem_loc_first;
                instruction_list _pre_decl;
        };

        //! \class cond_translator
        //! \brief Translator for conditionals  (control statements).
        class cond_translator
            : public translator_base
        {
            public:
                cond_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}



                virtual ~cond_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
                instruction_list _body;
        };

        //! \class condcont_translator
        //! \brief Translator for "condconts"  (control statements).
        class condcont_translator
            : public translator_base
        {
            public:
                condcont_translator(parser_id_t node_type,
                                    parse_node_attributes const& node_attr,
                                    symbol_table & st,
                                    const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr),
                      _2nd_visit(false), _else(false)
                {}


                virtual ~condcont_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                bool _2nd_visit;
                bool _else;
                instruction_list _left;
                instruction_list _body;
        };

        //! \class while_translator
        //! \brief Translator for while loops (control statements).
        class while_translator
            : public translator_base
        {
            public:
                while_translator(parser_id_t node_type,
                                 parse_node_attributes const& node_attr,
                                 symbol_table & st,
                                 const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~while_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);

            private:
                instruction_list _left;
                instruction_list _condition;
                instruction_list _body;
        };

        //! \class prog_translator
        //! \brief Translator for the grammar start symbol.
        class prog_translator
            : public translator_base
        {
            public:
                prog_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~prog_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);
        };
        
        //! \class stmt_translator
        //! \brief Translator for the statement rule.
        // XXX:  This is a temporary hack for I3.
        class stmt_translator
            : public translator_base
        {
            public:
                stmt_translator(parser_id_t node_type,
                                parse_node_attributes const& node_attr,
                                symbol_table & st,
                                const command_registry & cr)
                    : translator_base(node_type, node_attr, st, cr)
                {}


                virtual ~stmt_translator()
                {}

                virtual std::pair < bool, instruction_list >
                operator () (instruction_list const& ins,
                             parser_id_t prev_node_type,
                             parse_node_attributes const& prev_node_attr)
                throw (translator_exception);
        };
    }
}
#endif
