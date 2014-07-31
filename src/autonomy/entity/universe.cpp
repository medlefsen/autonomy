//! \file
//! \brief Universe implementation details.

#include <autonomy/entity/universe.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::entity::universe>);

BOOST_CLASS_EXPORT(autonomy::entity::universe);

namespace autonomy
{
    namespace entity
    {
        void universe::controller(size_t which_queue)
        {}

        location_module & universe::location_module() const
        {
            return ((*_which_game).location_module());
        }

        autonomy::processor & universe::processor() const
        {
            return ((*_which_game).processor());
        }
    }
}
