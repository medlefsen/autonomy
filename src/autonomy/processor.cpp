//! \file
//! \brief
//!
//! Primary Author:  Matt Edlefsen
//! Contributing Authors:  Andrew Fitz Gibbon, Dylan Leeman, Aaron Weeden

#include <autonomy/processor.hpp>
#include <boost/foreach.hpp>
#include <ctime>

namespace autonomy
{
    processor::processor(const processor& copy)
        : going(false), queue_index(copy.queue_index)
    {
        copy.lock();
        _entity_list = copy._entity_list;
        copy.unlock();
    }
    void processor::add(entity_id_t entity_ptr)
    {
        add_mutex.lock();
        if (entity_list_mutex.try_lock())
        {
            _entity_list.insert(entity_ptr);
            remove_mutex.lock();
            update_entity_list();
            entity_list_mutex.unlock();
            remove_mutex.unlock();
        }
        else
        {
            add_queue.push_back(entity_ptr);
        }
        add_mutex.unlock();
    }
    void processor::remove(entity_id_t entity_ptr)
    {
        remove_mutex.lock();
        if (entity_list_mutex.try_lock())
        {
            _entity_list.erase(entity_ptr);
            add_mutex.lock();
            update_entity_list();
            entity_list_mutex.unlock();
            add_mutex.unlock();
        }
        else
        {
            remove_queue.push_back(entity_ptr);
        }
        remove_mutex.unlock();
    }
 
    void processor::do_tick()
    {
	const int NANOSECONDS = 1000000000;
#ifdef DEBUG
        std::cout << "Processor: Lock for tick" << std::endl;
#endif
        lock();
        {
#ifdef DEBUG
            std::cout << "Processor: Start tick with "<< _entity_list.size() << " entities" << std::endl;
#endif
            std::set<entity_id_t>::iterator i = _entity_list.begin();
            while(i != _entity_list.end())
            {
                (**i).activate(current_queue());
                ++i;
            }
#ifdef DEBUG
            std::cout << "Processor: Finish Tick" << std::endl;
#endif
            queue_index = 1 - queue_index;
        }
        unlock(); 
        timespec t = { 0 , NANOSECONDS / TICKS_PER_SECOND };
        nanosleep(&t,NULL);
    }
    void processor::reset()
    {
        if (is_going())
            stop();
        lock();
        {
            _entity_list.clear();
        }
        unlock();
    }

    void processor::unlock() const
    {
        add_mutex.lock();
        remove_mutex.lock();
        update_entity_list();
        add_mutex.unlock();
        remove_mutex.unlock();
        entity_list_mutex.unlock();
    }
    
    // This could be better, for example things added and then removed
    // won't be removed because the erases are done first.  In Iteration 4
    // this is fixed.
    void processor::update_entity_list() const
    {
        BOOST_FOREACH(entity_id_t& ent, remove_queue)
        {
            _entity_list.erase(ent);
        }
        _entity_list.insert(add_queue.begin(),add_queue.end());
        add_queue.clear();
        remove_queue.clear();
    }
    size_t processor::num_entities() const
    {
        size_t size;
        lock();
        {
            size = _entity_list.size();
        }
        unlock();
        return size;
    }



}
