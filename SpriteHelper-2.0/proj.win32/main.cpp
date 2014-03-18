#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "CCDirector.h"

USING_NS_CC;

#if COCOS2D_DEBUG > 0
#define USE_WIN32_CONSOLE
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	int nRet = 0;

#ifdef USE_WIN32_CONSOLE
	AllocConsole();
	SetConsoleCP( CP_UTF8 );
	SetConsoleOutputCP( CP_UTF8 );
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif
    srand(time(0));
	::SetCurrentDirectory( _T(".\\Resources") );
	// create the application instance
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	if(eglView) {
		eglView->setViewName("SpriteHelper-2.0");
		eglView->setFrameSize(1024, 768);
		nRet = CCApplication::sharedApplication()->run();
	}
#ifdef USE_WIN32_CONSOLE
	FreeConsole();
#endif
	return nRet;
}
