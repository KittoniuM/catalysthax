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

#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
//#include <dinputd.h>
#include "NewIDirectInputDevice8.h"

interface NewIDirectInput8 : public IDirectInput8
{
public:
	NewIDirectInputDevice8 MyDInputDevice8;
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMS lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
	HRESULT __stdcall CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lpDirectInputDevice, LPUNKNOWN pUnkOuter);
	HRESULT __stdcall EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT __stdcall EnumDevicesBySemantics(LPCTSTR ptszUserName, LPDIACTIONFORMAT lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCB lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT __stdcall FindDevice(REFGUID rguidClass, LPCTSTR ptszName, LPGUID pguidInstance);
	HRESULT __stdcall GetDeviceStatus(REFGUID rguidInstance);
	HRESULT __stdcall Initialize(HINSTANCE hinst, DWORD dwVersion);
	HRESULT __stdcall RunControlPanel(HWND hwndOwner, DWORD dwFlags);
};

