#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <wchar.h>
#define DIV 1024
#define WIDTH 7
//#pragma warning(disable:4996)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
HWND hWnd;
int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// ���������� ���� ����� ������ 


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("4"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				// �������� ����

	//HMENU WINAPI a;
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&����� 1");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"��������");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"���������");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&����� 2");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"��������");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"���������");
	}
	SetMenu(hWnd, MainMenu);

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return 0;
}
HANDLE hThread1;
HANDLE hThread2;
DWORD WINAPI Thread1(LPVOID t);
DWORD WINAPI Thread2(LPVOID t);

int a = 0;
BOOL fin1 = true;
BOOL fin2 = true;

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)		 // ���������� ���������
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// ���������� ��������� 
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COMMAND:
		switch (wParam)
		{
		case 1001:
		{
			fin1 = true;
			hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			break;
		}
		case 1002:
		{
			TerminateThread(hThread1, 0);
			CloseHandle(hThread1);
			fin1 = FALSE;
			break;
		}
		case 1003:
		{
			fin2 = TRUE;
			hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
			break;
		}
		case 1004:
		{
			TerminateThread(hThread2, 0);
			CloseHandle(hThread2);
			fin2 = FALSE;
			break;
		}
		}
	}
	return 0;
}

DWORD WINAPI Thread1(LPVOID t)
{
	RECT rect;
	int f = 0;
	int g = 0;
	int d = 0;
	int k = 0;
	int h = 0;
	while (fin1)
	{
		GetWindowRect(HWND(t), &rect);
		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hBrush);
		d = rand() % 20;
		//h = rand() % 10,
		f = rand() % 10,
			g = rand() % 30,
			Ellipse(hdc, f * d, g * d, 20 + f * d, 20 + g * d);
		Sleep(2000);
	}
	return (0);


}

DWORD WINAPI Thread2(LPVOID t)
{
	int width = 0;
	int height = 0;
	RECT rect;
	TCHAR buff[300];
	HPEN hPen;
	HPEN myPen;
	MEMORYSTATUSEX statex;
	while (fin2)
	{
		int a;
		int x = 0;
		a = 0;
		while (fin2)
		{
			GetWindowRect(HWND(t), &rect);
			if (a == 0)
			{
				HDC hdc = GetDC(HWND(t));
				HBRUSH hBrush;
				HPEN hPen;
				for (int i = 750; i < 951; i++)
				{
					//if (x == 0)
					{
						MoveToEx(hdc, 850, 50, NULL);
						myPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
						SelectObject(hdc, myPen);
						LineTo(hdc, i - 1, 200); //Sleep(10);
						//InvalidateRect(hWnd, NULL, TRUE);

						MoveToEx(hdc, 850, 50, NULL);
						myPen = CreatePen(PS_SOLID, 10, RGB(rand() % 255, rand() % 255, rand() % 255));
						SelectObject(hdc, myPen);
						LineTo(hdc, i, 200); Sleep(10);
						//InvalidateRect(hWnd , NULL, TRUE);

						//x = 1;
					}


				}
				for (int i = 951; i > 749; i--)
				{
					MoveToEx(hdc, 850, 50, NULL);
					myPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
					SelectObject(hdc, myPen);
					LineTo(hdc, i + 1, 200); //Sleep(10);
					//InvalidateRect(hWnd, NULL, TRUE);

					MoveToEx(hdc, 850, 50, NULL);
					myPen = CreatePen(PS_SOLID, 10, RGB(rand() % 255, rand() % 255, rand() % 255));
					SelectObject(hdc, myPen);
					LineTo(hdc, i, 200); Sleep(10);
					//InvalidateRect(hWnd, NULL, TRUE);

				}


			}


		}

	}
	return 0;
}