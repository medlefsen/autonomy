//! \file
//! \brief
//! 
//! Primary Author:  Andrew Fitz Gibbon
//! Contributing Authors:  Dylan Leeman, Dylan Parkhurst, Aaron Weeden

#include <autonomy/standard/dui.hpp>

#include <limits.h>
#include <unistd.h>

#include <typeinfo>

#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/integer_traits.hpp>

#include <autonomy/script_builtins.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/script_instruction.hpp>

#include <autonomy/standard/move.hpp>
#include <autonomy/standard/create_drone.hpp>
#include <autonomy/standard/create_station.hpp>
#include <autonomy/standard/create_asteroid.hpp>

#include <autonomy/standard/asteroid.hpp>
#include <autonomy/standard/base_station.hpp>
#include <autonomy/standard/scripted_drone.hpp>

namespace autonomy { namespace standard
{
   const int STATION_FUEL = 100;
   const int MAP_MIN      = INT_MIN;
   const int MAP_MAX      = INT_MAX;


   dui::dui()
       : _interactive(true),
         _started(false),
         _has_quit(false)
   {
      _dui_thread = boost::thread(boost::bind(&dui::run,boost::ref(*this),boost::ref(std::cin)));
   }


   dui::dui(std::string filename)
       : _interactive(false),
         _started(false),
         _has_quit(false)
   {
      _dui_thread = boost::thread(boost::bind(&dui::run_file,boost::ref(*this),filename));
   }

   dui::~dui()
   {
       if(!has_quit())
       {
           end_game();
       }
       _dui_thread.join();
   }


   void dui::run(std::istream & is)
   {
      cmd_map_t   cmd_map;
      std::string cmd;
      cmd_map["help"]    = &dui::help;
      cmd_map["start"]   = &dui::start_game;
      cmd_map["execute"] = &dui::run_for;
      cmd_map["sleep"]   = &dui::sleep_for;
      cmd_map["create"]  = &dui::create_entity;
      cmd_map["save"]    = &dui::save_game;
      cmd_map["load"]    = &dui::load_game;
      cmd_map["status"]  = &dui::status;
      cmd_map["pause"]   = &dui::pause_game;
      cmd_map["resume"]  = &dui::resume_game;
      cmd_map["stop"]    = &dui::stop_game;
      cmd_map["quit"]    = &dui::end_game;
      cmd_map["exit"]    = &dui::end_game;

      if (_interactive)
      {
         std::cerr << "Welcome to Autonomy: A Space Programming Game!" << std::endl
                   << "\tType 'help' at the prompt to see a list of available commands." << std::endl
                   << "autonomy> ";
      }
      is >> cmd;

      while(!_has_quit && is.good())
      {
         typename cmd_map_t::iterator i = cmd_map.find(cmd);
         if ( i == cmd_map.end() )
         {   
            std::cerr << "Invalid Command!" << std::endl;
         }   
         else
         {
            (this->*(i->second))(is);
         }

         // If we don't check _has_quit here, the dui
         // will wait for more input before quitting.
         if (!_has_quit)
         {
            if (_interactive)
               std::cerr << "autonomy> ";
            is >> cmd;
         }
      }
#ifdef DEBUG
      std::cerr << "DUI: Run finished" << std::endl;
#endif
   }


   void dui::run_file(std::string filename)
   {
      std::ifstream file(filename.c_str());
      if (!file.good())
      {
         std::cerr << "Bad filename!" << std::endl;
      }

      run(file);
      _interactive = true;
      run(std::cin);
   }
   

   void dui::help(std::istream & is)
   {
      std::cerr << "A list of helpful commands:" << std::endl
                << "\thelp:     Displays this list of commands again." << std::endl
                << "\tstart:   Starts a new game." << std::endl
                << "\texecute: Runs the processor(s) for a specified number of ticks." << std::endl
                << "\tsleep:   Suspends debug_ui operation for a specified number of microseconds." << std::endl
                << "\tsave:    Saves the current game." << std::endl
                << "\tload:    Loads from a saved game file." << std::endl
                << "\tcreate:  Creates a given entity at the given point." << std::endl
                << "\tstatus:  Prints out various information about the game." << std::endl
                << "\tpause:   Pauses the game." << std::endl
                << "\tresume:  Starts up a previously paused game." << std::endl
                << "\tstop:    Ends the game but does not quit the console." << std::endl
                << "\tquit:    Ends the game and quits the console." << std::endl;
   }


   void dui::start_game(std::istream & is)
   {
      if (!get_game().processor().is_going() && !_started)
      {
         std::cerr << "Starting the game..." << std::endl;

         if (!create_base()) return; 

#ifdef DEBUG
         std::cerr << "start_game(): _started = true" << std::endl;
#endif
         started_mutex.lock();
         _started = true;
         started_mutex.unlock();

#ifdef DEBUG
         std::cerr << "start_game(): processor.start()" << std::endl;
#endif

         _proc_thread = boost::thread(boost::bind(&processor::start, boost::ref(get_game().processor()) ));
      }
      else if(get_game().processor().is_going())
      {
         std::cerr << "A game is already running!" << std::endl;
      }
      else if(_started)
      {
        std::cerr << "A game has already been created!" << std::endl;
        resume_game();
      }
      else
      {
        std::cerr << "You broke something entirely different there." << std::endl;
      }
   }
   

