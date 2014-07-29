//! \file
//! \brief
//! 
//! Primary Author:  Andrew Fitz Gibbon
//! Contributing Authors:  Dylan Leeman, Dylan Parkhurst, Aaron Weeden

#include <autonomy/dui.hpp>

#include <limits.h>
#include <unistd.h>

#include <typeinfo>

#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/integer_traits.hpp>

#include <autonomy/script_library.hpp>
#include <autonomy/script_builtins.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/script_instruction.hpp>

#include <autonomy/action/move.hpp>
#include <autonomy/action/create_drone.hpp>
#include <autonomy/action/create_station.hpp>
#include <autonomy/action/create_asteroid.hpp>

#include <autonomy/entity/asteroid.hpp>
#include <autonomy/entity/base_station.hpp>
#include <autonomy/entity/scripted_drone.hpp>

namespace autonomy {

   const int STATION_FUEL = 100;
   const int MAP_MIN      = INT_MIN;
   const int MAP_MAX      = INT_MAX;

   template <typename P>
   dui<P>::dui()
       : _interactive(true),
         _started(false),
         _has_quit(false),
         _loc(parent().location_module()),
         _library(parent().script_library()),
         _proc(parent().processor())
   {
      _dui_thread = boost::thread(boost::bind(&dui<P>::run,boost::ref(*this),boost::ref(std::cin)));
   }

   template <typename P>
   dui<P>::dui(std::string filename)
       : _interactive(false),
         _started(false),
         _has_quit(false),
         _loc(parent().location_module()),
         _library(parent().script_library()),
         _proc(parent().processor())
   {
      _dui_thread = boost::thread(boost::bind(&dui<P>::run_file,boost::ref(*this),filename));
   }
  template <typename P>
      inline
   dui<P>::~dui()
   {
       if(!has_quit())
       {
           end_game();
       }
       _dui_thread.join();
   }

   template <typename P>
   void dui<P>::run(std::istream & is)
   {
      cmd_map_t   cmd_map;
      std::string cmd;
      cmd_map["help"]    = &::autonomy::dui<P>::help;
      cmd_map["start"]   = &::autonomy::dui<P>::start_game;
      cmd_map["execute"] = &::autonomy::dui<P>::run_for;
      cmd_map["sleep"]   = &::autonomy::dui<P>::sleep_for;
      cmd_map["create"]  = &::autonomy::dui<P>::create_entity;
      cmd_map["save"]    = &::autonomy::dui<P>::save_game;
      cmd_map["load"]    = &::autonomy::dui<P>::load_game;
      cmd_map["status"]  = &::autonomy::dui<P>::status;
      cmd_map["pause"]   = &::autonomy::dui<P>::pause_game;
      cmd_map["resume"]  = &::autonomy::dui<P>::resume_game;
      cmd_map["stop"]    = &::autonomy::dui<P>::stop_game;
      cmd_map["quit"]    = &::autonomy::dui<P>::end_game;
      cmd_map["exit"]    = &::autonomy::dui<P>::end_game;

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

   template <typename P>
   void dui<P>::run_file(std::string filename)
   {
      std::ifstream file(filename.c_str());
      if (!file.good())
      {
         std::cerr << "Bad filename!" << std::endl;
      }

      run(file);
   }
   
   template <typename P>
   void dui<P>::help(std::istream & is)
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

   template <typename P>
   void dui<P>::start_game(std::istream & is)
   {
      if (!_proc.is_going() && !_started)
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
         std::cerr << "start_game(): _proc.start()" << std::endl;
#endif

         _proc_thread = boost::thread(boost::bind(&processor::start, boost::ref(_proc) ));
      }
      else if(_proc.is_going())
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
   
   template <typename P>
   void dui<P>::run_for(std::istream & is)
   {
     unsigned int ticks;
     
     if (_interactive)
        std::cerr << "Number of ticks?: ";
     ticks = safe_int_input(is);
   
     if (!_proc.is_going()) 
     {
        std::cerr << "Executing:  " << ticks << " ticks." << std::endl;

        create_base();

        // By doing start here as _proc.start instead of a thread
        // means that control will only return to the DUI once 
        // the ticks have completed.
        //_proc_thread = boost::thread(boost::bind(&processor::start, boost::ref(_proc),ticks));
        _proc.start(ticks);
     }
     else
     {
        std::cerr << "The game is already running!" << std::endl;
     }
   }
   
   template <typename P>
   void dui<P>::sleep_for(std::istream & is)
   {
     unsigned int microsecs;
   
     if (_interactive)
        std::cerr << "How many microseconds? ";
     is >> microsecs;
   
     std::cerr << "Sleeping for " << microsecs << " microseconds." << std::endl;
     usleep(microsecs);
   }
   
   template <typename P>
   void dui<P>::create_entity(std::istream & is)
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
  	 
	      if((typeid(parent().query(entity_loc)) == typeid(entity::asteroid))
	         ||(typeid(parent().query(entity_loc)) == typeid(entity::drone))
	         ||(typeid(parent().query(entity_loc)) == typeid(entity::base_station)))
         {
	         std::cerr << "An entity already exists at " << entity_loc << std::endl;
         }
	      else
	      {
	         parent().uni()->send_action(1 - _proc.current_queue(),
                      (new action::create_asteroid(fuel,
                                                   entity_loc,
                                                   parent().uni())));
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
   
         my_script = _library.new_script(filename);
         _library.read_script( my_script, file );

         compiler_errors = _library.compile_script(my_script);
         if ( compiler_errors != std::string() )
         {
            std::cerr << compiler_errors << std::endl;
         }
         else
         {
            boost::shared_ptr<instruction_list> compiled_script(_library.fetch_compiled_script( my_script ));
       
#ifdef DEBUG
           BOOST_FOREACH( boost::shared_ptr<script_instruction> a, *compiled_script )
           {
              std::cerr << a->name() << std::endl;
           }
#endif
   
           parent().uni()->send_action(1 - _proc.current_queue(),
                     (new action::create_drone(fuel,
                                               entity_loc,
                                               compiled_script,
                                               parent().uni())));
         }
      }
      else
         std::cerr << "Unrecognized type!" << std::endl;

      if (_interactive)
         std::cerr << std::endl;
   }
   
