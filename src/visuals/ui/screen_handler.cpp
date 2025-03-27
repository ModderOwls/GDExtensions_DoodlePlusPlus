
#include "screen_handler.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


ScreenHandler::ScreenHandler() { }

ScreenHandler::~ScreenHandler() { }


void ScreenHandler::on_win()
{
    if (screen_win == nullptr) return;

    screen_win->set_visible(true);
}
//While time is not used, useful as by default the score manager also passes a time parameter in its signal.
void ScreenHandler::on_win_time(const float time)
{
    if (screen_win == nullptr) return;

    screen_win->set_visible(true);
}

void ScreenHandler::on_game_over()
{
    if (screen_game_over == nullptr) return;

    screen_game_over->set_visible(true);
}

void ScreenHandler::on_restart()
{
    if (screen_game_over == nullptr || screen_win == nullptr) return;
    
    screen_win->set_visible(false);
    screen_game_over->set_visible(false);
}


void ScreenHandler::_bind_methods() 
{
	//Bind methods for other scripts to use.
    ClassDB::bind_method(D_METHOD("set_screen_game_over", "new_screen_game_over"), &ScreenHandler::set_screen_game_over);
    ClassDB::bind_method(D_METHOD("get_screen_game_over"), &ScreenHandler::get_screen_game_over);
    
    ClassDB::bind_method(D_METHOD("set_screen_win", "new_screen_win"), &ScreenHandler::set_screen_win);
    ClassDB::bind_method(D_METHOD("get_screen_win"), &ScreenHandler::get_screen_win);
    
    ClassDB::bind_method(D_METHOD("on_win"), &ScreenHandler::on_win);
    ClassDB::bind_method(D_METHOD("on_win_time", "time"), &ScreenHandler::on_win_time);
    ClassDB::bind_method(D_METHOD("on_game_over"), &ScreenHandler::on_game_over);
    ClassDB::bind_method(D_METHOD("on_restart"), &ScreenHandler::on_restart);


	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "screen_game_over", PROPERTY_HINT_NODE_TYPE, "Control"), "set_screen_game_over", "get_screen_game_over");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "screen_win", PROPERTY_HINT_NODE_TYPE, "Control"), "set_screen_win", "get_screen_win");
}

//Game over screen s(g)etters
void ScreenHandler::set_screen_game_over(Control* new_screen_game_over) { screen_game_over = new_screen_game_over; }
Control* ScreenHandler::get_screen_game_over() const { return screen_game_over; }

//Game over screen s(g)etters
void ScreenHandler::set_screen_win(Control* new_screen_win) { screen_win = new_screen_win; }
Control* ScreenHandler::get_screen_win() const { return screen_win; }