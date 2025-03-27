#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot 
{
	class RestartHandler : public Node 
	{
		GDCLASS(RestartHandler, Node)

        private:
            Node* active_node = nullptr;

		protected:
			static void _bind_methods();

		public:
            RestartHandler();
			~RestartHandler();

			void _ready() override;

            Ref<PackedScene> restart_node = nullptr;

            void restart();

            void set_restart_node(Ref<PackedScene> new_restart_node);
            Ref<PackedScene> get_restart_node() const;
	};
}