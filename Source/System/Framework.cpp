#include "Framework.h"

LRESULT Framework::HandleMessage(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps{};
		BeginPaint(hwnd,&ps);
		EndPaint(hwnd,&ps);
	}
	break;
	case WM_DESTROY:
	PostQuitMessage(0);
	break;
	case WM_CREATE:
	break;
	case WM_KEYDOWN:
	if(wParam == VK_ESCAPE)
	{
		PostMessage(hwnd,WM_CLOSE,0,0);
	}
	break;
	case WM_ENTERSIZEMOVE:
	break;
	case WM_EXITSIZEMOVE:
	break;
	default:
	return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}