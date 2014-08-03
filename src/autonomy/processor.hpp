//! \file processor.hpp
//! \brief Defines the processor component. Holds a set of entities that it
//! runs through.  Is mostly thread safe.
//!
//! Primary Author:  Matt Edlefsen
//! Contributing Authors:  Dylan Leeman, Andrew Fitz Gibbon, Aaron Weeden

#ifndef AUTONOMY_PROCESSOR_HPP
#define AUTONOMY_PROCESSOR_HPP

#include <autonomy/util/serialization.hpp>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <autonomy/entity.hpp>
#include <atomic>

namespace autonomy
{
    class processor
    {
        friend class boost::serialization::access;

        public:
        static const int TICKS_PER_SECOND = 30;
            processor()
                : going(false), queue_index(0)
            {
            }
            //! copy constructor
            //! NOT THREAD SAFE
            //! Do not use this unless
            //! the other processor is stopped
            //! and no other thread is doing an add or remove
            processor(const processor& copy);

            //! add entity
            //! Adds a shared_ptr to an entity
            //! to the processor
            void add(entity_id_t entity_ptr);
          
            //! remove entity
            //! Removes a shared_ptr to an entity 
            //! from the processor
            void remove(entity_id_t entity_ptr);
          
            void do_tick();

            //! Starts the processor running
            void start()
            {
                going = true;
                while(going)  do_tick();
#ifdef DEBUG
                std::cout << "Processor: Start finished" << std::endl;
#endif
            }
            void start(unsigned int max_ticks)
            {
                going = true;
                for(;going && max_ticks > 0;--max_ticks) do_tick();
                going = false;
            }
                         
            //! Stops the processor
            void stop()
            {
#ifdef DEBUG
                std::cout << "Stopping processor" << std::endl;
#endif
                going = false;
            }
            //! Clears the processor
            //! Can cause a deadlock if done from within a entity controller.
            void reset();
           
            //! returns the current action queue
            size_t current_queue() const
            {
                return queue_index;
            }
            //! Returns if the processor is running
            bool is_going() const 
            {
                return going;
            }

            //! Returns the number of entities in the processor
            size_t num_entities() const;

        private:
            void lock() const
            {
                entity_list_mutex.lock();
            }
            void unlock() const;
            void update_entity_list() const;
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                // do locking to make sure nobody is in the middle of anything while we
                // save/load
                assert(!is_going());
                add_mutex.lock();
                remove_mutex.lock();
                update_entity_list();
                {
                    ar & BOOST_SERIALIZATION_NVP(queue_index);
                    ar & BOOST_SERIALIZATION_NVP(_entity_list);
                }
                add_mutex.unlock();
                remove_mutex.unlock();
                entity_list_mutex.unlock();
            }

            //THIS IS VERY DANGEROUS
            // These are all mutable because of the add/remove
            // semantics which allow entities to be added/removed
            // to the processor while it's locked by placing
            // the request in a temporary queue which is then emptied
            // when the entity list becomes available
            //
            // Because of this any time we lock/unlock
            // we need to alter the entity list.
            //
            // Editors of this class must be VERY careful
            // to preserve constness in all other ways
            // in the methods.
            mutable std::set<entity_id_t> _entity_list;
            mutable boost::shared_mutex entity_list_mutex;

            mutable std::vector<entity_id_t> add_queue;
            mutable boost::mutex add_mutex;

            mutable std::vector<entity_id_t> remove_queue;
            mutable boost::mutex remove_mutex;

            std::atomic<bool> going;
            size_t queue_index;
    };

}
#endif
