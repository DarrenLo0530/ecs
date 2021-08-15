#version 460 core

struct Material {
	sampler2D textureDiffuse1;
};

in VS_OUT {
	vec2 texCoord;
} fs_in;

out vec4 fragColor;

uniform Material material;

vec2 texCoord;

void main() {
	texCoord = fs_in.texCoord;

	fragColor = texture(material.textureDiffuse1, texCoord);
}