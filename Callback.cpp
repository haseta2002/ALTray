// Callback.cpp : �v���O�C�� ALTray �p �R�[���o�b�N�֐��C���v�������e�[�V�����t�@�C��
//
#include "ALTray.h"
#include "almapi.h"
#include "callback.h"

#include <crtdbg.h>

#define PROFILE_SECTION	"ALTray"
WNDPROC lpfnFolderProc = NULL;
WNDPROC lpfnOldFolderProc = NULL;
//////////////////////////////////////////////////////////////////////////////
// �K�{�̊֐�
// �ȉ��̂Q�̊֐��͕K���������A�G�N�X�|�[�g���Ă��������B

LPCTSTR WINAPI APCGetPlugName(void)
{
	// �����Ńv���O�C������Ԃ��Ă�������
	return "ALTray";
}

BOOL WINAPI APCStartUp(LPCTSTR version)
{
	// AL-Mail32 ���N�����鎞�ɁA��x�����Ă΂�܂�
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// ���

void WINAPI APCVersionInfo(HWND hWnd)
{
    // �����Ńo�[�W��������\�����Ă�������
    MessageBox(hWnd, "ALTray Version 0.1", "�v���O�C�����", MB_OK);
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
    // ���C����ʂ��쐬����ۂɌĂяo����܂�
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
    // ���C����ʂ�������ۂɌĂяo����܂�
	if (lpfnFolderProc) {
		FreeProcInstance(lpfnFolderProc);
		_RPT0(_CRT_WARN,"�T�u�N���X���I��\n");
	}
}

