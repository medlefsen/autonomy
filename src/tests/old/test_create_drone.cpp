#include <unistd.h>
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <autonomy/game.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/script_instruction.hpp>
#include <autonomy/script_builtins.hpp>
#include <autonomy/script_library.hpp>

#include <autonomy/action.hpp>
#include <autonomy/action/create_drone.hpp>

#include <autonomy/entity.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/scripted_drone.hpp>
using namespace std;
using namespace autonomy;

int main() {
   boost::thread            proc_thread;
   game                     mygame;
   util::coord_pair         drone_loc(1,1);
   location_module< game >& loc = mygame.location_module();
   entity_id_t myuni(static_cast<entity_generic*>(new entity::universe(mygame)));

   script_object_id_t my_script;
   script_library< game > my_library;

   my_script = my_library.new_script("Test");
   my_library.set_script( my_script, "move(2,2);" );
   my_library.compile_script(my_script);
   boost::shared_ptr<instruction_list> compiled_script(my_library.fetch_compiled_script( my_script ));

   size_t q = 0;

   cout << "Adding myuni to the game's processor." << endl;
   mygame.processor().add(myuni);

   cout << "Sending action to myuni to create drone." << endl;
   myuni->send_action(q, (new action::create_drone(100, drone_loc, compiled_script, myuni)));

   cout << "Starting the processor in a separate thread." << endl;
   proc_thread = boost::thread(boost::bind(&processor::start,boost::ref(mygame.processor())));

   sleep(1);
   if (loc.query(drone_loc) != entity_id_t()) cout << "Found drone.\n";

   cout << "Stopping the processor." << endl;
   mygame.processor().stop();

   proc_thread.join();
   return(0);
}
