#include <windows.h>

#include "d3d9.h"
#include "main.h"

tDirect3DCreate9 oDirect3DCreate9;


/*
IDirectInput8 *pDInput8;						//Original Device pointer
NewIDirectInput8 MyDInput8;
NewIDirectInput8 *pMyDInput8;				//Wrapped Device pointer
*/

IDirect3D9 *APIENTRY hkDirect3DCreate9(UINT SDKVersion)
{
//	add_log("Direct3DCreate9(%i) succeeded...", SDKVersion);
	/*_asm{
		pushad;
		mov eax, ebx;
		mov ebx, eax;
		mov eax, ebx;
		mov ebx, eax;
		popad;
	}*/

	IDirect3D9 *d3dint = oDirect3DCreate9(SDKVersion);

	

	if( d3dint != NULL )
	{
		hkIDirect3D9 *ret = new hkIDirect3D9(&d3dint);
	//	
	//	add_log("Hooked Direct3D9 interface: 0x%x -> 0x%x", ret->m_pD3Dint, ret);
	}
	else

	return d3dint;
}






