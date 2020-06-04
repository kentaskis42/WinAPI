#include <Windows.h>
#include <Windows.h>
#include <tchar.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <iostream> 
#include <cmath>    
#include <commdlg.h>
#include <shlobj.h>
#include <wingdi.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Äåñêðèïòîð òåêóùåãî ïðèëîæåíèÿ 
	HINSTANCE Prev, 	// Â ñîâðåìåííûõ ñèñòåìàõ âñåãäà 0 
	LPTSTR cmd, 		// Êîìàíäíàÿ ñòðîêà 
	int mode) 		// Ðåæèì îòîáðàæåíèÿ îêíà
{
	HWND hWnd;		// Äåñêðèïòîð ãëàâíîãî îêíà ïðîãðàììû 
	MSG msg; 		// Ñòðóêòóðà äëÿ õðàíåíèÿ ñîîáùåíèÿ 
	WNDCLASS wc; 	// Êëàññ îêíà
	// Îïðåäåëåíèå êëàññà îêíà 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Èìÿ êëàññà îêíà 
	wc.lpfnWndProc = WndProc; 					// Ôóíêöèÿ îêíà 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Ñòèëü îêíà 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Ñòàíäàðòíàÿ èêîíêà 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Ñòàíäàðòíûé êóðñîð 
	wc.lpszMenuName = NULL; 					// Íåò ìåíþ 
	wc.cbClsExtra = 0; 						// Íåò äîïîëíèòåëüíûõ äàííûõ êëàññà 
	wc.cbWndExtra = 0; 						// Íåò äîïîëíèòåëüíûõ äàííûõ îêíà 
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); 	// Çàïîëíåíèå îêíà áåëûì öâåòîì


	// Ðåãèñòðàöèÿ êëàññà îêíà
	if (!RegisterClass(&wc)) return 0;

	// Ñîçäàíèå îêíà 
	hWnd = CreateWindow(WinName,			// Èìÿ êëàññà îêíà 
		_T("Äç"), 		// Çàãîëîâîê îêíà 
		WS_OVERLAPPEDWINDOW, 		// Ñòèëü îêíà 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Ðàçìåðû îêíà 
		500, 				// width 
		500, 				// Height 
		HWND_DESKTOP, 				// Äåñêðèïòîð ðîäèòåëüñêîãî îêíà 
		NULL, 						// Íåò ìåíþ 
		This, 						// Äåñêðèïòîð ïðèëîæåíèÿ 
		NULL); 					// Äîïîëíèòåëüíîé èíôîðìàöèè íåò 

	ShowWindow(hWnd, mode); 				// Ïîêàçàòü îêíî
	SetTimer(hWnd, 1, USER_TIMER_MINIMUM, NULL);
	// Öèêë îáðàáîòêè ñîîáùåíèé 


	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Êíîïêà");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Êíîïêà");

	}

	SetMenu(hWnd, MainMenu);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Ôóíêöèÿ òðàíñëÿöèè êîäîâ íàæàòîé êëàâèøè 
		DispatchMessage(&msg); 		// Ïîñûëàåò ñîîáùåíèå ôóíêöèè WndProc() 
	}
	return 0;
}





int Calc(HDC dc, int W, int H, double Ph)
{
	double NUM = 0;

	HPEN hPen; //Îáúÿâëÿåòñÿ êèñòü


	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	//CreatePen(PS_SOLID, 1, RGB(0, 128, 256)); //Ñîçäà¸òñÿ îáúåêò
	SelectObject(dc, hPen);

	for (int x = -100; x < 100; x++)
	{
		NUM = 0;
		{
			NUM += -(4 * (sin(x) / cos(x)) + 5 * cos((5.4 / 2.3) * x));

			LineTo(dc, 10*x, 10*NUM+200);
		}
	}
    //#define DeletePen(hPen)
	//DeleteObject((HGDIOBJ)(HPEN)(hPen));

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//CreatePen(PS_SOLID, 1, RGB(0, 128, 256)); //Ñîçäà¸òñÿ îáúåêò
	SelectObject(dc, hPen);
	//Sleep(5000);
	for (int y = -100; y < 100; y++)
	{
		NUM = 0;
		{
			NUM += -(y+ (sin((5.4 / 2.3) * y)));

			LineTo(dc, 10*y, 10*NUM+470);
		}
	}

	return 0;
}

BOOL fin1 = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	int wmId, wmEvent;
	static bool Move = true;
	static int Phase = 0, Width, Height;
	HPEN hPen; //Îáúÿâëÿåòñÿ êèñòü


	switch (message)		 // Îáðàáîò÷èê ñîîáùåíèé
	{


	case WM_COMMAND:
		switch (wParam)
		{
		case 1001:
		{

			HDC dc = GetDC(hWnd);
			//HBRUSH hBrush;
			HPEN hPen;
			//hBrush = CreateSolidBrush(RGB(240, 240, 5));
			hPen = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
			MoveToEx(dc, 140, 150, NULL);
			SelectObject(dc, hPen);
			LineTo(dc, 333, 150);
			LineTo(dc, 333, 333);
			LineTo(dc, 140, 333);
			LineTo(dc, 140, 150);

			ReleaseDC(hWnd, dc);
			break;
		}
		break;
		}

	case WM_RBUTTONDOWN:
		Move = !Move;
		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_TIMER:
		if (Move)
			Phase++;
		else
			break;

	case WM_PAINT:
	{
		//PAINTSTRUCT ps;
		HDC dc = BeginPaint(hWnd, &ps);
		MoveToEx(dc, 230, 0, NULL);
		LineTo(dc, 230, 500);
		MoveToEx(dc, 0, 230, NULL);
		LineTo(dc, 500, 230);
		
		//hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		////CreatePen(PS_SOLID, 1, RGB(0, 128, 256)); //Ñîçäà¸òñÿ îáúåêò
		//SelectObject(dc, hPen); //Îáúåêò äåëàåòñÿ òåêóùèì
		Calc(dc, Width, Height, Phase);
		

		while (fin1==true)
		{

				//HDC dc = GetDC(hWnd);
				//HBRUSH hBrush;
				HPEN hPen;
				//hBrush = CreateSolidBrush(RGB(240, 240, 5));
				hPen = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
				MoveToEx(dc, 140, 150, NULL);
				SelectObject(dc, hPen);
				LineTo(dc, 333, 150);
				LineTo(dc, 333, 333);
				LineTo(dc, 140, 333);
				LineTo(dc, 140, 150);
				
				ReleaseDC(hWnd, dc);
			

		}


		//EndPaint(hWnd, &ps);

		break;
	}



	case WM_SIZE:
		Width = LOWORD(lParam), Height = HIWORD(lParam);
		break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break; 			// Çàâåðøåíèå ïðîãðàììû 
	default: 			// Îáðàáîòêà ñîîáùåíèÿ ïî óìîë÷àíèþ 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}
