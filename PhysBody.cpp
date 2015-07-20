
#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Box2D/Box2D/Box2D.h"

PhysBody::PhysBody(b2World* world, b2Body* body, const SDL_Rect& rect, body_type type) : world(world), body(body), rect(rect), type(type)
{}

PhysBody::~PhysBody()
{
	world->DestroyBody(body);
	body = NULL;
}

double PhysBody::GetAngle() const
{
	return RADTODEG * body->GetAngle();
}

void PhysBody::GetPosition(int& x, int& y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - rect.w / 2;
	y = METERS_TO_PIXELS(pos.y) - rect.h / 2;
}

void PhysBody::SetLinearSpeed(int x, int y)
{
	body->SetLinearVelocity(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)));
}

void PhysBody::SetAngularSpeed(float speed)
{
	body->SetAngularVelocity(speed * DEGTORAD);
}