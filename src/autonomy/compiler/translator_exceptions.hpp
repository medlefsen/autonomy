//! \file translator_exceptions.hpp
//! \brief Exception classes that may be thrown by the translator.
#ifndef AUTONOMY_COMPILER_TRANSLATOR_EXCEPTIONS_HPP
#define AUTONOMY_COMPILER_TRANSLATOR_EXCEPTIONS_HPP

#include <string>
#include <exception>

#include <autonomy/compiler/parser_ids.hpp>

namespace autonomy 
{
    namespace compiler
    {
        //! \class translator_exception
        //! \brief Generic translator exception.
        class translator_exception
            : public std::exception
        {
            public:
                translator_exception(std::string const& msg);

                ~translator_exception() throw ()
                {}

                virtual const char* what() const throw ();

            private:
                std::string _msg;
        };

        //! \class corrupted_parse_tree
        //! \brief Exception for parse trees recognized as malformed.
        class corrupted_parse_tree
            : public translator_exception
        {
            public:
                corrupted_parse_tree(parser_id_t at_node, parser_id_t prev_node);

                ~corrupted_parse_tree() throw ()
                {}
        };

        //! \class undeclared_variable
        //! \brief Thrown when attempting to reference an undeclared variable.
        class undeclared_variable
            : public translator_exception
        {
            public:
                undeclared_variable(std::string const& symbol);

                ~undeclared_variable() throw ()
                {}
        };

        //! \class undefined_command
        //! \brief Thrown when attempting to access an unavailable command.
        class undefined_command
            : public translator_exception
        {
            public:
                undefined_command(std::string const& symbol);

                ~undefined_command() throw ()
                {}
        };
    }
}
#endif
