namespace autonomy
{
    template < typename ParentT >
    script_object_id_t script_library<ParentT>::new_script(
        std::string name)
    {
        // use temporary shared pointer as advised by the Boost.Smart_ptr
        // documentation
        boost::shared_ptr< script_object > temp;

        // default construct the script if it has no name, because that
        // behaviour is slightly different
        if ( name == std::string() )
        {
            temp = boost::shared_ptr< script_object >(new script_object);
        }
        else
        {
            temp = boost::shared_ptr< script_object >(new script_object(name));
        }
        _script_store_mutex.lock();
        _script_store.insert(std::make_pair(temp->id(), temp));
        _script_store_mutex.unlock();
        return temp->id();
    }

    template < typename ParentT >
    std::string script_library<ParentT>::fetch_name( script_object_id_t script ) const
    {
        std::string name;

        _script_store_mutex.lock_shared();
        _script_store_t::const_iterator script_handle(_script_store.find(script));
        if ( script_handle != _script_store.end() )
        {
            name = script_handle->second->name();
        }
        _script_store_mutex.unlock_shared();
        return name;
    }

    template < typename ParentT >
    bool script_library<ParentT>::set_script( script_object_id_t script,
                                     std::string text )
    {
        _script_store_mutex.lock_upgrade();
        _script_store_t::iterator script_handle(_script_store.find(script));

        if ( script_handle == _script_store.end() )
        { 
            // no such script exists
            _script_store_mutex.unlock_upgrade();
            return false;
        }
        _script_store_mutex.unlock_upgrade_and_lock();
        script_handle->second->set_raw(text);
        _script_store_mutex.unlock();
        return true;
    }

    template < typename ParentT >
    bool script_library<ParentT>::read_script( script_object_id_t script,
                                      std::istream & is )
    {
        _script_store_mutex.lock_upgrade();

        _script_store_t::iterator script_handle(_script_store.find(script));
        if ( script_handle == _script_store.end() )
        {
            // no such script exists
            _script_store_mutex.unlock_upgrade();
            return false;
        }
        _script_store_mutex.unlock_upgrade_and_lock();
        is >> (*script_handle->second);
        _script_store_mutex.unlock();
        return true;
    }

    template < typename ParentT >
    bool script_library<ParentT>::rename_script ( script_object_id_t script,
                                         std::string name )
    {
        _script_store_mutex.lock_upgrade();

        _script_store_t::iterator script_handle(_script_store.find(script));
        if ( script_handle == _script_store.end() )
        {          
            // no such script exists
            _script_store_mutex.unlock_upgrade();
            return false;
        }
        _script_store_mutex.unlock_upgrade_and_lock();
        script_handle->second->name() = name;
        _script_store_mutex.unlock();
        return true;
    }

    template < typename ParentT >
    bool script_library<ParentT>::replace_script( script_object_id_t script,
                                         const std::string & text )
    {
        _script_store_mutex.lock_upgrade();
        _script_store_t::iterator script_handle(_script_store.find(script));
        if ( script_handle == _script_store.end() )
        {          
            // no such script exists
            _script_store_mutex.unlock_upgrade();
            return false;
        }
        _script_store_mutex.unlock_upgrade_and_lock();
        script_handle->second->set_raw(text);
        _script_store_mutex.unlock();
        return true;
    }

    template < typename ParentT >
    void script_library<ParentT>::delete_script( script_object_id_t script )
    {
        _script_store_mutex.lock();
        _script_store.erase(script);
        _script_store_mutex.unlock();
    }

    template < typename ParentT >
    std::string script_library<ParentT>::compile_script( script_object_id_t script )
    {
        _script_store_mutex.lock_upgrade();
        _script_store_t::iterator script_handle(_script_store.find(script));
        if ( script_handle == _script_store.end() )
        {
            _script_store_mutex.unlock_upgrade();
            return std::string("Unable to compile non-existent script object.");
        }
        _script_store_mutex.unlock_upgrade_and_lock();
        std::string errors(script_handle->second->compile());
        _script_store_mutex.unlock();
        return errors;
    }

    template < typename ParentT >
    boost::shared_ptr< instruction_list > script_library<ParentT>::fetch_compiled_script(
        script_object_id_t script ) const
    {
        boost::shared_ptr< instruction_list > compiled;
        _script_store_mutex.lock_shared();

        _script_store_t::const_iterator 
            script_handle(_script_store.find(script));
        if ( script_handle != _script_store.end() )
        {
            compiled  = script_handle->second->compiled_script();
        }
        _script_store_mutex.unlock_shared();

        return compiled;
    }

    template < typename ParentT >
    std::vector< std::pair < script_object_id_t, std::string > > 
    script_library<ParentT>::fetch_scripts( ) const
    {
      std::vector< std::pair< script_object_id_t, std::string > > scripts;
      _script_store_mutex.lock_shared();
      std::copy(_script_store.begin(),_script_store.end(),scripts.begin());
      _script_store_mutex.unlock_shared();
      return scripts;
    }

}
