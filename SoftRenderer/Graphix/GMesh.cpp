#include "GMesh.h"
#include <iostream>
#include <fstream>

GMesh::GMesh()
{
	data = NULL;
	color = NULL;
	size = 0;
}

GMesh::GMesh(const string& filename)
{
	set(filename);
}

bool GMesh::set(const string& filename)
{
	ifstream file;

	file.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		file.open(filename);
		file >> size;
		data = new vec3[size];
		color = new Color[size];

		int r, g, b;
		for (int i = 0; i < size; ++i)
		{
			file >> data[i].x >> data[i].y >> data[i].z; 
			file >> r >> g >> b;
			color[i] = Color(r, g, b);
		}
		file.close();
	}

	catch (ifstream::failure e)
	{
		cout << "Error: " << filename << " not found or unable to read!" << endl;
		return false;
	}

	return true;
}

Color* GMesh::getColor() { return color; }
vec3* GMesh::getData() { return data; }
int GMesh::getSize() { return size; }