   void dui::run_for(std::istream & is)
   {
     unsigned int ticks;
     
     if (_interactive)
        std::cerr << "Number of ticks?: ";
     ticks = safe_int_input(is);
   
     if (!get_game().processor().is_going()) 
     {
        std::cerr << "Executing:  " << ticks << " ticks." << std::endl;

        create_base();

        // By doing start here as processor.start instead of a thread
        // means that control will only return to the DUI once 
        // the ticks have completed.
        //_proc_thread = boost::thread(boost::bind(&processor::start, boost::ref(_proc),ticks));
        get_game().processor().start(ticks);
     }
     else
     {
        std::cerr << "The game is already running!" << std::endl;
     }
   }
   

   void dui::sleep_for(std::istream & is)
   {
     unsigned int microsecs;
   
     if (_interactive)
        std::cerr << "How many microseconds? ";
     is >> microsecs;
   
     std::cerr << "Sleeping for " << microsecs << " microseconds." << std::endl;
     usleep(microsecs);
   }
   

   void dui::create_entity(std::istream & is)
   {
      int                    x,y,fuel;
      std::string            type;
      std::string            filename;
      util::coord_pair       entity_loc;
      script_object_id_t     my_script;
      std::string            compiler_errors;
   
      if (_interactive)
         std::cerr << "Create drone or asteroid?: ";
      is >> type;
   
      if (type == "asteroid")
      {   
         if (_interactive)
            std::cerr << "x? ";
         x = safe_int_input(is);

         if (_interactive)
            std::cerr << "y? ";
         y = safe_int_input(is);

         if (_interactive)
            std::cerr << "Fuel? ";
         fuel = safe_int_input(is);
   
         entity_loc.x() = x;
         entity_loc.y() = y;
  	 
	      if((typeid(get_game().location_module().query(entity_loc)) == typeid(asteroid))
	         ||(typeid(get_game().location_module().query(entity_loc)) == typeid(drone))
	         ||(typeid(get_game().location_module().query(entity_loc)) == typeid(base_station)))
         {
	         std::cerr << "An entity already exists at " << entity_loc << std::endl;
         }
	      else
	      {
	         get_game().uni()->send_action<create_asteroid>(fuel, entity_loc, get_game().uni());
         }
      }
      else if (type == "drone")
      {
         if (_interactive)
            std::cerr << "Filename?: " << std::endl;
         is >> filename;
   
         if (_interactive)
            std::cerr << "x? ";
         x = safe_int_input(is);

         if (_interactive)
            std::cerr << "y? ";
         y = safe_int_input(is);

         if (_interactive)
            std::cerr << "Fuel? ";
         fuel = safe_int_input(is);
   
         std::ifstream file(filename.c_str());
         if (!file.good())
         {
            std::cerr << "Bad filename!" << std::endl;
            return;
         }
   
         entity_loc.x() = x;
         entity_loc.y() = y;
   
         my_script = lib_.new_script(filename);
         lib_.read_script( my_script, file );

         compiler_errors = lib_.compile_script(my_script);
         if ( compiler_errors != std::string() )
         {
            std::cerr << compiler_errors << std::endl;
         }
         else
         {
            boost::shared_ptr<instruction_list> compiled_script(lib_.fetch_compiled_script( my_script ));
       
#ifdef DEBUG
           BOOST_FOREACH( boost::shared_ptr<script_instruction> a, *compiled_script )
           {
              std::cerr << a->name() << std::endl;
           }
#endif
   
           get_game().uni()->send_action<create_drone>(fuel, entity_loc, compiled_script, get_game().uni());
         }
      }
      else
         std::cerr << "Unrecognized type!" << std::endl;

      if (_interactive)
         std::cerr << std::endl;
   }
   

   void dui::save_game(std::istream & is)
   {
      pause_game();
      std::string filename;
      
      if (_interactive)
         std::cerr << "\tFilename?: ";
      is >> filename;
   
      if (get_game().save(filename))
          std::cerr << "Saved successfully" << std::endl;
      else
          std::cerr << "Save failed" << std::endl;
   }
   

   void dui::load_game(std::istream & is)
   {
      std::string filename;

      if (get_game().processor().is_going())
         std::cerr << "The game must be paused before loading." << std::endl; 
      else
      {
	      if (_interactive)
	         std::cerr << "\tFilename?: ";
         is >> filename;
   
         if( get_game().restore(filename))
             std::cerr << "Loaded successfully" << std::endl;
         else
             std::cerr << "Load failed" << std::endl;
      }
   }
   

