#include <autonomy/action_handler/destroy_entity_default.hpp>

namespace autonomy
{
    namespace action_handler
    {
        BOOST_CLASS_EXPORT(hide_entity_default);
        BOOST_CLASS_EXPORT(destroy_entity_default);

        void hide_entity_default::execute( entity::universe & entity, 
                                           size_t which_queue )
        {
            location_module<game> & loc (entity.location_module());
            BOOST_FOREACH(action::hide_entity * he, _action_group)
            {
                loc.remove(he->entity());
            }
        }

        void destroy_entity_default::execute( entity::universe & entity, 
                                              size_t which_queue )
        {
            processor & proc(entity.processor());
            BOOST_FOREACH(action::destroy_entity * de, _action_group)
            {
                proc.remove(de->entity());
            }
        }
    }
}
