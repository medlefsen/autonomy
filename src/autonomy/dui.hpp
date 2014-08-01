//! \file
//! \brief
//! 
//! Primary Author:  Andrew Fitz Gibbon
//! Contributing Authors:  Dylan Leeman, Dylan Parkhurst

#ifndef AUTONOMY_DUI_HPP
#define AUTONOMY_DUI_HPP
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include <boost/optional.hpp>
#include <boost/thread.hpp>

#include <autonomy/game.hpp>

namespace autonomy
{
   template <typename parent_type>
   class dui
   {
      public:
         typedef std::map<std::string, void(autonomy::dui<parent_type>::*)(std::istream & is)> cmd_map_t;

         dui();
         dui(std::string filename);

         ~dui();

         parent_type& parent()
         {   
            return *static_cast<parent_type*>(this);
         }   

         const parent_type& parent() const
         {   
            return *static_cast<const parent_type*>(this);
         } 

         // Fucntions that are mapped to commands in cmp_map
         void help          (std::istream & is = std::cin);
         void start_game    (std::istream & is = std::cin);
         void run_for       (std::istream & is = std::cin);
         void sleep_for     (std::istream & is = std::cin);
         void create_entity (std::istream & is = std::cin);
         void save_game     (std::istream & is = std::cin);
         void load_game     (std::istream & is = std::cin);
         void status        (std::istream & is = std::cin);
         void pause_game    (std::istream & is = std::cin);
         void resume_game   (std::istream & is = std::cin);
         void stop_game     (std::istream & is = std::cin);
         void end_game      (std::istream & is = std::cin);

         void run           (std::istream & is = std::cin);
         void run_file      (std::string filename);
         int safe_int_input (std::istream & is = std::cin);
         bool create_base    ();

         bool has_quit() const
         {
            return _has_quit;
         }
      private:
         boost::thread  _dui_thread;
         boost::thread  _proc_thread;
         bool           _interactive;
         bool           _started;
         bool           _has_quit;
         boost::mutex   started_mutex;
         boost::mutex   has_quit_mutex;
         //entity_id_t   _uni;
         location_module& _loc;
         script_library&  _library;
         processor&                      _proc;
   };
   template <typename T>
       boost::optional<T> prompt(std::istream & is, std::string prompt);

}

#include <autonomy/dui.inc.cpp>
#endif
