// My_App.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "My_App.h"
#include"CShape.h"
#include <windowsx.h>
#include <vector>

using namespace std;

#define MAX_LOADSTRING 100
#define MAX_BUFF		255//1

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name





// ----------Phan khai bao-----------
HWND hOut;
HMENU hMenu;
Point p1, p2;
bool isDown = false;
ShapeMode currShapeMode = DRAWELLIPSE;
vector<CShape*> shapes;
CShape* currShape = NULL;
COLORREF currColor = RGB(219, 50, 54);
int currPenSize = 1;
int currPenStyle = PS_SOLID;
HPEN hPen = CreatePen(currPenStyle, currPenSize, currColor);
HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 255));
int windowWidth = 1080, windowHeight = 720;

//Khai bao ham
void AddMenus(HWND hWnd);
void WindowMode(HWND hWnd);
void initNewObject();
void WindowCheck(HWND hWnd);
void WindowRefresh(HWND hWnd);
int check(vector<CShape*> shapes);
void checkUndo(vector<CShape*> shapes);
void countShapes(vector<CShape*> shapes,int& COUNT_DRAWRECT,
										int& COUNT_DRAWELLIPSE,
										int& COUNT_DRAWCIRCLE,
										int& COUNT_DRAWSEMICIRCLE,
										int& COUNT_DRAWTRIANGLE,
										int& COUNT_DRAWSQUARE,
										int& COUNT_DRAWPOLYGON,
										int& COUNT_LINE);



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYAPP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT ptrPoly[20]; //Mảng chứa tạm thời các điểm của đa giác
	static int countPoly = 0;//Biến đếm các điểm của đa giác
	int wmId;
	PAINTSTRUCT ps;
	HDC hdc;
	
    switch (message)
    {
		
	case WM_CREATE:
	{
		SetWindowTextW(hWnd, TEXT("Application_OOP"));
		AddMenus(hWnd);
		WindowCheck(hWnd);
		WindowRefresh(hWnd);
		WindowMode(hWnd);
	}
	break;
	case WM_LBUTTONDOWN:
		
		if (!isDown && currShapeMode == DRAWPOLYGON)
		{
			p1 = newPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			if (countPoly > 0) {
				ptrPoly[countPoly].x = p1.getX();
				ptrPoly[countPoly].y = p1.getY();
				countPoly++;
				//Xử lý kết thúc vẽ đa giác: điểm đầu = điểm cuối
				if (abs(ptrPoly[countPoly - 1].x - ptrPoly[0].x) < 5 && abs(ptrPoly[countPoly - 1].y - ptrPoly[0].y) < 5)
				{
					for (int i = countPoly; i < 20; i++)
					{
						ptrPoly[i].x = ptrPoly[0].x;
						ptrPoly[i].y = ptrPoly[0].y;
					}

					//Đổi chế độ vẽ
					currShapeMode = MODE_WAITING;
					WindowMode(hWnd);

					//Vẽ chính thức
					//Thêm vào stack
					CPolygon* polygon = new CPolygon;
					polygon->SetData(ptrPoly,countPoly, currColor, currPenStyle, currPenSize);
					shapes.push_back(polygon);

					// Xóa bộ nhớ tạm
					for (int i = 0; i < countPoly; i++)
					{
						ptrPoly[i].x = 0;
						ptrPoly[i].y = 0;
					}
					countPoly = 0;
					//

					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
			}
			if (countPoly == 0) {
				initNewObject();
				ptrPoly[countPoly].x = p1.getX();
				ptrPoly[countPoly].y = p1.getY();
				countPoly++;
			}
			isDown = true;
		}else if(!isDown)
		{
			p1 = newPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			initNewObject();
			isDown = true;
		}
		break;
	case WM_LBUTTONUP:
	{
		isDown = false;
		p2 = newPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

			//Vẽ chính thức 
			switch (currShapeMode)
			{
			case LINE:
			{
				CLine* line = new CLine;
				line->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(line);
			}
			break;
			case DRAWRECT:
			{
				CRectangle* rect = new CRectangle;
				rect->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(rect);
			}
			break;
			case DRAWSQUARE:
			{
				CSquare* square = new CSquare;
				square->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(square);
			}
			break;
			case DRAWELLIPSE:
			{
				CEllipse* ellipse = new CEllipse;
				ellipse->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(ellipse);
			}
			break;
			case DRAWCIRCLE:
			{
				CCircle* circle = new CCircle;
				circle->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(circle);
			}
			break;
			case DRAWSEMICIRCLE:
			{
				CSemicircle* semicircle = new CSemicircle;
				semicircle->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(semicircle);
			}
			break;
			case DRAWTRIANGLE:
			{
				CTriangle* triangle = new CTriangle;
				triangle->SetData(p1.getX(), p1.getY(), p2.getX(), p2.getY(), currColor, currPenStyle, currPenSize);
				shapes.push_back(triangle);
			}
			break;
			case DRAWPOLYGON:
				//MessageBeep(MB_OK);
				if (countPoly ==1) {
					ptrPoly[countPoly].x = p2.getX();
					ptrPoly[countPoly].y = p2.getY();
					countPoly++;
				}
				break;
			case MODE_WAITING:
				break;
			case FILLELLIPSE:
				break;
			default:
				MessageBox(hWnd, L"Lỗi", L"Thông báo", MB_OK | MB_ICONERROR);
			}
		
		//InvalidateRect(hWnd, NULL, TRUE);
	}
	break;
	case WM_MOUSEMOVE:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);		
		if (isDown)
		{
			p2 = newPoint(x, y);
			InvalidateRect(hWnd, NULL, TRUE); //Invalidate lại window để khi chuyển qua sự kiện paint nó sẽ vẽ các nét vẽ tạm thời
		}
		if (currShapeMode == DRAWPOLYGON&&countPoly>1)
		{
			p2 = newPoint(x, y);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
    case WM_COMMAND:
        {
			
            int wmId = LOWORD(wParam);
			
            // Parse the menu selections:
            switch (wmId)
            {
			/*case ID_FILE_NEW:
				saveToBinaryFile(defaultFilePath);
				defaultFilePath = "data.bin";
				shapes.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				break;*/
			/*case ID_FILE_OPEN:
				openFileDialog();
				break;*/
			case CHECK_BUTTON:
				MessageBeep(MB_OK);
				WindowCheck(hWnd);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case REFRESH_BUTTON:
				MessageBeep(MB_OK);
				WindowRefresh(hWnd);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case EDIT_MENU_CLEAR:
				shapes.clear();
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case EDIT_MENU_UNDO:
				checkUndo(shapes);
				shapes.pop_back();
				check(shapes);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case DRAW_MENU_DUONG_THANG:
				currShapeMode = LINE;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_CHU_NHAT:
				currShapeMode = DRAWRECT;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_VUONG:
				currShapeMode = DRAWSQUARE;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_ELLIPSE:
				currShapeMode = DRAWELLIPSE;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_TRON:
				currShapeMode = DRAWCIRCLE;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_BAN_NGUYET:
				currShapeMode = DRAWSEMICIRCLE;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_TAM_GIAC:
				currShapeMode = DRAWTRIANGLE;
				WindowMode(hWnd);
				break;
			case DRAW_MENU_DA_GIAC:
				currShapeMode = DRAWPOLYGON;
				WindowMode(hWnd);
				break;
			case COLOR_MENU_RED:
				currColor = RGB(219, 50, 54);
				break;
			case COLOR_MENU_GREEN:
				currColor = RGB(60, 186, 84);
				break;
			case COLOR_MENU_BLUE:
				currColor = RGB(72, 133, 237);
				break;
			case COLOR_MENU_YELLOW:
				currColor = RGB(244, 194, 13);
				break;
			/*case ID_FILE_SAVE:
				saveToBinaryFile(defaultFilePath);
				break;
			case ID_FILE_SAVEAS:
				saveFileDialog();
				break;*/
			case STYLE_MENU_SOLID:
				currPenStyle = PS_SOLID;
				break;
			case STYLE_MENU_DASH:
				currPenStyle = PS_DASH;
				break;
			case STYLE_MENU_DOT:
				currPenStyle = PS_DOT;
				break;
			case STYLE_MENU_DASHDOT:
				currPenStyle = PS_DASHDOT;
				break;
            case HELP_MENU_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...\
			
			//Rectangle(hdc, 100, 100, 600, 400);
			
			//Vẽ lại các hình đã lưu
			for (int i = 0; i < shapes.size(); i++)
			{
				hPen = CreatePen(shapes[i]->getPenStyle(), shapes[i]->getPenSize(), shapes[i]->getColor());
				SelectObject(hdc, hPen);
				shapes[i]->Draw(hdc,hPen,hbr);
			}

			//Vẽ tạm thời hình đa giác khi chưa hoàn thành
			if (countPoly>1) {
				hPen = CreatePen(currPenStyle, currPenSize, currColor);
				SelectObject(hdc, hPen);
				MoveToEx(hdc, ptrPoly[0].x, ptrPoly[0].y, NULL);
				LineTo(hdc, ptrPoly[1].x, ptrPoly[1].y);
				for (int i = 2; i < countPoly; i++)
				{
					LineTo(hdc, ptrPoly[i].x, ptrPoly[i].y);
				}
				
			}
		
			//Vẽ các hình không phải đa giác
			if (isDown && currShapeMode!=DRAWPOLYGON&&currShapeMode!= MODE_WAITING)
			{
				//Vẽ nét vẽ tạm thời khi chưa Mouse Up
				hPen = CreatePen(currPenStyle, currPenSize, currColor);
				SelectObject(hdc, hPen);
				currShape->SetData(p1.getX(),p1.getY(),p2.getX(),p2.getY(), currColor, currPenStyle, currPenSize);
				currShape->Draw(hdc,hPen,hbr);
			}

			//Vẽ đa giác
			if (currShapeMode == DRAWPOLYGON)
			{
				//Vẽ nét vẽ tạm thời khi chưa Mouse Up : đường thẳng khi vẽ đa giác 
				hPen = CreatePen(currPenStyle, currPenSize, currColor);
				SelectObject(hdc, hPen);
				MoveToEx(hdc, ptrPoly[countPoly - 1].x, ptrPoly[countPoly - 1].y, NULL);
				LineTo(hdc, p2.getX(), p2.getY());
				if (countPoly == 1)
				{
					MoveToEx(hdc, p1.getX(), p1.getY(), NULL);
					LineTo(hdc, p2.getX(), p2.getY());
				}
				
			}
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void initNewObject()
{
	switch (currShapeMode)
	{
	case LINE:
		currShape = new CLine();
		break;
	case DRAWRECT:
		currShape = new CRectangle();
		break;
	case DRAWSQUARE:
		currShape = new CSquare();
		break;
	case DRAWELLIPSE:
		currShape = new CEllipse();
		break;
	case DRAWSEMICIRCLE:
		currShape = new CSemicircle();
		break;
	case DRAWCIRCLE:
		currShape = new CCircle();
		break;
	case DRAWTRIANGLE:
		currShape = new CTriangle();
		break;
	case FILLRECT:
		break;
	case FILLELLIPSE:
		break;
	default:
		break;
	}
}



void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hDrawMenu = CreateMenu();
	HMENU hEditMenu = CreateMenu();
	HMENU hColorMenu = CreateMenu();
	HMENU hStyleMenu = CreateMenu();
	HMENU hHelpMenu = CreateMenu();

	//Menu File
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, TEXT("Mới"));
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, TEXT("Thoát"));

	//Menu Ve
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_DUONG_THANG, TEXT("Đường thẳng"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_TRON, TEXT("Hình tròn"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_ELLIPSE, TEXT("Hình ellipse"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_BAN_NGUYET, TEXT("Hình bán nguyệt"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_DA_GIAC, TEXT("Hình đa giác"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_CHU_NHAT, TEXT("Hình chữ nhật"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_VUONG, TEXT("Hình vuông"));
	AppendMenu(hDrawMenu, MF_STRING, DRAW_MENU_TAM_GIAC, TEXT("Hình tam giác"));
	
	//Edit menu
	AppendMenu(hEditMenu, MF_STRING, EDIT_MENU_CLEAR, TEXT("Xóa màn hình"));
	AppendMenu(hEditMenu, MF_STRING, EDIT_MENU_UNDO, TEXT("Quay lại"));

	//Menu Color
	AppendMenu(hColorMenu, MF_STRING, COLOR_MENU_RED, TEXT("Màu đỏ"));
	AppendMenu(hColorMenu, MF_STRING, COLOR_MENU_GREEN, TEXT("Màu xanh lá"));
	AppendMenu(hColorMenu, MF_STRING, COLOR_MENU_BLUE, TEXT("Màu xanh dương"));
	AppendMenu(hColorMenu, MF_STRING, COLOR_MENU_YELLOW, TEXT("Màu vàng"));
	AppendMenu(hColorMenu, MF_STRING, DRAW_MENU_DA_GIAC, TEXT("Tùy chọn.."));

	//Menu Style
	AppendMenu(hStyleMenu, MF_STRING, STYLE_MENU_SOLID, TEXT("__________"));
	AppendMenu(hStyleMenu, MF_STRING, STYLE_MENU_DASH, TEXT("- - - - - - -"));
	AppendMenu(hStyleMenu, MF_STRING, STYLE_MENU_DOT, TEXT(". . . . . . . . ."));
	AppendMenu(hStyleMenu, MF_STRING, STYLE_MENU_DASHDOT, TEXT("- . - . - . -"));

	//Menu Help
	AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_ABOUT, TEXT("Thông tin"));

	//Thanh menu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, TEXT("Tệp"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hDrawMenu, TEXT("Vẽ"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, TEXT("Chỉnh sửa"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hColorMenu, TEXT("Màu"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hStyleMenu, TEXT("Nét vẽ"));
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, TEXT("Trợ giúp"));
	SetMenu(hWnd, hMenu);
}



void WindowCheck(HWND hWnd)
{
	//Gọi hàm kiểm tra
	
	int countShapes = check(shapes);

	//Xử lý in ra cửa sổ làm việc
	wchar_t count[10] = L""; //Tạo chuỗi
	wchar_t out[30] = L"Số hình cắt: "; //Tạo chuỗi
	swprintf_s(count, L"%i", countShapes); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(out, count); // Nối chuỗi "out" + "count" 

	//Tạo nút check 
	CreateWindow(L"Button", L" Kiểm tra ", WS_VISIBLE | WS_CHILD, 510, 5, 80, 20,hWnd, (HMENU)CHECK_BUTTON, NULL, NULL);
	//Tạo cửa sổ xuất hOut
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 5, 100, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, out);//Xuất ra cửa sổ hout
}


void WindowRefresh(HWND hWnd)
{
	//Tạo nút check 
	CreateWindow(L"Button", L"Tải lại", WS_VISIBLE | WS_CHILD, 90, 5, 60, 20, hWnd, (HMENU)REFRESH_BUTTON, NULL, NULL);
	CreateWindow(L"static", L"Bộ đếm:", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 5, 70, 20, hWnd, NULL, NULL, NULL);
	//Khai báo các biến điếm cho mỗi hình 
	int COUNT_DRAWRECT = 0;
	int COUNT_DRAWELLIPSE = 0;
	int COUNT_DRAWCIRCLE = 0;
	int COUNT_DRAWSEMICIRCLE = 0;
	int COUNT_DRAWTRIANGLE = 0;
	int COUNT_DRAWSQUARE = 0;
	int COUNT_DRAWPOLYGON = 0;
	int COUNT_LINE = 0;

	//Gọi hàm kiểm tra
	countShapes(shapes, COUNT_DRAWRECT, COUNT_DRAWELLIPSE, COUNT_DRAWCIRCLE, COUNT_DRAWSEMICIRCLE,
		COUNT_DRAWTRIANGLE, COUNT_DRAWSQUARE, COUNT_DRAWPOLYGON, COUNT_LINE);

	wchar_t countRect[10] = L""; //Tạo chuỗi
	wchar_t outRect[30] = L"Hình chữ nhật: "; //Tạo chuỗi
	swprintf_s(countRect, L"%i", COUNT_DRAWRECT); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outRect, countRect); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 30, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outRect);//Xuất ra cửa sổ hout

	////////////////////////////////////////////////////////////
	
	wchar_t countEllipse[10] = L""; //Tạo chuỗi
	wchar_t outEllipse[30] = L"Hình Ellipse: "; //Tạo chuỗi
	swprintf_s(countEllipse, L"%i", COUNT_DRAWELLIPSE); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outEllipse, countEllipse); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 55, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outEllipse);//Xuất ra cửa sổ hout
	///////////////////////////////////////////////////////////////
	
	wchar_t countCircle[10] = L""; //Tạo chuỗi
	wchar_t outCircle[30] = L"Hình tròn: "; //Tạo chuỗi
	swprintf_s(countCircle, L"%i", COUNT_DRAWCIRCLE); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outCircle, countCircle); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 80, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outCircle);//Xuất ra cửa sổ hout
	///////////////////////////////////////////////////////////////////

		
	wchar_t countSemicircle[10] = L""; //Tạo chuỗi
	wchar_t outSemicircle[30] = L"Hình bán nguyệt: "; //Tạo chuỗi
	swprintf_s(countSemicircle, L"%i", COUNT_DRAWSEMICIRCLE); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outSemicircle, countSemicircle); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 105, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outSemicircle);//Xuất ra cửa sổ hout
	//////////////////////////////////////////////////////////////////////

	wchar_t countTriangle[10] = L""; //Tạo chuỗi
	wchar_t outTriangle[30] = L"Hình tam giác: "; //Tạo chuỗi
	swprintf_s(countTriangle, L"%i", COUNT_DRAWTRIANGLE); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outTriangle, countTriangle); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 130, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outTriangle);//Xuất ra cửa sổ hout
	////////////////////////////////////////////////////////////////////////

	wchar_t countSquare[10] = L""; //Tạo chuỗi
	wchar_t outSquare[30] = L"Hình vuông: "; //Tạo chuỗi
	swprintf_s(countSquare, L"%i", COUNT_DRAWSQUARE); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outSquare, countSquare); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 155, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outSquare);//Xuất ra cửa sổ hout
	///////////////////////////////////////////////////////////////////////////
	
	wchar_t countPolygon[10] = L""; //Tạo chuỗi
	wchar_t outPolygon[30] = L"Hình đa giác: "; //Tạo chuỗi
	swprintf_s(countPolygon, L"%i", COUNT_DRAWPOLYGON); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outPolygon, countPolygon); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 180, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outPolygon);//Xuất ra cửa sổ hout
	////////////////////////////////////////////////////////////////////////////////
	wchar_t countLine[10] = L""; //Tạo chuỗi
	wchar_t outLine[30] = L"Đường thẳng: "; //Tạo chuỗi
	swprintf_s(countLine, L"%i", COUNT_LINE); //Gán dữ liệu số nguyên cho chuỗi
	wcscat_s(outLine, countLine); // Nối chuỗi "out" + "count" 
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		15, 205, 135, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, outLine);//Xuất ra cửa sổ hout

}
int check(vector<CShape*> shapes)
{
	int count = 0;     //Đếm số lượng các hình giao nhau với đường thẳng
	
	for (int i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->getType() == LINE)  //TÌm các đường thẳng trong Shapes
		{
			for (int j = 0; j < shapes.size(); j++) //Tìm các hình khác đường thẳng
			{
				switch (shapes[j]->getType())
				{
				case DRAWELLIPSE:
					/*if (checkEllipse(shapes[i]->getPointA(), shapes[i]->getPointB(), shapes[j]->getPointA(), shapes[j]->getPointB()) == 0)
					{
						shapes[j]->setColor(RGB(219, 50, 54));
						shapes[j]->setPenSize(1);
					}*/
					if (checkEllipse(shapes[i]->getPointA(), shapes[i]->getPointB(), shapes[j]->getPointA(), shapes[j]->getPointB()) == 1)
					{
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
				case DRAWCIRCLE:
					/*if (checkEllipse(shapes[i]->getPointA(), shapes[i]->getPointB(), shapes[j]->getPointA(), shapes[j]->getPointB()) == 0)
					{
						shapes[j]->setColor(RGB(219, 50, 54));
						shapes[j]->setPenSize(1);
					}*/
					if (checkEllipse(shapes[i]->getPointA(), shapes[i]->getPointB(), shapes[j]->getPointA(), shapes[j]->getPointB()) == 1)
					{
						
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
				case DRAWRECT:
					/*if (checkRect(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 0)
					{
						shapes[j]->setColor(RGB(219, 50, 54));
						shapes[j]->setPenSize(1);
					}*/
					if (checkRect(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 1)
					{
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
				case DRAWSQUARE:
					/*if (checkRect(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 0)
					{
						shapes[j]->setColor(RGB(219, 50, 54));
						shapes[j]->setPenSize(1);
					}*/
					if (checkRect(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 1)
					{
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
				case DRAWSEMICIRCLE:
					/*if(checkSemicircle(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 0)
					{
						shapes[j]->setColor(RGB(219, 50, 54));
						shapes[j]->setPenSize(1);
					}*/
					if (checkSemicircle(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 1)
					{
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
				case DRAWTRIANGLE:
					if (checkTriangle(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 1)
					{
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
				case DRAWPOLYGON:
					POINT ptr[20];
					shapes[j]->getPtr(ptr);
					if (checkMulti(ptr,shapes[j]->getCount(), shapes[i]->getPointA(), shapes[i]->getPointB()) == 1)
					{
						shapes[j]->setFlag(1);
						count++;
						shapes[i]->setFlag(1);
					}
					break;
						
				default:
					break;
				}
			}
			
			
			
		}
	}
	if(count==0)
		for (int i = 0; i < shapes.size(); i++)
		{
			
			shapes[i]->setFlag(0);
		}
	return count;
	
}


void countShapes(vector<CShape*> shapes,    int& COUNT_DRAWRECT,
											int& COUNT_DRAWELLIPSE,
											int& COUNT_DRAWCIRCLE,
											int& COUNT_DRAWSEMICIRCLE,
											int& COUNT_DRAWTRIANGLE,
											int& COUNT_DRAWSQUARE,
											int& COUNT_DRAWPOLYGON,
											int& COUNT_LINE)
{
	for (int i = 0; i < shapes.size(); i++) //Đếm số lượng từng hình 
	{
		switch (shapes[i]->getType())
		{
		case DRAWELLIPSE:
			COUNT_DRAWELLIPSE++;
			break;
		case DRAWCIRCLE:
			COUNT_DRAWCIRCLE++;
			break;
		case DRAWRECT:
			COUNT_DRAWRECT++;
			break;
		case DRAWSQUARE:
			COUNT_DRAWSQUARE++;
			break;
		case DRAWSEMICIRCLE:
			COUNT_DRAWSEMICIRCLE++;
			break;
		case DRAWTRIANGLE:
			COUNT_DRAWTRIANGLE++;
			break;
		case DRAWPOLYGON:
			COUNT_DRAWPOLYGON++;
			break;
		case LINE:
			COUNT_LINE++;
			break;
		default:
			break;
		}
	}
}


void WindowMode(HWND hWnd)
{
	//wchar_t mode[30] = L""; //Tạo chuỗi
	wchar_t out[60] = L"Chế độ vẽ: "; //Tạo chuỗi
	switch (currShapeMode)
	{
	case DRAWELLIPSE:
		wcscat_s(out, L"hình ellipse");
		break;
	case DRAWCIRCLE:
		wcscat_s(out, L"hình tròn");
		break;
	case DRAWRECT:
		wcscat_s(out, L"hình chữ nhật");
		break;
	case DRAWSQUARE:
		wcscat_s(out, L"hình vuông");
		break;
	case DRAWSEMICIRCLE:
		wcscat_s(out, L"hình bán nguyệt");
		break;
	case DRAWTRIANGLE:
		wcscat_s(out, L"hình tam giác ");
		break;
	case DRAWPOLYGON:
		wcscat_s(out, L"hình đa giác");
		break;
	case LINE:
		wcscat_s(out, L"đường thẳng");
		break;
	case MODE_WAITING:
		wcscat_s(out, L"Chờ...");
		break;
	default:
		break;
	}
	hOut = CreateWindow(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
		400, 26, 190, 20, hWnd, NULL, NULL, NULL);
	SetWindowText(hOut, out);//Xuất ra cửa sổ hout

}


/////////////////////////////////////////////////////////////////
void checkUndo(vector<CShape*> shapes)
{
	if (shapes[shapes.size() - 1]->getType() == LINE)
	{
		for (int j = 0; j < shapes.size(); j++) //Tìm các hình khác đường thẳng
		{
			switch (shapes[j]->getType())
			{
			case DRAWELLIPSE:
				if (checkEllipse(shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB(), shapes[j]->getPointA(), shapes[j]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
				}

				break;
			case DRAWCIRCLE:
				if (checkEllipse(shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB(), shapes[j]->getPointA(), shapes[j]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
					/*shapes[j]->setColor(RGB(219, 50, 54));
					shapes[j]->setPenSize(1);*/
				}

				break;
			case DRAWRECT:
				if (checkRect(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
				}

				break;
			case DRAWSQUARE:
				if (checkRect(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
				}

				break;
			case DRAWSEMICIRCLE:
				if (checkSemicircle(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
				}
				break;
			case DRAWTRIANGLE:
				if (checkTriangle(shapes[j]->getPointA(), shapes[j]->getPointB(), shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
				}
				break;
			case DRAWPOLYGON:
				POINT ptr[20];
				shapes[j]->getPtr(ptr);
				if (checkMulti(ptr, shapes[j]->getCount(), shapes[shapes.size() - 1]->getPointA(), shapes[shapes.size() - 1]->getPointB()) == 1)
				{
					shapes[j]->setFlag(0);
				}
				break;
			default:
				break;
			}
		}
	}
	
}