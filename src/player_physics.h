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
		void movement_air();
		void on_floor_hit(Dictionary& ray);

		Dictionary push_raycast(Vector2 from, Vector2 to);

		float inputLeft = 0;
		float inputRight = 0;

		float deltaPhysF;

	protected:
		static void _bind_methods();

	public:
		player_physics();
		~player_physics();

		float inputHorizontal = 0;

		Vector2 velocity;

		float acceleration = 640;
		float topSpeed = 45;
		float gravity = 72;
		float jumpHeight = 64;
		float drag = 300;

		float height = 8;

		void _ready() override;
		void _physics_process(double delta) override;
		void _unhandled_input(const Ref<InputEvent> &input) override;

		void set_acceleration(const float new_acceleration);
		float get_acceleration() const;

		void set_topSpeed(const float new_topSpeed);
		float get_topSpeed() const;

		void set_gravity(const float new_gravity);
		float get_gravity() const;

		void set_jumpHeight(const float new_jumpHeight);
		float get_jumpHeight() const;

		void set_drag(const float new_drag);
		float get_drag() const;

		void set_height(const float new_height);
		float get_height() const;
	};
}

#endif