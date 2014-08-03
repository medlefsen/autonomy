//! \file
//! \brief
//!
//! Primary Author:  Matt Edlefsen
//! Contributing Authors:  Dylan Leeman, Andrew Fitz Gibbon

#include <iostream>
#include <fstream>

#include <boost/archive/archive_exception.hpp>

#include <autonomy/game.hpp>
#include <autonomy/entity/universe.hpp>

#ifndef DUI
#include <autonomy/gui.hpp>
#endif

namespace autonomy
{
    game::game()
        : autonomy::processor(),
          _uni(new entity::universe(*static_cast<game*>(this))),
          _uis{
#ifndef DUI
            generic_ui<game>::create<gui<game>>()
#endif
          }
    {
       processor().add(_uni);
       for(auto ui : _uis) {
         ui.init(*this);
       }
    }

    void game::update_ui()
    {
      for(auto ui : _uis) {
        ui.do_update();
      }
    }

    bool game::save(std::string filename) const
    {
        std::ofstream ofs(filename.c_str());
        if( ofs.good() )
        {
            boost::archive::text_oarchive oa(ofs);
            oa << BOOST_SERIALIZATION_NVP(*this);
        }
        else
        {
            //TODO dylan should make this an exception or something
            std::cerr << "Invalid Filename!" << std::endl;
            return false;
        }
        return true;
    }

    bool game::restore(std::string filename)
    {
       std::ifstream ifs(filename.c_str());
       bool ret = true;
       if( ifs.good() )
       {
           try
           {
             boost::archive::text_iarchive ia(ifs); //This is what throws
             ia >> BOOST_SERIALIZATION_NVP(*this);
           }
           catch (...)
           {
               throw;
               ret = false;
           }
       }
       else
           ret = false;
       
       ifs.close();
       return ret;
    }
}
