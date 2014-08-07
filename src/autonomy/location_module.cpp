//! \file
//! \brief
//!
//! Primary Author:  Dylan Leeman
//! Contributing Author:  Matt Edlefsen

#include <autonomy/location_module.hpp>

namespace autonomy 
{
    
        entity_id_t location_module::query( util::coord_pair location ) const
        {
            entity_id_t located;

            _location_map_mutex.lock_shared();

            _location_map_t::const_iterator
                relation_found(
                        std::find_if( _location_map.begin(), _location_map.end(), location_relation_pred( location) ));
            if ( relation_found != _location_map.end() )
            {
                located = relation_found->first;
            }

            _location_map_mutex.unlock_shared();

            return located;
        }

    //! Maps the given entity to the given location, this operation
    //! will fail if an entity is already mapped to the location,
    //! returns whether the operation was successful
    
        bool location_module::move( entity_id_t entity, util::coord_pair destination )
        {
            // assume move will succeed, slightly better performance
            bool move_succeeded(true);

            _location_map_mutex.lock_upgrade();

            _location_map_t::iterator 
                current_relation(std::find_if(_location_map.begin(),
                                              _location_map.end(),
                                              location_relation_pred(entity)));
            _location_map_t::const_iterator 
                proposed_relation(std::find_if(_location_map.begin(),
                                               _location_map.end(),
                                               location_relation_pred(destination)));

            if ( ( proposed_relation != _location_map.end()) 
                    && ( proposed_relation->first != entity ) )
            { 
                // there is already an entity at the proposed location,
                // and it isn't this entity
                move_succeeded = false;
                _location_map_mutex.unlock_upgrade();
            }
            else
            {
                _location_map_mutex.unlock_upgrade_and_lock();
                if ( current_relation == _location_map.end() )
                {
                    _location_map.push_back( relation_t(entity, destination) );
                }
                else
                {
                    current_relation->second = destination;
                }
                _location_map_mutex.unlock();
            }
            return move_succeeded;
        }

    //! Removes a relation given an entity_id
    
        void location_module::remove( entity_id_t entity )
        {
            _location_map_mutex.lock_upgrade();

            _location_map_t::iterator 
                current_relation(std::find_if(_location_map.begin(),
                                              _location_map.end(),
                                              location_relation_pred(entity)));
            if ( current_relation != _location_map.end() )
            {
                _location_map_mutex.unlock_upgrade_and_lock();
                _location_map.erase(current_relation);
                _location_map_mutex.unlock();
            }
            else
            {
                _location_map_mutex.unlock_upgrade();
            }
        }

    //! Returns the coordinates of an entity, given an entity_id,
    //! if the entity has no corresponding relation, a
    //! util::INVALID_LOCATION will be returned
    
        util::coord_pair location_module::locate( entity_id_t entity ) const
        { 
            util::coord_pair entity_at(util::INVALID_LOCATION);
            

            _location_map_mutex.lock_shared();

            _location_map_t::const_iterator 
                current_relation(std::find_if(_location_map.begin(),
                        _location_map.end(),
                        location_relation_pred(entity)));
            if ( current_relation != _location_map.end() )
            {
                entity_at = current_relation->second;
            }
            _location_map_mutex.unlock_shared();

            return entity_at; 
        }


    //! Given a pair of coordinates corresponding to the "south-west"
    //! and "north-east" corners of a viewport, returns a view_t container
    //! with all of the relations in the viewport
    
        typename location_module::view_ptr_t location_module::view( util::coord_pair sw, util::coord_pair ne ) const
        {
            view_ptr_t results(new view_t);

            _location_map_mutex.lock_shared();

            for ( _location_map_t::const_iterator i(_location_map.begin());
                    i != _location_map.end();
                    ++i )
            {
                if ((i->second.x() >= sw.x()) && (i->second.x() <= ne.x())
                        && ( i->second.y() >= sw.y())
                        && ( i->second.y() <= ne.y()) )
                {
                    results->push_back(*i);
                }
            }

            _location_map_mutex.unlock_shared();

            return results;
        }

    
        bool location_module::location_relation_pred::operator()(relation_t relation) const
        {
            return ( ( _entity_equal == entity_id_t() && relation.second ==
                        _location_equal )
                    || ( _location_equal == util::INVALID_LOCATION
                        && relation.first == _entity_equal)
                    || ( relation.first == _entity_equal
                        && relation.second == _location_equal ) );
        }
    
        void location_module::clear()
        {
            _location_map_mutex.lock();
            _location_map.clear();
            _location_map_mutex.unlock();
        }

}

