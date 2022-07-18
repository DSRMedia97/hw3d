#include <Windows.h>
#include <string>
#include <sstream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(97);
		break;
	case WM_KEYDOWN: // Not case sensitive - could be any button on the keyboard - use when case is not important (ie: movement controls)
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Respect");
		}
		break;
	case WM_KEYUP: 
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Dangerfield");
		}
		break;
	case WM_CHAR: // Text input - case sensitive - use when case is important (ie: capturing typing of a character name)
		{
			static std::string title;
			title.push_back((char)wParam);
			SetWindowText(hWnd, title.c_str());
		}	
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS pt = MAKEPOINTS(lParam);
			std::ostringstream oss;
			oss << "(" << pt.x << "," << pt.y << ")";
			SetWindowText(hWnd, oss.str().c_str());
		}
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
	const auto pClassName = "hw3dbutts";
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
		"Happy Hard Window",
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