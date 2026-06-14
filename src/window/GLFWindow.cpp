#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <window/GLFWindow.h>

#include <stdexcept>
#include <iostream>

int GLFWindow::validateDimension(int value, const std::string& name)
{
	if (value <= 0)
		throw std::invalid_argument(name + " must be a positive integer.");

	return value;
}

// Constructors ==========================================

GLFWindow::GLFWindow()
	: m_width(Defaults::WIDTH), m_height(Defaults::HEIGHT), m_title(Defaults::TITLE)
{
	init();
}

GLFWindow::GLFWindow(int width, int height)
	: m_width(validateDimension(width, "width")),
	m_height(validateDimension(height, "height")),
	m_title(Defaults::TITLE)
{
	init();
}

GLFWindow::GLFWindow(int width, int height, const std::string& title)
	: m_width(validateDimension(width, "width")),
	m_height(validateDimension(height, "height")),
	m_title(title)
{
	init();
}

void GLFWindow::shutdown()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
}

GLFWindow::~GLFWindow()
{
	shutdown();
}

// IWindow Interface Implementation =====================

void GLFWindow::init()
{
	if (!glfwInit())
		throw std::runtime_error("OpenGLWindow: glfwInit() failed");

	setGLFWHints();

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		throw std::runtime_error("OpenGLWindow: glfwCreateWindow() failed");
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("OpenGLWindow: gladLoadGLLoader() failed");

	// Keep stored dimensions in sync if GLFW adjusted them
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
}

void GLFWindow::pollEvents()
{
	glfwPollEvents();
}

void GLFWindow::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

bool GLFWindow::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

int GLFWindow::getWidth()  const { return m_width; }
int GLFWindow::getHeight() const { return m_height; }

void GLFWindow::setGLFWHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Defaults::GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Defaults::GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // required on macOS
#endif
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

void GLFWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void::GLFWindow::update()
{
	swapBuffers();
	pollEvents();
}