// AL-Mail32 API Version 1.10

#if !defined(_ALAPI_H_ALTRAY__INCLUDED_)
#define _ALAPI_H_ALTRAY__INCLUDED_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

extern UINT (WINAPI *APARegistCallback)(void (WINAPI *)(HWND, DWORD), DWORD);
extern UINT (WINAPI *APASetTimer)(UINT, BOOL (WINAPI *)(UINT, DWORD), DWORD);
extern BOOL (WINAPI *APAKillTimer)(UINT);
extern BOOL (WINAPI *APAIsBusy)(void);
extern LPCTSTR (WINAPI *APAGetMailbox)(void);
extern LPCTSTR (WINAPI *APAGetAccount)(HWND);
extern LPCTSTR (WINAPI *APAGetFolderName)(LPCTSTR);
extern BOOL (WINAPI *APAImportFile)(LPCTSTR, LPCTSTR, DWORD);
extern BOOL (WINAPI *APASaveMail)(LPCTSTR, LPCTSTR, BOOL, BOOL);
extern BOOL (WINAPI *APAMoveMail)(LPCTSTR, LPCTSTR);
extern BOOL (WINAPI *APAMarkMail)(LPCTSTR, UINT, UINT);
extern BOOL (WINAPI *APADeleteMail)(LPCTSTR);
extern LPCTSTR (WINAPI *APAFolderGetCurrentFolder)(HWND);
extern LPCTSTR (WINAPI *APAFolderGetCurrentEntry)(HWND);
extern LPCTSTR (WINAPI *APAFolderGetSelectEntry)(HWND, BOOL);
extern BOOL (WINAPI *APAFolderChangePassword)(HWND, LPCTSTR);
extern BOOL (WINAPI *APAFolderMailTo)(HWND, LPCTSTR);
extern BOOL (WINAPI *APAFolderReply)(HWND, LPCTSTR);
extern BOOL (WINAPI *APAFolderForward)(HWND, LPCTSTR);
extern BOOL (WINAPI *APAFolderOpenMail)(HWND, LPCTSTR, BOOL);
extern LPCTSTR (WINAPI *APASendGetText)(HWND, BOOL);
extern LPCTSTR (WINAPI *APASendGetHeader)(HWND);
extern BOOL (WINAPI *APASendSetText)(HWND, LPCTSTR);
extern BOOL (WINAPI *APASendSetHeader)(HWND, LPCTSTR);
extern HWND (WINAPI *APASendGetEditor)(HWND);
extern LPCTSTR (WINAPI *APAViewGetText)(HWND);
extern LPCTSTR (WINAPI *APAViewGetHeader)(HWND);
extern BOOL (WINAPI *APAViewSetText)(HWND, LPCTSTR);
extern LPCTSTR (WINAPI *APAViewGetPath)(HWND);
extern HWND (WINAPI *APAViewGetEditor)(HWND);
extern BOOL (WINAPI *APAViewChangeMail)(HWND, LPCTSTR);
extern int (WINAPI *APASjisToJis)(LPTSTR, LPCTSTR, int);
extern int (WINAPI *APAJisToSjis)(LPTSTR, LPCTSTR, int);

#ifdef __cplusplus
}  // end extern "C"
#endif

#endif	// _ALAPI_H_ALTRAY__INCLUDED_
