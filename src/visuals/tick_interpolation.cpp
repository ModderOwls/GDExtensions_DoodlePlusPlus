
#include "tick_interpolation.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


TickInterpolation::TickInterpolation() 
{
    lastPosition = Vector2(0, 0);

	engine = nullptr;
	physicsNode = nullptr;
}

TickInterpolation::~TickInterpolation() { }

void TickInterpolation::_bind_methods() 
{	
	//Export variables to inspector.
	ClassDB::bind_method(D_METHOD("get_physicsNode"), &TickInterpolation::get_physicsNode);
	ClassDB::bind_method(D_METHOD("set_physicsNode", "new_physicsNode"), &TickInterpolation::set_physicsNode);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "physicsNode", PROPERTY_HINT_NODE_TYPE, "Node2D"), "set_physicsNode", "get_physicsNode");
}


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
	if (physicsNode == nullptr) return;

    float physicsInterpF = (float)engine->get_physics_interpolation_fraction();

    set_global_position(lastPosition.lerp(physicsNode->get_global_position(), physicsInterpF));
}

void TickInterpolation::_physics_process(double delta)
{
	if (physicsNode == nullptr) return;

    lastPosition = physicsNode->get_global_position();
}


//Physics node s(g)etters
void TickInterpolation::set_physicsNode(Node2D* new_physicsNode) { physicsNode = new_physicsNode; }
Node2D* TickInterpolation::get_physicsNode() const { return physicsNode; }