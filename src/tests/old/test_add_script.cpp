#include <iostream>

#include <autonomy/game.hpp>
#include <autonomy/entity/scripted_drone.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/script_instruction.hpp>
#include <autonomy/script_object.hpp>
#include <autonomy/script_library.hpp>

using namespace std;
using namespace autonomy;

int main()
{
   string filename;
   script_object_id_t my_script;
   script_library< game > my_library;

   cout << "Filename: ";
   cin >> filename;

   my_script = my_library.new_script("Test");

   my_library.set_script( my_script, "move(2,2,);" );

   return(0);
}
