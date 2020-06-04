#include <Windows.h>
#include <tchar.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush(RGB(200, 200, 200)); 	// Заполнение окна белым цветом


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Светофор"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	TCHAR instructuion[] = _T("STOP");
	HDC hDC = ::GetDC(hWnd);
	static int x = 0;

	switch (message)		 // Обработчик сообщений
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
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}