   template <typename P>
   void dui<P>::save_game(std::istream & is)
   {
      pause_game();
      std::string filename;
      
      if (_interactive)
         std::cerr << "\tFilename?: ";
      is >> filename;
   
      if (parent().save(filename))
          std::cerr << "Saved successfully" << std::endl;
      else
          std::cerr << "Save failed" << std::endl;
   }
   
   template <typename P>
   void dui<P>::load_game(std::istream & is)
   {
      std::string filename;

      if (_proc.is_going())
         std::cerr << "The game must be paused before loading." << std::endl; 
      else
      {
	      if (_interactive)
	         std::cerr << "\tFilename?: ";
         is >> filename;
   
         if( parent().restore(filename))
             std::cerr << "Loaded successfully" << std::endl;
         else
             std::cerr << "Load failed" << std::endl;
      }
   }
   
   template <typename P>
   void dui<P>::status(std::istream & is)
   {
      util::coord_pair sw(MAP_MIN,MAP_MIN);
      util::coord_pair ne(MAP_MAX,MAP_MAX);
      typename location_module< P > ::view_ptr_t  current_view = _loc.view(sw,ne);
      typename std::vector< typename location_module<P>::relation_t >::iterator view_iterator = current_view->begin();
      entity_id_t current_entity;
   
      if (_proc.is_going())
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
      
            if (typeid(*current_entity) == typeid(entity::base_station))
            {
               std::cerr << "\tBase Station"; 
               std::cerr << " (f:" << static_cast <entity::drone*>(&(*current_entity))->get_fuel() << ')';
            }
            else if (typeid(*current_entity) == typeid(entity::asteroid))
            {
               std::cerr << "\tAsteroid";
               std::cerr << " (f:" << static_cast <entity::asteroid*>(&(*current_entity))->get_fuel() << ')';
            }
            else if (typeid(*current_entity) == typeid(entity::scripted_drone))
            {
               std::cerr << "\tScripted Drone";
               std::cerr << " (f:" << static_cast <entity::scripted_drone*>(&(*current_entity))->get_fuel() << ')';
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
   
   template <typename P>
   void dui<P>::pause_game(std::istream & is)
   {
     if(!_started)
     {
       std::cerr << "You have not yet started a game!" << std::endl;
     }
     else
     {
      parent().pause();
      std::cerr << "Game Paused." << std::endl;
     }
   }
   
   template <typename P>
   void dui<P>::resume_game(std::istream & is)
   {
      if (!_proc.is_going() && _started) 
      {
         std::cerr << "Resuming game..." << std::endl;
   
         _proc_thread = boost::thread(
                          boost::bind(&processor::start,
                                      boost::ref(_proc),
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
   
   template <typename P>
   void dui<P>::stop_game(std::istream & is)
   {
      parent().pause();
#ifdef DEBUG
    std::cerr << "Paused!" << std::endl; 
#endif
      _loc.clear();

      started_mutex.lock();
      _started = false;
      started_mutex.unlock();

#ifdef DEBUG
    std::cerr << "Stopping" << std::endl;
#endif
      _proc.stop();
#ifdef DEBUG
      std::cerr << "Joining" << std::endl;
#endif
      _proc_thread.join();
      std::cerr << "Ended the game." << std::endl;
   }
   
   template <typename P>
   void dui<P>::end_game(std::istream & is)
   {
      std::cerr << "Exiting the game..." << std::endl;

      has_quit_mutex.lock();
      _has_quit = true;
      has_quit_mutex.unlock();
      
#ifdef DEBUG
      std::cerr << "_proc.stop()" << std::endl;
#endif
      if(_started)
          stop_game();
#ifdef DEBUG
      std::cerr << "Done with end_game" << std::endl;
#endif
   }
   
   template <typename P>
   int dui<P>::safe_int_input(std::istream & is)
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

   template <typename P>
   bool dui<P>::create_base()
   {
      if (!_started)
      {
         bool make_station = true;

#ifdef DEBUG
         std::cerr << "start_game(): initialize station_loc" << std::endl;
#endif
         util::coord_pair station_loc(0,0);

         if( parent().location_module().query(station_loc).is_valid() )
         {
            if ( typeid(*parent().location_module().query(station_loc))
                   == typeid(entity::base_station) )
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
            parent().uni()->send_action(1, static_cast<action_generic*>(
                        new action::create_station(STATION_FUEL, station_loc)));
         }
      }

      return true;
   }
}
