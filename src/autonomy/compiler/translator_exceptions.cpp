//! \file translator_exceptions.cpp
//! \brief Implementation of translator exception classes.

#include <boost/lexical_cast.hpp>

#include <autonomy/compiler/translator_exceptions.hpp>

namespace autonomy 
{
    namespace compiler
    {
        //! \class translator_exception
        //! \brief Generic translator exception.
        translator_exception::translator_exception(std::string const& msg)
            : exception(), _msg(msg)
        {
            _msg = "Translator error: " + _msg;
        }

        const char* translator_exception::what() const throw ()
        {
            return (_msg.c_str());
        }

        //! \class corrupted_parse_tree
        //! \brief Exception for parse trees recognized as malformed.
        corrupted_parse_tree::corrupted_parse_tree(parser_id_t at_node,
                                                   parser_id_t prev_node)
            : translator_exception((std::string(
                                        "corrupted parse tree [at parser = ") +
                                    boost::lexical_cast < std::string >
                                    (at_node) + ", previous parser = " +
                                    boost::lexical_cast < std::string >
                                    (prev_node) + "]"))
        {}

        //! \class undeclared_variable
        undeclared_variable::undeclared_variable(std::string const& symbol)
            : translator_exception("undefined reference to variable:  "  +
                                   symbol)
        {}

        //! \class undefined_command
        undefined_command::undefined_command(std::string const& symbol)
            : translator_exception("undefined reference to command:  " + symbol)
        {}
    }
}
