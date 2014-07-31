//! \file
//! \brief
//!
//! Primary Author:  Nathan Myers
//! Contributing Authors: Andrew Fitz Gibbon, Dylan Leeman, Aaron Weeden
//! Originally copied from autonomy/gui.cpp by Matt Edlefsen and Nathan Myers

#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <iostream>

namespace autonomy
{
  template <typename P>
  gui<P>::gui()
    : done(false), _do_update(true),  gui_state(GAME), title_screen(NULL), 
      dont_do_drugs(NULL), screen(NULL), text_buffer(NULL), FONT(NULL), 
      debug(false), paused(false), gridded(false), SCREEN_BPP(32), 
      HUD_SIZE(150), TICK_DELAY(100), parent_(nullptr)
  {
    viewport.set_resolution(800, 600);
    viewport.x(-(static_cast<int>(viewport.x_res()/2)));
    viewport.y(-(static_cast<int>(viewport.y_res()/2)));
    update_event.type = SDL_USEREVENT;
    update_event.user.code = 0;
    update_event.user.data1 = NULL;
    update_event.user.data2 = NULL;
  }

  template<typename P>
    void gui<P>::init(P& parent)
    {
      parent_ = &parent;
      gui_thread = boost::thread(boost::bind(&gui<P>::run,boost::ref(*this)));
    }

  template <typename P>
  gui<P>::~gui()
  {
    done = true;
    SDL_PushEvent(&update_event);
    gui_thread.join();
    clean_up();
  }

  template <typename P>
  void gui<P>::get_entities()
  {
    util::coord_pair sw(viewport.game_x(), 
                        -(viewport.game_y()) - viewport.game_y_res());
    util::coord_pair ne(viewport.game_x() + viewport.game_x_res(), 
                        -(viewport.game_y()));
    _entities = parent().location_module().view(sw,ne);
    return;
  }

  template <typename P>
  void gui<P>::do_update()
  {
    update_mutex.lock();
    _do_update = true;
    update_mutex.unlock();
    // jolts the run loop into doing something
    SDL_PushEvent(&update_event);
    return;
  }

  template <typename P>
  void gui<P>::run()
  {
    if(!(init()))
      std::cout << "\nAutonomy> "; // return the promt if initialization 
                                   //   steals it
    /* since this is sans images/music we need to start off with the game  */
    display_HUD();
    /**                                                                   **/
    while(!done)
      {
        if (_do_update)
          {
            // this locking is maybe not needed since having a race condition
            // here isn't a big deal but might as well be pedantic.
            update_mutex.lock();
            _do_update = false;
            update_mutex.unlock();
            get_entities();
          }
        switch(gui_state)
          {
          case SPLASH:
            {
              if(event.type == SDL_MOUSEBUTTONDOWN)
                resolve_mouse_click(0,0,1);
              break;
            }
          case TITLE:
            {
              if(event.type == SDL_MOUSEBUTTONDOWN)
                resolve_mouse_click(0,0,1);
              break;
            }
          case GAME:
            {
              if( event.type == SDL_USEREVENT )
                {
                  display_world();
                  display_HUD();
                }

              if(event.type == SDL_MOUSEBUTTONDOWN)
                {      
                  resolve_mouse_click
                    (event.button.x, event.button.y,event.button.button);  
                }

              if( event.type == SDL_KEYDOWN )
                {
                  switch( event.key.keysym.sym ) 
                    {
                    case SDLK_MINUS:
                      {
                        viewport.zoom_out(2);
                        display_world();
                        break;
                      }
                    case SDLK_EQUALS:
                      {
                        viewport.zoom_in(2);
                        display_world();
                        break;
                      }
                    case SDLK_UP: 
                      {
                        viewport.pan_up(viewport.drone_size() * 3); 
                        display_world();
                        break;
                      } 
                    case SDLK_DOWN: 
                      { 
                        viewport.pan_down(viewport.drone_size() * 3); 
                        display_world();
                        break; 
                      }
                    case SDLK_LEFT: 
                      {
                        viewport.pan_left(viewport.drone_size() * 3); 
                        display_world();
                        break; 
                      }
                    case SDLK_RIGHT: 
                      {   
                        viewport.pan_right(viewport.drone_size() * 3); 
                        display_world();
                        break; 
                      }
                    case SDLK_ESCAPE:
                      {
                        display_menu();
                        paused = true;
                        gui_state = MENU;
                        break;
                      }
                    case SDLK_SPACE:
                      {
                        print_debug();
                        break;
                      }
                    case SDLK_g:
                      {
                        if (gridded)
                          gridded = false;
                        else
                          gridded = true;
                        display_world();
                        break;
                      }
                    case SDLK_d:
                      {
                        if (debug)
                          {
                            std::cout << "debug off" << std::endl;
                            debug = false;
                          }                        
                        else
                          {
                            std::cout << "debug on" << std::endl;
                            debug = true;
                          }
                        break;
                      }
                    default:
                      break;
                    }
                }
              break;
            } // end of case game
          case MENU:
            {
              if((event.type == SDL_KEYDOWN) && 
                 (event.key.keysym.sym == SDLK_ESCAPE))
                {
                  display_world();
                  display_HUD();
                  paused = false;
                  gui_state = GAME;
                }
              break;
            }
          default:
            {
              if (debug)
                std::cout << "main switch hit default" << std::endl;
              break;
            }
          } // end switch state

        if( event.type == SDL_QUIT )
          {
            done = true;
          }    

        if( SDL_Flip( screen ) == -1 )
          {
            if (debug)
              std::cout << "Error: function SDL_Flip failed";
          }
        if (SDL_WaitEvent(&event) != 1) done = true;
      }
    return;
  }
    
