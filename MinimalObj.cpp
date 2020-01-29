#include "minimalobj.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;

bool MinimalObj::read(char const * filename)
{
	// [FIXMELATER] could support more Obj information http://www.royriggs.com/obj.html
	ifstream in(filename, ios::binary);
	if (!in) return false;
	clear();
	while (true)
	{
		//char buffer[4096];
		//in.getline(buffer, 4096);
		//if (!in) break;

		string test;
		if (!getline(in, test)) break;


		stringstream strin(test);
		string s;
		strin >> s;

		if (s == "OFF")
		{
			int vertexCount, faceCount, somethingCount;
			in >> vertexCount >> faceCount >> somethingCount;
			vertex.reserve(vertexCount);
			for (int i = 0; i < vertexCount; ++ i)
			{
				vec4f v;
				in >> v.x >> v.y >> v.z;
				vertex.push_back(v);
			}
			face.reserve(faceCount);
			for (int i = 0; i < faceCount; ++ i)
			{
				int indexCount;
				in >> indexCount;
				vector<MinimalObjFaceVertex> f;
				f.reserve(indexCount);
				for (int j = 0; j < indexCount; ++ j)
				{
					MinimalObjFaceVertex mv;
					in >> mv.vertex;
					mv.uvw = -1;
					mv.normal = -1;
					f.push_back(mv);
				}
				face.push_back(f);
			}
			return true;
		}
		if (s == "v")
		{
			vec4f v;
			strin >> v.x >> v.y >> v.z;
			v.w = 1.0;
			vertex.push_back(v);
		}
		else if (s == "vt")
		{
			vec4f vt;
			strin >> vt.x >> vt.y >> vt.z;
			uvw.push_back(vt);
		}
		else if (s == "vn")
		{
			vec4f vn;
			strin >> vn.x >> vn.y >> vn.z;
			vn.w = 0.0;
			normal.push_back(vn);
		}
		else if (s == "f")
		{
			vector<MinimalObjFaceVertex> f;
			while (true)
			{
				MinimalObjFaceVertex mv;
				strin >> mv.vertex;
				if (!strin) break;
				-- mv.vertex;
				mv.uvw = -1;
				mv.normal = -1;
				if (strin.peek() == '/')
				{
					strin.get();
					if (strin.peek() != '/')
					{
						strin >> mv.uvw;
						-- mv.uvw;
					}
					if (strin.peek() == '/')
					{
						strin.get();
						strin >> mv.normal;
						-- mv.normal;
					}
				}
				f.push_back(mv);
			}
			face.push_back(f);
		}
	}
	return true;
}

bool MinimalObj::write(char const * filename) const
{
	ofstream out(filename);
	if (!out) return false;
	out << "# MinimalObj" << '\n';
	if (faceColor.size()) out << "mtllib " << filename << ".mtl" << '\n';
	for (int v = 0; v < vertex.size(); ++ v)
		out << "v " << vertex[v].x << " " << vertex[v].y << " " << vertex[v].z << '\n';
	for (int v = 0; v < uvw.size(); ++ v)
		out << "vt " << uvw[v].x << " " << uvw[v].y << " " << uvw[v].z << '\n';
	for (int v = 0; v < normal.size(); ++ v)
		out << "vn " << normal[v].x << " " << normal[v].y << " " << normal[v].z << '\n';
	for (int f = 0; f < face.size(); ++ f)
	{
		if (faceColor.size() && (!f || faceColor[f] != faceColor[f - 1])) out << "usemtl m" << f << '\n';
		out << "f ";
		for (int v = 0; v < face[f].size(); ++ v)
		{
			out << face[f][v].vertex + 1;
			if (uvw.size())
			{
				out << "/" << face[f][v].uvw + 1;
				if (normal.size())
					out << "/" << face[f][v].normal + 1;
			}
			out << " ";
		}
		out << '\n';
	}
	if (faceColor.size())
	{
		ofstream mout((string(filename) + ".mtl").c_str());
		if (!mout) return false;
		for (int f = 0; f < face.size(); ++ f) if (!f || faceColor[f] != faceColor[f - 1])
		{
			mout << "newmtl m" << f << '\n';
			mout << "Kd " << faceColor[f][0] << " " << faceColor[f][1] << " " << faceColor[f][2] << '\n';
		}
	}
	return true;
}

void MinimalObj::clear()
{
	vertex.clear();
	uvw.clear();
	normal.clear();
	face.clear();
	faceColor.clear();
}