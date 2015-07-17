#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	p2Point<int> origin;
	p2Point<int> destination;
};