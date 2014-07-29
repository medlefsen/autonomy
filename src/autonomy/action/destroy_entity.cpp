#include <autonomy/action/destroy_entity.hpp>

BOOST_CLASS_EXPORT(autonomy::hide_entity_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::destroy_entity_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::action::hide_entity);
BOOST_CLASS_EXPORT(autonomy::action::destroy_entity);

namespace autonomy
{

    namespace action
    {

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
