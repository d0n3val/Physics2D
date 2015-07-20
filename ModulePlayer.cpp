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

	graphics = App->textures->Load("pinball/box128.png");
	SDL_Rect r;
	r.x = 500;
	r.y = 100;
	r.w = r.h = 128;

	//body = App->physics->AddBody(r);

	r.x = 400;
	r.y = 400;

	body2 = App->physics->AddBody(r, b_kinematic);
	body2->SetAngularSpeed(90.0f);

	r.x = 625;
	r.y = 400;

	body3 = App->physics->AddBody(r, b_kinematic);
	body3->SetAngularSpeed(-90.0f);

	/*"x":0.8924999237060547,"y":0.13166671991348267},0.4741665720939636,"y":0.7966667413711548},0.06749987602233887,"y":0.09166669845581055}*/

	background = App->textures->Load("pinball/pinball_map.png");

	r.x = 0;
	r.y = 0;
	r.w = 1024;
	r.h = 1024;

	//r.w = 160;
	//r.h = 156;



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

	//body->GetPosition(x, y);
	//App->renderer->Blit(graphics, x, y, NULL, 1.0f, body->GetAngle());

	body2->GetPosition(x, y);
	App->renderer->Blit(graphics, x, y, NULL, 1.0f, body2->GetAngle());

	body3->GetPosition(x, y);
	App->renderer->Blit(graphics, x, y, NULL, 1.0f, body3->GetAngle());

	return UPDATE_CONTINUE;
}


