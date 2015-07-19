#pragma once
#include "Module.h"
#include "Globals.h"

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define GRAVITY_X 0.0f
#define GRAVITY_Y -5.0f

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class b2World;
class b2Body;

enum body_type
{
	b_dynamic,
	b_static,
	b_kinematic
};

struct PhysBody
{
	b2Body* b;
	SDL_Rect r;
	body_type t;

	double GetAngle() const;
	void GetPosition(int& x, int& y) const;
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* AddBody(const SDL_Rect& rect, body_type type = b_dynamic);

private:

	b2World* world;
	p2List<PhysBody*> bodies;
};