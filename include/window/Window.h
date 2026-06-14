#pragma once

class Window {
public:
	virtual ~Window() = default;

	virtual void pollEvents() = 0;
	virtual void swapBuffers() = 0;
	virtual void update() = 0;
	virtual bool shouldClose() = 0;
	virtual void shutdown() = 0;

	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
};

