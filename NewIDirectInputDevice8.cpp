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

#include "main.h"
#include "d3d9.h"

#include "NewIDirectInput8.h"
#include "NewIDirectInputDevice8.h"

extern IDirectInput8 *pDInput8;						//Original Device pointer
extern NewIDirectInput8 *pMyDInput8;				//Wrapped Device pointer


HRESULT __stdcall NewIDirectInputDevice8::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	HRESULT Result = pDInputDevice8->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
	/*if (!m_bIsMouse)
		return Result;
	//If there is no user input available check if we want to inject something
	if (*pdwInOut == 0)
	{
		if (GameInfo.m_MoveMouseX != 0)
		{
			*pdwInOut = 1;
			rgdod->dwOfs = DIMOFS_X;
			rgdod->dwData = GameInfo.m_MoveMouseX;
			GameInfo.m_MoveMouseX = 0;
			//GameInfo.m_MousePositionY += rgdod->dwData;
		}
		else if (GameInfo.m_MoveMouseY != 0)
		{
#ifdef TESTMODE
			fprintf(GameInfo.m_pTweaksLogFile, "T1 GMY:%05i GCWX:%08.2f\n", 
			GameInfo.m_MoveMouseY, GameInfo.m_Camera.WorldRotation.x);
#endif
			*pdwInOut = 1;
			rgdod->dwOfs = DIMOFS_Y;
			rgdod->dwData = GameInfo.m_MoveMouseY;
			GameInfo.m_MoveMouseY = 0;
			//GameInfo.m_MousePositionY += rgdod->dwData;
		}
	}
	else
	{
		switch (rgdod->dwOfs)
		{
			case DIMOFS_BUTTON0:
				break;
			case DIMOFS_BUTTON1:
				break;
			case DIMOFS_BUTTON2:
				break;
			case DIMOFS_BUTTON3:
				break;
			case DIMOFS_BUTTON4:
				break;
			case DIMOFS_BUTTON5:
				break;
			case DIMOFS_BUTTON6:
				break;
			case DIMOFS_BUTTON7:
				break;

			case DIMOFS_X:
				if (GameInfo.m_MoveMouseX != 0)
				{
					rgdod->dwData = GameInfo.m_MoveMouseX;
					GameInfo.m_MoveMouseX = 0;
				}
				else
				{
					rgdod->dwData = (DWORD)(((int)rgdod->dwData * ((float)GameInfo.m_Settings.m_MouseSpeed / 100)) + 0.5f);
					GameInfo.m_LastCameraMouseX = GameInfo.m_MousePositionX;
					GameInfo.m_MousePositionX += rgdod->dwData;
				}
				break;
			case DIMOFS_Y:
#ifdef TESTMODE
			fprintf(GameInfo.m_pTweaksLogFile, "T2 GMY:%05i GCWX:%08.2f\n", 
			GameInfo.m_MoveMouseY, GameInfo.m_Camera.WorldRotation.x);
#endif
				if (GameInfo.m_MoveMouseY != 0)
				{
					rgdod->dwData = GameInfo.m_MoveMouseY;
					GameInfo.m_MoveMouseY = 0;
				}
				else
				{
					rgdod->dwData = (DWORD)(((int)rgdod->dwData * ((float)GameInfo.m_Settings.m_MouseSpeed / 100)) + 0.5f);
					GameInfo.m_LastCameraMouseY = GameInfo.m_MousePositionY;
					GameInfo.m_MousePositionY += rgdod->dwData;
				}
                break;
			case DIMOFS_Z:
				break;
		}
	}*/
	return Result;
}


ULONG __stdcall NewIDirectInputDevice8::Release(void)
{
	return pDInputDevice8->Release();
}

//****************************** FUNCTIONS BELOW ARE PASS-THROUGH ONLY ******************************

HRESULT __stdcall NewIDirectInputDevice8::QueryInterface(REFIID iid, void ** ppvObject)
{
	return pDInputDevice8->QueryInterface(iid, ppvObject);
}

