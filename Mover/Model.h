#pragma once 
#include "Mesh.h"
#include "Component.h"

struct Model : public Component<Model> {
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
};