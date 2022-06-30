//MBW

#include <cstdio>
#include "Window.h"
#include "Buffer.h"

#include "Shader.h"
#include "math/Math.h"
#include "File.h"
#include "entities/Entity.h"

int main()
{
	Window window("Willy", 1280, 720);
	window.create();

	Shader shader = createShader("src/vs_basic.txt", "src/fs_basic.txt");
	shader.setUniform("transform");
	shader.setUniform("view");
	shader.setUniform("perspective");

	Matrix4f view = Translate(Vector3f(0, -1.0f, -5.0f));
	Matrix4f perspective = Perspective(70.0f, (1280.0f / 720.0f), 0.001f, 1000.0f);

	Entity e = Entity(loadOBJ("src/chevelle.obj"));

	glEnable(GL_DEPTH_TEST);

	while (!window.shouldClose())
	{
		window.clear(0.1f, 0.1f, 0.1f, 1.0f);
		bindShader(shader);
		bindMesh(e.mesh);

		e.rotate(Vector3f(0, 1, 0), 0.001f);

		shader.uniform("transform", e.getTransform());
		shader.uniform("view", view);
		shader.uniform("perspective", perspective);
		glDrawElements(GL_TRIANGLES, e.mesh.size, GL_UNSIGNED_INT, 0);

		window.update();
		window.render();
	}
	return 0;
}