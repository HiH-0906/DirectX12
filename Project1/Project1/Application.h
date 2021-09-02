#pragma once
#include <windows.h>
#include <memory>

class Dx12Wrapper;
/// <summary>
/// アプリケーションを管理する
/// シングルトンクラス
/// </summary>
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
	~Application();
private:
	void InitWindow(void);

	WNDCLASSEX w_;
	HWND windowHandle_;
	std::unique_ptr<Dx12Wrapper> dx_;
	Application();
};

