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
	flipper_fx = App->audio->LoadFx("pinball/flipper.wav");

	flipper_up1.graphic = App->textures->Load("pinball/flipper_up1.png");
	flipper_up2.graphic = App->textures->Load("pinball/flipper_up2.png");

	spring.graphic = App->textures->Load("pinball/spring.png");
	spring_fx = App->audio->LoadFx("pinball/spring2.wav");

	ball.body = App->physics->AddBody(563, 582, 28, b_dynamic, 1.0f, 0.3f, true);

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

	flipper1.body = App->physics->AddBody({132, 918, 96, 35}, vertex1, 16, b_dynamic);
	flipper1_wheel = App->physics->AddBody(149, 932, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper1.body, flipper1_wheel, -35, 0, 0, 0, 30, -30);

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

	flipper2.body = App->physics->AddBody({273, 920, 96, 35}, vertex2, 16, b_dynamic);
	flipper2_wheel = App->physics->AddBody(350, 935, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper2.body, flipper2_wheel, 35, 0, 0, 0, 30, -30);

	flipper_up1.body = App->physics->AddBody({410, 432, 71, 26}, vertex1, 16, b_dynamic);
	flipper_up1_wheel = App->physics->AddBody(305, 443, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper_up1.body, flipper_up1_wheel, -35, 0, 0, 0, 20, -20);

	flipper_up2.body = App->physics->AddBody({406, 393, 71, 26}, vertex2, 16, b_dynamic);
	flipper_up2_wheel = App->physics->AddBody(473, 401, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper_up2.body, flipper_up2_wheel, 25, 0, 0,0, 55, -5);

	spring.body = App->physics->AddBody({565, 943, 45, 47}, b_dynamic);
	spring_wheel = App->physics->AddBody(535, 907, 10, b_static);
	App->physics->CreateLineJoint(spring.body, spring_wheel, 0, 0, 0, 0, 20.0f, 1.0f);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(ball.graphic);
	App->textures->Unload(flipper1.graphic);
	App->textures->Unload(flipper2.graphic);
	App->textures->Unload(flipper_up1.graphic);
	App->textures->Unload(flipper_up2.graphic);

	App->physics->DestroyBody(ball.body);
	App->physics->DestroyBody(flipper1.body);
	App->physics->DestroyBody(flipper2.body);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	static float spring_push = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		ball.body->Push(0.0f, -400.0f);
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->audio->PlayFx(flipper_fx);
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipper1.body->Turn(-360);
		flipper_up1.body->Turn(-360);
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper2.body->Turn(360);
		flipper_up2.body->Turn(360);
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		spring_push += 175.0f;
		spring.body->Push(0, spring_push);
	}
	else
		spring_push = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		App->audio->PlayFx(spring_fx);
	}

	int x, y;

	ball.body->GetPosition(x, y);
	App->renderer->Blit(ball.graphic, x, y, NULL, 1.0f);//, ball.body->GetAngle());

	flipper1.body->GetPosition(x, y);
	App->renderer->Blit(flipper1.graphic, x, y, NULL, 1.0f, flipper1.body->GetAngle());

	flipper2.body->GetPosition(x, y);
	App->renderer->Blit(flipper2.graphic, x, y, NULL, 1.0f, flipper2.body->GetAngle());

	flipper_up1.body->GetPosition(x, y);
	App->renderer->Blit(flipper_up1.graphic, x, y, NULL, 1.0f, flipper_up1.body->GetAngle());

	flipper_up2.body->GetPosition(x, y);
	App->renderer->Blit(flipper_up2.graphic, x, y, NULL, 1.0f, flipper_up2.body->GetAngle());

	spring.body->GetPosition(x, y);
	App->renderer->Blit(spring.graphic, x, y, NULL, 1.0f, spring.body->GetAngle());

	return UPDATE_CONTINUE;
}


