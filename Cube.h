#include "CommonIncludes.h"
#include "Shape.h"
#include "Shader.h"
#include "Texture.h"

class Cube : public Shape
{
public:
	Cube();
	void Draw(Shader& shader) const override;
	void setPosition(const glm::vec3& newPosition);
	glm::vec3 getPosition(Cube cube);

private:
	unsigned int VAO, VBO;
	glm::vec3 position;
};