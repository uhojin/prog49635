#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "standardincludes.h"

class WindowController : public Singleton<WindowController>
{
public:
	// ctors
	WindowController();
	virtual ~WindowController();

	// Accessors
	GLFWwindow* GetWindow() { if (m_window == nullptr) { NewWindow(); } return m_window; }

	// Methods
	void NewWindow();
	Resolution GetResolution();

private:
	// Members
	GLFWwindow* m_window;
};

#endif // !WINDOW_CONTROLLER_H
