#include <windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND hPlusButton;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    const char CLASS_NAME[] = "Calculator Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);


    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Calculator",
        WS_OVERLAPPEDWINDOW,


        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,

        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);


    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
          case WM_CREATE:
        // Create a button with a plus sign
        hPlusButton = CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "+",       // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            10,        // x position
            10,        // y position
            50,        // Button width
            50,        // Button height
            hwnd,      // Parent window
            (HMENU) 1, // Control ID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);     // Pointer not needed

        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1)
        {
            // Handle the button click
            MessageBox(hwnd, "Plus button clicked!", "Info", MB_OK);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(hwnd, &ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
