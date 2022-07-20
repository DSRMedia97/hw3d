#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Window wnd(800, 300, "Guinea Pigs");

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
	
	return msg.wParam;
}