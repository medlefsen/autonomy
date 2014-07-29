#ifndef AUTONOMY_ACTION_HANDLER_FWD_HPP
#define AUTONOMY_ACTION_HANDLER_FWD_HPP
#include <autonomy/util/id.hpp>
namespace autonomy
{
    class action_handler_generic;

    template < typename ActionT, typename TargetT >
    class action_handler_base;

    typedef util::id<action_handler_generic*> action_handler_id_t;
}
#endif
