#include "File.h"
#include "math/Math.h"

String read(const char* path)
{
	FILE* file;
	fopen_s(&file, path, "r");
	char* data = new char[1025]{ 0 };
	String m;	
	if (file != 0)
	{
		fread(data, 1, 1024, file);
		data[1024] = '\0';
		m = String(data);
		int resizes = 0;
		while (m.getLength() >= resizes++ * 1024)
		{
			delete[] data;
			data = new char[1025]{ 0 };
			fread(data, 1, 1024, file);
			data[1024] = '\0';
			m += String(data);
		}
	}
	else printf("Could not find file %s!\n", path);
	delete[] data;
	return m;
}

Mesh loadOBJ(String path)
{
	Array<Vertex> finalVertices;
	Array<int> finalIndices;

	Array<Vector3f> positions;

	Array<String> file = read(path.data).split('\n');
	for (int i = 0; i < file.depth; i++)
	{
		Array<String> m = file.get(i).split(' ');
		if (m.get(0) == "v")
		{
			positions.add(Vector3f(m.get(1).parse(), m.get(2).parse(), m.get(3).parse()));
		}
		if (m.get(0) == "f")

		{
			for (int vertex = 0; vertex < 3; vertex++) {
				Array<String> split = m.get(vertex + 1).split('/');
				Vector3f pos = positions.get(split.get(0).parse() - 1);
				finalVertices.add(Vertex(pos.x, pos.y, pos.z));
				finalIndices.add(finalIndices.depth);
				//MBW
			}
		}
	}

	return Mesh::create(finalVertices, finalIndices);
}

