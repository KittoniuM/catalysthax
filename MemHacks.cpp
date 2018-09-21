#include <windows.h>
#include "MemHacks.h"
#include "CVAR.h"

extern CCVAR				*pCVar;

HANDLE dwRendDX9Base;
HANDLE hnd;

BYTE Nop2Bytes[2] = {0x90,0x90};
BYTE Nop6Bytes[6] = {0x90,0x90,0x90,0x90,0x90,0x90};

BYTE oTag1[6];
BYTE oTag2[6];
BYTE oTag3[6];

BYTE ohTag1[6];
BYTE ohTag2[6];
BYTE ohTag3[6];

BYTE otagDist[2];

BYTE otf[2] = {0x75, 0x0f} ;

BYTE odist[2] = {0x74, 0x70} ;

BYTE okit1[2] = {0x75, 0x34} ;
BYTE okit2[2] = {0x75, 0x0C} ;

BYTE o3d[2] = {0x75, 0x0E} ;
BYTE orad[2] = {0x74, 0x4A} ;
BYTE omin[2] = {0x75, 0x62} ;

BYTE TagJmp[6] = {0xE9, 0xF4, 0x00, 0x00, 0x00, 0x90} ;

DWORD dr;

DWORD wback;DWORD wback2;
BYTE *dess;

LPVOID virt = 0;


void TeamPts(DWORD *team)
{
	//DWORD pts = 0;
	//DWORD ptss = 0;
	_asm{
		pushad;
		MOV     ECX, [0x987C10];
		cmp		ecx, 0;
		je dne;
		MOV     EDX, [ECX];
		cmp		edx, 0;
		je dne;
		XOR     EAX, EAX;
		MOV     EDI, 2;
	//	CMP     [ESI+23C], EDI
		//SETNE   AL;
		mov     EAX, 1;
		cmp		[EDX+10], 0;
		je dne;
		PUSH    EAX;
		CALL    [EDX+10];
		cmp		eax, 0;
		je dne;
		mov		eax, [eax+0x84];
		mov ebx, team;
		mov [ebx], eax;
dne:
		popad;
	}
	_asm{
		pushad;
		MOV     ECX, [0x987C10];
		cmp		ecx, 0;
		je dnee;
		MOV     EDX, [ECX];
		cmp		edx, 0;
		je dnee;
		XOR     EAX, EAX;
		MOV     EDI, 2;
	//	CMP     [ESI+23C], EDI
		//SETNE   AL;
		mov     EAX, 2;
		cmp		[EDX+10], 0;
		je dnee;
		PUSH    EAX;
		CALL    [EDX+10];
		cmp		eax, 0;
		je dnee;
		mov		eax, [eax+0x84];
		mov ebx, team;
		add ebx, 4;
		mov [ebx], eax;
dnee:
		popad;
	}
	//return pts;
}

__declspec( naked ) VOID MyWrite(DWORD dest, DWORD src, DWORD len)
{
	_asm{
		push ebp;
		mov ebp, esp;
		pushad;
		mov ebx, src;
		mov edx, dest;
		mov ecx, len;
		xor eax, eax;
	srt:
		mov ah, byte ptr [ebx];
		mov [edx], ah;
		inc ebx;
		inc edx;
		dec ecx;
		cmp ecx, 0;
		jnz srt;

		popad;
		mov esp, ebp;
		pop ebp;
		ret;
	}
}

VOID FixCalls(DWORD start, DWORD OrigBase, DWORD len)
{
	_asm{
		push eax;
		push ebx;
		push ecx;
		push edx;
		mov edx, start;
		mov ecx, len;
		mov ebx, OrigBase;
		xor eax, eax;
strr:
		mov ah, byte ptr [edx];
		cmp ah, 0xe8;
		je equ;
		inc edx;
		inc ebx;
		dec ecx;
		cmp ecx, 0;
		jnz strr;
		jmp dne;

equ:
		push ebx;
		mov eax, [edx+1];
		add ebx, eax;
		add ebx, 5;
		sub ebx, edx;
		sub ebx, 5;
		mov [edx+1], ebx;
		xor eax, eax;
		pop ebx;

		add edx, 5;
		add ebx, 5;
		sub ecx, 5;
		cmp ecx, 0;
		jnz strr;
dne:
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}
}








