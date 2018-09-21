/*
	Project : Direct3D StarterKit v3.0
	Author	: Matthew L (Azorbix)
	Date	: June 10th, 2005

	Credits :
		Tetsuo:			Help with hooking the device
		LanceVorgin:	His name is funny
		p47r!ck:		Hes German
		Hybrid:			Knows DirectX9
		Dom1n1k:		Helped with detourfunc
		Da_BuzZ:		Helped alot with d3d8
		Sparten:		Bugfix with GetDirect3D()

		Dockman:		A Game-Deception Head Honcho
		Absolution:		A Game-Deception Head Honcho
		UNI:			The Game-Deception Head Honcho Fries Supreme!
		Game-Deception
	
	Tools used:
		Microsoft Visual Studio .NET 2003
		DirectX9 SDK Update (summer 2004)

	Information:
		This StarterKit was developed for Game-Deception
		visit us at http://www.game-deception.com
*/



#pragma warning(disable:4311) // warning C4311: 'type cast' : pointer truncation from 'PIMAGE_DOS_HEADER' to 'DWORD'
#pragma warning(disable:4312) // warning C4312: 'type cast' : conversion from 'unsigned long' to 'PIMAGE_NT_HEADERS' of greater size



#include <windows.h>
#include <fstream>
#include <stdio.h>

#include "AmHttpSocket.h"


//#include "Common.h"
#include "main.h"
#include "d3d9.h"
#include "Hooks.h"
#include "d3d9dev.h"
#include "Input.h"
#include "CRC32.h"


using namespace std;
char *ss ;
char *ssb ;
bool author = false;

CAmHttpSocket https;
///////ddraw///////
BYTE dcbuff[4];
BYTE lbuff[4];
//DWORD ThreadID=NULL;
//DDSURFACEDESC2 SDes;
LPVOID ssData = 0;
bool fake = false;
///////ddraw///////


TCHAR szRoot1[4] = "C:\\";
void Init(void);
void sectwo(void);
DWORD ThreadID=NULL;
char hwval = 0;
HWND b;
HWND wto=0;
DWORD ftick=0;
DWORD ltick=0;
DWORD tick=0;

HMODULE dll;

COPYDATASTRUCT cpy;
COPYDATASTRUCT cp;
DWORD shw=0;
//Globals

ofstream ofile;	
char dlldir[320];
DWORD hws=0;
bool lopp = true;
bool auths = false;
bool dele = false;
//DWORD dllcrc = 0x7b052139; DWORD seccrc = 0x1cfbe152; DWORD initcrc = 0x20c0b3b5;

//extern IDirectDrawSurface4	*gDDrawSurf;
extern CDynamicCrc32		*pCrC;

extern char szBuffer[100];
extern char szBuffer2[100];
extern char szBuffer4[100];
extern char szBuffer3[100];
extern char szBuffer5[100];
extern char szBuffer6[100];

#define MakePtr( type, ptr, addValue )( type )( ( DWORD )( ptr ) + ( DWORD )( addValue ) )

void Inii(void)
{
	MessageBox(0, "HIT", "HIT", 0);
}
HMODULE hMod;
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

//	DWORD flags = 
//	static int cnt = 0;
	
	int i;
	switch(ul_reason_for_call)
	{
		
		case DLL_PROCESS_ATTACH:
			


			dll = hModule;
			
			hMod = LoadLibrary("d3d9.dll");	
			
			GetModuleFileName(hModule, dlldir, 512);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, 0, &ThreadID);
			for(i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break; } }

			ofile.open(GetDirectoryFile("hacklog.txt"), ios::app);

			Create();

			

		

			
			
			

			/*	
		if(!author) Sleep(500);
			if(!author) Sleep(500);
			if(!author) Sleep(500);
			if(!author) Sleep(500);
			if(!author) Sleep(500);
			if(!author) Sleep(500);
			//
if(author) MessageBox(0, "AUTHS SUCCESS!!!", "HIT", 0);
else  MessageBox(0, "AUTHS FAILURE!!!", "FUCT!!!", 0);			

			while(cnt < 200)
			{
				cnt++;
				if(author) goto don;
				Sleep(10);
			}
don:
		//	if(ss == 0) goto sccjmp;

			

		

			if(!strcmp(ssb, ss))
			{
			
			MessageBox(0, "Hooking d3d", "failed", 0);
		
			oDirect3DCreate9 = (tDirect3DCreate9)DetourFunc(
				(BYTE*)GetProcAddress(hMod, "Direct3DCreate9"),
				(BYTE*)hkDirect3DCreate9, 
				5);

			hMod = LoadLibrary("DINPUT8.DLL");	

			if(hMod == 0) hMod = GetModuleHandle("DINPUT8.DLL");

			pDirectInput8Create = (tDirectInput8Create)DetourFunc(
				(BYTE*)GetProcAddress(hMod, "DirectInput8Create"),
				(BYTE*)hkDirectInput8Create, 
				5);
			}

				DisableThreadLibraryCalls(hModule);




sccjmp:*/
			break;

		case DLL_PROCESS_DETACH:

			break;
	}
	return true;
}


