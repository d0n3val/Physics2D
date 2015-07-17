#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;

	// idle animation (just the ship)
	idle.frames.PushBack({66, 1, 32, 14});

	// move upwards
	up.frames.PushBack({100, 1, 32, 14});
	up.frames.PushBack({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;
	
	// Move down
	down.frames.PushBack({33, 1, 32, 14});
	down.frames.PushBack({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/ship.png");

	position.x = 150;
	position.y = 120;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}


