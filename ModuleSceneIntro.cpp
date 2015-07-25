#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Music
	//App->audio->PlayMusic("pinball/Rhinoceros2.ogg", 0.0f);

	// Graphics
	graphics = App->textures->Load("pinball/pinball.png");
	bouncer1.texture = bouncer2.texture = App->textures->Load("pinball/bouncer_hit.png");

	bouncer1.fx = bouncer2.fx = App->audio->LoadFx("pinball/ding_short.wav");

	float points[49 * 2] = {
		0, 0,
		0, -818,
		-22, -897,
		-69, -953,
		-125, -994,
		-195, -1019,
		-370, -1019,
		-402, -1004,
		-433, -970,
		-440, -927,
		-437, -896,
		-430, -856,
		-404, -808,
		-411, -803,
		-435, -851,
		-448, -900,
		-453, -997,
		-461, -1007,
		-468, -1014,
		-485, -1012,
		-494, -1001,
		-496, -979,
		-491, -851,
		-485, -809,
		-467, -752,
		-469, -742,
		-477, -748,
		-500, -808,
		-507, -971,
		-518, -988,
		-531, -991,
		-561, -990,
		-575, -978,
		-582, -962,
		-582, -833,
		-576, -761,
		-558, -685,
		-507, -523,
		-551, -413,
		-551, -351,
		-585, -309,
		-585, -106,
		-413, 1,
		-255, 2,
		-81, -106,
		-83, -309,
		-132, -373,
		-44, -564,
		-44, 0
	};
	float p2[] = {
		0, 0, 0, 48, 139, 143, 131, 108, 100, 60, 65, 26, 28, 4, 2, 0
	};
	float p3[] = {
		0,0,6,-1,10,1,14,139,28,203,43,247,262,357,262,380,270,388,334,404,326,447,305,515,296,515,296,506,319,449,317,437,308,425,291,416,274,417,266,427,255,472,175,431,170,425,162,376,155,367,135,355,112,353,105,361,114,409,91,403,21,204,5,145,0,-1
	};
	float p4[] = {
		0,0,104,-171,125,-227,132,-283,133,-324,126,-324,80,-228,82,-221,99,-211,97,-198,56,-147,40,-145,-1,-5,0,0
	};
	float p5[] = {
		0,0,10,0,9,100,103,158,103,166,95,166,0,106,0,-1
	};
	float p6[] = {
		0, 0,11, 0,11, 106,- 87, 168,- 93, 164,- 91, 155,3, 98,1, 0
	};
	float p7[] = {
		0, 0,7, 0,7, 52,-2, 52,- 1, 1
	};
	float p8[] = {
		0, 0,10, 0,10, 50,1, 50,1, 0
	};
	float p9[] = {
		0, 0, 10, 0, 10, 54, 1, 54, 1, -1
	};

	App->physics->AddEdge({585, 1024, 585, 1024}, points, 49 * 2);
	App->physics->AddEdge({382, 54, 585, 1024}, p2, 16);
	App->physics->AddEdge({35, 70, 585, 1024}, p3, 64);
	App->physics->AddEdge({390, 607, 585, 1024}, p4, 26);
	App->physics->AddEdge({34, 749, 585, 1024}, p5, 16);
	App->physics->AddEdge({456, 750, 585, 1024}, p6, 16);
	App->physics->AddEdge({248, 54, 585, 1024}, p7, 10);
	App->physics->AddEdge({293, 45, 585, 1024}, p8, 10);
	App->physics->AddEdge({334, 46, 585, 1024}, p9, 10);

	// Other elements

	// Small bouncy ball bottom center under flippers
	App->physics->AddBody(248, 1024, 24, b_static, 1.0f, 0.8f);

	// Two big bouncers on top
	bouncer1.body = App->physics->AddBody(256, 175, 50, b_static, 1.0f, 1.5f);
	bouncer1.body->listener = this;

	bouncer2.body = App->physics->AddBody(343, 169, 50, b_static, 1.0f, 1.5f);
	bouncer2.body->listener = this;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);
	App->textures->Unload(bouncer1.texture); // same as bouncer2.texture

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(graphics, 0, 0);

	if(bouncer1.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), bouncer1.hit_timer) == false)
			App->renderer->Blit(bouncer1.texture, 237, 155);
		else
			bouncer1.hit_timer = 0;
	}

	if(bouncer2.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), bouncer2.hit_timer) == false)
			App->renderer->Blit(bouncer2.texture, 323, 150);
		else
			bouncer2.hit_timer = 0;
	}

	char str[10];
	sprintf_s(str, "%d,%d", App->input->GetMouseX(), App->input->GetMouseY());
	App->window->SetTitle(str);

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::OnCollision(PhysBody* body1, PhysBody* body2)
{
	if(bouncer1.body == body1)
	{
		bouncer1.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer1.fx);
	}
	else if(bouncer2.body == body1)
	{
		bouncer2.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer2.fx);
	}
}