
#include "restart_handler.h"
#include <godot_cpp/core/class_db.hpp>
#include "../visuals/sound_manager.h"

using namespace godot;


RestartHandler::RestartHandler() { }

RestartHandler::~RestartHandler() { }

void RestartHandler::_ready()
{
	Engine* engine = Engine::get_singleton();

	//Ensure it doesn't run in the editor.
	if (!engine->is_editor_hint())
	{
        restart();
	}
}


void RestartHandler::restart() 
{
	if (!restart_node.is_valid())
	{
		print_error("Attach a platform prefab to the platform manager!");

		return;
	}

    //Destroy it if there's an object active already.
    if (active_node != nullptr)
    {
        active_node->queue_free();
    }

	active_node = Object::cast_to<Node>(restart_node->instantiate());

	add_child(active_node);

	//Reset time speed.
	Engine::get_singleton()->set_time_scale(1);

	//Play the start sound.
	SoundManager::get_instance()->play_sound("Start");

	emit_signal("on_restart");
}


void RestartHandler::_bind_methods() 
{
	//Bind methods for other scripts to use.
    ClassDB::bind_method(D_METHOD("set_restart_node", "new_restart_node"), &RestartHandler::set_restart_node);
    ClassDB::bind_method(D_METHOD("get_restart_node"), &RestartHandler::get_restart_node);
    
    ClassDB::bind_method(D_METHOD("restart"), &RestartHandler::restart);
    

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "restart_node", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_restart_node", "get_restart_node");


    ADD_SIGNAL(MethodInfo("on_restart"));
}

//Win amount s(g)etters
void RestartHandler::set_restart_node(Ref<PackedScene> new_restart_node) { restart_node = new_restart_node; }
Ref<PackedScene> RestartHandler::get_restart_node() const { return restart_node; }