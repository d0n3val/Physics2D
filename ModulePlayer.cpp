#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball.graphic = App->textures->Load("pinball/ball.png");
	flipper1.graphic = App->textures->Load("pinball/flipper1.png");
	flipper2.graphic = App->textures->Load("pinball/flipper2.png");

	ball.body = App->physics->AddBody(600, 500, 28, b_dynamic, 1.0f, 0.3f, true);

	float vertex1[16] = {
		-0.50190f, -0.01053f,
		-0.46388f, -0.32632f,
		-0.35741f, -0.51579f,
		0.42966f, -0.27368f,
		0.49430f, -0.00000f,
		0.42966f, 0.26316f,
		-0.36882f, 0.49474f,
		-0.46388f, 0.29474f
	};

	flipper1.body = App->physics->AddBody({213, 918, 132, 48}, vertex1, 16, b_dynamic);
	flipper1_wheel = App->physics->AddBody(166, 918, 10, b_kinematic);

	App->physics->CreateRevoluteJoint(flipper1.body, flipper1_wheel, -35, 0, 0, 0, 45, -45);

	float vertex2[16] = {
		-0.50000f, -0.02083f,
		-0.40909f, -0.29167f,
		0.33333f, -0.52083f,
		0.45455f, -0.35417f,
		0.50000f, -0.02083f,
		0.45455f, 0.29167f,
		0.37121f, 0.50000f,
		-0.43182f, 0.27083f
	};

	flipper2.body = App->physics->AddBody({375, 918, 132, 48}, vertex2, 16, b_dynamic);
	flipper2_wheel = App->physics->AddBody(420, 918, 10, b_static);

	App->physics->CreateRevoluteJoint(flipper2.body, flipper2_wheel, 35, 0, 0, 0, 45, -45);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(ball.graphic);
	App->textures->Unload(flipper1.graphic);

	App->physics->DestroyBody(ball.body);
	App->physics->DestroyBody(flipper1.body);

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

	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		ball.body->Push(0.0f, -500.0f);
	}

	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		flipper1.body->Turn(-360);
	}

	if(App->input->GetKey(SDL_SCANCODE_RSHIFT) == KEY_REPEAT)
	{
		flipper2.body->Turn(360);
	}

	ball.body->GetPosition(x, y);
	App->renderer->Blit(ball.graphic, x, y, NULL, 1.0f);//, ball.body->GetAngle());

	flipper1.body->GetPosition(x, y);
	App->renderer->Blit(flipper1.graphic, x, y, NULL, 1.0f, flipper1.body->GetAngle());

	flipper2.body->GetPosition(x, y);
	App->renderer->Blit(flipper2.graphic, x, y, NULL, 1.0f, flipper2.body->GetAngle());

	return UPDATE_CONTINUE;
}