void *InterceptDllCall( HMODULE hModule, char *szDllName, char *szFunctionName, DWORD pNewFunction )
{
	PIMAGE_DOS_HEADER pDosHeader;

	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
	PIMAGE_THUNK_DATA pThunk;

	DWORD dwOldProtect, dwOldProtect2;

	void *pOldFunction;

	if( !( pOldFunction = GetProcAddress( ( HMODULE )GetModuleHandle( szDllName ), szFunctionName ) ) )
		return( 0 );

	pDosHeader = ( PIMAGE_DOS_HEADER )hModule;

	if( pDosHeader->e_magic != IMAGE_DOS_SIGNATURE )
		return( NULL );

	IMAGE_OPTIONAL_HEADER * opthdr =(IMAGE_OPTIONAL_HEADER *) 
                     ((BYTE*)pDosHeader+pDosHeader->e_lfanew+24);

    IMAGE_IMPORT_DESCRIPTOR * descriptor=(IMAGE_IMPORT_DESCRIPTOR *)
     ((BYTE*)pDosHeader+ 
     opthdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	
	if(descriptor->FirstThunk == 0)
		return( NULL );

	pImportDesc = descriptor;

	while( pImportDesc->Name )
	{
		char *szModuleName = MakePtr( char *, pDosHeader,	pImportDesc->Name );


		if( !lstrcmpi( szModuleName, szDllName ) )
			break;

		pImportDesc++;
	}

	if( pImportDesc->Name == NULL )
		return( NULL );

	pThunk = MakePtr( PIMAGE_THUNK_DATA, pDosHeader,	pImportDesc->FirstThunk );

	while( pThunk->u1.Function )
	{
		if( pThunk->u1.Function == ( DWORD )pOldFunction )
		{
			VirtualProtect( ( void * )&pThunk->u1.Function, sizeof( DWORD ), PAGE_EXECUTE_READWRITE, &dwOldProtect );
			pThunk->u1.Function = ( DWORD )pNewFunction;
			VirtualProtect( ( void * )&pThunk->u1.Function, sizeof( DWORD ), dwOldProtect, &dwOldProtect2 );

			//AddLog("Hooked %s at %s Successfully!! old address: 0x%x new address: 0x%x", szDllName, szFunctionName, pOldFunction, pNewFunction);
			return( pOldFunction );
		}
		pThunk++;
	}
	return( NULL ); 
}


HMODULE ( WINAPI *pLoadLibrary ) ( IN LPCSTR lpLibFileName );
HMODULE WINAPI LoadLibrary_Hook( IN LPCSTR lpLibFileName )
{
	HMODULE hRet = pLoadLibrary( lpLibFileName );

//	if( strstr( lpLibFileName, "ddraw.dll" ) ){
//		GetProcAddress( hRet, "DirectDrawCreate" ) ;
//		__asm mov [ pDirectDrawCreate ], eax;
//	//	AddLog("Loaded");
	//	InterceptDllCall( hRet, "ddraw.dll", "DirectDrawCreate", ( DWORD )&DirectDrawCreate_Hook );
//	}
//	add_log("%s 0x%x", lpLibFileName, hRet);

	if( strstr( lpLibFileName, "RendDX9.dll" ) ) 
	{
		add_log("initDll Adr: 0x%x",GetProcAddress(GetModuleHandle("RendDX9.dll"), "initDll"));

			while(GetAsyncKeyState(VK_END) == 0)
		{
			Sleep(5);
		}
		
		/*pHookinitDLL = (HookinitDLL_t)DetourFunc(
			(BYTE*)GetProcAddress(GetModuleHandle("RendDX9.dll"), "initDll"),
			(BYTE*)HookinitDLL,	5);
		add_log("Rend intDll hooked: 0x%x 0x%x", HookinitDLL, pHookinitDLL);*/
	}



//	if( strstr( lpLibFileName, "pbcl.dll" ) ) {
//		InterceptDllCall( hRet, "ddraw.dll", "DirectDrawCreate", ( DWORD )&DirectDrawCreate_Hook );
//		__asm mov [ pDirectDrawCreate ], eax;
//		WriteProcessMemory(GetCurrentProcess(), (void*)LoadLibrary, &lbuff, 5, 0);
//	}

	return( hRet );
}






void sectwo(void)
{
//	if(pCrC->GetCrc32((const char *)&DllMain) == dllcrc)
//	{
		DWORD serialNumber, maxComponentLength, fsFlags;

	  TCHAR szFileSystem[12];
	  TCHAR szVolumeName[24];

  

	  //szRoot[0] = (TCHAR)(Drive & 0xFF);

		GetVolumeInformation(szRoot1, szVolumeName, sizeof(szVolumeName), &serialNumber, &maxComponentLength,
			 &fsFlags, szFileSystem, sizeof(szFileSystem));
		hws = serialNumber;

		strcpy(szBuffer5, szBuffer3);
		_itoa(serialNumber, szBuffer6, 16);
		strcat(szBuffer5, szBuffer6);

		ss = https.GetPage(szBuffer5);
		ssb = szBuffer6;
		if(!strcmp(ssb, ss))
		{
			author = true;
		//	MessageBox(0, "SUCCESSSFUL!!!!!!!!", "SUC!!", 0);
			
		}
		else
		{
			author = false;
		//	MessageBox(0, "WRONG!!!!!!!", "FUK!!", 0);

		}
		//MessageBox(0, "WRONG!!!!!!!", "FUK!!", 0);

//	}


}


//void Inii(void)
//{
//	MessageBox(0, "HIT", "HIT", 0);
//}




/*

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
   {
   case WM_COPYDATA:
	   CopyMemory((PVOID)&cpy,(CONST VOID *) lParam, 12);
	 //  MessageBox(0, "BF2 COPYDATA Hit!!!!!!!!!!!!!", "copydata", 0);
		
		switch (cpy.dwData)
		{
		case 3:
			if( cpy.cbData == hws)
			{
				ltick = GetTickCount();
				lopp = false;
				auths = true;
				cp.dwData = 6;
				cp.cbData = ltick;
				SendMessage(wto, WM_COPYDATA, 0, (DWORD) &cp);
			}
			else
			{
				dele = true;
				cp.dwData = 7;
				cp.cbData = (DWORD)dll;
				SendMessage(wto, WM_COPYDATA, 0, (DWORD) &cp);
			}
			break;
		}
		break;
	}
	return 0;
}*/




bool WINAPI /*DllMain*/asdasd(HMODULE hDll, DWORD dwReason, PVOID pvReserved)
{
	
	if(dwReason == DLL_PROCESS_ATTACH)
	{
	
		
	//	Inii();

//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Inii, NULL, 0, &ThreadID);
			if (!ThreadID)
			{
				//cpy.dwData = 0xFF;
				//cpy.cbData = 0;
				//SendMessage(FindWindow(NULL, "Receiver"), WM_COPYDATA, 0, (DWORD) &cpy); 
			//	MessageBox(0, "Thread Failed!", "failed", 0);
			}
		//	else MessageBox(0, "Thread PASSED!", "passed", 0);


	//	MessageBox(0, "Begining", "failed", 0);
		

			dll = hDll;

		GetModuleFileName(hDll, dlldir, 512);
		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break; } }
		
		
DisableThreadLibraryCalls(hDll);
		

		//if(pCrC->GetCrc32((const char *)&Init) == initcrc && pCrC->GetCrc32((const char *)&sectwo) == seccrc)
	//	{
		////////@@@@@@@@@@///////
		ofile.open(GetDirectoryFile("hacklog.txt"), ios::app);
		////////@@@@@@@@@@///////
		Create();
	//	add_log("CRC init: 0x%x", pCrC->GetCrc32((const char *)&Init)); //   <<<<-----------------

		
	//	MessageBox(0, "Begining5", "failed", 0);

		

		

		
	
		HMODULE hMod = LoadLibrary("d3d9.dll");	

Sleep(500);
	/*	static int cnt = 0;
		while(cnt < 200)
		{
			cnt++;
			if(ss) goto don;
			Sleep(10);
		}
don:*/


		//ss = https.GetPage("http://www.catalyst-hax.com/autologin.php");

	//	wto = FindWindow(NULL, "Injector Ready");
	//	if(wto == 0)
	//		dele = true;
		//DWORD serialNumber, maxComponentLength, fsFlags;

  //TCHAR szFileSystem[12];
  //TCHAR szVolumeName[24];
  

  //szRoot[0] = (TCHAR)(Drive & 0xFF);

  /*GetVolumeInformation(szRoot1, szVolumeName, sizeof(szVolumeName), &serialNumber, &maxComponentLength,
     &fsFlags,
     szFileSystem,
     sizeof(szFileSystem)
   );
  hws = serialNumber;*/

	//LONG wHook=SetWindowLong(b, GWL_WNDPROC,(DWORD) WndProc);
	//if (!wHook)
	//	return true;
		
	
		
	//	add_log("CheckSum: 0x%x", pCrC->GetCheckSum32((PBYTE)&Init, strlen((const char *)&Init))); 
	//	add_log("CheckSum100: 0x%x", pCrC->GetCheckSum32((PBYTE)&Init, 100)); 

		//add_log("Checksum: 0x%x", pCrC->GetCheckSum32((PBYTE)(dll+0x1000), 0x30000)); 
		/*ftick = GetTickCount();
	cpy.dwData = 2;
	cpy.cbData = (DWORD)&shw;
	

//	add_log("Serial Address: 0x%x", shw);

	SendMessage(wto, WM_COPYDATA, 0, (DWORD) &cpy);
	

	//add_log("Serial Address After: 0x%x real: 0x%x", shw, serialNumber);

	

/*MSG msg;
	while(lopp)
	{
		PeekMessage(&msg, b, 0, 0, PM_REMOVE);
		if(msg.message == WM_COPYDATA) MessageBox(0, "BF2 CopyMessage HIT!", "HiT", 0);
		
		/*thk = GetTickCount();
		if(thk ==0 || thk > 150)
		{
			WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x10000, 0);
			return false;
			lopp = false;
			
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		//}
	}*/
	/*DWORD ost = ltick - ftick;
	if(ost == 0 || ost > 150)
	{
		WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x10000, 0);
		return true;
	}

	*/
//Sleep(2000);


//SetWindowLong(b, GWL_WNDPROC,(DWORD) wHook);

	//	if(!strcmp("1.0", ss))
	//	{
		/******	if( shw == serialNumber)
				auths = true;
			else dele = true;***********/
		
			/*ltick = GetTickCount();
			ltick -= ftick;
			cpy.dwData = 6;
				cpy.cbData = GetTickCount();
				SendMessage(wto, WM_COPYDATA, 0, (DWORD) &cpy);

			if(ltick > 1050) dele = true;

			if(dele)
			{
				cpy.dwData = 7;
				cpy.cbData = (DWORD)dll;
				SendMessage(wto, WM_COPYDATA, 0, (DWORD) &cpy);
			}
			else
			{
				cpy.dwData = 6;
				cpy.cbData = GetTickCount();
				SendMessage(wto, WM_COPYDATA, 0, (DWORD) &cpy);
			}*/

				//WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x10000, 0);
				

		
		

		//add_log("\n---------------------\nTatniumD3D Started...\n---------------------");
		//if(!auths)
		//	goto secjmp;
		
	



	/*if(strcmp((const char *)&szBuffer6, ss))
	{
		dele = true;
		MessageBox(0, "FAILED", "failed", 0);
		goto secjmp; // WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x10000, 0);
	}
	else
	{*/
		

		if(!strcmp((const char *)&szBuffer6, ss))
		{

		MessageBox(0, "Hooking d3d", "yea bitch", 0);
		
	
		oDirect3DCreate9 = (tDirect3DCreate9)DetourFunc(
			(BYTE*)GetProcAddress(hMod, "Direct3DCreate9"),
			(BYTE*)hkDirect3DCreate9, 
			5);

		hMod = LoadLibrary("DINPUT8.DLL");	

		if(hMod == 0) hMod = GetModuleHandle("DINPUT8.DLL");

		pDirectInput8Create = (tDirectInput8Create)DetourFunc(
			(BYTE*)GetProcAddress(hMod, "DirectInput8Create"),
			(BYTE*)hkDirectInput8Create, 
			5);
		}


		/*

		
add_log("initDll Address: 0x%x", GetProcAddress(GetModuleHandle("RendDX9.dll"), "initDll"));
		

		pHookinitDLL = (HookinitDLL_t)DetourFunc(
			(BYTE*)GetProcAddress(GetModuleHandle("RendDX9.dll"), "initDll"),
			(BYTE*)HookinitDLL, 
			5);*/
		

	/*	pGetProcAddress = (tGetProcAddress)DetourFunc(
			(BYTE*)GetProcAddress(GetModuleHandle("Kernel32"), "GetProcAddress"),
			(BYTE*)hkGetProcAddress, 
			5);*/
	//	while(!GetAsyncKeyState(VK_END))

//	}	
//		else
//			MessageBox(0, "Hack out of date, Please update.", "Catalyst-Hax", 0);
	//	}
//secjmp:
		return true;


	}

	else if(dwReason == DLL_PROCESS_DETACH)
	{
	//	add_log("---------------------\nTatniumD3D Exiting...\n---------------------\n");
		if(ofile) { ofile.close(); }
	}

    return false;
}

