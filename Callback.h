// Callback.h : プラグイン ALTray 用 コールバック関数ヘッダーファイル

#if !defined(ALM__CALLBACK_H_ALTRAY__INCLUDED_)
#define ALM__CALLBACK_H_ALTRAY__INCLUDED_

#include <windows.h>

#define APMENU_FOLDER_SYSTEM	100
#define APMENU_FOLDER_FRAME		101
#define APMENU_FOLDER_CONTEXT	102
#define APMENU_FOLDER_TREE		103

#define APMENU_VIEW_SYSTEM		200
#define APMENU_VIEW_FRAME		201
#define APMENU_VIEW_CONTEXT		202
#define APMENU_VIEW_URL			203

#define APMENU_SEND_SYSTEM		300
#define APMENU_SEND_FRAME		301
#define APMENU_SEND_CONTEXT		302
#define APMENU_SEND_ADDRESS		303

#define APFILTER_NONE			0
#define APFILTER_SERVER_DELETE	1
#define APFILTER_SERVER_SAVE	2
#define APFILTER_FILE_DELETE	4

#ifdef __cplusplus
extern "C" {
#endif

LPCTSTR WINAPI APCGetPlugName(void);
void WINAPI APCVersionInfo(HWND);
void WINAPI APCSetup(HWND);
BOOL WINAPI APCStartUp(LPCTSTR);
void WINAPI APCCleanUp(void);
int WINAPI APCRecFilter(LPCTSTR);

// メイン画面
void WINAPI APCFolderCreate(HWND);
void WINAPI APCFolderClose(HWND);
void WINAPI APCFolderInitMenu(HWND, HMENU, UINT);
void WINAPI APCFolderLoad(HWND, LPCTSTR);
void WINAPI APCFolderEndRetrieve(HWND);
BOOL WINAPI APCFolderPreOpenView(HWND, LPCTSTR);

// メールVIEW画面
void WINAPI APCViewCreate(HWND);
void WINAPI APCViewClose(HWND);
void WINAPI APCViewInitMenu(HWND, HMENU, UINT);
void WINAPI APCViewLoadMail(HWND, LPCTSTR, LPCTSTR);

// 送信画面
void WINAPI APCSendCreate(HWND);
void WINAPI APCSendClose(HWND);
void WINAPI APCSendInitMenu(HWND, HMENU, UINT);
BOOL WINAPI APCSendPost(HWND, LPCTSTR);

#ifdef __cplusplus
}  // end extern "C"
#endif

#endif	// ALM__CALLBACK_H_ALTRAY__INCLUDED_
