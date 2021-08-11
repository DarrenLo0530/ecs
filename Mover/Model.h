#pragma once 
#include "Mesh.h"
#include "Texture.h"
#include "Component.h"

struct Model : public Component<Model> {
public:
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
};