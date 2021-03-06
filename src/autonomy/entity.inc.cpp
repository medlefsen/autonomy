//! \file
//!
//! Primary Author:  Dylan Leeman

#include <algorithm>
#include <list>

#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <autonomy/action_handler.hpp>

namespace autonomy
{
    template < typename EntityT >
    void entity_base<EntityT>::clear_actions(size_t which_queue)
    {
        BOOST_FOREACH(action_base<EntityT>* actptr, _action_lists[which_queue])
        {
            delete actptr;
        }
        _action_lists[which_queue].clear();
    }

    template < typename EntityT >
    void entity_base<EntityT>::handle_actions(size_t which_queue)
    {
        // sort actions //
        std::sort(_action_lists[which_queue].begin(), 
                  _action_lists[which_queue].end(), 
                  action_default_handler_cmp<EntityT>() );

        std::list<action_handler_generic*> handlers;

        // TODO:  make this exception-safe, we don't want a memory leak
        BOOST_FOREACH(action_base<EntityT>* & i, _action_lists[which_queue])
        {
            if ( handlers.size() == 0 
                    || action_handler_id_t(*handlers.back()) 
                        != (*i).default_handler_type() )
            {
                // must add an instance of this handler
                handlers.push_back((*i).default_handler());
            }
            (*handlers.back()).append_action(*static_cast<action_generic*>(i));
        }

        // process actions //
        BOOST_FOREACH(action_handler_generic * & i, handlers)
        {
            (*i)(*this, which_queue);
            delete i;
        }

        // clear action list //
        clear_actions(which_queue);
    }
}
