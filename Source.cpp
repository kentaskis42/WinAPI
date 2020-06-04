#include <Windows.h>
#include <tchar.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
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
	wc.hbrBackground = CreateSolidBrush(RGB(200, 200, 200)); 	// ���������� ���� ����� ������


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("��������"), 		// ��������� ���� 
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

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}
	return 0;
}

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	TCHAR instructuion[] = _T("STOP");
	HDC hDC = ::GetDC(hWnd);
	static int x = 0;

	switch (message)		 // ���������� ���������
	{
		//break;
	//a3:
	case WM_RBUTTONDOWN:

		x = 2;
		InvalidateRect(hWnd, NULL, false);


		break;
		//if (x == 2) goto a2;
	case WM_LBUTTONDOWN:

		x = 1;
		InvalidateRect(hWnd, NULL, true);


		//a2:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (x == 0)
		{
			Rectangle(hDC, 50, 50, 200, 500);
			HBRUSH hBrush12;
			hBrush12 = CreateSolidBrush(RGB(120, 0, 0));
			SelectObject(hDC, hBrush12);
			Ellipse(hDC, 75, 75, 175, 175);

			HBRUSH hBrush13;
			hBrush13 = CreateSolidBrush(RGB(120, 120, 0));
			SelectObject(hDC, hBrush13);
			Ellipse(hDC, 75, 200, 175, 300);

			HBRUSH hBrush14;
			hBrush14 = CreateSolidBrush(RGB(0, 120, 0));
			SelectObject(hDC, hBrush14);
			Ellipse(hDC, 75, 325, 175, 425);
		}

		if (x == 1)
		{

			//int a = 1;
			//while (a == 1)

			{
				Rectangle(hDC, 50, 50, 200, 500);
				{
					HBRUSH hBrush;
					hBrush = CreateSolidBrush(RGB(220, 0, 0));
					SelectObject(hDC, hBrush);
					Ellipse(hDC, 75, 75, 175, 175);

					HBRUSH hBrush1;
					hBrush1 = CreateSolidBrush(RGB(120, 120, 0));
					SelectObject(hDC, hBrush1);
					Ellipse(hDC, 75, 200, 175, 300);

					HBRUSH hBrush2;
					hBrush2 = CreateSolidBrush(RGB(0, 120, 0));
					SelectObject(hDC, hBrush2);
					Ellipse(hDC, 75, 325, 175, 425);
				}
				Sleep(1500);
				{
					HBRUSH hBrush3;
					hBrush3 = CreateSolidBrush(RGB(120, 0, 0));
					SelectObject(hDC, hBrush3);
					Ellipse(hDC, 75, 75, 175, 175);

					HBRUSH hBrush4;
					hBrush4 = CreateSolidBrush(RGB(220, 220, 0));
					SelectObject(hDC, hBrush4);
					Ellipse(hDC, 75, 200, 175, 300);

					HBRUSH hBrush5;
					hBrush5 = CreateSolidBrush(RGB(0, 120, 0));
					SelectObject(hDC, hBrush5);
					Ellipse(hDC, 75, 325, 175, 425);
				}
				Sleep(1500);
				{
					HBRUSH hBrush6;
					hBrush6 = CreateSolidBrush(RGB(120, 0, 0));
					SelectObject(hDC, hBrush6);
					Ellipse(hDC, 75, 75, 175, 175);

					HBRUSH hBrush7;
					hBrush7 = CreateSolidBrush(RGB(120, 120, 0));
					SelectObject(hDC, hBrush7);
					Ellipse(hDC, 75, 200, 175, 300);

					HBRUSH hBrush8;
					hBrush8 = CreateSolidBrush(RGB(0, 220, 0));
					SelectObject(hDC, hBrush8);
					Ellipse(hDC, 75, 325, 175, 425);
				}
				Sleep(1500);
				//x = 0;
				//goto a3;

			}
		}
		if (x == 2)
		{
			Rectangle(hDC, 50, 50, 200, 500);
			TextOut(hDC, 100, 525, instructuion, _tcslen(instructuion));
			{
				HBRUSH hBrush9;
				hBrush9 = CreateSolidBrush(RGB(220, 0, 0));
				SelectObject(hDC, hBrush9);
				Ellipse(hDC, 75, 75, 175, 175);

				HBRUSH hBrush10;
				hBrush10 = CreateSolidBrush(RGB(120, 120, 0));
				SelectObject(hDC, hBrush10);
				Ellipse(hDC, 75, 200, 175, 300);

				HBRUSH hBrush11;
				hBrush11 = CreateSolidBrush(RGB(0, 120, 0));
				SelectObject(hDC, hBrush11);
				Ellipse(hDC, 75, 325, 175, 425);
				Sleep(5000);
			}
		}
		EndPaint(hWnd, &ps);
		//return 0;
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break; 			// ���������� ��������� 
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}