ULONG __stdcall NewIDirectInputDevice8::AddRef(void)
{
	return pDInputDevice8->AddRef();
}

HRESULT __stdcall NewIDirectInputDevice8::Acquire()
{
	return pDInputDevice8->Acquire();
}

HRESULT __stdcall NewIDirectInputDevice8::BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags)
{
	return pDInputDevice8->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter)
{
	return pDInputDevice8->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
}

HRESULT __stdcall NewIDirectInputDevice8::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
	return pDInputDevice8->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
}

HRESULT __stdcall NewIDirectInputDevice8::EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType)
{
	return pDInputDevice8->EnumEffects(lpCallback, pvRef, dwEffType);
}

HRESULT __stdcall NewIDirectInputDevice8::EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
	return pDInputDevice8->EnumEffectsInFile(lpszFileName, pec, pvRef, dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return pDInputDevice8->EnumObjects(lpCallback, pvRef, dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::Escape(LPDIEFFESCAPE pesc)
{
	return pDInputDevice8->Escape(pesc);
}

HRESULT __stdcall NewIDirectInputDevice8::GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
{
	return pDInputDevice8->GetCapabilities(lpDIDevCaps);
}

HRESULT __stdcall NewIDirectInputDevice8::GetDeviceInfo(LPDIDEVICEINSTANCE pdidi)
{
	return pDInputDevice8->GetDeviceInfo(pdidi);
}

HRESULT __stdcall NewIDirectInputDevice8::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	return pDInputDevice8->GetDeviceState(cbData, lpvData);
}

HRESULT __stdcall NewIDirectInputDevice8::GetEffectInfo(LPDIEFFECTINFO pdei, REFGUID rguid)
{
	return pDInputDevice8->GetEffectInfo(pdei, rguid);
}

HRESULT __stdcall NewIDirectInputDevice8::GetForceFeedbackState(LPDWORD pdwOut)
{
	return pDInputDevice8->GetForceFeedbackState(pdwOut);
}

HRESULT __stdcall NewIDirectInputDevice8::GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader)
{
	return pDInputDevice8->GetImageInfo(lpdiDevImageInfoHeader);
}

HRESULT __stdcall NewIDirectInputDevice8::GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
{
	return pDInputDevice8->GetObjectInfo(pdidoi, dwObj, dwHow);
}

HRESULT __stdcall NewIDirectInputDevice8::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	return pDInputDevice8->GetProperty(rguidProp, pdiph);
}

HRESULT __stdcall NewIDirectInputDevice8::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
	return pDInputDevice8->Initialize(hinst, dwVersion, rguid);
}

HRESULT __stdcall NewIDirectInputDevice8::Poll()
{
	return pDInputDevice8->Poll();
}

HRESULT __stdcall NewIDirectInputDevice8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return pDInputDevice8->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
	return pDInputDevice8->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
}

HRESULT __stdcall NewIDirectInputDevice8::SendForceFeedbackCommand(DWORD dwFlags)
{
	return pDInputDevice8->SendForceFeedbackCommand(dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::SetActionMap(LPDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags)
{
	return pDInputDevice8->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	return pDInputDevice8->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT __stdcall NewIDirectInputDevice8::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
	return pDInputDevice8->SetDataFormat(lpdf);
}

HRESULT __stdcall NewIDirectInputDevice8::SetEventNotification(HANDLE hEvent)
{
	return pDInputDevice8->SetEventNotification(hEvent);
}

HRESULT __stdcall NewIDirectInputDevice8::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	return pDInputDevice8->SetProperty(rguidProp, pdiph);
}

HRESULT __stdcall NewIDirectInputDevice8::Unacquire()
{
	return pDInputDevice8->Unacquire();
}

HRESULT __stdcall NewIDirectInputDevice8::WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
	return pDInputDevice8->WriteEffectToFile(lpszFileName, dwEntries, rgDiFileEft, dwFlags);
}
