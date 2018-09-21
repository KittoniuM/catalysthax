/*

This program is copyright 2003 by evilbert.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include <windows.h>

#define INITGUID

#include "NewIDirectInput8.h"


//extern CGameInfo GameInfo;
extern IDirectInput8 *pDInput8;						//Original Device pointer
extern NewIDirectInput8 *pMyDInput8;				//Wrapped Device pointer


HRESULT __stdcall NewIDirectInput8::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
//	add_log("DirectInput8Create Success!!!!!");
	//Create DirectInput Device
	NewIDirectInputDevice8 *pMyDInputDevice8 = new NewIDirectInputDevice8;
	if (rguid == GUID_SysMouse)
		pMyDInputDevice8->m_bIsMouse = true;
	else
		pMyDInputDevice8->m_bIsMouse = false;
	HRESULT Result = pDInput8->CreateDevice(rguid, (LPDIRECTINPUTDEVICE8*)&pMyDInputDevice8->pDInputDevice8, pUnkOuter);
	*lplpDirectInputDevice = (LPDIRECTINPUTDEVICE8)pMyDInputDevice8;

	return Result;
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************

HRESULT __stdcall NewIDirectInput8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pDInput8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall NewIDirectInput8::AddRef(void)
{
	return pDInput8->AddRef();
}

ULONG __stdcall NewIDirectInput8::Release(void)
{
	return pDInput8->Release();
}

HRESULT __stdcall NewIDirectInput8::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, 
													 LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return pDInput8->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}

HRESULT __stdcall NewIDirectInput8::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return pDInput8->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT __stdcall NewIDirectInput8::EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, 
														   LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return pDInput8->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT __stdcall NewIDirectInput8::FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance)
{
	return pDInput8->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT __stdcall NewIDirectInput8::GetDeviceStatus(REFGUID rguidInstance)
{
	return pDInput8->GetDeviceStatus(rguidInstance);
}

HRESULT __stdcall NewIDirectInput8::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return pDInput8->Initialize(hinst, dwVersion);
}

HRESULT __stdcall NewIDirectInput8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return pDInput8->RunControlPanel(hwndOwner, dwFlags);
}
