//! \file type.hpp
//! \brief Header for enacting ADS type system.

#ifndef AUTONOMY_COMPILER_TYPE_TYPE_HPP
#define AUTONOMY_COMPILER_TYPE_TYPE_HPP
#include <string>

namespace autonomy 
{
    namespace compiler
    {
        namespace type
        {
            typedef std::string type_t; 

            bool exists(std::string type);
        }
    }
}
#endif
