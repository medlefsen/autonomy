//! \file
//! \brief
//!
//! Primary Author:  Andrew Fitz Gibbon
//! Contributing Authors:  Matt Edlefsen, Dylan Leeman

#include <autonomy/game.fwd.hpp>
#ifndef AUTONOMY_GAME_HPP
#define AUTONOMY_GAME_HPP
#include <autonomy/util/serialization.hpp>
#include <autonomy/processor.hpp>
#include <autonomy/location_module.hpp>
#include <autonomy/script_library.hpp>
#include <autonomy/dui.hpp>
#include <autonomy/generic_ui.hpp>
#include <vector>

namespace autonomy
{
    class game
        : public processor,
          public location_module< game >,
          public script_library< game >,
          public dui< game >

    {
        friend class boost::serialization::access;
        public:
            game();
            game(std::string filename);

            autonomy::processor & processor()
            {
                return *static_cast<autonomy::processor*>(this);
            }
            const autonomy::processor & processor() const
            {
                return *static_cast<const autonomy::processor*>(this);
            }
            autonomy::location_module<game> & location_module()
            {
                return *static_cast<autonomy::location_module<game>*>(this);
            }
            const autonomy::location_module<game> & location_module() const
            {
                return *static_cast<const autonomy::location_module<game>*>(this);
            }
            autonomy::script_library<game> & script_library() 
            {
                return *static_cast<autonomy::script_library<game>*>(this);
            }
            const autonomy::script_library<game> & script_library() const
            {
                return *static_cast<const autonomy::script_library<game>*>(this);
            }
            autonomy::dui<game> & dui()
            {
                return *static_cast<autonomy::dui<game>*>(this);
            }
            const autonomy::dui<game> & dui() const
            {
                return *static_cast<const autonomy::dui<game>*>(this);
            }
            autonomy::dui<game> & dui(std::string filename)
            {
                return *static_cast<autonomy::dui<game>*>(this);
            }
            const autonomy::dui<game> & dui(std::string filename) const
            {
                return *static_cast<const autonomy::dui<game>*>(this);
            }

            void update_ui();

            // Tentative functions for pause/resume
            void pause()
            {
                processor().stop();
            }
            void resume()
            {
                processor().start();
            }

            //! Serialize self to a file.
            bool save(std::string filename) const;

            //! "Deserialize" self back into the current state.
            bool restore(std::string filename);

            entity_id_t uni() const
            {
               return _uni;
            }
            std::string file() const
            {
               return _file;
            }
        private:
            entity_id_t _uni;
            std::string _file;
            std::vector<generic_ui<game>> _uis;


            template< class Archive >
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(autonomy::processor);
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(autonomy::location_module< game >);
                ar & BOOST_SERIALIZATION_NVP(_uni);
                ar & BOOST_SERIALIZATION_NVP(_file);
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(autonomy::script_library< game >);
            }
    };
}

#endif
