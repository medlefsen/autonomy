//! \file
//! \brief Declaration of location_module class.
//!
//! Primary Author:  Dylan Leeman
//! Contributing Authors: Andrew Fitz Gibbon, Matt Edlefsen

#ifndef AUTONOMY_LOCATION_MODULE_HPP
#define AUTONOMY_LOCATION_MODULE_HPP

#include <list>
#include <utility>

#include <boost/shared_ptr.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <autonomy/entity.hpp>

#include <autonomy/util/coord_pair.hpp>
#include <autonomy/util/serialization.hpp>

namespace autonomy
{
    //! \class location_module
    //! \brief The location_module tracks the locations of every object
    //!        associated with a universe entity.
        class location_module
        {
            friend class boost::serialization::access;
            public:
            typedef std::pair< entity_id_t, util::coord_pair > relation_t;
            typedef std::vector< relation_t >                  view_t;
            typedef boost::shared_ptr< view_t >                view_ptr_t;

            private:
            typedef std::list< relation_t > _location_map_t;

            _location_map_t _location_map;
            mutable boost::shared_mutex _location_map_mutex;

            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    _location_map_mutex.lock();
                    ar & BOOST_SERIALIZATION_NVP(_location_map);
                    _location_map_mutex.unlock();
                }

            public:

            location_module()
            {}

            ~location_module()
            {}

            //! Given a coordinate pair, returns the identifier of any
            //! entities at that location
            entity_id_t query( util::coord_pair location ) const;

            //! Maps the given entity to the given location, this operation
            //! will fail if an entity is already mapped to the location,
            //! returns whether the operation was successful
            bool move( entity_id_t entity, util::coord_pair destination );

            //! Removes a relation given an entity_id
            void remove( entity_id_t entity );

            //! Returns the coordinates of an entity, given an entity_id,
            //! if the entity has no corresponding relation, a
            //! util::INVALID_LOCATION will be returned
            util::coord_pair locate( entity_id_t entity ) const;


            //! Given a pair of coordinates corresponding to the "south-west"
            //! and "north-east" corners of a viewport, returns a view_t container
            //! with all of the relations in the viewport
            view_ptr_t view( util::coord_pair sw, util::coord_pair ne ) const;

            //! Clears all entites
            void clear();

            class location_relation_pred
            {
                public:
                location_relation_pred ( entity_id_t entity )
                    : _entity_equal( entity ),
                     _location_equal(util::INVALID_LOCATION)
                {}

                location_relation_pred( util::coord_pair location )
                    : _entity_equal(), _location_equal( location )
                {}

                location_relation_pred( relation_t relation )
                    : _entity_equal( relation.first ),
                    _location_equal( relation.second )
                {}

                bool operator()(relation_t relation) const;

                private:

                entity_id_t _entity_equal;
                util::coord_pair _location_equal;
            };
        };
}
#endif