VOID intMemHacks()
{


	if(!virt)
		virt=VirtualAlloc(NULL, 0x10000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	dwRendDX9Base = GetModuleHandle("RendDX9.dll");
	hnd = GetCurrentProcess();

	dr = (DWORD)dwRendDX9Base + 0x12CDC2;
	ReadProcessMemory(hnd, (void*)dr, &oTag1, 6, 0);
	dr = (DWORD)dwRendDX9Base + 0x12CDB3;
	ReadProcessMemory(hnd, (void*)dr, &oTag2, 6, 0);
	dr = (DWORD)dwRendDX9Base + 0x12CD9D;
	ReadProcessMemory(hnd, (void*)dr, &oTag3, 6, 0);

	dr = (DWORD)dwRendDX9Base + 0x1B15CD;
	ReadProcessMemory(hnd, (void*)dr, &ohTag1, 6, 0);
	dr = (DWORD)dwRendDX9Base + 0x1B16FE;
	ReadProcessMemory(hnd, (void*)dr, &ohTag2, 6, 0);
	dr = (DWORD)dwRendDX9Base + 0x1B174C;
	ReadProcessMemory(hnd, (void*)dr, &ohTag3, 6, 0);

	dr = (DWORD)dwRendDX9Base + 0x12C103;
	ReadProcessMemory(hnd, (void*)dr, &otagDist, 2, 0);

}
VOID TagsOn1()
{
	static bool frstt=true;
	if(frstt)
	{
		frstt = false;
	//virt=VirtualAlloc(NULL, 0x10000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//dwRendDX9Base = GetModuleHandle("RendDX9.dll");

	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback) ;

	dr = (DWORD)dwRendDX9Base + 0x1A0000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback2);

	BYTE jmn[4];

	dr = (DWORD)dwRendDX9Base + 0x12A9B0;

	memcpy(virt, (const void *)dr, 0x445);
	FixCalls((DWORD)virt,(DWORD) dr,(DWORD) 0x445);

	dr += 0x1b8;
	DWORD vv = (DWORD)virt;
	DWORD vp = vv+0x1b8; 
	memcpy((void *)vp, (const void *)dr, 7);


	dr = (DWORD)virt + 0x1E2;

	MyWrite(dr, (DWORD)&TagJmp, 6);
	
	dr = (DWORD)virt + 0x1D3;
	
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);
	
	dr = (DWORD)virt + 0x1BD;
	
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);



	jmn[0] = 0xe9;
	vp = (DWORD)dwRendDX9Base;
	DWORD jb = (DWORD)(vv - (vp + 0x12A9B0)) - 5;
	memcpy((void*)&jmn[1], (const void *)&jb, 4);

	dr = (DWORD)dwRendDX9Base + 0x12A9B0;
	
	MyWrite(dr, (DWORD)&jmn, 5);

	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback) ;

	dr = (DWORD)dwRendDX9Base + 0x1A0000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback2);
	} else
	{
		dr = (DWORD)virt + 0x1E2;

	MyWrite(dr, (DWORD)&TagJmp, 6);
	
	dr = (DWORD)virt + 0x1D3;
	
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);
	
	dr = (DWORD)virt + 0x1BD;
	
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);
	}
}





