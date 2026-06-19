#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <camera/Camera.h>
class Window {
public:
	virtual ~Window() = default;

	virtual void pollEvents() = 0;
	virtual void swapBuffers() = 0;
	virtual void update() = 0;
	virtual bool shouldClose() = 0;
	virtual void shutdown() = 0;
	virtual void processInput(Camera& camera) = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	GLFWwindow* m_window = nullptr;
};

