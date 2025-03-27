#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/control.hpp>

namespace godot 
{
	class ScreenHandler : public Control 
	{
		GDCLASS(ScreenHandler, Control)

        private:
            Control* screen_game_over = nullptr;
            Control* screen_win = nullptr;

		protected:
			static void _bind_methods();

		public:
            ScreenHandler();
			~ScreenHandler();

            void on_win();
            void on_win_time(const float time);
            void on_game_over();
            void on_restart();

			void set_screen_game_over(Control* new_screen_game_over);
			Control* get_screen_game_over() const;

			void set_screen_win(Control* new_win);
			Control* get_screen_win() const;
	};
}