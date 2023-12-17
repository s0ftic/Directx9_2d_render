#include "window_manager.h"

bool WindowManager::IsActive() {
	return window_message.message != WM_QUIT;
}

void WindowManager::HandleMessage() {
	while (PeekMessage(&window_message, nullptr, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&window_message);
		DispatchMessage(&window_message);

		if (window_message.message == WM_QUIT) break;
	}
}

HWND WindowManager::GetWindowDescriptor() {
	return window_descriptor;
}

bool WindowManager::SpawnWindow(WNDPROC wnd_proc)
{
	if (!wnd_proc) {
		return false;
	}

	WNDCLASSEXA window_class;
	ZeroMemory(&window_class, sizeof(WNDCLASSEXA));
	window_class.cbSize = sizeof(WNDCLASSEXA);
	
	window_class.style = CS_CLASSDC;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.lpfnWndProc = wnd_proc;
	window_class.hInstance = GetModuleHandleA(NULL);
	window_class.lpszClassName = "NavalBattleEngine";

	if (!RegisterClassExA(&window_class)) {
		MessageBoxA(0, "Failed to crate window class", "Error", MB_ICONERROR);
		return false;
	}

	RECT client_area;
	client_area.left = 0;
	client_area.right = shared_settings->size_w;
	client_area.top = 0;
	client_area.bottom = shared_settings->size_h;
	AdjustWindowRect(&client_area, shared_settings->flags, FALSE);
	int window_width = client_area.right - client_area.left;
	int window_height = client_area.bottom - client_area.top;

	HWND hwnd_buff = CreateWindowExA(0,
				"NavalBattleEngine",				//class name
				shared_settings->name,				//window name
				shared_settings->flags,				//wwindow flag
				shared_settings->start_pos_x,	    //start pos x	
				shared_settings->start_pos_y,	    //start pos y
				window_width,			//size x
				window_height,			//size y
				nullptr,		
				nullptr,
				GetModuleHandleA(NULL),				//instance
				nullptr);

	if (!hwnd_buff) {
		MessageBoxA(0, "Failed to crate window", "Error", MB_ICONERROR);
		return false;
	}

	ShowWindow(hwnd_buff,SW_SHOW);
	UpdateWindow(hwnd_buff);

	window_descriptor = hwnd_buff;

	return true;
}

WindowManager* WindowManager::instance = nullptr;