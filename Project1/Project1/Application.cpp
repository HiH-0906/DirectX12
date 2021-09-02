#include <tchar.h>
#include <iostream>

#include "Application.h"
#include "DirectX12/Dx12Wrapper.h"

using namespace std;
namespace
{
	constexpr LONG window_width = 640;
	constexpr LONG window_heigth = 480;
}

/// �ʓ|�����Ǐ����Ȃ���΂����Ȃ��֐�
LRESULT WindowProcedure(HWND windowHandle_, UINT msg, WPARAM wparam, LPARAM lpram)
{
	// �E�B���h�E���j�����ꂽ��Ă΂��
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);	// OS�ɑ΂��āu�������̃A�v���͏I���v�Ɠ`����
		return 0;
	}
	return DefWindowProc(windowHandle_, msg, wparam, lpram);	//�K��̏������s��
}

void Application::Initialize(void)
{
	InitWindow();
}

void Application::InitWindow(void)
{
	// �E�B���h�E�N���X�̐������o�^
	w_.cbSize = sizeof(WNDCLASSEX);
	w_.lpfnWndProc = (WNDPROC)(WindowProcedure);	// �R�[���o�b�N�֐��̎w��
	w_.lpszClassName = _T("DX12Sample");			// �A�v���P�[�V�����N���X��(�K��)
	w_.hInstance = GetModuleHandle(nullptr);		// �n���h���̎擾

	RegisterClassEx(&w_);						// �A�v���P�[�V�����N���X(�E�B���h�E�N���X�̎w������߂�)

	RECT wrc = { 0,0,window_width,window_heigth };	// �E�B���h�E�̃T�C�Y�����߂�

	// �֐����g���ăE�B���h�E�̃T�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�I�u�W�F�N�g�̐���
	windowHandle_ = CreateWindow(w_.lpszClassName,	// �N���X���w��
		_T("DX12 �e�X�g"),						// �^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,					// �^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,							// �\��x���W��OS�ɂ��C��
		CW_USEDEFAULT,							// �\��y���W��OS�ɂ��C��
		wrc.right - wrc.left,					// �E�B���h�E��
		wrc.bottom - wrc.top,					// �E�B���h�E��
		nullptr,								// �e�E�B���h�E�n���h��
		nullptr,								// ���j���[�n���h��
		w_.hInstance,							// �Ăяo���A�v���P�[�V�����n���h��
		nullptr									// �ǉ��p�����[�^�[
		);

	if (windowHandle_ == nullptr)
	{
		LPVOID messageBuffer = nullptr;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&messageBuffer,
			0,
			nullptr
		);
		OutputDebugString((TCHAR*)messageBuffer);
		cout << (TCHAR*)messageBuffer << endl;
		LocalFree(messageBuffer);
	}
}

Application::Application()
{
}

void Application::Run(void)
{
	// �E�B���h�E�\��
	ShowWindow(windowHandle_, SW_SHOW);

	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// �A�v���P�[�V�������I������Ƃ���message��WM_QUIT�ɂȂ�
		if (msg.message == WM_QUIT)
		{
			break;
		}
	}
}

void Application::Terminate(void)
{
	UnregisterClass(w_.lpszClassName, w_.hInstance);
}

Application::~Application() = default;
