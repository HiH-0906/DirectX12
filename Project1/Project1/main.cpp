#include "Application.h"

#ifdef _DEBUG
#include <iostream>
#endif	// _DEBUG

using namespace std;


// @brief �R���\�[����ʂɃt�H�[�}�b�g�t���������\��
// @param format (%d�Ƃ�%f�Ƃ���)
// @patam �ϒ�����
// @remarks ���̊֐��̓f�o�b�N�p�ł��B�f�o�b�N���ɂ��������܂���
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