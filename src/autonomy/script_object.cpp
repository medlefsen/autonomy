//! \file
//! \brief script object class
//! 
//! Primary Author:  Dylan Leeman
//! Contributing Author:  Aaron Weeden

#include <boost/integer_traits.hpp>

#include <autonomy/script_object.hpp>
#include <autonomy/command_registry.hpp>
#include <autonomy/script_instruction.hpp>
#include <autonomy/instruction_list.hpp>

#include <autonomy/script_commands.hpp>

#include <autonomy/compiler/parse.hpp>
#include <autonomy/compiler/symbol_table.hpp>
#include <autonomy/compiler/translator_functors.hpp>
#include <autonomy/compiler/parser_translator_map.hpp>

namespace autonomy
{
    script_object_id_t script_object::_next_id =
        boost::integer_traits< script_object_id_t >::const_min;

    boost::mutex script_object::_next_id_mutex;

    instruction_list translate(
        compiler::parse_tree_match_t::tree_iterator root,
        compiler::parse_tree_match_t::tree_iterator parent,
        const instruction_list & il,
        compiler::symbol_table & st,
        compiler::parser_translator_map & pt_map,
        const command_registry & cr );


    std::string script_object::compile()
    {
        compiler::symbol_table st;
        compiler::parse::program the_program;
        compiler::parse::skipper skip_p;
        compiler::parse_node_attributes empty;

        compiler::parser_translator_map pt_map;

        // Populate translator map, no help for this
        pt_map.register_translator< compiler::parse::DECL_ID, compiler::decl_translator >( );
        pt_map.register_translator< compiler::parse::ASGN_ID, compiler::asgn_translator >();
        pt_map.register_translator< compiler::parse::BASE_ID, compiler::base_translator >();
        pt_map.register_translator< compiler::parse::FACTORCONT_ID,
            compiler::factorcont_translator >();
        pt_map.register_translator< compiler::parse::TERMCONT_ID, compiler::termcont_translator >();
        pt_map.register_translator< compiler::parse::EXPRCONT_ID, compiler::exprcont_translator >();
        pt_map.register_translator< compiler::parse::RELCONT_ID, compiler::relcont_translator >();
        pt_map.register_translator< compiler::parse::LLIT_ID, compiler::llit_translator >();
        pt_map.register_translator< compiler::parse::CONJCONT_ID, compiler::conjcont_translator >();
        pt_map.register_translator< compiler::parse::BEXPRCONT_ID,
            compiler::bexprcont_translator >();
        pt_map.register_translator< compiler::parse::CMD_ID, compiler::cmd_translator >();
        pt_map.register_translator< compiler::parse::COND_ID, compiler::cond_translator >();
        pt_map.register_translator< compiler::parse::WHILE_ID, compiler::while_translator >();
        pt_map.register_translator< compiler::parse::CONDCONT_ID, compiler::condcont_translator >();
        pt_map.register_translator< compiler::parse::PROG_ID, compiler::prog_translator >();
        pt_map.register_translator< compiler::parse::STMT_ID, compiler::stmt_translator >();


        command_registry cr;
        // Populate Command registry, will be done dynamically in future
        boost::shared_ptr<script_instruction> 
            move_ptr(static_cast<script_instruction*>(new move));
        cr.add_command("move", move_ptr);

        boost::shared_ptr<script_instruction> 
            get_x_ptr(static_cast<script_instruction*>(new get_x));
        cr.add_command("get_x", get_x_ptr);
        boost::shared_ptr<script_instruction> 
            get_y_ptr(static_cast<script_instruction*>(new get_y));
        cr.add_command("get_y", get_y_ptr);

        boost::shared_ptr<script_instruction> 
            scan_ptr(static_cast<script_instruction*>(new scan));
        cr.add_command("scan", scan_ptr);

        boost::shared_ptr<script_instruction> 
            is_drone_ptr(static_cast<script_instruction*>(new is_drone));
        cr.add_command("is_drone", is_drone_ptr);
        boost::shared_ptr<script_instruction> 
            is_asteroid_ptr(static_cast<script_instruction*>(new is_asteroid));
        cr.add_command("is_asteroid", is_asteroid_ptr);
        boost::shared_ptr<script_instruction> 
            is_base_ptr(static_cast<script_instruction*>(new is_base));
        cr.add_command("is_base", is_base_ptr);

        boost::shared_ptr<script_instruction>
            rand_dir_ptr(static_cast<script_instruction*>(new rand_dir));
        cr.add_command("rand_dir", rand_dir_ptr);

        boost::shared_ptr<script_instruction>
            mine_ptr(static_cast<script_instruction*>(new mine));
        cr.add_command("mine", mine_ptr);

        boost::shared_ptr<script_instruction>
            unload_ptr(static_cast<script_instruction*>(new unload));
        cr.add_command("unload", unload_ptr);

        // done populating command registry


        compiler::parse_input_iterator_t begin(_raw_form.begin(), _raw_form.end());
        compiler::parse_input_iterator_t end;

        boost::spirit::tree_parse_info
            < compiler::parse_input_iterator_t,
              compiler::parse_tree_node_factory_t >
                parsed = boost::spirit::pt_parse< compiler::parse_tree_node_factory_t >
                            ( begin, end, the_program, skip_p );

        // clear the internal compiled form, if there are no entities with references
        // to the script, it will be destructed, otherwise they will retain their
        // reference
        _compiled_form = boost::shared_ptr<instruction_list>();

        if ( !parsed.full )
        {
            return std::string("Parse error.");
        }

        try
        {
            _compiled_form 
                = boost::shared_ptr< instruction_list >(new instruction_list(
                            translate(parsed.trees.begin(), 
                                      compiler::parse_tree_match_t::tree_iterator(),
                                      instruction_list(), 
                                      st, pt_map, cr))); 
        }
        catch ( compiler::translator_exception error )
        {
            return std::string(error.what());
        }
        // no compiler errors
        return std::string();
    }

