#include "Physics.h"
#include "Time.h"
namespace thomas
{
	btDiscreteDynamicsWorld* Physics::s_world;
	bool Physics::Init()
	{
		// collision configuration contains default setup for memory, collision setup. Advanced
	    //  users can create their own configuration.
		btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
		// use the default collision dispatcher. For parallel processing you can use a diffent
		//dispatcher(see Extras / BulletMultiThreaded)
		btCollisionDispatcher * dispatcher = new btCollisionDispatcher(collisionConfiguration);
		
		// btDbvtBroadphase is a good general purpose broadphase. You can also try out
		//btAxis3Sweep.
		btBroadphaseInterface * overlappingPairCache = new btDbvtBroadphase();
		
		// the default constraint solver. For parallel processing you can use a different solver
		//(see Extras / BulletMultiThreaded)
		btSequentialImpulseConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

		s_world = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		s_world->setGravity(btVector3(0, -9.82, 0));
		return true;

	}
	void Physics::Update()
	{
		s_world->stepSimulation(Time::GetDeltaTime(), 7);

	}
	void Physics::Destroy()
	{
	}
}
