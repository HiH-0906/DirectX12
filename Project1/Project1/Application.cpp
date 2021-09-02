#include <tchar.h>
#include <iostream>

#include "Application.h"

using namespace std;
namespace
{
	constexpr LONG window_width = 640;
	constexpr LONG window_heigth = 480;
}

/// 面倒だけど書かなければいけない関数
LRESULT WindowProcedure(HWND hwnd_, UINT msg, WPARAM wparam, LPARAM lpram)
{
	// ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);	// OSに対して「もうこのアプリは終わる」と伝える
		return 0;
	}
	return DefWindowProc(hwnd_, msg, wparam, lpram);	//規定の処理を行う
}

void Application::Initialize(void)
{
	InitWindow();
}

void Application::InitWindow(void)
{
	// ウィンドウクラスの生成＆登録
	

	w_.cbSize = sizeof(WNDCLASSEX);
	w_.lpfnWndProc = (WNDPROC)(WindowProcedure);	// コールバック関数の指定
	w_.lpszClassName = _T("DX12Sample");			// アプリケーションクラス名(適当)
	w_.hInstance = GetModuleHandle(nullptr);		// ハンドルの取得

	RegisterClassEx(&w_);						// アプリケーションクラス(ウィンドウクラスの指定を決める)

	wrc_ = { 0,0,window_width,window_heigth };	// ウィンドウのサイズを決める

	// 関数を使ってウィンドウのサイズを補正する
	AdjustWindowRect(&wrc_, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウオブジェクトの生成
	hwnd_ = CreateWindow(w_.lpszClassName,	// クラス名指定
		_T("DX12 テスト"),						// タイトルバーの文字
		WS_OVERLAPPEDWINDOW,					// タイトルバーと境界線があるウィンドウ
		CW_USEDEFAULT,							// 表示x座標はOSにお任せ
		CW_USEDEFAULT,							// 表示y座標はOSにお任せ
		wrc_.right - wrc_.left,					// ウィンドウ幅
		wrc_.bottom - wrc_.top,					// ウィンドウ高
		nullptr,								// 親ウィンドウハンドル
		nullptr,								// メニューハンドル
		w_.hInstance,							// 呼び出しアプリケーションハンドル
		nullptr,								// 追加パラメーター
		);

	if (hwnd_ == nullptr)
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

void Application::Run(void)
{
	// ウィンドウ表示
	ShowWindow(hwnd_, SW_SHOW);

	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// アプリケーションが終了するときにmessageがWM_QUITになる
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
