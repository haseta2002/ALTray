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
// �K�{�̊֐�

LPCTSTR WINAPI APCGetPlugName(void)
{
	// �v���O�C������Ԃ��Ă�������
	return "ALTray";
}

void WINAPI APCVersionInfo(HWND hWnd)
{
	// �o�[�W��������\�����Ă�������
	//MessageBox(hWnd, "ALTray Version 0.2",
	//	"�v���O�C�����", MB_OK);
	DialogBox(g_hInstance,
			MAKEINTRESOURCE(IDD_DIALOG_ABOUT), hWnd, (DLGPROC)AboutProc);
}

BOOL WINAPI APCStartUp(LPCTSTR version)
{
	// AL-Mail32 ���N�����鎞�ɁA��x�����Ă΂�܂�
	char profile[_MAX_PATH];

	// ALTray�̐ݒ��ǂݍ���
	lstrcpy(profile, APAGetMailbox());
	lstrcat(profile, "ALTray.ini");
	bMin = GetPrivateProfileInt("Tray", "Min",
										TRUE, profile);
	bClose = GetPrivateProfileInt("Tray", "Close",
										TRUE, profile);

	return TRUE;
}

// ����L�Q�̊֐��͕K���������A�G�N�X�|�[�g���Ă��������B
//	 ����ȊO�̊֐��͕K�v�Ȃ��̂����������A�s�p�̂��̂̓\�[�X����폜���Ă���
//	 �����B

//////////////////////////////////////////////////////////////////////////////
// �ݒ�
void WINAPI APCSetup(HWND hWnd)
{
    // �K�v�ȏꍇ�́A�����Ńv���O�C���̃I�v�V�����ݒ��ʂ��J���Ă�������
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
		_RPT0(_CRT_WARN,"�T�u�N���X��\n");
	}
}

void WINAPI APCFolderClose(HWND hWnd)
{
	if (lpfnFolderProc) {
		FreeProcInstance(lpfnFolderProc);
		_RPT0(_CRT_WARN,"�T�u�N���X���I��\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// �_�C�A���O
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
			if(hParent != NULL){ // �e�E�C���h�E�̒����Ɉړ�
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