__declspec( naked ) VOID TagsOn()
{
	if(pCVar->Settings.bNametags)
	{
		dr = (DWORD)dwRendDX9Base + 0x12CDC2;
		MyWrite(dr, (DWORD)(DWORD)&TagJmp, 6);

		dr = (DWORD)dwRendDX9Base + 0x12CDB3;
		MyWrite(dr, (DWORD)&Nop6Bytes, 6);

		dr = (DWORD)dwRendDX9Base + 0x12CD9D;
		MyWrite(dr, (DWORD)&Nop6Bytes, 6);

		///////////distance tags/////////////
		//dr = (DWORD)dwRendDX9Base + 0x12C103;
		//MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	}
	
	_asm ret;
}
VOID TagsOff1()
{
	dr = (DWORD)virt + 0x1E2;

	MyWrite(dr, (DWORD)&oTag1, 6);
	
	dr = (DWORD)virt + 0x1D3;
	
	MyWrite(dr, (DWORD)&oTag2, 6);
	
	dr = (DWORD)virt + 0x1BD;
	
	MyWrite(dr, (DWORD)&oTag3, 6);

}

__declspec( naked ) VOID tfOn()
{
	dr = (DWORD)dwRendDX9Base + 0x12B00D;
	MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	_asm ret;
}
__declspec( naked ) VOID tfOff()
{
	dr = (DWORD)dwRendDX9Base + 0x12B00D;
	MyWrite(dr, (DWORD)&otf, 2);
	_asm ret;
}

__declspec( naked ) VOID TagDist()
{
	if(pCVar->Settings.Dist)
	{
		dr = (DWORD)dwRendDX9Base + 0x12E333;
		MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	}
	_asm ret;
}
__declspec( naked ) VOID TagDistOff()
{
	if(pCVar->Settings.Dist)
	{
		dr = (DWORD)dwRendDX9Base + 0x12E333;
		MyWrite(dr, (DWORD)&odist, 2);
	}
	_asm ret;
}
__declspec( naked ) VOID TagsOff()
{
	if(pCVar->Settings.bNametags)
	{

		dr = (DWORD)dwRendDX9Base + 0x12CDC2;
		MyWrite(dr, (DWORD)&oTag1, 6);
		dr = (DWORD)dwRendDX9Base + 0x12CDB3;
		MyWrite(dr, (DWORD)&oTag2, 6);
		dr = (DWORD)dwRendDX9Base + 0x12CD9D;
		MyWrite(dr, (DWORD)&oTag3, 6);

	//	dr = (DWORD)dwRendDX9Base + 0x12C103;
	//	MyWrite(dr, (DWORD)&otagDist, 2);
	}
	
	_asm ret;
}
__declspec( naked ) VOID Mine()
{
	if(pCVar->Settings.bMines)
	{
		dr = (DWORD)dwRendDX9Base + 0x12CA61;
		MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	}
	_asm ret;
}
__declspec( naked ) VOID MineOff()
{
	if(pCVar->Settings.bMines)
	{
		dr = (DWORD)dwRendDX9Base + 0x12CA61;
		MyWrite(dr, (DWORD)&omin, 2);
	}
	_asm ret;
}
void dTags1()
{
	static bool frstt=true;
	if(frstt)
	{
		frstt = false;
	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback) ;


	BYTE jmn[4];

	dr = (DWORD)dwRendDX9Base + 0x12A410;

	DWORD vp = (DWORD)virt + 0x500;
	
	memcpy((void *)vp, (const void *)dr, 0xEB);
	FixCalls((DWORD)vp,(DWORD) dr,(DWORD) 0xEB);

	DWORD vv = vp;
	vp += 0xCD;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);

	jmn[0] = 0xe9;
	DWORD jb = (DWORD)(vv - (dr)) - 5;
	memcpy((void*)&jmn[1], (const void *)&jb, 4);

	MyWrite(dr, (DWORD)&jmn, 5);


	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback) ;
	} else
	{
		DWORD vp = (DWORD)virt + 0x500;
	vp += 0xCD;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);
	}





}

__declspec( naked ) void dTags()
{
	if(pCVar->Settings.b3DMap)
	{
		dr = (DWORD)dwRendDX9Base + 0x12C70D;
		MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	}
	
	_asm ret;
}
void doff1()
{
	DWORD vp = (DWORD)virt + 0x500;
	vp += 0xCD;

	MyWrite(vp, (DWORD)&o3d, 2);
}



__declspec( naked ) void doff()
{
	if(pCVar->Settings.b3DMap)
	{
	dr = (DWORD)dwRendDX9Base + 0x12C70D;
	MyWrite(dr, (DWORD)&o3d, 2);
	}
	_asm ret;
}

