#include "Alplug.h"
#include "Alapi.h"
#include "Resource.h"

//#include <stdio.h>
//#include <windowsx.h>
//#include <richedit.h>
#include <crtdbg.h>

#define PROFILE_SECTION	"ALTray"
WNDPROC lpfnFolderProc = NULL;
WNDPROC lpfnOldFolderProc = NULL;
BOOL bMin;
BOOL bClose;

BOOL CALLBACK DialogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

//////////////////////////////////////////////////////////////////////////////
// 必須の関数

LPCTSTR WINAPI APCGetPlugName(void)
{
	// プラグイン名を返してください
	return "ALTray";
}

void WINAPI APCVersionInfo(HWND hWnd)
{
	// バージョン情報を表示してください
	//MessageBox(hWnd, "ALTray Version 0.2",
	//	"プラグイン情報", MB_OK);
	DialogBox(g_hInstance,
			MAKEINTRESOURCE(IDD_DIALOG_ABOUT), hWnd, (DLGPROC)AboutProc);
}

BOOL WINAPI APCStartUp(LPCTSTR version)
{
	// AL-Mail32 が起動する時に、一度だけ呼ばれます
	char profile[_MAX_PATH];

	// ALTrayの設定を読み込む
	lstrcpy(profile, APAGetMailbox());
	lstrcat(profile, "ALTray.ini");
	bMin = GetPrivateProfileInt("Tray", "Min",
										TRUE, profile);
	bClose = GetPrivateProfileInt("Tray", "Close",
										TRUE, profile);

	return TRUE;
}

// ※上記２つの関数は必ず実装し、エクスポートしてください。
//	 それ以外の関数は必要なものだけ実装し、不用のものはソースから削除してくだ
//	 さい。

//////////////////////////////////////////////////////////////////////////////
// 設定
void WINAPI APCSetup(HWND hWnd)
{
    // 必要な場合は、ここでプラグインのオプション設定画面を開いてください
	DialogBox(g_hInstance,
			MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc);
}

LRESULT APIENTRY FolderProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_SYSCOMMAND:
		if ((wParam == SC_CLOSE && bClose) || (wParam == SC_MINIMIZE && bMin)) {
			PostMessage(hwnd, WM_COMMAND, 32828, NULL);
			return 1;
		}
		break;
	case WM_COMMAND:
		if (wParam == 32828) {
			PlaySound("Minimize", NULL, SND_ALIAS | SND_ASYNC | SND_NODEFAULT | SND_NOSTOP);	// winmm.lib needed
		}
		break;
	case WM_SHOWWINDOW:
		if ((BOOL)wParam) {
			PlaySound("RestoreUp", NULL, SND_ALIAS | SND_ASYNC | SND_NODEFAULT | SND_NOSTOP);	// winmm.lib needed
		}
	}
	return CallWindowProc((WNDPROC)lpfnOldFolderProc, hwnd, message, wParam, lParam);
}

void WINAPI APCFolderCreate(HWND hWnd)
{
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
	if (lpfnFolderProc) {
		FreeProcInstance(lpfnFolderProc);
		_RPT0(_CRT_WARN,"サブクラス化終了\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// ダイアログ
BOOL CALLBACK DialogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg){
		case WM_COMMAND:
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL){
				if(LOWORD(wParam) == IDOK){
					bMin =
						SendDlgItemMessage(hwnd, IDC_CHECK_MIN, BM_GETCHECK, 0, 0) == BST_CHECKED?1: 0;
					bClose =
						SendDlgItemMessage(hwnd, IDC_CHECK_CLOSE, BM_GETCHECK, 0, 0) == BST_CHECKED?1: 0;


					char profile[_MAX_PATH];
					lstrcpy(profile, APAGetMailbox());
					lstrcat(profile, "ALTray.ini");

					LPCTSTR num[] = {"0", "1"};

					WritePrivateProfileString
						("Tray", "Min", num[bMin], profile);
					WritePrivateProfileString
						("Tray", "Close", num[bClose], profile);
				}
				EndDialog(hwnd, IDOK);
				return TRUE;
			}
			break;
		case WM_INITDIALOG:
/*			HWND hParent = GetParent(hwnd);
			if(hParent != NULL){ // 親ウインドウの中央に移動
				RECT rect, parentRect;
				GetWindowRect(hwnd, &rect);
				GetWindowRect(hParent, &parentRect);

				int w = rect.right - rect.left;
				int h = rect.bottom - rect.top;
				int ParentW = parentRect.right - parentRect.left;
				int ParentH = parentRect.bottom - parentRect.top;
				int x = (parentRect.left + (ParentW - w)/2 + 4) & ~7;
				int y = parentRect.top + (ParentH - h) / 2;
				MoveWindow(hwnd, x, y, w, h, TRUE);
				ShowWindow(hwnd, SW_RESTORE);
			}
*/
			if(bMin)
				SendDlgItemMessage(hwnd, IDC_CHECK_MIN, BM_SETCHECK, TRUE, 0);
			if(bClose)
				SendDlgItemMessage(hwnd, IDC_CHECK_CLOSE, BM_SETCHECK, TRUE, 0);
			return TRUE;

	}
	return FALSE;
}

BOOL CALLBACK AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg){
		case WM_COMMAND:
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL){
				EndDialog(hwnd, IDOK);
				return TRUE;
			}
			break;
	}
	return FALSE;
}
