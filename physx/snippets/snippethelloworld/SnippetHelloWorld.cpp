// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2025 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

// ****************************************************************************
// This snippet illustrates simple use of physx
//
// It creates a number of box stacks on a plane, and if rendering, allows the
// user to create new stacks and fire a ball from the camera position
// ****************************************************************************

#include <ctype.h>

#include "PxPhysicsAPI.h"

#include "../snippetcommon/SnippetPrint.h"
#include "../snippetcommon/SnippetPVD.h"
#include "../snippetutils/SnippetUtils.h"

#include "RagdollData.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene		= NULL;

PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;


PxRigidDynamic* gRagdollActors[Skeleton::count];


const Skeleton::Enum createList[] =
{
	Skeleton::pelvis,

	Skeleton::tail,
	Skeleton::tail1,
	Skeleton::tail2,

	Skeleton::spine,
	Skeleton::spine1,
	Skeleton::head,

	// uncommenting all shapes leads to the ragdoll flying off into space
	//Skeleton::tail3
};

PxRigidDynamic* createRagdollActor(const PxTransform& actorGlobalPose, const PxU32 actorIndex) {
	static const Skeleton::Enum* createListBegin = std::begin(createList);
	static const Skeleton::Enum* createListEnd = std::end(createList);
	if (std::find(createListBegin, createListEnd, actorIndex) == createListEnd)
	{
		return nullptr;
	}


	const Ragdoll::Geometry& ragdollGeometry = Ragdoll::geometry[actorIndex];
	
	physx::PxGeometryHolder geometryHolder = ragdollGeometry.geometry;
	if (geometryHolder.getType() == physx::PxGeometryType::eCONVEXMESH)
	{
		const Ragdoll::ConvexDataArray& convex = *ragdollGeometry.convexPointer;

		PxConvexMeshDesc convexMeshDesc;
		convexMeshDesc.points.data = convex.data();
		convexMeshDesc.points.count = static_cast<PxU32>(convex.size());
		convexMeshDesc.points.stride = sizeof(PxVec3);
		convexMeshDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

		geometryHolder.convexMesh().convexMesh = PxCreateConvexMesh(PxCookingParams(PxTolerancesScale()), convexMeshDesc, gPhysics->getPhysicsInsertionCallback());
	}

	
	PxRigidDynamic* actor = gPhysics->createRigidDynamic(actorGlobalPose);
	actor->setName(Skeleton::names[actorIndex]);
	actor->setCMassLocalPose(Ragdoll::localMassCenters[actorIndex]);
	PxRigidBodyExt::updateMassAndInertia(*actor, 1.0f);

	//printf("Created actor %s\n", Skeleton::names[actorIndex]);

	PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, geometryHolder.any(), *gMaterial); (void)shape;
	shape->setName(Skeleton::names[actorIndex]);
	shape->setLocalPose(Ragdoll::shapeLocalPose[actorIndex]);

	gScene->addActor(*actor);

	const Skeleton::Enum parentBone = Skeleton::parentBones[actorIndex];
	if (parentBone != Skeleton::invalid && actorIndex != Skeleton::pelvis)
	{
		if (PxRigidDynamic* parentActor = gRagdollActors[parentBone])
		{
			PxTransform parentPose = Ragdoll::jointParentPoses[actorIndex];
			parentPose.q.normalize();

			PxSphericalJoint* joint = PxSphericalJointCreate(*gPhysics, parentActor, parentPose, actor, PxTransform(PxIdentity));
			joint->setConstraintFlag(PxConstraintFlag::eCOLLISION_ENABLED, false);

			//printf(" - Attached %s to %s\n", Skeleton::names[actorIndex], Skeleton::names[parentBone]);
		}
	}
	

	return actor;
}

void createRagdoll(const PxVec3 globalPose)
{
	for (PxU8 i_actor = 0; i_actor < Skeleton::count; ++i_actor)
	{
		PxTransform actorPose = Ragdoll::actorGlobalPoses[i_actor];
		actorPose.p += globalPose;

		gRagdollActors[i_actor] = createRagdollActor(actorPose, i_actor);
	}
}


PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity=PxVec3(0))
{
	PxRigidDynamic* dynamic = PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	dynamic->setMass(2.0f);
	gScene->addActor(*dynamic);
	return dynamic;
}

void createStatic()
{
	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0,1,0,0), *gMaterial);
	gScene->addActor(*groundPlane);
}

void initPhysics(bool /*interactive*/)
{	
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);
	PxInitExtensions(*gPhysics, gPvd);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.solverType = PxSolverType::eTGS;
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.cpuDispatcher = gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	
	gScene = gPhysics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if(pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	createStatic();

	createRagdoll(PxVec3(0.0f, 1.f, 0.0f));
}

void stepPhysics(bool /*interactive*/)
{
	gScene->simulate(1.0f/60.0f);
	gScene->fetchResults(true);
}
	
void cleanupPhysics(bool /*interactive*/)
{
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);
	if(gPvd)
	{
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();	gPvd = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(gFoundation);
	
	//printf("SnippetHelloWorld done.\n");
}

void keyPress(unsigned char key, const PxTransform& camera)
{
	switch(toupper(key))
	{
	case 'C':	createRagdoll(PxVec3(0.0f, 1.0f, 0.0f));	break;
	case ' ':	createDynamic(camera, PxSphereGeometry(0.4f), camera.rotate(PxVec3(0,0,-1))*40);	break;
	}
}

int snippetMain(int, const char*const*)
{
#ifdef RENDER_SNIPPET
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}
