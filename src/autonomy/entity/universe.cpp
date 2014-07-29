//! \file
//! \brief Universe implementation details.

#include <autonomy/entity/universe.hpp>

namespace autonomy
{
    BOOST_CLASS_EXPORT(entity_base<entity::universe>);
    namespace entity
    {
        BOOST_CLASS_EXPORT(universe);
        void universe::controller(size_t which_queue)
        {}

        location_module<game> & universe::location_module() const
        {
            return ((*_which_game).location_module());
        }

        autonomy::processor & universe::processor() const
        {
            return ((*_which_game).processor());
        }
    }
}