    void script_object::set_raw( const std::string & raw_text )
    {
        _compiled_form = boost::shared_ptr< instruction_list >();
        _raw_form = raw_text;
    }

    std::istream & operator>> ( std::istream & is, script_object & so )
    {
        so._compiled_form = boost::shared_ptr < instruction_list >();
        std::string line;
        while ( is.good() )
        {
            getline( is, line, '\n' );
            so._raw_form += line + '\n';
        }
        return is;
    }


    //! \function translate
    //! \brief    Translates a parsed subtree to Autonomy instruction lists
    instruction_list translate(
        compiler::parse_tree_match_t::tree_iterator root,
        compiler::parse_tree_match_t::tree_iterator parent,
        const instruction_list & il,
        compiler::symbol_table & st,
        compiler::parser_translator_map & pt_map,
        const command_registry & cr )
    {
        instruction_list ins;
        std::pair < bool, instruction_list > status;

        compiler::construct_translator_ptr trans_constructor
        = pt_map.translator(root->value.id().to_long());

        std::auto_ptr< compiler::translator_base > translator
        = (*trans_constructor)(root->value.id().to_long(),
                               root->value.value(), st, cr);

        if (parent == compiler::parse_tree_match_t::tree_iterator())
        {
            // this node has no parent, call it's translator's
            // operator() with the appropriate parameters
            compiler::parse_node_attributes nil;
            status = (*translator)(il, compiler::NIL_ID, nil);
        }
        else
        {
            // call this node's translator with the parent node as the
            // node just processed
            status = (*translator)(il,
                                   parent->value.id().to_long(),
                                   parent->value.value());
        }
        root->value.value(translator->attributes());


        compiler::parse_tree_match_t::tree_iterator child(root->children.begin());
        while (child != root->children.end() && status.first)
        {
            ins = translate(child, root, status.second, st, pt_map, cr);
            status = (*translator)(ins,
                                   child->value.id().to_long(),
                                   child->value.value());
            root->value.value(translator->attributes());

            ++child;
        }

        return status.second;
    }

}
