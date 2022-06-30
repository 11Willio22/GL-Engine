#pragma once
#include <cstdio>
#include "String.h"
#include "Buffer.h"

String read(const char* path);
Mesh loadOBJ(String path);