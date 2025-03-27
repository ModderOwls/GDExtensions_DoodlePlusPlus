#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>

namespace godot 
{
	class VariableLabel : public Label
	{
		GDCLASS(VariableLabel, Label)

		protected:
			static void _bind_methods();

		public:
            VariableLabel();
			~VariableLabel();

            void set_integer(const int value);
            void set_float(const float value);
	};
}