#include "register_types.h"

#include "game_logic/player_physics.h"
#include "game_logic/platform_manager.h"
#include "game_logic/score_manager.h"
#include "game_logic/restart_handler.h"

#include "visuals/camera_chase_handler.h"
#include "visuals/tick_interpolation.h"
#include "visuals/sound_manager.h"

#include "visuals/ui/variable_label.h"
#include "visuals/ui/timer_label.h"
#include "visuals/ui/screen_handler.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) 
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(PlayerPhysics);
	GDREGISTER_CLASS(PlatformManager);
	GDREGISTER_CLASS(ScoreManager);
	GDREGISTER_CLASS(RestartHandler);

	GDREGISTER_CLASS(CameraChaseHandler);
	GDREGISTER_CLASS(TickInterpolation);
	GDREGISTER_CLASS(SoundManager);

	GDREGISTER_CLASS(VariableLabel);
	GDREGISTER_CLASS(TimerLabel);
	GDREGISTER_CLASS(ScreenHandler);
}

void uninitialize_example_module(ModuleInitializationLevel p_level) 
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) 
	{
		return;
	}
}

extern "C" 
{
	// Initialization.
	GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) 
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_example_module);
		init_obj.register_terminator(uninitialize_example_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}