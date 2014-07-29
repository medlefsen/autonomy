//! \file
//!
//! Primary Author:  Dylan Leeman

#include <autonomy/action_handler.fwd.hpp>
#include <autonomy/entity.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_HPP
#define AUTONOMY_ACTION_HANDLER_HPP

#include <vector>
#include <list>
#include <utility>
#include <algorithm>

#ifdef DEBUG
#include <iostream>
#endif

#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>

#include <autonomy/util/serialization.hpp>

#include <autonomy/util/id.hpp>
#include <autonomy/action.hpp>
namespace autonomy
{
    //! \class
    //! \brief Fundamental base class of all action_handlers.
    //! 
    //! This class permits polymorphic collections of action_handlers.
    class action_handler_generic
    {
        public:
            action_handler_generic(){}

            virtual ~action_handler_generic(){}

            virtual void append_action( action_generic & action ) = 0;

            virtual void operator()( entity_ref_t entity, size_t which_queue ) = 0;

        private:
            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {
            }
    };

    //! \class
    //! \brief Class from which to derive action_handlers.
    //!
    //! All action handlers should derive from this class.  The template
    //! parameters of this class correspond to the type of action and the
    //! type of entity for which this handler operates.
    template < typename ActionT, typename TargetT >
    class action_handler_base
        : public action_handler_generic
    {
        public:
            action_handler_base()
            {}

            virtual ~action_handler_base()
            {
                clear();
            }

            virtual void append_action( action_generic & action )
            {
                _action_group.push_back(static_cast< ActionT* >(&action));
            }

            virtual void execute( TargetT & entity, size_t which_queue ) = 0;

            virtual void operator()( entity_ref_t entity, size_t which_queue )
            {
                execute(static_cast< TargetT& >(entity), which_queue);
            }

            virtual void clear()
            {
                _action_group.clear();
            }

        protected:
            typedef std::vector< ActionT* > _action_group_t;
            _action_group_t _action_group;
        private:
            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_handler_generic);
                ar & BOOST_SERIALIZATION_NVP(_action_group);
            }
    };

    //! \class
    //! \brief Special form of action_handler that chains many sub handlers.
    template < typename ActionT, typename TargetT >
    class action_handler_chain
        : public action_handler_base< ActionT, TargetT >
    {
        private:
            typedef action_handler_base<ActionT, TargetT> _handler_link_t;
        public:
            action_handler_chain(){}

            virtual ~action_handler_chain()
            {
                BOOST_FOREACH(_handler_link_t* handler_ptr, _handler_chain)
                {
                    delete handler_ptr;
                }
                _handler_chain.clear();
            }

            virtual void append_action( action_generic & action )
            {
                BOOST_FOREACH(_handler_link_t* next_handler, _handler_chain)
                {
                    next_handler->append_action(action);
                }
            }

            virtual void execute( TargetT & entity, size_t which_queue )
            {
                BOOST_FOREACH(_handler_link_t* next_handler, _handler_chain)
                {
                    next_handler->execute(entity, which_queue);
                }
            }

            template < typename SoughtT >
            bool in_chain() const 
            {
                action_handler_id_t sought_id(static_cast<SoughtT*>(NULL));
                BOOST_FOREACH(const _handler_link_t* next_handler, _handler_chain)
                {
                    action_handler_id_t next_handler_type(next_handler);
                    if (next_handler_type == sought_id)
                    {
                        return true;
                    }
                }
            }

            template < typename HandlerT >
            void append() throw()
            {
                _handler_link_t* handler(new HandlerT);
                
                // in the unlikely event that something goes wrong in the next two
                // calls, we must make sure that the newly allocated memory is freed
                try
                {
                    if ( !in_chain<HandlerT>() )
                    {
                        _handler_chain.push_back(handler);
                    }
                }
                catch (...)
                {
                    delete handler;
                    throw;
                }
            }

            void swap( action_handler_chain<ActionT, TargetT> & new_chain )
            {
                _handler_chain.swap(new_chain);
            }
        private:
            std::list< _handler_link_t* > _handler_chain;

            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {
                ar & make_nvp(util::id< action_handler_base<ActionT,TargetT> >().name().c_str(),
                        boost::serialization::base_object< action_handler_base<ActionT, TargetT> >(*this)); 
                ar & BOOST_SERIALIZATION_NVP(_handler_chain);
            }

    };
}
#endif
