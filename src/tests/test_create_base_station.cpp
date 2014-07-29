#include <unistd.h>
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <autonomy/game.hpp>

#include <autonomy/action.hpp>
#include <autonomy/action/create_drone.hpp>

#include <autonomy/entity.hpp>
#include <autonomy/entity/base_station.hpp>
#include <autonomy/entity/universe.hpp>
using namespace std;
using namespace autonomy;

int main() {
   boost::thread            proc_thread;
   game                     mygame;
   util::coord_pair         station_loc(0,0);
   location_module< game >& loc = mygame.location_module();
   entity_id_t myuni(static_cast<entity_base*>(new entity::universe(mygame)));

   size_t q = 0;

   cout << "Adding myuni to the game's processor." << endl;
   mygame.processor().add(myuni);

   cout << "Sending action to myuni to create base_station." << endl;
   myuni->send_action(q, (new action::create_station(100, station_loc, myuni)));

   cout << "Starting the processor in a separate thread." << endl;
   proc_thread = boost::thread(boost::bind(&processor<game>::start,boost::ref(mygame.processor())));

   sleep(1);
   if (loc.query(station_loc) != entity_id_t()) cout << "Found base station.\n";

   cout << "Stopping the processor." << endl;
   mygame.processor().stop();

   proc_thread.join();
   return(0);
}
