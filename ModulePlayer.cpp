#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("pinball/ball.png");

	body = App->physics->AddBody(600,500, 30);

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
	int x, y;

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->physics->AddBody(App->input->GetMouseX(), App->input->GetMouseY(), 50);
	}

	body->GetPosition(x, y);
	App->renderer->Blit(graphics, x, y, NULL, 1.0f);//, body->GetAngle());

	return UPDATE_CONTINUE;
}


