#include <autonomy/action_handler/where_default.hpp>

namespace autonomy
{
    namespace action_handler
    {
        BOOST_CLASS_EXPORT(where_default);
        BOOST_CLASS_EXPORT(where_response_default);

        void where_default::execute( entity::universe & entity, 
                                     size_t which_queue )
        {
            location_module<game> & loc(entity.location_module());
            BOOST_FOREACH(action::where * wa, _action_group)
            {
                util::coord_pair where(loc.locate(entity_id_t(wa->subject())));
                wa->subject()->send_action(which_queue,
                        static_cast<action_generic*>(
                            new action::where_response(wa->query_dimension() 
                                                       == action::where::X ?
                                                        where.x() : where.y())));
            }
        }

        void where_response_default::execute( entity::scripted_drone & entity, 
                                              size_t which_queue )
        {
            BOOST_FOREACH(action::where_response * wr, _action_group)
            {
                entity.push_stack(wr->distance());
            }
        }
    }
}
