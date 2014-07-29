//! \file type.cpp
//! \brief Implementation of functions for typing ADL.

#include <autonomy/compiler/type.hpp>

namespace autonomy
{
    namespace compiler
    {
        namespace type
        {
            bool exists(std::string type)
            {
                return (type == "int");
            }
        }
    }
}
