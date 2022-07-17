#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(97);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine,
	int nCmdShow)
{
	const auto pClassName = L"hw3dbutts";
	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc; // Long Pointer Function Windows Procedure set to Default Windows Procedure
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	// create window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		L"Happy Hard Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,  // Styles: https://docs.microsoft.com/en-us/windows/desktop/winmsg/window-styles
		200, 200, 640, 480,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	// draw the window
	ShowWindow(hWnd, SW_SHOW);

	// message pump
	MSG msg;
	BOOL getResult;
	while (getResult = GetMessage(&msg, nullptr, 0, 0) > 0) //Get all messages -> returns 1 if valid; 0 for Quit Message; and -1 for invalid message / error
	{
		TranslateMessage(&msg); // const pointer will not modify the message 
		DispatchMessage(&msg);
	}

	if (getResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
	
	return 0;
}