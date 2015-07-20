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
class PhysBody;

enum body_type
{
	b_dynamic,
	b_static,
	b_kinematic
};

class PhysBody
{
public:

	PhysBody(b2World* world, b2Body* body, const SDL_Rect& rect, body_type type);
	~PhysBody();

	double GetAngle() const;
	void GetPosition(int& x, int& y) const;
	void SetLinearSpeed(int x, int y);
	void SetAngularSpeed(float speed);

private:

	b2World* world;
	b2Body* body;
	SDL_Rect rect;
	body_type type;
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

	PhysBody* AddBody(const SDL_Rect& rect, body_type type = b_dynamic, float density = 1.0f);
	PhysBody* AddBody(int x, int y, int radius, body_type type = b_dynamic, float density = 1.0f);
	PhysBody* AddBody(const SDL_Rect& rect, float* points, uint count, body_type type = b_dynamic, float density = 1.0f);
	PhysBody* AddEdge(const SDL_Rect& rect, float* points, uint count);

	void DestroyBody(PhysBody* body);

private:

	b2World* world;
	p2List<PhysBody*> bodies;
};