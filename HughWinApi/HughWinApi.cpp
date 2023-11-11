// HughWinApi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "HughWinApi.h"

using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HWND mainHwnd; // 김진형) 메인 윈도우

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HUGHWINAPI, szWindowClass, MAX_LOADSTRING);

    // 김진형) 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 김진형) LoadAccelerator는 윈도우에서 제공하는 단축키 모드다.
    // 김진형) 게임에선 메시지를 거치지 않고 실시간으로 바로 키 입력을 받을거기에 우선 패스
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HUGHWINAPI));

    MSG msg;

    // 김진형) Timer 설정을 통해 1초마다 업데이트
    // SetTimer(mainHwnd, 0, 1000, NULL);

    // 기본 메시지 루프입니다:
    // 김진형) GetMessage는 메시지큐에 있는걸 꺼내서 MSG 구조체에 넣는다.
    // 김진형) GetMessage는 메시지큐에서 메시지 확인 될 때까지 대기하는 큰 특징이 있다.
    // 김진형) msg.message == WM_QUIT 인 경우 false를 반환 -> 프로그램 종료
    // 김진형) 따라서 현재 구조는 메시지 반응형으로 게임에는 부적합

    //while (GetMessage(&msg, nullptr, 0, 0))

    // 김진형) PeekMessage는 메시지 유무와 상관없이 항상 반환하는데
    // 김진형) 메시지 큐에서 메시지를 확인한 경우 true, 메시지 큐에 메시지가 없는 경우 false 반환

    DWORD prevCnt = GetTickCount64();
    DWORD stkCnt = 0; //누적된 시간

    
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) // 메시지가 있는 경우 호출
        {
            int mssCnt = GetTickCount64(); //메시지 처리한 시간
            if (msg.message == WM_QUIT)
                break;

            // 김진형) msg.hwnd는 어떤 프로세스의 윈도우인지 핸들
            // 김진형) WndProc에서 메시지를 받아 처리한다. (여기서 커스텀 가능)
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            int difTime = GetTickCount64() - mssCnt;
            stkCnt += difTime;
        }
        else // 메시지가 없는 경우 호출
        {
            DWORD curCnt = GetTickCount64();
            if (1000 < prevCnt - curCnt) // 1초가 지난경우
            {
                float timeRatio = (float)stkCnt / 1000.0f; // 누적 시간대바 얼마나 흘렀는 지
                wchar_t szBuff[50] = {};
                swprintf_s(szBuff, L"비율 : %f", timeRatio);
                SetWindowText(mainHwnd, szBuff);

                prevCnt = curCnt;
            }
        }
    }
    

    //KillTimer(mainHwnd, 10);
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HUGHWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HUGHWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

      mainHwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!mainHwnd)
   {
      return FALSE;
   }

   ShowWindow(mainHwnd, nCmdShow);
   UpdateWindow(mainHwnd);

   return TRUE;
}


#include <vector>

// 김진형) 전역 변수
//int mouseX = 0, mouseY = 0; // 마우스 좌표

struct objInfo
{
    POINT objPos; // 오브젝트 위치
    POINT objScale; // 오브젝트 크기
};

POINT leftTop; // 좌상단 위치
POINT rightBtm; // 우하단 위치

vector<objInfo> objInfoVec; // objInfo 구조체 담을 vector

bool lBtnDown = false; // 마우스 좌클릭인지 아닌지

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
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
    case WM_PAINT: //김진형) 무효화 영역이 발샐한 경우 메시지 발생, 최근엔 창을 완전히 내리고 열어야 발생한다.
        {
            PAINTSTRUCT ps;

            // 김진형) Device Context를 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...            
            HPEN hMyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //김진형) 직접 팬을 만들어서 DC에 넣음
            HBRUSH hMyBrush = CreateSolidBrush(RGB(255, 255, 0)); // 김진형) 직접 브러쉬를 만들어 DC에 넣음

            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hMyPen); // 김진형) 기본 펜 ID 값을 받아옴
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hMyBrush); // 김진형) 기본 브러쉬 ID 값을 받아옴)

            //Rectangle(hdc, 10, 10, 100, 100); // 김진형) 변경된 펜으로 사각형을 그림

            // 마우스 좌클릭시 그려줌
            if (lBtnDown)
            {
                Rectangle(hdc, leftTop.x, leftTop.y, rightBtm.x, rightBtm.y);
            }

            for (size_t i = 0; i < objInfoVec.size(); i++)
            {
                Rectangle(hdc,
                    objInfoVec[i].objPos.x - objInfoVec[i].objScale.x / 2,
                    objInfoVec[i].objPos.y - objInfoVec[i].objScale.y / 2,
                    objInfoVec[i].objPos.x + objInfoVec[i].objScale.x / 2,
                    objInfoVec[i].objPos.y + objInfoVec[i].objScale.y / 2);
            }

            SelectObject(hdc, hDefaultPen); // 김진형) DC의 펜을 원래 펜으로 되돌림
            SelectObject(hdc, hDefaultBrush); // 김진형) DC의 브러쉬를 원래 브러쉬로 되돌림

            DeleteObject(hMyPen); // 김진형) 사용된 펜 삭제 요청
            DeleteObject(hDefaultBrush); // 김진형) 사용된 브러쉬 삭제 요청

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN: //김진형) 키 입력을 통해 움직여보자
        {
            switch (wParam)
            {
                case VK_UP:
                    //objPos.y -= 5;
                    InvalidateRect(hWnd, NULL, true);
                    break;
                case VK_DOWN:
                    //objPos.y += 5;
                    InvalidateRect(hWnd, NULL, true);
                    break;
                case VK_LEFT:
                    //objPos.x -= 5;
                    InvalidateRect(hWnd, NULL, true);
                    break;
                case VK_RIGHT:
                    //objPos.x += 5;
                    InvalidateRect(hWnd, NULL, true);
                    break;
            }
        }
        break;
    case WM_LBUTTONDOWN: //마우스 좌클릭 시
        {
            //mouseX = LOWORD(lParam);
            //mouseY = HIWORD(lParam);
            
            //좌클릭 시작점의 마우스 좌표를 받아온다.
            leftTop.x = LOWORD(lParam);
            leftTop.y = HIWORD(lParam);

            lBtnDown = true;
        }
        break;
    case WM_LBUTTONUP: //마우스 좌클릭 뗐을 때
        {
            //해당 위치에서 오브젝트 그리기
            objInfo info = { };
            info.objPos.x = (leftTop.x + rightBtm.x) / 2;
            info.objPos.y = (leftTop.y + rightBtm.y) / 2;

            info.objScale.x = abs(leftTop.x - rightBtm.x);
            info.objScale.y = abs(leftTop.y - rightBtm.y);

            objInfoVec.push_back(info);

            lBtnDown = false;
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    case WM_MOUSEMOVE: //마우스 이동시
        {
            //마우스 우 하단의 좌표를 받아온다.
            rightBtm.x = LOWORD(lParam);
            rightBtm.y = HIWORD(lParam);
            //InvalidateRect(hWnd, NULL, true); //무효화 영역 실행하여 그려줌을 갱신
        }
        break;
    case WM_TIMER:
        // SetTimer 함수의 마지막 인자는 여기서 처리된다.
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
