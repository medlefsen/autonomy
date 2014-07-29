#include <autonomy/game.hpp>
#include <getopt.h>
#include <iostream>
#include <string>

using namespace autonomy;

int main( int argc, char ** argv)
{
   int ch;
   std::string filename = "";

   while ( (ch = getopt(argc, argv, "f:") ) != -1)
   {
      switch (ch)
      {
         case 'f':
            std::cout << "Running game using the commands given in " << optarg << std::endl;
            filename = optarg;
            break;
         case 'h':
         case '?':
         default:
            std::cout << "Usage: " << argv[0] << " [-f <filename>]" << std::endl
                      << "\t-f <filename>:\n\t\tRun game using <filename>, a list of commands to use." << std::endl
                      << "\t\tDo 'help' after running with no arguements to see possible commands." << std::endl;
            exit(1);
      }
   }

   if (filename != "")
      game new_game(filename);
   else
      game new_game;
#ifdef DEBUG
   std::cout << "Autonomy Finished!" << std::endl;
#endif
   return(0);
}
