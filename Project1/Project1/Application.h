#pragma once
#include <windows.h>

class Application
{
public:
	static Application& GetInstance()
	{
		static Application s_instance;
		return s_instance;
	}
	void Initialize(void);
	void Run(void);
	void Terminate(void);

private:
	void InitWindow(void);

	WNDCLASSEX w_;
	RECT wrc_;
	HWND hwnd_;

	Application() = default;
	~Application() = default;
};

