#include <autonomy/entity/scripted_drone.hpp>

#include <typeinfo>

#include <boost/foreach.hpp>

#include <autonomy/action/destroy_entity.hpp>
#include <autonomy/action/scan.hpp>
#include <autonomy/action/mine.hpp>
#include <autonomy/action/move.hpp>
#include <autonomy/action/where.hpp>

#include <autonomy/entity/asteroid.hpp>
#include <autonomy/entity/base_station.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::entity::scripted_drone>);
BOOST_CLASS_EXPORT(autonomy::entity::scripted_drone);
namespace autonomy
{
    namespace entity
    {

        void scripted_drone::controller()
        {
            // process instructions, if necessary
            if ( _wait_ticks > 0 )
            {
                --_wait_ticks;
            }
            else
            {
                if ( get_fuel() <= 0 )
                {
                    universe()->send_action(new actor::destroy_entity(*this));
                    return;
                }
                else
                {
                    _wait_ticks = (*_script)[_pc]->execute(*this);
                    ++_pc;
                }
            }
        }

        void scripted_drone::goto_inst(int line)
        {
            --line;
            //_next_inst = _script->begin() +
            //(line % static_cast< int >(_script->size()));
            _pc = (line % static_cast< int >(_script->size()));
        }

        void scripted_drone::move_inst(int off)
        {
            // int next_index = _next_inst - _script->begin();
            // goto_inst(next_index + off);
            goto_inst(_pc + off);
        }
    }
}