void radar1()
{
	static bool frstt=true;
	if(frstt)
	{
		frstt = false;
	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback) ;


	BYTE jmn[4];

	dr = (DWORD)dwRendDX9Base + 0x12C420;

	DWORD vp = (DWORD)virt + 0x3000;
	
	memcpy((void *)vp, (const void *)dr, 0x4B4);
	FixCalls((DWORD)vp,(DWORD) dr,(DWORD) 0x4B4);

	DWORD vv = vp;
	vp = vv + 0x379;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);

	vp = vv + 0x13E;

	dr = (DWORD)dwRendDX9Base + 0x12C420 + 0x13E;

	MyWrite(vp, dr, 7);

	vp = vv + 0x2AA;

	dr = (DWORD)dwRendDX9Base + 0x12C420 + 0x2AA;

	MyWrite(vp, dr, 7);

	vp = vv + 0x276;

	dr = (DWORD)dwRendDX9Base + 0x12C420 + 0x276;

	MyWrite(vp, dr, 0x10);

	dr = (DWORD)dwRendDX9Base + 0x12C420;

	jmn[0] = 0xe9;
	DWORD jb = (DWORD)(vv - (dr)) - 5;
	memcpy((void*)&jmn[1], (const void *)&jb, 4);

	MyWrite(dr, (DWORD)&jmn, 5);


	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback) ;
	} else
	{
		DWORD vp = (DWORD)virt + 0x3000;
	vp = vp + 0x379;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);
	}


}

__declspec( naked ) void radar()
{
	if(pCVar->Settings.bRadar)
	{
	dr = (DWORD)dwRendDX9Base + 0x12E9C9;
	MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	}
	
	_asm ret;
}
void radoff1()
{
	DWORD vp = (DWORD)virt + 0x3000;
	vp = vp + 0x379;

	MyWrite(vp, (DWORD)&orad, 2);

}

__declspec( naked ) void radoff()
{
	if(pCVar->Settings.bRadar)
	{
	dr = (DWORD)dwRendDX9Base + 0x12E9C9;
	MyWrite(dr, (DWORD)&orad, 2);
	}
	
	_asm ret;
}

void Health1()
{
	static bool frstt=true;
	if(frstt)
	{
		frstt = false;



	dr = (DWORD)dwRendDX9Base + 0x1A0000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback2);




	BYTE jmn[4];

	dr = (DWORD)dwRendDX9Base + 0x1AABB0;

	DWORD vp = (DWORD)virt + 0x1000;
	
	memcpy((void *)vp, (const void *)dr, 0xA97);
	FixCalls((DWORD)vp,(DWORD) dr,(DWORD) 0xA97);



	DWORD vv = vp;
	vp = vv + 0x8D;

	MyWrite(vp, (DWORD)&Nop6Bytes, 6);

	vp = vv + 0x1be;

	MyWrite(vp, (DWORD)&Nop6Bytes, 6);

	

	vp = vv + 0x206;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0x206;

	MyWrite(vp, dr, 6);


vp = vv + 0x20C;

	MyWrite(vp, (DWORD)&Nop6Bytes, 6);


	vp = vv + 0xF1;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0xF1;

	MyWrite(vp, dr, 0x8);

	vp = vv + 0x111;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0x111;

	MyWrite(vp, dr, 0x10);

	vp = vv + 0x63C;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0x63C;

	MyWrite(vp, dr, 0xB);

	vp = vv + 0x658;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0x658;

	MyWrite(vp, dr, 0x1C);

	vp = vv + 0x729;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0x729;

	MyWrite(vp, dr, 0x9);

	vp = vv + 0x9c2;
	dr = (DWORD)dwRendDX9Base + 0x1AABB0 + 0x9c2;

	MyWrite(vp, dr, 0x15);


	dr = (DWORD)dwRendDX9Base + 0x1AABB0;
	jmn[0] = 0xe9;
	DWORD jb = (DWORD)(vv - (dr)) - 5;
	memcpy((void*)&jmn[1], (const void *)&jb, 4);

	MyWrite(dr, (DWORD)&jmn, 5);


	dr = (DWORD)dwRendDX9Base + 0x1A0000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback2);
	} else 
	{
		DWORD vp = (DWORD)virt + 0x1000;

	DWORD vv = vp;
	vp = vv + 0x8D;

	MyWrite(vp, (DWORD)&Nop6Bytes, 6);

	vp = vv + 0x1be;

	MyWrite(vp, (DWORD)&Nop6Bytes, 6);

	vp = vv + 0x20C;

	MyWrite(vp, (DWORD)&Nop6Bytes, 6);
	}


}

