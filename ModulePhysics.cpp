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
}

// Called before render is available
bool ModulePhysics::Init()
{
	//LOG("Creating Physics environment");
	bool ret = true;

	return ret;
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics environment");

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	return true;
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
	// get center
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		uint8 green = b->GetType() == b2BodyType::b2_staticBody ? 255 : 0;
		uint8 blue = b->GetType() == b2BodyType::b2_kinematicBody ? 255 : 0;
		
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();

					int32 count = polygonShape->GetVertexCount();

					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));

						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, green, blue);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));

					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, green, blue);
				}
				break;

				case b2Shape::e_circle:
					LOG("Circle!");
				break;

				case b2Shape::e_edge:
				LOG("Edge!");
				break;
			}
		}
	}

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

	p2List_item<PhysBody*>* item = bodies.getFirst();

	while(item != NULL)
	{
		delete item->data;
		item = item->next;
	}

	bodies.clear();

	// Delete the whole physics world!
	delete world;

	return true;
}

//
PhysBody* ModulePhysics::AddBody(const SDL_Rect& rect, body_type type )
{
	b2BodyDef box;
	
	
	switch(type)
	{
		case b_static:
			box.type = b2_staticBody;
			break;

		case b_kinematic:
			box.type = b2_kinematicBody;
			break;
		default:
			box.type = b2_dynamicBody;
			break;
	}

	box.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	box.angle = 0.0f;

	b2Body* b = world->CreateBody(&box);

	b2PolygonShape box_shape;
	box_shape.SetAsBox(PIXEL_TO_METERS(rect.w/2), PIXEL_TO_METERS(rect.h/2));

	b2FixtureDef box_fixture;
	box_fixture.shape = &box_shape;
	box_fixture.density = 1;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody();

	ret->r = rect;
	ret->b = b;
	ret->t = type;

	bodies.add(ret);

	return ret;
}

double PhysBody::GetAngle() const
{
	return RADTODEG * b->GetAngle();
}

void PhysBody::GetPosition(int& x, int& y) const
{
	b2Vec2 pos = b->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - r.w / 2;
	y = METERS_TO_PIXELS(pos.y) - r.h / 2;
}