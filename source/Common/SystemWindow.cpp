#include "SystemWindow.h"
#include "PAssert.h"

#if defined WINDOWS
SystemWindow::SystemWindow(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) : mInstance(instance),
mWindowClass(windowClass), mWindowTitle(windowTitle), mShowCommand(showCommand), mWindowHandle(NULL)
{
	mScreenWidth = SCREEN_WIDTH;
	mScreeHeight = SCREEN_HEIGHT;
	mIsFullScreen = FULL_SCREEN;
}

POINT SystemWindow::CenterWindow(unsigned int windowWidth, unsigned int windowHeight)
{
	POINT center;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

#pragma warning(disable:4127)
	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// chenge the display to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		center.x = center.y = 0;
		mIsFullScreen = true;
	}
	else
	{
		center.x = (screenWidth - windowWidth) / 2;
		center.y = (screenHeight - windowHeight) / 2;
	}
#pragma warning(default:4127)

	return center;
}

const HWND SystemWindow::GetWindowHandle() const
{
	ASSERT(mWindowHandle != NULL, "Something went wrong the Window handle was null.");
	return mWindowHandle;
}

const HINSTANCE SystemWindow::GetInstance() const
{
	return mInstance;
}

LRESULT WINAPI SystemWindow::WndProc(HWND windowHandle, unsigned int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(windowHandle, message, wParam, lParam);
}
#endif

SystemWindow::~SystemWindow()
{
	Shutdown();
}

void SystemWindow::Initialize()
{
#if defined WINDOWS
	ZeroMemory(&mWindow, sizeof(mWindow));
	mWindow.cbSize = sizeof(WNDCLASSEX);
	mWindow.style = CS_CLASSDC;
	mWindow.lpfnWndProc = WndProc;
	mWindow.hInstance = mInstance;
	mWindow.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	mWindow.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	mWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
	mWindow.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
	mWindow.lpszClassName = (LPCSTR)mWindowClass.c_str();

	RECT windowRectangle = { 0, 0, mScreenWidth, mScreeHeight };
	AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

	RegisterClassEx(&mWindow);
	POINT center = CenterWindow(mScreenWidth, mScreeHeight);
	mWindowHandle = CreateWindow((LPCSTR)mWindowClass.c_str(), (LPCSTR)mWindowTitle.c_str(), WS_OVERLAPPEDWINDOW, center.x, center.y, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, nullptr, nullptr, mInstance, nullptr);

	ShowWindow(mWindowHandle, mShowCommand);
	UpdateWindow(mWindowHandle);
#endif
}

void SystemWindow::Shutdown()
{
#if defined WINDOWS
	// Remove the window
	DestroyWindow(mWindowHandle);
	mWindowHandle = nullptr;

	// Remove the application instance
	UnregisterClass((LPCSTR)mWindowClass.c_str(), mInstance);
#endif
}

const unsigned int SystemWindow::ScreenWidth() const
{
	return mScreenWidth;
}

const unsigned int SystemWindow::ScreenHeight() const
{
	return mScreeHeight;
}

const bool SystemWindow::IsFullScreen() const
{
	return mIsFullScreen;
}