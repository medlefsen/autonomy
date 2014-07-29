#ifndef AUTONOMY_ENTITY_FWD_HPP
#define AUTONOMY_ENTITY_FWD_HPP
#include <autonomy/util/id.hpp>
namespace autonomy
{
    class entity_generic;
    typedef entity_generic & entity_ref_t;
    typedef util::id<entity_generic*> entity_type_id_t;
    class entity_id_t;
}
#endif
