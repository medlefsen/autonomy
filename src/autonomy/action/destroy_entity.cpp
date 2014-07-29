#include <autonomy/action/destroy_entity.hpp>

namespace autonomy
{
    BOOST_CLASS_EXPORT(hide_entity_handler_base_t);
    BOOST_CLASS_EXPORT(destroy_entity_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(hide_entity);
        BOOST_CLASS_EXPORT(destroy_entity);

        action_handler_generic * hide_entity::default_handler()
        {
            return new action_handler::hide_entity_default;
        }

        action_handler_generic * destroy_entity::default_handler()
        {
            return new action_handler::destroy_entity_default;
        }
    }
}
