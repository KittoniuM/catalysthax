
#include <windows.h>
#include <dinput.h>

#include "d3d9.h"
#include "main.h"
#include "Input.h"
#include "Hooks.h"
#include "CVAR.h"

#define M_PI		3.14159265358979323846

tDirectInput8Create pDirectInput8Create;

extern CPlayerManager* pPlayerManager;
extern D3DMATRIX *world;
extern CCVAR				*pCVar;
extern IDirect3DDevice9 *m_pd;
extern float ScreenCenterX;
extern float ScreenCenterY;

DWORD CreateDev=0;
DWORD DevData=0;

DWORD psss=0;DWORD mptr=0;

DWORD popr;

DWORD **mousePtr = 0;
DWORD gui; DWORD llp=0; DWORD outer=0;
DWORD rtn;

long curX=0;
long curY=0;
int sz = 0;
long sq = 0;
long sa = 0;
long oset = 0;
long sas = 0;
LPDIDEVICEOBJECTDATA pdod;

float cy = 0.0f;
float ystand = 0.0f;
float cx = 0.0f;
float cz = 0.06f;

long vall = 100;


bool stopm = false;

float calx[3]; float caly[3];

__declspec( naked ) VOID hkDevData(DWORD *iface,
					      DWORD dodsize,
					      LPDIDEVICEOBJECTDATA dod,
					      LPDWORD entries,
					      DWORD flags
) 
{
	
	
	_asm{
		push ebp;
		mov ebp, esp;//	

		pushad;
		
		push flags;
		push entries;
		push dod;
		push dodsize;
		push iface;
		call DevData;

		mov rtn, eax;

		popad;
	}

	_asm pushad;

	if(pCVar->Settings.intaim != 9)
	{
		if(pCVar->Settings.intaim == 8)
		{
			CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
			if(locPlayer != NULL)
			{
				calx[1] = locPlayer->Info->PlayerInfo->XAngle;
				caly[1] = locPlayer->Info->PlayerInfo->YAngle;
				calx[1] -= calx[0];
				caly[1] -= caly[0];
				if(calx[1] != 0 && caly[1] != 0)
				{
					calx[3] = 10.0f / calx[1];
					caly[3] = 10.0f / caly[1] ;
				}
				pCVar->Settings.movX = -10;
				pCVar->Settings.movY = -10;
				pCVar->Settings.cfov = locPlayer->FOV ;
				pCVar->Settings.intaim++;
			}
			add_log("X: %f  Y: %f", calx[3], caly[3]);
		}
		if(pCVar->Settings.intaim == 7)
			pCVar->Settings.intaim++;

		if(pCVar->Settings.intaim == 6)
			pCVar->Settings.intaim++;

		if(pCVar->Settings.intaim == 5)
			pCVar->Settings.intaim++;

		if(pCVar->Settings.intaim == 4)
			pCVar->Settings.intaim++;

		if(pCVar->Settings.intaim == 3)
			pCVar->Settings.intaim++;

		if(pCVar->Settings.intaim == 2)
			pCVar->Settings.intaim++;
		
		if(pCVar->Settings.intaim == 1)
		{
			CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
			if(locPlayer != NULL)
			{
				calx[0] = locPlayer->Info->PlayerInfo->XAngle;
				caly[0] = locPlayer->Info->PlayerInfo->YAngle;
				pCVar->Settings.movX = 10;
				pCVar->Settings.movY = 10;
				pCVar->Settings.intaim++;
			}
		}
	}
//	if(pCVar->Settings.intaim != 0 && pCVar->Settings.intaim != 9)
//		while(GetAsyncKeyState(VK_F10) == 0)
//		{
//		}
	/*_asm popad;
	
	

  



	




	_asm pushad;*/
	
	//if(GetAsyncKeyState(VK_F10)&1)
	//	pCVar->Settings.intaim = 11;

	if(pCVar->Settings.Aim && pCVar->Settings.aimok)
	{
		pCVar->Settings.aimok = false;
		_asm pushad;
		aim();
		_asm popad;
	}

	if(pCVar->Settings.recoil)
	{
		_asm pushad;
		recoil();
		_asm popad;
	}

		



	if(iface == (DWORD*)mptr)
	{
		if(*entries == 0)  //Check for user input
		{
			/*if(GetAsyncKeyState(VK_F10)&1)
			{
				pdod = dod;
				
				*entries = 2;
				_asm{
					push eax;
					push ebx;
					mov eax, dod;
					mov [eax], 0;
					mov ebx, vall;
					mov [eax+4], ebx;
					add eax, dodsize;
					mov [eax], 4;
					mov [eax+4], ebx;
					pop ebx;
					pop eax;
				}/*
					
				pdod->dwOfs = DIMOFS_X;
				pdod->dwData = 100;
				pdod += dodsize;

			//	pdod += sizeof(DIDEVICEOBJECTDATA);
				pdod->dwOfs = DIMOFS_Y;
				pdod->dwData = 100;
			}*/
			
			if(pCVar->Settings.movX != 0)
			{
				sq = pCVar->Settings.movX;
				curX += sq;
				_asm{
					push eax;
					push ebx;
					mov eax, dod;
					mov [eax], 0;
					mov ebx, sq;
					mov [eax+4], ebx;
					pop ebx;
					pop eax;
				}
				pCVar->Settings.movX = 0;
				//dod[*entries]->dwOfs = DIMOFS_X;
				//dod[*entries]->dwData = pCVar->Settings.movX;
				//
				*entries += 1;
			}
			if(pCVar->Settings.movY != 0)
			{
				sz = (*entries) * dodsize;
				sq = pCVar->Settings.movY;
				curY += sq;
				_asm{
					push eax;
					push ebx;
					mov eax, dod;
					add eax, sz;
					mov [eax], 4;
					mov ebx, sq;
					mov [eax+4], ebx;
					pop ebx;
					pop eax;
				}
				pCVar->Settings.movY = 0;
				//dod[*entries]->dwOfs = DIMOFS_Y;
				//dod[*entries]->dwData = pCVar->Settings.movY;
				//
				*entries += 1;
			}


			
		} else 
		{
			//while(GetAsyncKeyState(VK_F9) == 0)
			//{
				//sz += 4;
			//}
			for(int i = 0; i < *entries; i++)
			{
				sz = i * dodsize;

				_asm{
					mov eax, dod;
					add eax, sz;
					mov sq, eax;//sq = ptr to base dod
					mov eax, [eax];
					mov sas, eax;
				}

				if(sas == 0)
				{
					if(pCVar->Settings.recoil)
					{
						_asm{
							mov eax, sq;
							mov eax, [eax+4];
							mov oset, eax;
						}
						pCVar->Settings.recvec.x += oset / ( calx[3] * (pCVar->Settings.cfov / pCVar->Settings.rfov));

							//pCVar->Settings.recvec.x = oset / calx[3] 
						pCVar->Settings.movX += oset;
					
					}


					if(pCVar->Settings.stopm)
					{
						_asm{
							push ebx;
							mov eax, sq;						//sq = ptr to base dod
							xor ebx, ebx;
							mov [eax+4], ebx;
							pop ebx
						}
					}
					if(pCVar->Settings.movX != 0)
					{
						sa = pCVar->Settings.movX;
						_asm{
							push ebx;
							mov eax, sq;
							mov ebx, sa;
							mov [eax+4], ebx;
							pop ebx;
						}
						pCVar->Settings.movX = 0;

					}
				}
				if(sas == 4)
				{
					if(pCVar->Settings.recoil)
					{
						_asm{
							mov eax, sq;
							mov eax, [eax+4];
							mov oset, eax;
						}
						pCVar->Settings.recvec.y += oset / ( caly[3] * ( pCVar->Settings.cfov / pCVar->Settings.rfov ));

						pCVar->Settings.movY += oset;
					
					}


					if(pCVar->Settings.stopm)
					{
						_asm{
							push ebx;
							mov eax, sq;
							xor ebx, ebx;
							mov [eax+4], ebx;
							pop ebx
						}
					}
					if(pCVar->Settings.movY != 0)
					{
						sa = pCVar->Settings.movY;
						_asm{
							push ebx;
							mov eax, sq;
							mov ebx, sa;
							mov [eax+4], ebx;
							pop ebx;
						}
						pCVar->Settings.movY = 0;
					}
				}
			}
			if(pCVar->Settings.movX != 0)
			{
				sz = (*entries) * dodsize;
				*entries = *entries + 1;
				
				sa = pCVar->Settings.movX;
				_asm{
					push ebx;
					mov eax, dod;
					add eax, sz;
					mov [eax], 0;
					mov ebx, sa;
					mov [eax+4], ebx;
				//	add eax, 0x14;
				//	xor ebx, ebx;
				//	mov [eax+4], ebx;
					pop ebx;
				}
				pCVar->Settings.movX = 0;
			}
			if(pCVar->Settings.movY != 0)
			{
				sz = (*entries ) * dodsize;
				*entries = *entries + 1;
				
				sa = pCVar->Settings.movY;
				_asm{
					push ebx;
					mov eax, dod;
					add eax, sz;
					mov [eax], 4;
					mov ebx, sa;
					mov [eax+4], ebx;
				//	add eax, 0x14;
				//	xor ebx, ebx;
				//	mov [eax+4], ebx;
					pop ebx;
				}
				pCVar->Settings.movY = 0;
			}












				/*switch(dod[i]->dwOfs)
				{
					case DIMOFS_BUTTON0:
						break;
					case DIMOFS_BUTTON1:
						break;
					case DIMOFS_BUTTON2:
						break;
					case DIMOFS_BUTTON3:
						break;
					/*case DIMOFS_BUTTON4:
						break;
					case DIMOFS_BUTTON5:
						break;
					case DIMOFS_BUTTON6:
						break;
					case DIMOFS_BUTTON7:
						break;//
					case DIMOFS_X:
						if(pCVar->Settings.stopm)
						{
							//*entries = 0;
							//dod->dwOfs = 0;
							dod[i]->dwData = 0;
						}
						if(pCVar->Settings.movX != 0)
						{
							//*entries = 2;
							//dod->dwOfs = DIMOFS_X;
							dod[i]->dwData = pCVar->Settings.movX;
							pCVar->Settings.movX = 0;
						}


						pCVar->Settings.camX = dod[i]->dwData;
						break;
					case DIMOFS_Y:
						if(pCVar->Settings.stopm)
						{
							//*entries = 0;
							//dod->dwOfs = 0;
							dod[i]->dwData = 0;
						}
						if(pCVar->Settings.movY != 0)
						{
							//*entries = 2;
							//dod->dwOfs = DIMOFS_Y;
							dod[i]->dwData = pCVar->Settings.movY;
							pCVar->Settings.movY = 0;
						}

						pCVar->Settings.camY = dod[i]->dwData;
						break;
					case DIMOFS_Z:
					break;
				}
			}*/
		}
	}


	//if(pCVar->Settings.intaim != 0 && pCVar->Settings.intaim != 9)
		//while(GetAsyncKeyState(VK_F11) == 0)
		//{
		//}

	
	_asm popad;

	_asm{
		pop ebp;
		//add esp, 0x20;
		/*pop popr;
		call DevData;
		push popr;*/
	}

	_asm mov eax, rtn;
	_asm retn 0x14;

}
/*LPDIRECTINPUTDEVICE8*///add_log("DeviceData Hit! Face: 0x%x size: 0x%x dod: 0x%x entries: 0x%x", iface, dodsize, dod, entries);
__declspec( naked ) VOID hkCreateDev(DWORD *pDev, REFGUID rguid,  DWORD **lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	_asm{
		push ebp;
		//push eax;
		mov ebp, esp;
		/*mov eax, [ebp+0x10];
		mov gui, eax;
		mov eax, [ebp+0x14];
		mov llp, eax;
		mov eax, [ebp+0x18];
		mov outer, eax;
		pop eax;*/
	}

	_asm pushad;
	//psss++;

	
//	add_log("Create Device Hit! rguid: 0x%x lplp: 0x%x Outer: 0x%x", rguid, lplpDirectInputDevice, pUnkOuter);
//	add_log("Create Device Hit! rguid: 0x%x lplp: 0x%x Outer: 0x%x", rguid, lplpDirectInputDevice, pUnkOuter);
//	add_log("Create Device Hit! Dev: 0x%x rguid: 0x%x lplp: 0x%x Outer: 0x%x", pDev, rguid, lplpDirectInputDevice, pUnkOuter);

	if (rguid == GUID_SysMouse){
		//	add_log("Mouse Device HIT: 0x%x", lplpDirectInputDevice);
			llp = (DWORD)lplpDirectInputDevice;
			psss = 5;

			

			RetourFunc( (BYTE*)GetProcAddress(GetModuleHandle("DINPUT8.DLL"), "DirectInput8Create"), (BYTE*)pDirectInput8Create, 5);


		//	mousePtr = (DWORD **)pUnkOuter;
	}/* else if (rguid == GUID_SysKeyboard){
			add_log("KEY Device HIT: 0x%x", lplpDirectInputDevice);
		//	mousePtr = (DWORD **)pUnkOuter;
	}*/
	_asm popad;

	_asm{
		pop ebp;
		pop popr;
		call CreateDev;
		push popr;
	//	push ebp;
		//push eax;
	//	mov ebp, esp;
	}

	_asm pushad;
	if(psss == 5)
	{
		

			psss=100;
		//	mptr = (DWORD) llp;
			DWORD addr=0;
			_asm{
				push eax;
				push ebx;
				mov eax, llp;
				mov eax, [eax];
				mov mptr, eax;
				mov eax, [eax];
				add eax, 0x28;
				//mov ebx, [eax];
				//mov DevData, ebx;
				mov addr, eax;
				pop ebx;
				pop eax;
			}

			DWORD cdr = (DWORD)&hkDevData;

			//sz = sizeof(DIDEVICEOBJECTDATA);
			


			ReadProcessMemory(GetCurrentProcess(), (void*)addr, &DevData, 4, 0);
		//	add_log("addr: 0x%x DevData: 0x%x mptr: 0x%x", addr, DevData, mptr); 

			WriteProcessMemory(GetCurrentProcess(), (void*)addr, (void*)&cdr, 4, 0);

		//while(GetAsyncKeyState(VK_END) == 0)
		//{
		//}
		
		

		//while(GetAsyncKeyState(VK_END) == 0)
		//{
		//}
	}
	_asm popad;
//	_asm pop ebp;


	_asm ret;
}





