#ifndef AUTONOMY_ACTION_FWD_HPP
#define AUTONOMY_ACTION_FWD_HPP
#include <autonomy/util/id.hpp>
namespace autonomy 
{
    class action_generic;

    template < typename EntityT >
    class action_base;

    typedef util::id<action_generic*> action_type_id_t;

    template < typename EntityT >
    class action_default_handler_cmp;
}
#endif
