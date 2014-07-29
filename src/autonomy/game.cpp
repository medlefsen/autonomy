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

namespace autonomy
{
    game::game()
        : autonomy::processor(),
          autonomy::dui<game>(),
          _uni(new entity::universe(*static_cast<game*>(this)))
    {
       processor().add(_uni);

       // If we don't keep the game's thread busy while
       // the dui is going it'll without us and bad
       // things will happen.
       while (!(dui().has_quit()))
       {
#ifdef DEBUG
           std::cout << "Game: Dui still running" << std::endl;
#endif
          sleep(1);
       }
#ifdef DEBUG
       std::cout << "Game: Finished" << std::endl;
#endif
    }

    game::game(std::string filename)
        : autonomy::processor(),
          autonomy::dui<game>(filename),
          _uni(new entity::universe(*static_cast<game*>(this))),
          _file(filename)
    {
       processor().add(_uni);
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
