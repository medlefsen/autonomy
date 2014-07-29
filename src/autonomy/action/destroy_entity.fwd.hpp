#ifndef AUTONOMY_ACTION_DESTROY_ENTITY_FWD_HPP
#define AUTONOMY_ACTION_DESTROY_ENTITY_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>

namespace autonomy
{
    namespace action
    {
        class hide_entity;
        class destroy_entity;
    }

    typedef action_handler_base<action::hide_entity, entity::universe>
        hide_entity_handler_base_t;
    typedef action_handler_base<action::destroy_entity, entity::universe>
        destroy_entity_handler_base_t;
}
#endif