HRESULT WINAPI hkDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf,LPVOID* ppvOut,  
  LPUNKNOWN punkOuter
)
{
//	add_log("DirectInput8Create(%i) succeeded...", dwVersion);

	//MyDInput8 = new NewIDirectInput8();

	HRESULT Result = pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	DWORD adr;// = (DWORD)**ppvOut;
	//adr += 0xC;

	
		_asm{
			push eax;
			mov eax, ppvOut;
			mov eax, [eax];
			mov eax, [eax];
			add eax, 0xC;
			mov adr, eax;
			//mov CreateDev, [eax];
			pop eax;
		}

	if(!CreateDev)
		ReadProcessMemory(GetCurrentProcess(), (void*)adr, &CreateDev, 4, 0);

		DWORD cdr = (DWORD)&hkCreateDev;

		
		WriteProcessMemory(GetCurrentProcess(), (void*)adr, (void*)&cdr, 4, 0);
	


//	add_log("DirectInput pp: 0x%x  p: 0x%x", ppvOut, *ppvOut);
	/*add_log("adr: 0x%x  cdr: 0x%x", adr, cdr);
	while(GetAsyncKeyState(VK_END) == 0)
	{
	}*/

	//pMyDInput8 = &MyDInput8;

	//*ppvOut = pMyDInput8;

	return Result;

}