void Init(void)
{
//	MessageBox(0, "INIT HIT", "thread success", 0);



	//if(pCrC->GetCrc32((const char *)&sectwo) ) ; 
	sectwo();

	if(!strcmp(ssb, ss))
	{
			
	//	MessageBox(0, "Hooking d3d", "failed", 0);
		
		oDirect3DCreate9 = (tDirect3DCreate9)DetourFunc(
			(BYTE*)GetProcAddress(hMod, "Direct3DCreate9"),
			(BYTE*)hkDirect3DCreate9, 
			5);

		hMod = LoadLibrary("DINPUT8.DLL");	

		if(hMod == 0) hMod = GetModuleHandle("DINPUT8.DLL");
		pDirectInput8Create = (tDirectInput8Create)DetourFunc(
			(BYTE*)GetProcAddress(hMod, "DirectInput8Create"),
			(BYTE*)hkDirectInput8Create, 
			5);

		
			

//		DetourFunction( ( PBYTE )LoadLibrary, ( PBYTE )&LoadLibrary_Hook );
//		__asm mov [ pLoadLibrary ], eax;
//
	//	pGetProcAddress = (tGetProcAddress)DetourFunc(
	//		(BYTE*)GetProcAddress(GetModuleHandle("Kernel32"), "GetProcAddress"),
	//		(BYTE*)hkGetProcAddress, 
	//		5);

		if(author)
		{
			
			while(GetModuleHandle("RendDX9.dll") == 0 )
			{
				//if(strcmp(ssb, ss) != 0) goto scjmp;
			//			WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x10000, 0);
				Sleep(10);
			}
			
			CClassManager ***pppClsm = (CClassManager***)0x971948;
			if(*pppClsm != 0) HookinitDLL(*pppClsm);
			else MessageBox(0, "Hook class by name failed!!", "Error", 0);


//			CClassManager ***pppClsm = (CClassManager***)0x967960;
//			if(*pppClsm != 0)
//				HookinitDLL(*pppClsm);
		}
	}



	
	//hwval = *ss;
//	MessageBox(0, "sectwo passed", "failed", 0);


	/*DWORD serialNumber, maxComponentLength, fsFlags;

  TCHAR szFileSystem[12];
  TCHAR szVolumeName[24];

  

  //szRoot[0] = (TCHAR)(Drive & 0xFF);

  GetVolumeInformation(szRoot1, szVolumeName, sizeof(szVolumeName), &serialNumber, &maxComponentLength,
     &fsFlags,
     szFileSystem,
     sizeof(szFileSystem)
   );
  hws = serialNumber;*/
	


//	add_log("Rend Address: 0x%x", GetModuleHandle("RendDX9.dll"));
//	while(GetModuleHandle("RendDX9.dll") == 0 )
//	{
		//if(strcmp(ssb, ss) != 0) goto scjmp;
	//			WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x10000, 0);
//		Sleep(10);
//	}
	/*CClassManager ****/
//	if(!auths)
//		goto scjmp;
//	add_log("initDll Address: 0x%x", GetProcAddress(GetModuleHandle("RendDX9.dll"), "initDll"));

	
//			pppClsm = (CClassManager***)0x967960;
//			if(*pppClsm != 0)
//				HookinitDLL(*pppClsm);
//scjmp:
	
//	Sleep(100);
//	if(/*strcmp((const char *)&szBuffer6, ss) ||//// dele) WriteProcessMemory(GetCurrentProcess(), dll, (void*)0x400000, 0x30000, 0);

	//return;
//	else
	//	add_log("fuckin shit didnt work!!");




	/*pHookinitDLL = (HookinitDLL_t)DetourFunc(
			(BYTE*)GetProcAddress(GetModuleHandle("RendDX9.dll"), "initDll"),
			(BYTE*)HookinitDLL, 
			5);
	pGetProcAddress = (tGetProcAddress)DetourFunc(
			(BYTE*)GetProcAddress(GetModuleHandle("Kernel32"), "GetProcAddress"),
			(BYTE*)hkGetProcAddress, 
			5);*/

}


