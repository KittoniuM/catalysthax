#define WIN32_LEAN_AND_MEAN

#ifndef _MAIN_H
#define _MAIN_H

char *GetDirectoryFile(char *filename);
void __cdecl add_log (const char * fmt, ...);
void *DetourFunc(BYTE *src, const BYTE *dst, const int len);
bool RetourFunc(BYTE *src, BYTE *restore, const int len);
void *InterceptDllCall( HMODULE hModule, char *szDllName, char *szFunctionName, DWORD pNewFunction );
//bool WINAPI DllMain(HMODULE hDll, DWORD dwReason, PVOID pvReserved);
//bool WINAPI DllMain2(HMODULE hDll, DWORD dwReason, PVOID pvReserved);
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//void Init(void);
//void sectwo(void);
//void secone(void);

#endif