   void dui::status(std::istream & is)
   {
      util::coord_pair sw(MAP_MIN,MAP_MIN);
      util::coord_pair ne(MAP_MAX,MAP_MAX);
      typename location_module ::view_ptr_t  current_view = get_game().location_module().view(sw,ne);
      typename std::vector< typename location_module::relation_t >::iterator view_iterator = current_view->begin();
      entity_id_t current_entity;
   
      if (get_game().processor().is_going())
      {
         std::cerr << "The game is running." << std::endl;
      }
      else if (_started)
      {
         std::cerr << "The game is paused." << std::endl;
      }
      else
      {
         std::cerr << "The game has not started." << std::endl;
      }
   
      std::cerr << "Total number of entities: " << current_view->size() << std::endl;
   
      if (current_view->size() > 0)
      {
         std::cerr << "Individual entities:" << std::endl;
         while ( view_iterator != current_view->end() )
         {
            current_entity = view_iterator->first;
      
            if (typeid(*current_entity) == typeid(base_station))
            {
               std::cerr << "\tBase Station"; 
               std::cerr << " (f:" << static_cast <drone*>(&(*current_entity))->get_fuel() << ')';
            }
            else if (typeid(*current_entity) == typeid(asteroid))
            {
               std::cerr << "\tAsteroid";
               std::cerr << " (f:" << static_cast <asteroid*>(&(*current_entity))->get_fuel() << ')';
            }
            else if (typeid(*current_entity) == typeid(scripted_drone))
            {
               std::cerr << "\tScripted Drone";
               std::cerr << " (f:" << static_cast <scripted_drone*>(&(*current_entity))->get_fuel() << ')';
            }
            else
            {
               std::cerr << "\tUnknown entity";
            }
            std::cerr  << ":\t"
                  << view_iterator->second
                  << std::endl;
      
            ++view_iterator;
         }
      }
   }
   

   void dui::pause_game(std::istream & is)
   {
     if(!_started)
     {
       std::cerr << "You have not yet started a game!" << std::endl;
     }
     else
     {
      get_game().pause();
      std::cerr << "Game Paused." << std::endl;
     }
   }
   

   void dui::resume_game(std::istream & is)
   {
      if (!get_game().processor().is_going() && _started) 
      {
         std::cerr << "Resuming game..." << std::endl;
   
         _proc_thread = boost::thread(
                          boost::bind(&processor::start,
                                      boost::ref(get_game().processor()),
                                      boost::integer_traits<unsigned int>::max() ));
      }
      else if(!_started)
      {
        std::cerr << "You have not yet started a game!" << std::endl;
      }
      else
      {
         std::cerr << "The game is already running!" << std::endl;
      }
   }
   

   void dui::stop_game(std::istream & is)
   {
      get_game().pause();
#ifdef DEBUG
    std::cerr << "Paused!" << std::endl; 
#endif
      get_game().location_module().clear();

      started_mutex.lock();
      _started = false;
      started_mutex.unlock();

#ifdef DEBUG
    std::cerr << "Stopping" << std::endl;
#endif
      get_game().processor().stop();
#ifdef DEBUG
      std::cerr << "Joining" << std::endl;
#endif
      _proc_thread.join();
      std::cerr << "Ended the game." << std::endl;
   }
   

   void dui::end_game(std::istream & is)
   {
      std::cerr << "Exiting the game..." << std::endl;

      has_quit_mutex.lock();
      _has_quit = true;
      has_quit_mutex.unlock();
      
#ifdef DEBUG
      std::cerr << "processor.stop()" << std::endl;
#endif
      if(_started)
          stop_game();
#ifdef DEBUG
      std::cerr << "Done with end_game" << std::endl;
#endif
   }
   

   int dui::safe_int_input(std::istream & is)
   {
      int input;

      while(!(is >> input))
      {
         is.clear();
         is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
         std::cerr << "Please input integer value: ";
      }

      return input;
   }

   template <typename T>
       boost::optional<T> prompt(std::istream & is, std::string prompt)
       {
           T input;
           std::cerr << prompt;
           is >> input;
           if(is.good())
               return boost::optional<T>(input);
           else
               return boost::optional<T>();
       }


   bool dui::create_base()
   {
      if (!_started)
      {
         bool make_station = true;

#ifdef DEBUG
         std::cerr << "start_game(): initialize station_loc" << std::endl;
#endif
         util::coord_pair station_loc(0,0);

         if( get_game().location_module().query(station_loc).is_valid() )
         {
            if ( typeid(*get_game().location_module().query(station_loc))
                   == typeid(base_station) )
               make_station = false;
            else
            {
               std::cerr << "Can't create base station: Entity exists at "
                         << station_loc << "." << std::endl
                         << "Aborting start!" << std::endl;
               return false;
            }
         }

         if ( make_station )
         {
#ifdef DEBUG
            std::cerr << "start_game(): send create_station action to _uni"
                      << std::endl;
#endif
            get_game().uni()->send_action<create_station>(STATION_FUEL, station_loc);
         }
      }

      return true;
   }

   void dui::wait()
   {
     _dui_thread.join();
   }
}}
