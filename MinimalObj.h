#ifndef _MINIMALOBJ_H
#define _MINIMALOBJ_H

#include <vector>
#include "vec4.h"

struct MinimalObjFaceVertex
{
	int vertex;
	int uvw;
	int normal;
};

struct MinimalObj
{
	// [NOTE] not optimized for speed
	std::vector<vec4f> vertex;
	std::vector<vec4f> uvw;
	std::vector<vec4f> normal;
	std::vector<std::vector<MinimalObjFaceVertex> > face;
	std::vector<vec4f> faceColor;	// [NOTE] optional
	bool read(char const * filename);
	bool write(char const * filename) const;
	void clear();
};

#endif
