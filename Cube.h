#include "CommonIncludes.h"
#include "Shape.h"
#include "Shader.h"

class Cube : public Shape
{
public:
	Cube();
	void Draw(Shader& shader, Texture& texture) const override;
private:
	unsigned int VAO, VBO;
};