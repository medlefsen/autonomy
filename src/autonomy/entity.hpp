//! \file
//! \brief
//!
//! Primary Author:  Andrew Fitz Gibbon
//! Contributing Authors:  Will Tomlinson, Dylan Parkhurst, Matt Edlefsen, 
//!    Dylan Leeman, Nathan Myers

#include <autonomy/entity.fwd.hpp>
#ifndef AUTONOMY_ENTITY_HPP
#define AUTONOMY_ENTITY_HPP

#include <typeinfo>
#include <vector>
#include <iostream>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/functional/hash.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>

#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/util/id.hpp>
#include <autonomy/action.hpp>
namespace autonomy
{
    class entity_generic
    {
        public:
            virtual ~entity_generic(){}

            virtual void activate(size_t which_queue) = 0;

            virtual void send_action(size_t which_queue, 
                                     action_generic* new_action) = 0;
        private:
            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {}
    };

    template < typename EntityT >
    class entity_base
        : public entity_generic
    {
        friend class boost::serialization::access;

        public:
            virtual ~entity_base()
            {
                clear_actions(0);
                clear_actions(1);
            }

            virtual void activate(size_t which_queue)
            {
                handle_actions(which_queue);
                controller(which_queue);
            }

            virtual void send_action(size_t which_queue, action_generic* new_action)
            {
                _action_lists[1 - which_queue].push_back(static_cast<action_base<EntityT>*>(new_action));
            }

        protected:
            const std::vector< action_generic* >& get_actions(size_t which_queue)
            {
                return _action_lists[which_queue];
            }

        private:
            std::vector< action_base<EntityT>* > _action_lists[2];

            virtual void controller(size_t which_queue) = 0;

            virtual void handle_actions(size_t which_queue);

            void clear_actions(size_t which_queue);

            template < class Archive >
            void serialize ( Archive & ar, const unsigned int version )
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(entity_generic);
                ar & BOOST_SERIALIZATION_NVP(_action_lists);
            }
    };

    // the type of a local handle to an entity, most likely will never need
    // to be changed
    typedef entity_generic & entity_ref_t;

    class entity_id_t
    {
        friend bool operator== (const entity_id_t & left, 
                                const entity_id_t & right );
        friend bool operator<  (const entity_id_t & left,
                                const entity_id_t & right );
#ifdef DEBUG
        friend std::ostream& operator<< (std::ostream & os, const entity_id_t ent);
#endif

        friend class boost::serialization::access;
        public:
            entity_id_t()
                : _entity_ptr(NULL)
            {}

            // copy constructor:  takes constant reference to entity_id_t
            entity_id_t(const entity_id_t & ent)
                : _entity_ptr(ent._entity_ptr)
            {}

            // this exists to prevent the compiler from choosing the erroneous
            // template option below, which it tries to do over the constructor
            // above
            entity_id_t(entity_id_t & ent)
                : _entity_ptr(ent._entity_ptr)
            {}

            // construct an entity pointer from an arbitrary pointer (as long
            // as that pointer can be cast to an entity_base pointer, that is,
            // as long as the object is entity_base or derived therefrom)
            template < typename EntityT >
            entity_id_t(EntityT * entity_ptr)
                : _entity_ptr(static_cast<entity_generic*>(entity_ptr))
            {}

            // construct an entity_id_t from a reference to an entity
            template < typename EntityT >
            entity_id_t(EntityT & entity_ref)
                : _entity_ptr(static_cast<entity_generic*>(&entity_ref))
            {}

            // assignment operator for entity_id_t, nothing fancy
            const entity_id_t & operator= (const entity_id_t & right)
            {
                _entity_ptr = right._entity_ptr;
                return *this;
            }

            entity_generic & operator*() const
            {
                return *_entity_ptr;
            }

            entity_generic * operator->() { return _entity_ptr; }

            void free() { delete _entity_ptr; }

            bool is_valid() { return _entity_ptr != NULL; }
        private:
            entity_generic* _entity_ptr;

            template < class Archive >
                void serialize ( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_NVP(_entity_ptr);
                }
    };

    inline
    bool operator== (const entity_id_t & left, 
                     const entity_id_t & right )
    {
        return (left._entity_ptr == right._entity_ptr);
    }

    inline 
    bool operator != (const entity_id_t & left,
                      const entity_id_t & right )
    {
        return !(left == right);
    }

    inline
    bool operator<  (const entity_id_t & left,
                     const entity_id_t & right )
    {
        return (left._entity_ptr < right._entity_ptr);
    }
#ifdef DEBUG
    inline
    std::ostream& operator<< (std::ostream & os, const entity_id_t ent)
    {
        return os << ent._entity_ptr;
    }
#endif
}
#include <autonomy/entity.inc.cpp>
#endif
