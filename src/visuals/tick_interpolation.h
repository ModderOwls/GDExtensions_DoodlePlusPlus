#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>

namespace godot 
{
	class TickInterpolation : public Node2D 
	{
		GDCLASS(TickInterpolation, Node2D)

		private:
			Vector2 last_position;

			Engine *engine;

		protected:
			static void _bind_methods();

		public:
			TickInterpolation();
			~TickInterpolation();

			void _ready() override;
			void _process(double delta) override;
			void _physics_process(double delta) override;

			Node2D* physics_node;

			void set_physics_node(Node2D* new_physics_node);
			Node2D* get_physics_node() const;
	};
}