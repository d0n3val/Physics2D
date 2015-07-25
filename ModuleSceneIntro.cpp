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

	// Sensors (blue lights on the floor)
	tex_light_tiny = App->textures->Load("pinball/sensor_tiny.png");
	tex_light_medium = App->textures->Load("pinball/sensor_med.png");
	tex_light_big = App->textures->Load("pinball/sensor_big.png");

	fx_light_tiny = App->audio->LoadFx("pinball/bonus2.wav");
	fx_light_medium = App->audio->LoadFx("pinball/bonus2.wav");
	fx_light_big = App->audio->LoadFx("pinball/bonus3.wav");

	lights.PushBack(Light(this, 422, 140, lightTypes::tiny));
	lights.PushBack(Light(this, 451, 159, lightTypes::tiny));
	lights.PushBack(Light(this, 481, 179, lightTypes::tiny));

	lights.PushBack(Light(this, 220, 514, lightTypes::tiny));
	lights.PushBack(Light(this, 251, 530, lightTypes::tiny));

	lights.PushBack(Light(this, 73, 525, lightTypes::tiny));
	lights.PushBack(Light(this, 61, 556, lightTypes::tiny));
	lights.PushBack(Light(this, 49, 587, lightTypes::tiny));

	lights.PushBack(Light(this, 73, 245, lightTypes::medium));
	lights.PushBack(Light(this, 64, 207, lightTypes::medium));
	lights.PushBack(Light(this, 61, 170, lightTypes::medium));
	lights.PushBack(Light(this, 58, 134, lightTypes::medium));
	lights.PushBack(Light(this, 57, 99, lightTypes::medium));
	lights.PushBack(Light(this, 55, 63, lightTypes::medium));
	lights.PushBack(Light(this, 13, 63, lightTypes::medium));
	lights.PushBack(Light(this, 13, 100, lightTypes::medium));
	lights.PushBack(Light(this, 14, 136, lightTypes::medium));
	lights.PushBack(Light(this, 15, 174, lightTypes::medium));
	lights.PushBack(Light(this, 19, 214, lightTypes::medium));
	lights.PushBack(Light(this, 25, 253, lightTypes::medium));
	lights.PushBack(Light(this, 34, 291, lightTypes::medium));
	lights.PushBack(Light(this, 46, 333, lightTypes::medium));
	lights.PushBack(Light(this, 61, 373, lightTypes::medium));

	lights.PushBack(Light(this, 266, 63, lightTypes::big));
	lights.PushBack(Light(this, 309, 58, lightTypes::big));
	lights.PushBack(Light(this, 352, 59, lightTypes::big));

	lights.PushBack(Light(this, 426, 32, lightTypes::big));
	lights.PushBack(Light(this, 385, 477, lightTypes::big));

	lights.PushBack(Light(this, 6, 870, lightTypes::big));
	lights.PushBack(Light(this, 472, 870, lightTypes::big));

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



	for(uint i = 0; i < lights.Count(); ++i)
	{
		if(lights[i].on == true)
		{
			App->renderer->Blit(lights[i].texture, lights[i].x, lights[i].y);
		}
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
		return;
	}
	
	if(bouncer2.body == body1)
	{
		bouncer2.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer2.fx);
		return;
	}

	for(uint i = 0; i < lights.Count(); ++i)
	{
		if(body1 == lights[i].body)
		{
			if(lights[i].on == false)
			{
				lights[i].on = true;
				App->audio->PlayFx(lights[i].fx);
			}
			return;
		}
	}
}

Light::Light(ModuleSceneIntro* scene, int x, int y, lightTypes type)
{
	this->type = type;
	this->x = x;
	this->y = y;

	int radius;

	switch(type)
	{
		case tiny:
			radius = 6;
			texture = scene->tex_light_tiny;
			fx = scene->fx_light_tiny;
			break;
		case medium:
			radius = 7;
			texture = scene->tex_light_medium;
			fx = scene->fx_light_medium;
			break;
		case big:
			radius = 11;
			texture = scene->tex_light_big;
			fx = scene->fx_light_big;
			break;
	}

	body = scene->App->physics->AddBody(x + radius, y + radius, radius * 2, b_static, 1.0f, 1.0f, false, true);
	body->listener = scene;
	on = false;
}