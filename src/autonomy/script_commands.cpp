#include <autonomy/script_commands.hpp> 
#include <autonomy/action/move.hpp>
#include <autonomy/action/mine.hpp>
#include <autonomy/action/scan.hpp>
#include <autonomy/action/unload.hpp>
#include <autonomy/action/create_drone.hpp>
#include <autonomy/action/where.hpp>
#include <autonomy/action/destroy_entity.hpp>
#include <ctime>

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::move>)
BOOST_CLASS_EXPORT(autonomy::move)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::get_x>)
BOOST_CLASS_EXPORT(autonomy::get_x)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::get_y>)
BOOST_CLASS_EXPORT(autonomy::get_y)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::scan>)
BOOST_CLASS_EXPORT(autonomy::scan)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::is_drone>)
BOOST_CLASS_EXPORT(autonomy::is_drone)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::is_asteroid>)
BOOST_CLASS_EXPORT(autonomy::is_asteroid)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::is_base>)
BOOST_CLASS_EXPORT(autonomy::is_base)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::rand_dir>)
BOOST_CLASS_EXPORT(autonomy::rand_dir)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::mine>)
BOOST_CLASS_EXPORT(autonomy::mine)

BOOST_CLASS_EXPORT(autonomy::script_instruction_base<autonomy::unload>)
BOOST_CLASS_EXPORT(autonomy::unload)


namespace autonomy {
    const int SCAN_FUEL_COST = 1;
    const int MOVE_FUEL_COST = 2;
    const int MINE_FUEL_AMOUNT = 5;
    const int UNLOAD_FUEL_AMOUNT = 5;

        unsigned int move::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            // note the implication here that even attempting to move
            // requires fuel
            if ( MOVE_FUEL_COST < drone.get_fuel() )
            {
                drone.drain_fuel(MOVE_FUEL_COST);
                int vert(drone.pop_stack());
                int horz(drone.pop_stack());
                drone.universe()->send_action(which_queue,
                        static_cast<action_generic*>(
                            new action::move_direction(horz, vert, drone)));
#if DEBUG
                std::cerr << "Created move action, sent:  " << entity_id_t(drone) << std::endl; 
#endif
                return 1;
            }
            else
            {
                drone.drain_fuel(drone.get_fuel());
                drone.universe()->send_action(which_queue, 
                                              new action::hide_entity(drone));
                return 1;
            }
        }

        unsigned int get_x::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            drone.universe()->send_action(which_queue,
                    static_cast<action_generic*>(
                        new action::where(action::where::X, drone)));
            return 1;
        }

        unsigned int get_y::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            drone.universe()->send_action(which_queue,
                    static_cast<action_generic*>(
                        new action::where(action::where::Y, drone)));
            return 1;
        }

        unsigned int scan::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            if(SCAN_FUEL_COST < drone.get_fuel())
            {
                int y(drone.pop_stack());
                int x(drone.pop_stack());
                drone.drain_fuel(SCAN_FUEL_COST);
                drone.universe()->send_action(which_queue,
                        static_cast<action_generic*>(
                            new action::scan(util::coord_pair(x, y), drone)));
                return 1;
            }
            else 
            {
                drone.drain_fuel(drone.get_fuel());
                drone.universe()->send_action(which_queue, 
                                              new action::hide_entity(drone));
                return 1;
            }
        }

        unsigned int is_drone::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            int entity_type(drone.pop_stack());
            if ( entity_type == static_cast<int>(entity::scripted_drone::DRONE) )
                drone.push_stack(1);
            else
                drone.push_stack(0);
            return 0;
        }

        unsigned int is_asteroid::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            int entity_type(drone.pop_stack());
            if ( entity_type == static_cast<int>(entity::scripted_drone::ASTEROID) )
                drone.push_stack(1);
            else
                drone.push_stack(0);
            return 0;
        }

        unsigned int is_base::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            int entity_type(drone.pop_stack());
            if ( entity_type == static_cast<int>(entity::scripted_drone::BASE) )
                drone.push_stack(1);
            else
                drone.push_stack(0);
            return 0;
        }

    boost::mt19937 rand_dir::rng(time(NULL));
    boost::uniform_int<> rand_dir::dir(-1,1);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rand_dir::_rand_dir(rng,dir);

        unsigned int rand_dir::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            drone.push_stack(_rand_dir());
            return 0;
        }

        unsigned int mine::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            int y(drone.pop_stack());
            int x(drone.pop_stack());

            drone.universe()->send_action(which_queue,
                    static_cast<action_generic*>(
                        new action::mine_location( util::coord_pair(x,y),
                            MINE_FUEL_AMOUNT, drone)));
            return 2;
        }
        
        unsigned int unload::execute(size_t which_queue, entity::scripted_drone & drone)
        {
            if ( UNLOAD_FUEL_AMOUNT < drone.get_fuel() )
            {
               int y(drone.pop_stack());
               int x(drone.pop_stack());

               drone.universe()->send_action(which_queue,
                       static_cast<action_generic*>(
                           new action::unload_fuel( util::coord_pair(x,y),
                               UNLOAD_FUEL_AMOUNT, drone)));
               return 2;
            }
            else 
            {
                drone.drain_fuel(drone.get_fuel());
                drone.universe()->send_action(which_queue, 
                                              new action::hide_entity(drone));
                return 2;
            }
        }
}
