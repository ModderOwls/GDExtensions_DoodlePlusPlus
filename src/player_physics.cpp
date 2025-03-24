
#include "player_physics.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/world2d.hpp>

using namespace godot;

PhysicsDirectSpaceState2D* spaceState;
Ref<PhysicsRayQueryParameters2D> query;

uint32_t rayMask = 0b01;

void player_physics::_bind_methods() 
{	
	//Export variables to inspector.	
	ClassDB::bind_method(D_METHOD("get_acceleration"), &player_physics::get_acceleration);
	ClassDB::bind_method(D_METHOD("set_acceleration", "new_acceleration"), &player_physics::set_acceleration);
	
	ClassDB::bind_method(D_METHOD("get_topSpeed"), &player_physics::get_topSpeed);
	ClassDB::bind_method(D_METHOD("set_topSpeed", "new_topSpeed"), &player_physics::set_topSpeed);

	ClassDB::bind_method(D_METHOD("get_gravity"), &player_physics::get_gravity);
	ClassDB::bind_method(D_METHOD("set_gravity", "new_gravity"), &player_physics::set_gravity);

	ClassDB::bind_method(D_METHOD("get_jumpHeight"), &player_physics::get_jumpHeight);
	ClassDB::bind_method(D_METHOD("set_jumpHeight", "new_jumpHeight"), &player_physics::set_jumpHeight);

	ClassDB::bind_method(D_METHOD("get_drag"), &player_physics::get_drag);
	ClassDB::bind_method(D_METHOD("set_drag", "new_drag"), &player_physics::set_drag);

	ClassDB::bind_method(D_METHOD("get_height"), &player_physics::get_height);
	ClassDB::bind_method(D_METHOD("set_height", "new_height"), &player_physics::set_height);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "acceleration"), "set_acceleration", "get_acceleration");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "topSpeed"), "set_topSpeed", "get_topSpeed");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity"), "set_gravity", "get_gravity");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "jumpHeight"), "set_jumpHeight", "get_jumpHeight");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "drag"), "set_drag", "get_drag");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "height"), "set_height", "get_height");
}

player_physics::player_physics() 
{
	deltaPhysF = 0;

	velocity = Vector2(0, 0);
}

player_physics::~player_physics() { }

void player_physics::_ready()
{
	Engine *engine = Engine::get_singleton();

	//Set up raycast variables.
	//Assuming it's like Godot C#/.Net, setting this every frame/tick creates garbage.
	spaceState = CanvasItem::get_world_2d()->get_direct_space_state();
	query = PhysicsRayQueryParameters2D::create(Vector2(0, 0), Vector2(0, -1), rayMask);

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

void player_physics::_physics_process(double delta)
{
	deltaPhysF = (float)delta;

	movement_air();

	//Update physics.
	Node2D::set_position(Node2D::get_position() + velocity * deltaPhysF);
}

void player_physics::movement_air()
{
	Vector2 position = Node2D::get_position();

	velocity.x += inputHorizontal * acceleration * deltaPhysF;

    //Apply drag when not holding a direction or standing still.
    if (inputHorizontal == 0)
    {
        if (velocity.x != 0)
        {
            float dragDelta = drag * deltaPhysF;

			//Ensure it doesn't push it below zero.
            if (abs(velocity.x) <= dragDelta)
            {
                velocity.x = 0;
            }
            else
            {
                velocity.x -= SIGN(velocity.x) * dragDelta;
            }
        }
    }

	//Cap max speed of player.
	if (abs(velocity.x) > topSpeed)
	{
		velocity.x = topSpeed * SIGN(velocity.x);
	}

	velocity.y += gravity * deltaPhysF;

	//Perform raycast.
	Dictionary ray = push_raycast(position, Vector2(0, height / 2 + .1f));

	//Detect for a floor only when going down.
	if (!ray.is_empty() && velocity.y >= 0)
	{
		on_floor_hit(ray);
	}
}

void player_physics::on_floor_hit(Dictionary& ray)
{
	velocity.y = -jumpHeight;

	Node2D::set_position((Vector2)ray["position"] + Vector2(0, -1) * height / 2);
}

void player_physics::_unhandled_input(const Ref<InputEvent> &input)
{
	if (input->is_echo() || !input->is_action_type()) return;

	//Simple script for more responsive feeling controls for keyboards. Inspired by Snap Tap.
	if (input->is_action("playerRight"))
	{
		inputRight = input->get_action_strength("playerRight");

		if (input->is_pressed())
		{
			inputHorizontal = inputRight;
		}
		else
		{
			inputHorizontal = -inputLeft;
		}
	}
	else if (input->is_action("playerLeft"))
	{
		inputLeft = input->get_action_strength("playerLeft");
		
		if (input->is_pressed())
		{
			inputHorizontal = -inputLeft;
		}
		else
		{
			inputHorizontal = inputRight;
		}
	}
}

Dictionary player_physics::push_raycast(const Vector2 from, const Vector2 to)
{
	query->set_from(from);
	query->set_to(from+to);

	return spaceState->intersect_ray(query); //do raycast thingamajig
}


//MoveSpeed s(g)etters
void player_physics::set_acceleration(const float new_acceleration) { acceleration = new_acceleration; }
float player_physics::get_acceleration() const { return acceleration; }

//TopSpeed s(g)etters
void player_physics::set_topSpeed(const float new_topSpeed) { topSpeed = new_topSpeed; }
float player_physics::get_topSpeed() const { return topSpeed; }

//Gravity s(g)etters
void player_physics::set_gravity(const float new_gravity) { gravity = new_gravity; }
float player_physics::get_gravity() const { return gravity; }

//JumpHeight s(g)etters
void player_physics::set_jumpHeight(const float new_jumpHeight) { jumpHeight = new_jumpHeight; }
float player_physics::get_jumpHeight() const { return jumpHeight; }

//Drag s(g)etters
void player_physics::set_drag(const float new_drag) { drag = new_drag; }
float player_physics::get_drag() const { return drag; }

//Height s(g)etters
void player_physics::set_height(const float new_height) { height = new_height; }
float player_physics::get_height() const { return height; }