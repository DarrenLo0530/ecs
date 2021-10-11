#include "Converter.h"

#include "Mover.h"
#include "EntityHandle.h"
#include "Camera.h"
#include "BasicRenderSystem.h"
#include "ModelLoader.h"
#include "StaticMeshLoader.h"
#include "ConvexMeshLoader.h"
#include "PlayerInput.h"
#include "RigidBody.h"

#include "PlayerInputSystem.h"
#include "PhysicsSystem.h"

#include <iostream>;
void Mover::init() {
	gameWorld = new World();

	camera = gameWorld->createEntity();
	Camera::createCamera(&camera);
	camera.getComponent<CameraComponent>().viewport = dimensions;

	// Systems
	gameWorld->registerUpdateSystem<PlayerInputSystem>();
	gameWorld->registerUpdateSystem<PhysicsSystem>();
	gameWorld->registerRenderSystem<BasicRenderSystem>(&camera);

	{
		EntityHandle cube = gameWorld->createEntity();

		Transform t = Transform{};
		t.position = glm::vec3(0.0, 5.0, -1.0);
		cube.addComponent(t);

		Model m = ModelLoader::loadModel("models/cube/cube.fbx");
		cube.addComponent(m);

		EntityMotionState* motionState = new EntityMotionState(&cube.getComponent<Transform>());

		btCollisionShape* collider = ConvexMeshLoader::loadMeshCollider("models/cube/cube.fbx");
		RigidBody rigidBody(collider, motionState, 5.0f);

		cube.addComponent(rigidBody);
	}

	{
		EntityHandle plane = gameWorld->createEntity();

		Transform t = Transform{};
		t.position = glm::vec3(0.0, -20.0, -1.0);
		plane.addComponent(t);

		Model m = ModelLoader::loadModel("models/plane/plane.obj");
		plane.addComponent(m);

		EntityMotionState* motionState = new EntityMotionState(&plane.getComponent<Transform>());

		btCollisionShape* collider = StaticMeshLoader::loadMeshCollider("models/plane/plane.obj");
		RigidBody rigidBody(collider, motionState, 0.0f);

		plane.addComponent(rigidBody);
	}

	{
		EntityHandle player = gameWorld->createEntity();


		player.addComponent<Transform>(Transform{});

		View view{};
		view.viewCamera = camera;
		player.addComponent<View>(view);

		PlayerInput playerInput{};
		playerInput.input = inputs;
		player.addComponent<PlayerInput>(playerInput);
	}
}


void Mover::update() {
	gameWorld->update();
}

void Mover::render(float interpolation) {
	gameWorld->render();
}