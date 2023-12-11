#include "CommonIncludes.h"

class Shape 
{
public:
	virtual void Draw(Shader& shader, Texture& texture) const = 0;
};