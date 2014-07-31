//! \file
//! \brief
//!
//! Primary Author: Nathan Myers
//! Contributing Authors: Matt Edlefsen, Maduna

#ifndef AUTONOMY_GUI_HPP
#define AUTONOMY_GUI_HPP
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <autonomy/viewport.hpp>
#include <autonomy/entity/drone.hpp>
#include <autonomy/entity/asteroid.hpp>
#include <autonomy/entity/base_station.hpp>
#include <autonomy/entity/scripted_drone.hpp>
#include <autonomy/location_module.hpp>
#include <autonomy/util/serialization.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/tuple/tuple.hpp>
#include <vector>
#include <typeinfo>
#include <string>
#include <boost/lexical_cast.hpp>

namespace autonomy
{
  // state keeps track of where the gui is at
 enum state 
    {
      SPLASH, //Winner's don't use drugs
      TITLE,  //title screen
      GAME,   //main game screenv
      MENU    //main menu
    };

  template <typename parent_type>
  class gui 
  {
      friend class boost::serialization::access;
  public:
    //! Gui Constructor
    //! Starts the gui_thread with the gui_frame function and initializes done to false
    gui();

    //! Gui Destructor
    //! Sets done to true and then joins gui_thread
    ~gui();

    void init(parent_type& parent);
    
    //! run()
    //! This is the main loop of the gui
    void run();

    //! forces the gui to update it's information
    void do_update();

    parent_type& parent()
    {
      return *parent_;
    }

    const parent_type& parent() const
    {
      return *parent_;
    }

  private:
    //private empty copy constructor needed because threads are noncopyable
    gui(const gui&) {} 
    //! fetches and stores 
    void get_entities();
    void display_world();
    void display_HUD();
    void display_menu();
    void resolve_mouse_click(int x, int y,int button);
    void print_debug();
    bool init();
    SDL_Surface* load_image( std::string filename );
    void apply_surface( int x, int y, SDL_Surface* source, 
                        SDL_Surface* destination );
    void clean_up();
    void display_entity(int color, int x, int y);
    void display_grid();
    int gui_trunc(double n);

    bool done;
    boost::mutex update_mutex;
    bool _do_update;
    //TODO Add local variables like list of location,entity type pairs to display

    entity_id_t selected_object;
    typename location_module::view_ptr_t _entities;
    boost::thread gui_thread;

    SDL_Event update_event;
    SDL_Event event;
    state gui_state;
    ui::viewport viewport;
    SDL_Surface *title_screen;
    SDL_Surface *dont_do_drugs;
    SDL_Surface *screen;
    SDL_Surface *text_buffer;
    Mix_Music *music; 
    TTF_Font *FONT;
    bool debug;
    bool paused;
    bool gridded;
    int SCREEN_BPP;
    int HUD_SIZE;
    int TICK_DELAY; 
    parent_type* parent_;

    template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
        }
   };
}
#include <autonomy/gui.inc.cpp>

#endif
