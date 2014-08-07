#include <autonomy/action_handler/destroy_entity_default.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::hide_entity_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::destroy_entity_default);

namespace autonomy
{
    namespace action_handler
    {

        void hide_entity_default::execute( entity::universe & entity )
        {
            location_module & loc (entity.location_module());
            for(auto& he : _action_group)
            {
                loc.remove(he->entity());
            }
        }

        void destroy_entity_default::execute( entity::universe & entity )
        {
            for(auto& de : _action_group)
            {
                entity.remove(de->entity());
            }
        }
    }
}
