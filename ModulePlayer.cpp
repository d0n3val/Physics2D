#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

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

	graphics = App->textures->Load("pinball/box128.png");
	SDL_Rect r;
	r.x = 500;
	r.y = 100;
	r.w = r.h = 128;

	body = App->physics->AddBody(r);

	r.x = 400;
	r.y = 400;

	body2 = App->physics->AddBody(r, b_static);

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

	body->GetPosition(x, y);
	App->renderer->Blit(graphics, x, y, NULL, 1.0f, body->GetAngle());

	body2->GetPosition(x, y);
	App->renderer->Blit(graphics, x, y, NULL, 1.0f, body2->GetAngle());

	return UPDATE_CONTINUE;
}