  template <typename P>
  void gui<P>::display_world()
  {
    // game field
    SDL_Rect game_field;
    game_field.x = 0;
    game_field.y = 0;
    game_field.w = viewport.x_res();
    game_field.h = viewport.y_res() - HUD_SIZE;
    SDL_FillRect(screen, &game_field, 0);
    BOOST_FOREACH( typename location_module::relation_t entity_data, 
                   *_entities)
      {
        if(typeid(*(entity_data.first)) == typeid(entity::scripted_drone))
          {
            display_entity(SDL_MapRGB(screen->format,0x5f,0x9e,0xa0),
                           entity_data.second.x(), 
                           entity_data.second.y());
          }
        else if(typeid(*entity_data.first) == typeid(entity::asteroid))
          {
            display_entity(SDL_MapRGB(screen->format,0xcd,0xb7,0xb5),
                           entity_data.second.x(), entity_data.second.y());
          }
        else if(typeid(*entity_data.first) == typeid(entity::base_station))
          {
            display_entity(SDL_MapRGB(screen->format,0x8b,0x45,0x13),
                           entity_data.second.x(), entity_data.second.y());
          }
      }
    
    // For making a highlight box around the selected object
    if(selected_object.is_valid())
      {
 //        util::coord_pair loc;
//         loc = parent().location_modulue().locate(selected_object);

//         (loc.x() - viewport.game_x()) * viewport.drone_size()
//           (loc.y() - viewport.game_y()) * viewport.drone_size()
      }

    if (gridded)
      display_grid();

    return;
  }

  template <typename P>
  void gui<P>::display_HUD()
  {
    SDL_Color WHITE = {255,255,255};

    SDL_Rect HUD;
    HUD.x = 0;
    HUD.y = viewport.y_res() - HUD_SIZE;
    HUD.w = viewport.x_res();
    HUD.h = HUD_SIZE;
    SDL_FillRect(screen, &HUD, SDL_MapRGB(screen->format,0x00,0x00,0x00));

    // draw line separating HUD and Field
    Uint8 R=0x99, G=0x99, B=0x99, A=0x99;
    hlineRGBA(screen,0,HUD.w,HUD.y,R,G,B,A);
  

    if(selected_object.is_valid())
      {
        std::string unit_type;
        std::string fuel;
        if(typeid(*selected_object) == typeid(entity::scripted_drone))
          {
            unit_type = "Drone";
            fuel = boost::lexical_cast<std::string>(static_cast<entity::drone&>(*selected_object).get_fuel());
          }
        if(typeid(*selected_object) == typeid(entity::asteroid))
          { 
            unit_type = "Asteroid";
            fuel = boost::lexical_cast<std::string>(static_cast<entity::asteroid&>(*selected_object).get_fuel());
          }    
        if(typeid(*selected_object) == typeid(entity::base_station))
          {
            unit_type = "Base Station";
            fuel = boost::lexical_cast<std::string>(static_cast<entity::drone&>(*selected_object).get_fuel());
          }

        std::string HUD_text = "Unit Type: " + unit_type + " --- Fuel " + fuel;
        text_buffer = TTF_RenderText_Blended(FONT, HUD_text.c_str(), WHITE);
        apply_surface( 10, viewport.y_res() - HUD_SIZE + 10, text_buffer, screen); 
      }
    return;
  }