__declspec( naked ) void Health()
{
	if(pCVar->Settings.bHealthTags)
	{
	dr = (DWORD)dwRendDX9Base + 0x1B15CD;
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);
	dr = (DWORD)dwRendDX9Base + 0x1B16FE;
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);
	dr = (DWORD)dwRendDX9Base + 0x1B174C;
	MyWrite(dr, (DWORD)&Nop6Bytes, 6);
	}
	
	_asm ret;
}
void Healthoff1()
{
	DWORD vp = (DWORD)virt + 0x1000;

	DWORD vv = vp;
	vp = vv + 0x8D;

	MyWrite(vp, (DWORD)&ohTag1, 6);

	vp = vv + 0x1be;

	MyWrite(vp, (DWORD)&ohTag2, 6);

	vp = vv + 0x20C;

	MyWrite(vp, (DWORD)&ohTag3, 6);

}

__declspec( naked ) void Healthoff()
{
	if(pCVar->Settings.bHealthTags)
	{
	dr = (DWORD)dwRendDX9Base + 0x1B15CD;
	MyWrite(dr, (DWORD)&ohTag1, 6);
	dr = (DWORD)dwRendDX9Base + 0x1B16FE;
	MyWrite(dr, (DWORD)&ohTag2, 6);
	dr = (DWORD)dwRendDX9Base + 0x1B174C;
	MyWrite(dr, (DWORD)&ohTag3, 6);
	}
	
	_asm ret;
}
void kits1()
{

	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback) ;


	BYTE jmn[4];

	dr = (DWORD)dwRendDX9Base + 0x129F60;

	DWORD vp = (DWORD)virt + 0x2000;
	
	memcpy((void *)vp, (const void *)dr, 0x59B);
	FixCalls((DWORD)vp,(DWORD) dr,(DWORD) 0x59B);

	DWORD vv = vp;
	vp = vv + 0xCA;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);

	vp = vv + 0x111;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);

	vp = vv + 0x130;

	MyWrite(vp, (DWORD)&Nop2Bytes, 2);


	jmn[0] = 0xe9;
	DWORD jb = (DWORD)(vv - (dr)) - 5;
	memcpy((void*)&jmn[1], (const void *)&jb, 4);

	MyWrite(dr, (DWORD)&jmn, 5);


	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback) ;

}

__declspec( naked ) void kits()
{
	if(pCVar->Settings.bKit)
	{
	dr = (DWORD)dwRendDX9Base + 0x12C25A;
	MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	dr = (DWORD)dwRendDX9Base + 0x12C2A1;
	MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	dr = (DWORD)dwRendDX9Base + 0x12C2C0;
	MyWrite(dr, (DWORD)&Nop2Bytes, 2);
	}
	
	_asm ret;
}
void kitsoff1()
{
	DWORD vp = (DWORD)virt + 0x2000;

	DWORD vv = vp;
	vp = vv + 0xCA;

	MyWrite(vp, (DWORD)&okit1, 2);

	vp = vv + 0x111;

	MyWrite(vp, (DWORD)&okit2, 2);

	vp = vv + 0x130;

	MyWrite(vp, (DWORD)&okit2, 2);

}

__declspec( naked ) void kitsoff()
{
	if(pCVar->Settings.bKit)
	{
	dr = (DWORD)dwRendDX9Base + 0x12C25A;
	MyWrite(dr, (DWORD)&okit1, 2);
	dr = (DWORD)dwRendDX9Base + 0x12C2A1;
	MyWrite(dr, (DWORD)&okit2, 2);
	dr = (DWORD)dwRendDX9Base + 0x12C2C0;
	MyWrite(dr, (DWORD)&okit2, 2);
	}
	
	_asm ret;
}

__declspec( naked ) void acOn()
{
	
	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback) ;

	dr = (DWORD)dwRendDX9Base + 0x1B0000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, PAGE_EXECUTE_READWRITE, &wback2);

	_asm ret;

}

__declspec( naked ) void acOff()
{
	
	dr = (DWORD)dwRendDX9Base + 0x120000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback) ;

	dr = (DWORD)dwRendDX9Base + 0x1B0000;
	dess = (BYTE*)dr;
	VirtualProtect(dess, 0x10000, wback, &wback2);

	_asm ret;

}
	





