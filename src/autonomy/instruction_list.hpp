//! \file
//! \brief
//!
//! Primary Author:  Dylan Leeman

#ifndef AUTONOMY_INSTRUCTION_LIST_HPP
#define AUTONOMY_INSTRUCTION_LIST_HPP
#include <vector>

#include <boost/shared_ptr.hpp>

#include <autonomy/script_instruction.hpp>

namespace autonomy 
{
    typedef std::vector< boost::shared_ptr< script_instruction > > instruction_list;

    inline
    instruction_list operator + (const instruction_list& left,
                                 const instruction_list& right)
    {
        instruction_list il(left);
        il.insert(il.end(), right.begin(), right.end());
        return il;
    }

    template < typename ptr_type >
    inline
    instruction_list operator + (const ptr_type left,
                                 const instruction_list& right)
    {
        instruction_list il(right);
        il.insert(il.begin(), boost::shared_ptr< script_instruction >(left));
        return il;
    }

    template < typename ptr_type >
    inline
    instruction_list& operator += (instruction_list& left, const ptr_type right)
    {
        left.push_back(boost::shared_ptr< script_instruction >(right));
        return left;
    }

    template < typename ptr_type >
    inline
    instruction_list operator + (const instruction_list& left,
                                 const ptr_type right)
    {
        instruction_list il(left);
        il += right;
        return il;
    }

    template < typename ptr_type >
    inline
    instruction_list inst_list(const ptr_type inst)
    {
        return instruction_list(1, boost::shared_ptr< script_instruction >(inst));
    }

    bool operator== (instruction_list const& left,
                     instruction_list const& right);

    bool operator!= (instruction_list const& left,
                     instruction_list const& right);

}
#endif
