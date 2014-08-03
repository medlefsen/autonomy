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
#include <autonomy/generic_ui.hpp>
#include <vector>

namespace autonomy
{
    class game
        : public processor

    {
        friend class boost::serialization::access;
        public:
            game();

            autonomy::processor & processor()
            {
                return *static_cast<autonomy::processor*>(this);
            }
            const autonomy::processor & processor() const
            {
                return *static_cast<const autonomy::processor*>(this);
            }
            autonomy::location_module & location_module()
            {
                return location_module_;
            }
            const autonomy::location_module & location_module() const
            {
                return location_module_;
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
        private:
            autonomy::location_module location_module_;
            entity_id_t _uni;
            std::vector<generic_ui<game>> _uis;


            template< class Archive >
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(autonomy::processor);
                ar & BOOST_SERIALIZATION_NVP(location_module_);
                ar & BOOST_SERIALIZATION_NVP(_uni);
            }
    };
}

#endif
