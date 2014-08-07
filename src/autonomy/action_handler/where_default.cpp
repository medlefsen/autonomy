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
            for(auto& wa : _action_group)
            {
                util::coord_pair where(loc.locate(entity_id_t(wa->subject())));
                wa->subject()->send_action(
                        static_cast<action_generic*>(
                            new actor::where_response(wa->query_dimension() 
                                                       == actor::where::X ?
                                                        where.x() : where.y())));
            }
        }

        void where_response_default::execute( entity::scripted_drone & entity )
        {
            for(auto& wr : _action_group)
            {
                entity.push_stack(wr->distance());
            }
        }
    }
}
