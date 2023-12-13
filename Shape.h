#include "CommonIncludes.h"

class Shape 
{
public:
	virtual void Draw(Shader& shader) const = 0;
};