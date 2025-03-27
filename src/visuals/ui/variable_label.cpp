
#include "variable_label.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


VariableLabel::VariableLabel() { }

VariableLabel::~VariableLabel() { }


void VariableLabel::set_integer(const int value)
{
    set_text(String::num_int64(value));
}

void VariableLabel::set_float(const float value)
{
    set_text(String::num_real(value));
}


void VariableLabel::_bind_methods() 
{
	//Bind methods for other scripts to use.
	ClassDB::bind_method(D_METHOD("set_integer", "value"), &VariableLabel::set_integer);
	ClassDB::bind_method(D_METHOD("set_float", "value"), &VariableLabel::set_float);
}