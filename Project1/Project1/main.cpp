#include "Application.h"

#ifdef _DEBUG
#include <iostream>
#endif	// _DEBUG

using namespace std;


// @brief コンソール画面にフォーマット付き文字列を表示
// @param format (%dとか%fとかの)
// @patam 可変長引数
// @remarks この関数はデバック用です。デバック時にしか動きません
void DebugOutoutFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

#ifdef _DEBUG
int main()
{
#else // _DEBUG
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
#endif // _DEBUG

	auto& app = Application::GetInstance();

	app.Initialize();
	app.Run();
	app.Terminate();

	return 0;
}