char *GetDirectoryFile(char *filename)
{
	static char path[320];
	strcpy(path, dlldir);
	strcat(path, filename);
	return path;
}

void *DetourFunc(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len+5);
	DWORD dwback;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwback);

	memcpy(jmp, src, len);	jmp += len;
	
	jmp[0] = 0xE9;
	*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

	VirtualProtect(src, len, dwback, &dwback);

	return (jmp-len);
}

bool RetourFunc(BYTE *src, BYTE *restore, const int len)
{
	DWORD dwback;
		
	if(!VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwback))	{ return false; }
	if(!memcpy(src, restore, len))							{ return false; }

	restore[0] = 0xE9;
	*(DWORD*)(restore+1) = (DWORD)(src - restore) - 5;

	if(!VirtualProtect(src, len, dwback, &dwback))			{ return false; }
	
	return true;
}	

void secone(void)
{
	DWORD serialNumber, maxComponentLength, fsFlags;

  TCHAR szFileSystem[12];
  TCHAR szVolumeName[24];
  

  //szRoot[0] = (TCHAR)(Drive & 0xFF);

  GetVolumeInformation(szRoot1, szVolumeName, sizeof(szVolumeName), &serialNumber, &maxComponentLength,
     &fsFlags,
     szFileSystem,
     sizeof(szFileSystem)
   );
  hws = serialNumber;
}

void __cdecl add_log (const char *fmt, ...)
{
	if(ofile != NULL)
	{
		if(!fmt) { return; }

		va_list va_alist;
		char logbuf[256] = {0};

		va_start (va_alist, fmt);
		_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
		va_end (va_alist);

		ofile << logbuf << endl;
	}
}
/*
bool WINAPI DllMainasd(HMODULE hDll, DWORD dwReason, PVOID pvReserved)
{
	
	if(dwReason == DLL_PROCESS_ATTACH)
	{
			dll = hDll;

		GetModuleFileName(hDll, dlldir, 512);
		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break; } }
		
		ofile.open(GetDirectoryFile("hacklog.txt"), ios::app);

		Create();

		add_log("CRC DllMain: 0x%x", pCrC->GetCrc32((const char *)DllMain2));

		add_log("CRC Init: 0x%x", pCrC->GetCrc32((const char *)Init));

		add_log("CRC SecTwo: 0x%x", pCrC->GetCrc32((const char *)sectwo));

		return true;
	}
	else if(dwReason == DLL_PROCESS_DETACH)
	{
		if(ofile) { ofile.close(); }
	}

    return false;
}
*/