  template <typename P>
  void gui<P>::display_menu()
  {
    SDL_Color WHITE = {255,255,255};


    // draw background
    SDL_FillRect(screen, NULL, 000077);

    // create message
    char *text = "Hello World!";

    // render text
    text_buffer = TTF_RenderText_Blended(FONT, text, WHITE );
    
    // check menu
    if (text_buffer == NULL)
      {
        if (debug)
        {
          std::cout << "Error: Falied to render text with error:" << std::endl;
          std::cout << TTF_GetError() << std::endl;
        }
        return;
      }
    
    apply_surface(10,10,text_buffer,screen);

    return;
  }

  template <typename P>
  int gui<P>::gui_trunc(double n)
  {
    if(n < 0)
      return static_cast<int>(n) - 1;
    else
      return static_cast<int>(n);
  }

  template <typename P>
  void gui<P>::resolve_mouse_click(int x, int y, int button)
  {
    switch(gui_state)
      {
      case SPLASH:
        {
          // apply_surface( 0, 0, title_screen, screen );
          gui_state = TITLE;
          break;
        }
      case TITLE:
        {
          //  Mix_HaltMusic();                
          display_world();
          display_HUD();
          paused = false;
          gui_state = GAME;
          break;
        }
      case GAME:
        {
          if( y < (viewport.y_res() - HUD_SIZE))
            {
              /*
                1 = Left Click
                2 = Middle Click
                3 = Right Click
              */
              switch(button)
                {
                case 1:
                  {
                    util::coord_pair posistion(gui_trunc(static_cast<double>((x + viewport.x()))/static_cast<double>(viewport.drone_size())), 
                                               -1 * gui_trunc(static_cast<double>((y + viewport.y()))/static_cast<double>(viewport.drone_size())));
                  selected_object = parent().location_module().query(posistion);
                  display_HUD();
                  if (debug)
                    std::cout << "--- Mouse Debug Info ---\n" 
                              << "pixel x; " << x
                              << "\npixel y: " << y
                              << "\ngame x: " 
                              << gui_trunc(static_cast<double>((x + viewport.x()))/static_cast<double>(viewport.drone_size()))
                              << "\ngame y: " 
                              << -1 * gui_trunc(static_cast<double>((y + viewport.y()))/static_cast<double>(viewport.drone_size()))
                              << std::endl;
                  }
                  break;          
                case 2:
                  if (debug)
                    std::cout << "maybe center viewport around this location" 
                              << std::endl;
                  break;
                case 3:
                  if (debug)
                    std::cout << "maybe display features of entity if any" 
                              << std::endl;
                  break;
                }
            }
          else
            {
              switch(button)
                {
                case 1:
                  if (debug)
                    std::cout << "you have clicked on HUD " 
                              << "with left mouse button" << std::endl;
                  break;
                case 2:
                  if (debug)
                    std::cout << "you have clicked on HUD "
                              << "with middle mouse button" << std::endl;
                  break;
                case 3:
                  if (debug)
                    std::cout << "you have clicked on HUD "
                              << "with right mouse button" << std::endl;
                  break;
                default:
                  break;
                }
            }
          
        }   break; // end case game
      case MENU:
        {
          if (debug)
            std::cout << "menu is on" << std::endl;
          break;
        } 
      default:
        break;
      }
    return;
  }

  template <typename P>
  void gui<P>::print_debug()
  {
    if (debug)
      {
        std::cout << "--- Spacebar Debug Info ---\n"
                  << "---pixels---\n"
                  << "viewport x = " << viewport.x()
                  << "\nviewport y = " << viewport.y()
                  << "\nviewport x resolution = " << viewport.x_res()
                  << "\nviewport y resolution = " << viewport.y_res()
                  << "\ndrone size = " << viewport.drone_size()
                  << std::endl
                  << "---game units---\n"
                  << "game x = " << viewport.game_x()
                  << "\ngame y = " << viewport.game_y()
                  << "\ngame x resolution = " << viewport.game_x_res()
                  << "\ngame y resolution = " << viewport.game_y_res()
                  << std::endl;
      }
 
    util::coord_pair sw(viewport.game_x(), 
                        -(viewport.game_y()) - viewport.game_y_res());
    util::coord_pair ne(viewport.game_x() + viewport.game_x_res(), 
                        -(viewport.game_y()));
    if (debug)
      std:: cout << "sw corner: " << sw.x() << " " << sw.y() << std::endl
                 << "ne corner: " << ne.x() << " " << ne.y() << std::endl;
    return;
  }

