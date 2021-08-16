#include "Mover.h"
#include "EntityHandle.h"
#include "Camera.h"
#include "BasicRenderSystem.h"
#include "ModelLoader.h"
#include "PlayerInput.h"

#include "PlayerInputSystem.h"
#include "CameraAttachSystem.h"
#include "AttachComponent.h"

void Mover::init() {
	gameWorld = new World();

	// Systems
	gameWorld->registerUpdateSystem<PlayerInputSystem>();
	gameWorld->registerUpdateSystem<CameraAttachSystem>();


	camera = gameWorld->createEntity();
	Camera::createCamera(&camera);

	// Systems 
	gameWorld->registerRenderSystem<BasicRenderSystem>(&camera, dimensions);

	EntityHandle backpack = gameWorld->createEntity();

	Transform t = Transform{};
	t.position = glm::vec3(0.0, 0.0, -1.0);
	backpack.addComponent(t);

	Model m = ModelLoader::loadModel("models/backpack/backpack.obj");
	backpack.addComponent(m);

	EntityHandle player = gameWorld->createEntity();


	player.addComponent<Transform>(Transform{});
	player.addComponent<View>(View{});
	PlayerInput playerInput{};
	playerInput.input = inputs;
	player.addComponent<PlayerInput>(playerInput);

	AttachComponent cameraAttach{};
	cameraAttach.attachedEntity = player;
	camera.addComponent<AttachComponent>(cameraAttach);



}


void Mover::update() {
	gameWorld->update();
}

void Mover::render(float interpolation) {
	gameWorld->render();
}