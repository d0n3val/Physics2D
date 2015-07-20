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
	r.w = 640;
	r.h = 1024;

	//r.w = 160;
	//r.h = 156;

	float points[25 * 2] = {
		0.30000001192092896, 0.05000000074505806,
		0.02500000037252903, 0.17499999701976776,
		0.02500000037252903, 0.45000001788139343,
		0.07500000298023224, 0.5250000357627869,
		0.05000000074505806, 0.6000000238418579,
		0.05000000074505806, 1.2000000476837158,
		0.3499999940395355, 1.524999976158142,
		0.6000000238418579, 1.5750000476837158,
		0.8500000238418579, 1.475000023841858,
		0.9750000238418579, 1.3250000476837158,
		1, 1.125,
		1, 0.10000000149011612,
		0.949999988079071, 0.10000000149011612,
		0.949999988079071, 1.125,
		0.9000000357627869, 1.3000000715255737,
		0.824999988079071, 1.350000023841858,
		0.9000000357627869, 1.024999976158142,
		0.9000000357627869, 0.824999988079071,
		0.824999988079071, 0.675000011920929,
		0.824999988079071, 0.574999988079071,
		0.9000000357627869, 0.45000001788139343,
		0.9000000357627869, 0.20000000298023224,
		0.625, 0.05000000074505806,
		0.625, 0,
		0.30000001192092896, 0};

	phys_background = App->physics->AddEdge(r, points, 25*2);

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

	//phys_background->GetPosition(x, y);
	//App->renderer->Blit(background, x, y, NULL, 1.0f, phys_background->GetAngle());

	return UPDATE_CONTINUE;
}