  template <typename P>
  SDL_Surface* gui<P>::load_image( std::string filename )
  {
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    loadedImage = SDL_LoadBMP( filename.c_str() );
    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
      {
        optimizedImage = SDL_DisplayFormat( loadedImage );     
        SDL_FreeSurface( loadedImage );
      }
    return optimizedImage;
  }

  template <typename P>
  void gui<P>::apply_surface( int x, int y, SDL_Surface* source, 
                              SDL_Surface* destination )
  {
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );

    return;
  }

  template <typename P>
  void gui<P>::clean_up()
  {
    // Free resources
    SDL_FreeSurface( text_buffer );
    TTF_CloseFont( FONT );
    TTF_Quit();

    // SDL_FreeSurface( dont_do_drugs );
    // SDL_FreeSurface( title_screen );
    // Mix_FreeMusic( music );
    // Mix_CloseAudio();

    SDL_Quit();
  }

  template <typename P>
  void gui<P>::display_entity(int color, int x, int y)
  {
    // for clipping towards HUD
    int game_field_h = viewport.y_res() - HUD_SIZE;
      
    SDL_Rect the_entity;
    the_entity.x = x * viewport.drone_size() - viewport.x();
    the_entity.y = -(y * viewport.drone_size()) - viewport.y();
    the_entity.w = viewport.drone_size();
    the_entity.h = viewport.drone_size();
    
    if (the_entity.y < game_field_h)     // if entity is on the game_field
      SDL_FillRect(screen, &the_entity, color);
          
    return;
  }

  template <typename P>
  void gui<P>::display_grid() 
  {
    // display grid for debugging
    Sint16 block = viewport.drone_size();
    Uint8 R=0x99, G=0x99, B=0x99, A=0x99;
    Sint16 field_h = viewport.y_res()-HUD_SIZE, field_w = viewport.x_res();
  
    // draw verticals
    for (Sint16 i = viewport.x() % block; i < field_w; i+=block)
      vlineRGBA(screen,i,0,field_h,R,G,B,A);

    // draw horizontals
    for (Sint16 i= viewport.y() % block; i <= field_h; i+=block)
      hlineRGBA(screen,0,field_w,i,R,G,B,A);
  
    return;
  }

  template <typename P>
  bool gui<P>::init()
  {
    screen = SDL_SetVideoMode( viewport.x_res(), viewport.y_res(), 
                               SCREEN_BPP, SDL_SWSURFACE );   

    // initialize SDL stuff
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
      {
        if (debug)
          std::cerr << "Error: function SDL_INIT_EVERYTHING failed\n";
        return false;
      }
    
    // set screen
    screen = SDL_SetVideoMode( viewport.x_res(), viewport.y_res(), 
                               SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
      {
        if (debug)
          std::cerr << "Error: Failed to set screen up\n";
        return false;
      }

    // initialize ttf   
    if( TTF_Init() == -1 )
      {
        if (debug)
          std::cout << "Error: Failed to initialize" << std::endl;
      }

    // open font
    FONT = TTF_OpenFont("../resources/FreeSans.ttf",20);
    if (FONT == NULL)
      {
        if (debug)
          std::cout << "Error: Falied to open font" << std::endl;
      }

    // this somehow broke, and now it spits a warning out on the commandline
    // the only fix I know of now is to switch to a wav, but I don't really 
    //   want to do that
    //music = Mix_LoadMUS( "../resources/title.mp3" );
    
    // cutting these out to improve performance for now
    
    //dont_do_drugs = load_image( "../resources/background.bmp" );
    //title_screen = load_image("../resources/title.bmp");
    
    //     if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    //       {
    //       if (debug)
    //         std::cerr << "Error: Failed to set audio up\n";
    //         return false;
    //       }
    
    //    if( music == NULL )
    //       {
    //    if (debug)
    //         std::cerr << "Error: Failed to load music\n";
    //         return false;
    //       }
        
    /* Cut out for speed's sake */
    
    //  apply_surface( 0, 0, dont_do_drugs, screen );
    
    
    //     if( Mix_PlayMusic( music, -1 ) == -1 )
    //       {
    //        if (debug)
    //         std::cerr << "Error: Unable to playback music\n";
    //         return false;
    //       }  
    
    // set window name
    SDL_WM_SetCaption( "Autonomy V1.0", NULL );
   
    // flip screen
    if( SDL_Flip( screen ) == -1 )
      {
        if (debug)
          std::cerr << "Error: function SDL_Flip failed";
        return false;
      }
    // SDL_TimerID tick_timer(TICK_DELAY, &step, NULL); 
    return true; 
  }
}

