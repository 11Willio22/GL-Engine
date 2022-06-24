#pragma once
#include <cstdio>

inline const char* read(const char* path)
{
	FILE* file;
	fopen_s(&file, path, "r");
	char* data = new char[1024]{0};
	if (file != 0) fread(data, 1, 1023, file);
	else printf("Could not find file %s!\n",path);
	return data;
}