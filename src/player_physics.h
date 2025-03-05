#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input_event.hpp>

namespace godot 
{
	class player_physics : public Node2D 
	{
		GDCLASS(player_physics, Node2D)

	private:
		void movement_grounded();
		void movement_air();

		Dictionary push_raycast(Vector2 from, Vector2 to);

		float deltaPhysF;

	protected:
		static void _bind_methods();

	public:
		player_physics();
		~player_physics();

		float inputHorizontal;

		bool grounded;
		Vector2 velocity;

		float gravity = 1;
		float moveSpeed = 2;

		float height = 5;

		void _ready() override;
		void _process(double delta) override;
		void _physics_process(double delta) override;
		void _unhandled_input(const Ref<InputEvent> &input) override;

		void set_gravity(const float new_gravity);
		float get_gravity() const;

		void set_moveSpeed(const float new_moveSpeed);
		float get_moveSpeed() const;

		void set_height(const float new_height);
		float get_height() const;
	};
}

#endif