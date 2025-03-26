
#include "tick_interpolation.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


TickInterpolation::TickInterpolation() 
{
    last_position = Vector2(0, 0);

	engine = nullptr;
	physics_node = nullptr;
}

TickInterpolation::~TickInterpolation() { }


void TickInterpolation::_ready()
{
	engine = Engine::get_singleton();

	//Ensure it doesn't run in the editor.
	if (engine->is_editor_hint())
	{
		set_process(false);
		set_physics_process(false);
	}
	else
	{
		set_process(true);
		set_physics_process(true);
	}
}

void TickInterpolation::_process(double delta)
{
	if (physics_node == nullptr) return;

    float physicsInterpF = (float)engine->get_physics_interpolation_fraction();

    set_global_position(last_position.lerp(physics_node->get_global_position(), physicsInterpF));
}

void TickInterpolation::_physics_process(double delta)
{
	if (physics_node == nullptr) return;

    last_position = physics_node->get_global_position();
}


void TickInterpolation::_bind_methods() 
{	
	//Export variables to inspector.
	ClassDB::bind_method(D_METHOD("get_physics_node"), &TickInterpolation::get_physics_node);
	ClassDB::bind_method(D_METHOD("set_physics_node", "new_physics_node"), &TickInterpolation::set_physics_node);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "physics_node", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_physics_node", "get_physics_node");
}

//Physics node s(g)etters
void TickInterpolation::set_physics_node(Node2D* new_physics_node) { physics_node = new_physics_node; }
Node2D* TickInterpolation::get_physics_node() const { return physics_node; }