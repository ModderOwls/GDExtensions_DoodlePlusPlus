
#include "score_handler.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


ScoreHandler::ScoreHandler() 
{

}

ScoreHandler::~ScoreHandler() { }

void ScoreHandler::_ready()
{
	Engine* engine = Engine::get_singleton();

	//Ensure it doesn't run in the editor.
	if (engine->is_editor_hint())
	{
		set_process(false);
		set_physics_process(false);

		return;
	}
	else
	{
		set_process(true);
		set_physics_process(true);
	}
}

ScoreHandler* ScoreHandler::get_instance() 
{
	return instance;
}


void ScoreHandler::check_win() 
{
    if (score >= 100) 
    {
		
    }
}


void ScoreHandler::_bind_methods() 
{
	//Bind methods for other scripts to use.
    ClassDB::bind_method(D_METHOD("add_score", "amount"), &ScoreHandler::add_score);
    ClassDB::bind_method(D_METHOD("get_score"), &ScoreHandler::get_score);
}

void ScoreHandler::add_score(int amount) 
{
    score += amount;
    
    check_win();
}

int ScoreHandler::get_score() const { return score; }