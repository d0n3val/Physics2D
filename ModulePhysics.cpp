#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
	#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
	#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
	delete world;
}

// Called before render is available
bool ModulePhysics::Init()
{
	LOG("Creating Physics environment");
	bool ret = true;

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	return ret;
}

// 
update_status ModulePhysics::PreUpdate()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world->Step(timeStep, velocityIterations, positionIterations);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::Update()
{
	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	return true;
}
