#include <autonomy/action_handler/where_default.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::where_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::where_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void where_default::execute( entity::universe & entity )
        {
            location_module & loc(entity.location_module());
            BOOST_FOREACH(action::where * wa, _action_group)
            {
                util::coord_pair where(loc.locate(entity_id_t(wa->subject())));
                wa->subject()->send_action(
                        static_cast<action_generic*>(
                            new action::where_response(wa->query_dimension() 
                                                       == action::where::X ?
                                                        where.x() : where.y())));
            }
        }

        void where_response_default::execute( entity::scripted_drone & entity )
        {
            BOOST_FOREACH(action::where_response * wr, _action_group)
            {
                entity.push_stack(wr->distance());
            }
        }
    }
}
