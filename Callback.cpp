// Callback.cpp : プラグイン ALTray 用 コールバック関数インプリメンテーションファイル
//
#include "ALTray.h"
#include "almapi.h"
#include "callback.h"

#include <crtdbg.h>

#define PROFILE_SECTION	"ALTray"
WNDPROC lpfnFolderProc = NULL;
WNDPROC lpfnOldFolderProc = NULL;
//////////////////////////////////////////////////////////////////////////////
// 必須の関数
// 以下の２つの関数は必ず実装し、エクスポートしてください。

LPCTSTR WINAPI APCGetPlugName(void)
{
	// ここでプラグイン名を返してください
	return "ALTray";
}

BOOL WINAPI APCStartUp(LPCTSTR version)
{
	// AL-Mail32 が起動する時に、一度だけ呼ばれます
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// 情報

void WINAPI APCVersionInfo(HWND hWnd)
{
    // ここでバージョン情報を表示してください
    MessageBox(hWnd, "ALTray Version 0.1", "プラグイン情報", MB_OK);
}

LRESULT APIENTRY FolderProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE || wParam == SC_MINIMIZE) {
			PostMessage(hwnd, WM_COMMAND, 32828, NULL);
			return 1;
		}
	}
	return CallWindowProc((WNDPROC)lpfnOldFolderProc, hwnd, message, wParam, lParam);
}

void WINAPI APCFolderCreate(HWND hWnd)
{
    // メイン画面が作成する際に呼び出されます
	if (lpfnFolderProc) {
		return;
	}
	lpfnFolderProc = MakeProcInstance((WNDPROC)FolderProc, g_hInstance);
	if (lpfnFolderProc) {
		lpfnOldFolderProc = (WNDPROC)SetWindowLong(hWnd, GWL_WNDPROC,
												(LONG)(WNDPROC)lpfnFolderProc);
		_RPT0(_CRT_WARN,"サブクラス化\n");
	}
}

void WINAPI APCFolderClose(HWND hWnd)
{
    // メイン画面が閉じられる際に呼び出されます
	if (lpfnFolderProc) {
		FreeProcInstance(lpfnFolderProc);
		_RPT0(_CRT_WARN,"サブクラス化終了\n");
	}
}

