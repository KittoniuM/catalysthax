/*	Direct3D9 Device */

#include <windows.h>
#include <stdio.h> 

#include <time.h>

#include "main.h"
#include "d3d9.h"
#include "CRC32.h"
#include "Hooks.h"
#include "CVAR.h"
#include "Menu.h"
#include "MemHacks.h"
//#include "Common.h"
#include "Zoom.h"
#include "Radar.h"


#define M_PI		3.14159265358979323846
#define crc
UINT m_Stride;

hkIDirect3DTexture9 *pCurrTex		= NULL;
hkIDirect3DTexture9 *pD3D9CurrTex	= NULL;
CDynamicCrc32		*pCrC			= NULL;
CCVAR				*pCVar			= NULL;
CCVAR				*pCVtmp			= NULL;
CCVAR				*pCVnull			= NULL;
CD3DFont			*g_pD3Dfont		= NULL;
CD3DFont			*g_rD3Dfont		= NULL;
CD3DFont			*g_tD3Dfont		= NULL;
CD3DRender			*g_pRender		= NULL;
Radar				*pRadar			= NULL;

CMenu				*pMenu			= NULL;

///////ddraw///////
DWORD ssintv = 0;
bool cleanpass = false;
//extern IDirectDrawSurface4	*gDDrawSurf;
//extern DDSURFACEDESC2 SDes;
//extern LPVOID ssData;
extern bool fake;
//////ddraw////////

bool bInitD3D = false;
bool eInitD3D = false;

float ScreenCenterX=0.0f;
float ScreenCenterY=0.0f;

float modr=1.0f;
float modd = 4.25f;

D3DXVECTOR3 dav[3];
////////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/////////////////////

float mvx[2];
float mvy[2];

float trec[3];

#ifdef crc
D3DPRIMITIVETYPE Typ;
INT Base;
UINT Min;
UINT Num;
UINT start;
UINT prim;
UINT strd = 0;
DWORD ctr;
DWORD ctr1=0;
DWORD ctr2=0;
DWORD ctrg=0;
DWORD ctrs=0;
DWORD ctra;
DWORD ctrb;
DWORD curtex;
DWORD tex;
DWORD list[300];
DWORD list1[100];
DWORD list2[100];
DWORD listg[100];
DWORD lists[100];
DWORD lista[100];
DWORD listb[100];
DWORD pass[300];
DWORD pctr;
DWORD nc;
bool colstr;
bool next = false;
bool next1 = false;
#endif
LPD3DXFONT m_font;

extern float calx[3]; 
extern float caly[3];
extern CPlayerManager* pPlayerManager;
bool dESP = false;
extern D3DVECTOR viewprt;
/*extern struct mMatrix
{
	D3DXMATRIX world;
	D3DXMATRIX view;
};*/
extern D3DMATRIX *world;

extern float mody;


bool frst = false;
D3DMATRIX view;
//D3DMATRIX world;


ID3DXLine *pLine;

char g_szClassList[7][20] = { "SpecialOp", "Sniper", "Assault", "Support", "Engineer", "Medic", "AntiTank" };

LPDIRECT3DTEXTURE9 	texTeamA;
LPDIRECT3DTEXTURE9 	texTeamB;
LPDIRECT3DTEXTURE9 	texWeapon;
LPDIRECT3DTEXTURE9 	texWhite;

LPDIRECT3DTEXTURE9 pink;
LPDIRECT3DTEXTURE9 dblue;
LPDIRECT3DTEXTURE9 yellow;

IDirect3DDevice9 *m_pd;

VOID Create( )
{	
	
	pCrC  = new CDynamicCrc32( );
	pCVar = new CCVAR		 ( );
	pCVtmp = new CCVAR		 ( );
	pCVnull = new CCVAR		 ( );

	pRadar = new Radar		 ( );
//	pCVnull->Settings.skipmenu = true;
}

VOID Destroy( )
{	
	delete pCrC;
	pCrC = NULL;
}

#define D3DHOOK_TEXTURES //comment this to disable texture hooking

void PrintText(LPD3DXFONT Font, int x, int y, int Red, int Green, int Blue, int Alpha, const char *text, ...) { 

	D3DCOLOR fontColor = D3DCOLOR_ARGB(Alpha, Red, Green, Blue);
	RECT rct; 
	rct.left=x; 
	rct.top=y; 
	rct.right=rct.left+1000; 
	rct.bottom=rct.top+20;
    va_list va_alist;
    char logbuf[256] = {0};
    va_start (va_alist, text);
    _vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
    va_end (va_alist);
	Font->DrawText(NULL, logbuf, -1, &rct, 0, fontColor );
}

VOID DrawBox(D3DXVECTOR3 screen, int team, float radi)
{
	float dis = radi * 2.0f;
	g_pRender->Begin(D3DPT_TRIANGLELIST);
	if(team == 2)
	{
		D3DAddQuad(g_pRender, screen.x - radi, screen.y - 1, dis, 1.0f, 0xFF0000FF);
		D3DAddQuad(g_pRender, screen.x - radi, screen.y-dis - 1, dis, 1.0f, 0xFF0000FF);
		D3DAddQuad(g_pRender, screen.x - radi - 1, screen.y-dis - 1 , 1.0f, dis + 1 , 0xFF0000FF);
		D3DAddQuad(g_pRender, screen.x + radi, screen.y-dis - 1 , 1.0f, dis + 1 , 0xFF0000FF);
	}
	else
	{
		D3DAddQuad(g_pRender, screen.x - radi, screen.y - 1, dis, 1.0f, 0xFFFF0000);
		D3DAddQuad(g_pRender, screen.x - radi, screen.y-dis - 1, dis, 1.0f, 0xFFFF0000);
		D3DAddQuad(g_pRender, screen.x - radi - 1, screen.y-dis - 1, 1.0f, dis + 1, 0xFFFF0000);
		D3DAddQuad(g_pRender, screen.x + radi, screen.y-dis - 1, 1.0f, dis + 1, 0xFFFF0000);
	}
	g_pRender->End();
}		


HRESULT CD3DManager::Initialize()
{
	/*
	initialize Resources such as textures 
	(managed and unmanaged [D3DPOOL]), 
	vertex buffers, and other D3D rendering resources
	...
	m_pD3Ddev->CreateTexture(..., ..., &m_pD3Dtexture);
	*/
	return S_OK;
}

HRESULT CD3DManager::PreReset()
{
	/*
	release all UNMANAGED [D3DPOOL_DEFAULT] 
	textures, vertex buffers, and other 
	volitile resources
	...
	_SAFE_RELEASE(m_pD3Dtexture);
	*/
	return S_OK;
}

HRESULT CD3DManager::PostReset()
{
	/*
	re-initialize all UNMANAGED [D3DPOOL_DEFAULT]
	textures, vertex buffers, and other volitile 
	resources
	...
	m_pD3Ddev->CreateTexture(..., ..., &m_pD3Dtexture);
	*/
	return S_OK;
}

HRESULT CD3DManager::Release()
{
	/*
	Release all textures, vertex buffers, and 
	other resources
	...
	_SAFE_RELEASE(m_pD3Dtexture);
	*/
	return S_OK;
}

//-----------------------------------------------------------------------------
VOID recoil()
{

	

}

VOID aim()
{
	mouse_event( MOUSEEVENTF_MOVE, 1, 1, 0, 0);
	static float ystand = 0.0f;
//	static int shotpass = 0;

	IDirect3DDevice9 *m_pD3Ddev = m_pd;

	int cond = pPlayerManager->pGetPlayersConnected();
		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();

		if(!pCVar->Settings.AimFPass)
		{
			CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( pCVar->Settings.ATarg ); 
			if(pPlayer != NULL && pPlayer->Spawned == 0 && locPlayer->Team != pPlayer->Team && pPlayer->Info->PlayerInfo->Health != 0 && pPlayer->Info->PlayerInfo->Health->Health > 0.0f )
			{
				D3DXVECTOR3 coords;

				if(pCVar->Settings.AHead && !pCVar->Settings.KAim)
				{

					coords.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._31 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._21 * pCVar->Settings.cy);
					coords.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._32 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._22 * pCVar->Settings.cy);
					coords.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._33 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._23 * pCVar->Settings.cy);
				}
				else
				{
					coords.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._31 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._21 * pCVar->Settings.cy);
					coords.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._32 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._22 * pCVar->Settings.cy);
					coords.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._33 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._23 * pCVar->Settings.cy);
				}

				dav[3] = dav[2]; dav[2] = dav[1]; dav[1] = dav[0]; dav[0] = coords - pCVar->Settings.ALastCoords;
				pCVar->Settings.ADelta = (dav[0] + dav[1] + dav[2] + dav[3]) / 4.0f;

				if( pCVar->Settings.APing && locPlayer->Ping > 0 )
				{
					float modif = pCVar->Settings.fps / (1000 / locPlayer->Ping) ;
					pCVar->Settings.ADelta = pCVar->Settings.ADelta * modif;
				}

					pCVar->Settings.ALastCoords = coords;

					if(pCVar->Settings.APing) coords += pCVar->Settings.ADelta;
				//	coords += pCVar->Settings.ADelta;

					if(pCVar->Settings.APred > 0 )
						coords += (pCVar->Settings.ADelta * pCVar->Settings.APred);				

				//	coords += pCVar->Settings.ADelta;

					if(pCVar->Settings.AHead && !pCVar->Settings.KAim)
					{
						if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y -= 0.09f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.46f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 0 )//??????
							coords.y += 0.46f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.09f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 1.23f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 0.73f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y += 0.61f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y += 1.11f;
					}
					else
					{
						if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y -= 0.26f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.70f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 0 )//??????
							coords.y += 0.20f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.26f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 1.23f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 0.73f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y += 0.80f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y += 0.43f;
					}

					D3DXVECTOR3 sorc, angles, up, newaim;
					sorc.x = locPlayer->Info->PlayerInfo->Matrix._41;
					sorc.y = locPlayer->Info->PlayerInfo->Matrix._42;
					sorc.z = locPlayer->Info->PlayerInfo->Matrix._43;

					up.x = 0.0f;
					up.y = 1.0f;
					up.z = 0.0f;
					D3DXMATRIX aim ;

					D3DXMatrixLookAtLH(&aim, &sorc, &coords, &up);

					D3DXMATRIX View = world[1];
					D3DVECTOR Angles;

					float hyp = sqrtf(View._33 * View._33 );
					Angles.x = atan2f( View._13, View._33 ) * 180 / M_PI;
					float sp=-View._23;

					if (sp<=-1.0f) Angles.y=-1.570796f;   //-pi/2
					else if (sp>=1.0f) Angles.y=1.570796f;   //pi/2
					else Angles.y=asin(sp);

					Angles.y = Angles.y * 180 / M_PI;
					Angles.z = 0.0f;

					D3DVECTOR nm;
					float hyp1 = sqrtf(aim._33 * aim._33 );
					nm.x = atan2f( aim._13, aim._33 ) * 180 / M_PI;

					sp = 0.0f;
					sp=-aim._23;
					if (sp<=-1.0f) nm.y=-1.570796f;   //-pi/2
					else if (sp>=1.0f) nm.y=1.570796f;   //pi/2  
					else nm.y=asin(sp);

					nm.y = nm.y * 180 / M_PI;
					nm.z = 0.0f;
					
					newaim.x = (nm.x - Angles.x) ;
					newaim.y = (nm.y - Angles.y);
					newaim.z = 0.0f;

					if (newaim.x>180)  newaim.x-=360;
					if (newaim.x<-180) newaim.x+=360;

					float tmp;
					if(locPlayer->FOV != 0)
						tmp = pCVar->Settings.cfov / locPlayer->FOV;
					else tmp = 1.0f;

					newaim.x = newaim.x * (calx[3] * tmp) ;
					newaim.y = newaim.y * (caly[3] * tmp) ;

						pCVar->Settings.movX = (long)newaim.x;
						pCVar->Settings.movY = (long)newaim.y;

					if(pCVar->Settings.AFire)
					{
						 mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}

				} 
				else if(pCVar->Settings.ASwitch) pCVar->Settings.AimFPass = true;
			
		


		}///////////////////////////////@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@////////////////////////////////////
		else
		{
			int pc=0;
			float LastD = 0xFFFFFFFF;
			int pbuf[100];
			int NearestPlayer = -1;
			double LastDistance = 0xFFFFFFFF;

			for(int i = 0; i < 255; i++)
			{
				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( i ); 
				if(pPlayer != NULL && pPlayer->Spawned == 0 && locPlayer->Team != pPlayer->Team )
				{
					D3DXVECTOR3 vecScreen;
					if ( bWorldtoScreenx( m_pD3Ddev, pPlayer, locPlayer, &vecScreen , true) )
					{

						if(pPlayer->Info->PlayerInfo->Health != 0 && pPlayer->Info->PlayerInfo->Health->Health > 0.0f)
						{

							double DistX = fabs(vecScreen.x - ScreenCenterX);
							double DistY = fabs(vecScreen.y - ScreenCenterY);
							double DistDiag = sqrt(pow(DistX, 2) + pow(DistY, 2));

							if(pCVar->Settings.smartTarg)
							{
								float ang[3];
								ang[0] = locPlayer->Info->PlayerInfo->Matrix._41 - pPlayer->Info->PlayerInfo->Matrix._41;
								ang[1] = locPlayer->Info->PlayerInfo->Matrix._42 - pPlayer->Info->PlayerInfo->Matrix._42;
								ang[2] = locPlayer->Info->PlayerInfo->Matrix._43 - pPlayer->Info->PlayerInfo->Matrix._43;
								float Distance = sqrt(ang[0] * ang[0] + ang[1] * ang[1] + ang[2] * ang[2]);
							
								float fRadius = ((( 300.0f * 90.0f ) / ( Distance * 90.0f)) / locPlayer->FOV) * 1.8f; 
								if(DistDiag < fRadius * modd)
								{
									if(Distance < LastD)
									{
										pc = i;
										LastD = Distance;
									}
								}							
							}
							if(DistDiag < LastDistance)
							{
								LastDistance = DistDiag;
								NearestPlayer = i;
								pCVar->Settings.ATarg = i;
							}
						}
					}
				}
			}
			if(NearestPlayer != -1)
			{
				if(pCVar->Settings.smartTarg && pc)	pCVar->Settings.ATarg = pc;

				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( pCVar->Settings.ATarg );
				pCVar->Settings.ALastCoords.x = pPlayer->Info->PlayerInfo->Matrix._41;
				pCVar->Settings.ALastCoords.y = pPlayer->Info->PlayerInfo->Matrix._42;
				pCVar->Settings.ALastCoords.z = pPlayer->Info->PlayerInfo->Matrix._43;
				dav[0].x = 0; dav[0].y = 0; dav[0].z = 0;
				dav[1] = dav[0]; dav[2] = dav[0]; dav[3] = dav[0];
				pCVar->Settings.AimFPass = false;

			}
		}
}


HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if( FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)) )
		return E_FAIL;
	
	WORD colour16 =	((WORD)((colour32>>28)&0xF)<<12)
			|(WORD)(((colour32>>20)&0xF)<<8)
			|(WORD)(((colour32>>12)&0xF)<<4)
			|(WORD)(((colour32>>4)&0xF)<<0);

	D3DLOCKED_RECT d3dlr;    
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for(int xy=0; xy < 8*8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}

VOID DrawX()
{

	D3DXVECTOR2 a[2];

	pLine->SetWidth( 1.0 ); 
    pLine->SetAntialias( true );    
    pLine->SetGLLines( true );    

	a[0].x = ScreenCenterX - 15;
	a[0].y = ScreenCenterY;
	a[1].x = ScreenCenterX + 15;
	a[1].y = ScreenCenterY;

	pLine->Begin( );
	pLine->Draw( a, 2, D3DCOLOR_XRGB( 255, 0, 0 ) );
	pLine->End( );

	a[0].x = ScreenCenterX - 1;
	a[0].y = ScreenCenterY - 15;
	a[1].x = ScreenCenterX - 1;
	a[1].y = ScreenCenterY + 15;

	pLine->Begin( );
	pLine->Draw( a, 2, D3DCOLOR_XRGB( 255, 0, 0 ) );
	pLine->End( );
}

HRESULT APIENTRY hkIDirect3DDevice9::BeginScene() 
{
	

	
		

	
/*	if(GetAsyncKeyState(VK_F1)&1)
	{
		setCommander();
	}

	if(GetAsyncKeyState(VK_F2)&1)
	{
		setCommanderoff();
	}*/


	pMenu->MenuSelection();

	frst = true;

	static bool fsst = false;
	if(!fsst)
	{

		g_pRender = new CD3DRender(128);	
		g_pD3Dfont = new CD3DFont("Verdana", 8, FCR_BOLD);
		g_rD3Dfont = new CD3DFont("Verdana", 8, FCR_BOLD);

		g_tD3Dfont = new CD3DFont("Verdana", 6, FCR_BOLD);

		
			D3DXCreateLine( m_pD3Ddev, &pLine );


			
		
	

		

		D3DXCreateFont(m_pD3Ddev, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("arial"), &m_font );

		fsst = true;
	}


	if (!bInitD3D) 
	{

		GenerateTexture(m_pD3Ddev, &texTeamA,    D3DCOLOR_ARGB(255,0,0,255)); 
		GenerateTexture(m_pD3Ddev, &texTeamB,    D3DCOLOR_ARGB(255,255,0,0)); 
		GenerateTexture(m_pD3Ddev, &texWeapon,    D3DCOLOR_ARGB(255,0,255,0)); 
		GenerateTexture(m_pD3Ddev, &texWhite,    D3DCOLOR_ARGB(255,255,255,255)); 
		GenerateTexture(m_pD3Ddev, &dblue,    D3DCOLOR_ARGB(255,0,191,255)); 
		GenerateTexture(m_pD3Ddev, &yellow,    D3DCOLOR_ARGB(255,255,255,0)); 
		GenerateTexture(m_pD3Ddev, &pink,    D3DCOLOR_ARGB(255,255,20,147)); 
		
		bInitD3D = true; 
	}





	return m_pD3Ddev->BeginScene();
}

HRESULT APIENTRY hkIDirect3DDevice9::QueryInterface(REFIID riid, LPVOID *ppvObj) 
{
	return m_pD3Ddev->QueryInterface(riid, ppvObj);
}

ULONG APIENTRY hkIDirect3DDevice9::AddRef() 
{
	m_refCount++;
	return m_pD3Ddev->AddRef();
}



HRESULT APIENTRY hkIDirect3DDevice9::BeginStateBlock() 
{
	return m_pD3Ddev->BeginStateBlock();
}

HRESULT APIENTRY hkIDirect3DDevice9::Clear(DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) 
{
	return m_pD3Ddev->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT APIENTRY hkIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect, D3DCOLOR color) 
{	
	return m_pD3Ddev->ColorFill(pSurface,pRect,color);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **ppSwapChain) 
{
	return m_pD3Ddev->CreateAdditionalSwapChain(pPresentationParameters, ppSwapChain);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) 
{
	return m_pD3Ddev->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture,pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	return m_pD3Ddev->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality,Discard,ppSurface, pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) 
{
	if( ( Usage & D3DUSAGE_WRITEONLY ) == D3DUSAGE_WRITEONLY )
		Usage -= D3DUSAGE_WRITEONLY; 
	return m_pD3Ddev->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer,pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	return m_pD3Ddev->CreateOffscreenPlainSurface(Width,Height,Format,Pool,ppSurface,pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) 
{
	return m_pD3Ddev->CreatePixelShader(pFunction, ppShader);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) 
{
	return m_pD3Ddev->CreateQuery(Type,ppQuery);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	return m_pD3Ddev->CreateRenderTarget(Width, Height, Format, MultiSample,MultisampleQuality, Lockable, ppSurface,pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) 
{
	return m_pD3Ddev->CreateStateBlock(Type, ppSB);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) 
{
	if( ( Usage & D3DUSAGE_WRITEONLY ) == D3DUSAGE_WRITEONLY )
		Usage -= D3DUSAGE_WRITEONLY; 

	HRESULT ret = m_pD3Ddev->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

#ifdef D3DHOOK_TEXTURES
	if(ret == D3D_OK)
	{
		hkIDirect3DTexture9 *pD3D9Tex = new hkIDirect3DTexture9(ppTexture, this, Width, Height, Format); 

		pD3D9Tex->pD3DTexture9 = *ppTexture;
		*ppTexture = ( IDirect3DTexture9* )pD3D9Tex;
	}
#endif

	return ret;
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) 
{
	if( ( Usage & D3DUSAGE_WRITEONLY ) == D3DUSAGE_WRITEONLY )
		Usage -= D3DUSAGE_WRITEONLY; 
	return m_pD3Ddev->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer,pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) 
{
	return m_pD3Ddev->CreateVertexDeclaration(pVertexElements,ppDecl);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) 
{

	return m_pD3Ddev->CreateVertexShader(pFunction, ppShader);
}

HRESULT APIENTRY hkIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle) 
{
	return m_pD3Ddev->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture,pSharedHandle);
}

HRESULT APIENTRY hkIDirect3DDevice9::DeletePatch(UINT Handle) 
{
	return m_pD3Ddev->DeletePatch(Handle);
}

HRESULT APIENTRY hkIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
//	m_pD3Ddev->SetTexture(0, texWeapon);

	#ifdef crc
	unsigned int i = 0;

	if(GetAsyncKeyState(VK_ADD)&1) 
	{
		//mod++;
		strd++;
		colstr = true;
	}
	if(GetAsyncKeyState(VK_SUBTRACT)&1)
	{
		//mod--;
		strd--;
		colstr = true;
	}
	if(GetAsyncKeyState(VK_NUMPAD0)&1)
	{
	//	add_log("Mod: %i", mod);
		if(colstr == true)
			colstr = false;
		else
			colstr = true;
	}
	if(colstr)
	{
		if(m_Stride == strd)
			for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i,texTeamA); 
	}

	
	if(m_Stride == strd && !colstr)
	{
		
		if (next)
		{
			if(pCurrTex->m_CrC32 != 0)
			{
				if(pCurrTex->m_CrC32 > 0x1000)
				{
					next = false;
					for(i = 0; i < ctr; i++)
					{
						if( list[i] == pCurrTex->m_CrC32)
						{
							next = true;
						}
					}
					for(i = 0; i < pctr; i++)
					{
						if( pass[i] == pCurrTex->m_CrC32)
						{
							next = true;
						}
					}
					if(!next)
					{
						/*if(pCurrTex->m_CrC32 == 0xFFFFFFFF)
						{
							Typ = Type;
							Base = BaseVertexIndex;
							Min =  MinVertexIndex;
							Num =  NumVertices;
							start = startIndex;
							prim = primCount;
							
						}////*/
						
						curtex = pCurrTex->m_CrC32;
					}
				}
			}
		}


		if(GetAsyncKeyState(VK_NUMPAD1)&1)	
		{
			
			if(pCurrTex->m_CrC32 != 0)
			{
				if(pCurrTex->m_CrC32 > 0x1000)
				{
					for(i = 0; i < ctr; i++)
					{
						if( list[i] == pCurrTex->m_CrC32)
						{
							next = true;
						}
					}
					for(i = 0; i < pctr; i++)
					{
						if( pass[i] == pCurrTex->m_CrC32)
						{
							next = true;
						}
					}

					if(!next)
					{
						/*if(pCurrTex->m_CrC32 == 0xFFFFFFFF)
						{
							Typ = Type;
							Base = BaseVertexIndex;
							Min =  MinVertexIndex;
							Num =  NumVertices;
							start = startIndex;
							prim = primCount;
							
						}///*/
						
						curtex = pCurrTex->m_CrC32;
					}
				}
				else
					next = true;
			}
			else
				next = true;
		}
		if(GetAsyncKeyState(VK_NUMPAD2)&1)	
		{
			//////////////////////////////////////////////////////////////
			pass[pctr] = curtex;
			pctr++;
			//pass2[ps] = rec;
			//ps++;
		}
		if(GetAsyncKeyState(VK_NUMPAD4)&1)
		{	
			int a = 0;
			for(i = 0; i < ctr; i++)
			{
				if(list[i] == curtex)
					a = 4;
			}
			if(a != 4)
			{
				list[ctr] = curtex;
				list1[ctr1] = curtex;
				ctr++;
				ctr1++;
			}
			else
				a = 0;
		}
		if(GetAsyncKeyState(VK_NUMPAD5)&1)
		{	
			int a = 0;
			for(i = 0; i < ctr; i++)
			{
				if(list[i] == curtex)
					a = 4;
			}
			if(a != 4)
			{
				list[ctr] = curtex;
				list2[ctr2] = curtex;
				ctr++;
				ctr2++;
			}
			else
				a = 0;
		}
		if(GetAsyncKeyState(VK_NUMPAD6)&1)
		{	
			int a = 0;
			for(i = 0; i < ctr; i++)
			{
				if(list[i] == curtex)
					a = 4;
			}
			if(a != 4)
			{
				list[ctr] = curtex;
				lists[ctrs] = curtex;
				ctr++;
				ctrs++;
			}
			else
				a = 0;
		}
		
		if(GetAsyncKeyState(VK_NUMPAD7)&1)
		{
			int a = 0;
			for(i = 0; i < ctr; i++)
			{
				if(list[i] == curtex)
					a = 4;
			}
			if(a != 4)
			{
				list[ctr] = curtex;
				lista[ctra] = curtex;
				ctr++;
				ctra++;
			}
			else
				a = 0;
		}

		if(GetAsyncKeyState(VK_NUMPAD8)&1)
		{
			int a = 0;
			for(i = 0; i < ctr; i++)
			{
				if(list[i] == curtex)
					a = 4;
			}
			if(a != 4)
			{
				list[ctr] = curtex;
				listb[ctrb] = curtex;
				ctr++;
				ctrb++;
			}
			else
				a = 0;
		}
		if(GetAsyncKeyState(VK_NUMPAD9)&1)
		{	
			int a = 0;
			for(i = 0; i < ctr; i++)
			{
				if(list[i] == curtex)
					a = 4;
			}
			if(a != 4)
			{
				list[ctr] = curtex;
				listg[ctrg] = curtex;
				ctr++;
				ctrg++;
			}
			else
				a = 0;
		}
		/*if(GetAsyncKeyState(VK_NUMPAD9)&1)
		{
			
				add_log("Player Helmit Middle: %f %f %f", playerA[0].ObjectMiddle[0].x, playerA[0].ObjectMiddle[0].y, playerA[0].ObjectMiddle[0].z);  
			
		}
		/*if(GetAsyncKeyState(VK_UP)&1)
		{
			
				add_log("Player Standing Middle: %f %f %f", playerA[0].ObjectMiddle[0].x, playerA[0].ObjectMiddle[0].y, playerA[0].ObjectMiddle[0].z);  
			
		}
		if(GetAsyncKeyState(VK_DOWN)&1)
		{
			
				add_log("Player Prone Middle: %f %f %f", playerA[0].ObjectMiddle[0].x, playerA[0].ObjectMiddle[0].y, playerA[0].ObjectMiddle[0].z);  
			
		}
		if(GetAsyncKeyState(VK_RIGHT)&1)
		{
			
				add_log("Player Crouched Middle: %f %f %f", playerA[0].ObjectMiddle[0].x, playerA[0].ObjectMiddle[0].y, playerA[0].ObjectMiddle[0].z);  
			
		}
		if(GetAsyncKeyState(VK_LEFT)&1)
		{
			
				add_log("Player Dead Middle: %f %f %f", playerA[0].ObjectMiddle[0].x, playerA[0].ObjectMiddle[0].y, playerA[0].ObjectMiddle[0].z);  
			
		}/*/
		
		/*if(pCurrTex->m_CrC32 == 0xFFFFFFFF)
		{
			if(next1)
			{
				next1 = false;
				rec.Typ = Type;
				rec.Base = BaseVertexIndex;
				rec.Min =  MinVertexIndex;
				rec.Num =  NumVertices;
				rec.start = startIndex;
				rec.prim = primCount;
				for(i = 0; i < ps; i++)
				{
					if(rec.start == pass2[i].start && rec.prim == pass2[i].prim && rec.Num == pass2[i].Num && rec.Min == pass2[i].Min) 
						next1 = true;
				}
			}


			if(rec.Typ == Type && rec.Base == BaseVertexIndex && rec.Min == MinVertexIndex && rec.Num == NumVertices && rec.start == startIndex && rec.prim == primCount)
			{
				DWORD dwOldZEnable = D3DZB_TRUE;

				m_pD3Ddev->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);
				m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //disable the Z buffer (wallhack)
				m_pD3Ddev->SetTexture(0, pink);
				m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);
			}
			for(i = 0; i < ia; i++ )
			{
				if(recA[i].Typ == Type && recA[i].Base == BaseVertexIndex && recA[i].Min == MinVertexIndex && recA[i].Num == NumVertices && recA[i].start == startIndex && recA[i].prim == primCount)
				{
					DWORD dwOldZEnable = D3DZB_TRUE;

					m_pD3Ddev->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //disable the Z buffer (wallhack)
					m_pD3Ddev->SetTexture(0, dblue);
					m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);
				}
			}
			for(i = 0; i < ib; i++ )
			{
				if(recB[i].Typ == Type && recB[i].Base == BaseVertexIndex && recB[i].Min == MinVertexIndex && recB[i].Num == NumVertices && recB[i].start == startIndex && recB[i].prim == primCount)
				{
					DWORD dwOldZEnable = D3DZB_TRUE;

					m_pD3Ddev->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //disable the Z buffer (wallhack)
					m_pD3Ddev->SetTexture(0, yellow);
					m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);
				}
			}

*
		}//////////////////*/

		
		if(curtex == pCurrTex->m_CrC32)
		{
			/*IDirect3DIndexBuffer9 *pIndexData = NULL;
		IDirect3DVertexBuffer9 *pStreamData = NULL;
		WORD *pIndex;
		BYTE *pData;
		UINT stride;
		UINT offset;
		
		m_pD3Ddev->GetStreamSource(0, &pStreamData, &offset,  &stride);
		m_pD3Ddev->GetIndices(&pIndexData);

		if(pIndexData->Lock(0, 0, (void**)&pIndex, D3DLOCK_READONLY) == D3D_OK)
		{
			if(pStreamData->Lock(0, 0, (void**)&pData, D3DLOCK_READONLY) == D3D_OK)
			{
				pData += BaseVertexIndex + MinVertexIndex;
				vertc *pTemp = (vertc*)pIndex[startIndex];

				D3DVECTOR high, low;

				high.x = ((D3DVECTOR*)(pTemp))->x;
				high.y = ((D3DVECTOR*)(pTemp))->y;
				high.z = ((D3DVECTOR*)(pTemp))->z;
				low = high;
				for(unsigned int i = 1; i < NumVertices; i++)
				{
					/*D3DVECTOR *pVector = (D3DVECTOR*)pTemp;
					if (pTemp->x < low.x)low.x = pTemp->x;
					if (pTemp->x > high.x)high.x = pTemp->x;
					if (pTemp->y < low.y)low.y = pTemp->y;
					if (pTemp->y > high.y)high.y = pTemp->y;
					if (pTemp->z < low.z)low.z = pTemp->z;
					if (pTemp->z > high.z)high.z = pTemp->z;

					pTemp++;	

					D3DVECTOR *pVector = (D3DVECTOR*)pTemp;
						if (pVector->x < low.x)
							low.x = pVector->x;
						if (pVector->x > high.x)
							high.x = pVector->x;
						if (pVector->y < low.y)
							low.y = pVector->y;
						if (pVector->y > high.y)
							high.y = pVector->y;
						if (pVector->z < low.z)
							low.z = pVector->z;
						if (pVector->z > high.z)
							high.z = pVector->z;
						pTemp++;
				}
				add_log("...  Low: %f %f %f  High: %f %f %f", low.x, low.y, low.z, high.x, high.y, high.z);

			}
			pStreamData->Unlock();
			pIndexData->Unlock();
		}

		pStreamData->Release();
		pIndexData->Release();//////*/

			DWORD dwOldZEnable = D3DZB_TRUE;

			m_pD3Ddev->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);
			m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //disable the Z buffer (wallhack)
			for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texWeapon); // colour model green
			m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
			m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable); //re-enable Z buffer
			//return m_pD3Ddev->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			
		}
		for(i = 0; i < ctra; i++)
		{
			if(lista[i] == pCurrTex->m_CrC32)
			{
				for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texTeamA);
			}
		}
		for(i = 0; i < ctrb; i++)
		{
			if(listb[i] == pCurrTex->m_CrC32)
			{
				for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texTeamB);
			}
		}
		for(i = 0; i < ctr1; i++)
		{
			if(list1[i] == pCurrTex->m_CrC32)
			{
				for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, dblue);
			}
		}
		for(i = 0; i < ctr2; i++)
		{
			if(list2[i] == pCurrTex->m_CrC32)
			{
				for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, yellow);
			}
		}
		for(i = 0; i < ctrs; i++)
		{
			if(lists[i] == pCurrTex->m_CrC32)
			{
				for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texWhite);
			}
		}
		for(i = 0; i < ctrg; i++)
		{
			if(listg[i] == pCurrTex->m_CrC32)
			{
				for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, pink);
			}
		}
	}
	if(GetAsyncKeyState(VK_F1)&1)
	{
		for(i = 0; i < ctra; i++)
		{
			add_log("|| Allies == 0x%X", lista[i]);
		}
		for(i = 0; i < ctrb; i++)
		{
			add_log("|| Axsis == 0x%X", listb[i]);
		}
		for(i = 0; i < ctr1; i++)
		{
			add_log("|| VehA == 0x%X", list1[i]);
		}
		for(i = 0; i < ctr2; i++)
		{
			add_log("|| VehB == 0x%X", list2[i]);
		}
		for(i = 0; i < ctrs; i++)
		{
			add_log("|| Scope == 0x%X", lists[i]);
		}
		for(i = 0; i < ctrg; i++)
		{
			add_log("|| Greb == 0x%X", listg[i]);
		}
		/*for(i = 0; i < ia; i++)
		{
			add_log("A startindex == 0x%x ||", recA[i].Num);
		}
		for(i = 0; i < ib; i++)
		{
			add_log("B startindex == 0x%x ||", recB[i].Num);
		}/////////////////////////////////////////*/
	}
	if(GetAsyncKeyState(VK_F2)&1)
	{
		add_log("Allies Head: 0x%X", curtex);
	}
	if(GetAsyncKeyState(VK_F3)&1)
	{
		add_log("Axis Head: 0x%X", curtex);
	}
	if(GetAsyncKeyState(VK_F5)&1)
	{
		add_log("Other: 0x%X", curtex);
	}
	/*if(GetAsyncKeyState(VK_NUMPAD5)&1)
	{
		m_pD3Ddev->SetTransform(D3DTS_VIEW, &lview2);
		
	}
	if(GetAsyncKeyState(VK_F9)&1)
	{
		recA[ia] = rec;
		pass2[ps] = rec;
		ia++;
		ps++;
	}
	if(GetAsyncKeyState(VK_F10)&1)
	{
		recB[ib] = rec;
		pass2[ps] = rec;
		ib++;
		ps++;
	}*/

#endif

	if(pCVar->Settings.bNoGrass && m_Stride==24 && pCurrTex->m_CrC32==0xB2715A2C)
	{
		return D3D_OK;
	}
	if(pCVar->Settings.bShell && m_Stride==24 && pCurrTex->m_CrC32==0x0)
	{
		return D3D_OK;
	}
	if(pCVar->Settings.bSky && m_Stride==32)
	{
		return D3D_OK;
	}
	
	if(pCVar->Settings.bNoScope && m_Stride==24 && (pCurrTex->m_CrC32==0x81ED57B7 || 
		pCurrTex->m_CrC32==0x58A99E5C || 
		pCurrTex->m_CrC32==0x4DBF25A0 || 
		pCurrTex->m_CrC32==0xF4894F40 || 
		pCurrTex->m_CrC32==0xF989BC58 || 

		pCurrTex->m_CrC32==0x4DBF25A0 || 
		pCurrTex->m_CrC32==0xF4894F40 || 
		pCurrTex->m_CrC32==0xF989BC58 || 

		pCurrTex->m_CrC32==0x8700E969))
	{
		return D3D_OK;
	}
	if(pCVar->Settings.bNoFlare && m_Stride==48)
	{
		return D3D_OK;
	}
	if(pCVar->Settings.bAsus && m_Stride==16)
	{

	/*	DWORD old1,  old2,  old3;

		m_pD3Ddev->GetRenderState( D3DRS_SRCBLEND, &old1);
		m_pD3Ddev->GetRenderState( D3DRS_DESTBLEND, &old2 );
		m_pD3Ddev->GetRenderState( D3DRS_ALPHABLENDENABLE, &old3 );*/


		m_pD3Ddev->SetRenderState( D3DRS_SRCBLEND, 0x5 );
		m_pD3Ddev->SetRenderState( D3DRS_DESTBLEND, 0x2 );
		m_pD3Ddev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	//	HRESULT ret = m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

	/*	m_pD3Ddev->SetRenderState( D3DRS_SRCBLEND, old1);
		m_pD3Ddev->SetRenderState( D3DRS_DESTBLEND, old2 );
		m_pD3Ddev->SetRenderState( D3DRS_ALPHABLENDENABLE, old3 );

		return ret;*/


	}
	if(pCVar->Settings.bWireframe && m_Stride==16)
	{
		DWORD owire;
		m_pD3Ddev->GetRenderState( D3DRS_FILLMODE, &owire );
		m_pD3Ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		HRESULT ret = m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

		m_pD3Ddev->SetRenderState( D3DRS_FILLMODE, owire );
		return ret;
	}
	if(pCVar->Settings.bWhiteWalls && m_Stride==16)
	{
		for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texWhite);
	}
	if(pCVar->Settings.bNoFog)
	{
		m_pD3Ddev->SetRenderState( D3DRS_FOGENABLE , false );
	}


	if(m_Stride==52)
	{
		if(pCurrTex->m_CrC32 != 0)
		{
			if(	pCurrTex->m_CrC32 == 0xE4757707 ||
				pCurrTex->m_CrC32 == 0xF37B733 ||
				pCurrTex->m_CrC32 == 0x882B2794 ||
				pCurrTex->m_CrC32 == 0xF2E7190C ||
				pCurrTex->m_CrC32 == 0x3E8B7EC1 ||

				pCurrTex->m_CrC32 == 0xFA9277A4 ||
				pCurrTex->m_CrC32 == 0xCE7DDFF0 ||
				pCurrTex->m_CrC32 == 0xE7DA3972 ||
				pCurrTex->m_CrC32 == 0x4618CB7 ||

				pCurrTex->m_CrC32 == 0x7A2B5933)
			{
				DWORD dwOldZEnable = D3DZB_TRUE;

				if(pCVar->Settings.bChams)
				{
					
					m_pD3Ddev->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //disable the Z buffer (wallhack)
					for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, dblue); // colour model green
					m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable); //re-enable Z buffer
					m_pD3Ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
					for(i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texTeamA);

					return m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

				}
				if(pCVar->Settings.bXQZWH)
				{
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
					m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);
					return m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				}
			}
			if(	pCurrTex->m_CrC32 == 0xAE4FA253 ||
				pCurrTex->m_CrC32 == 0x984AD799 ||
				pCurrTex->m_CrC32 == 0xFE183041 ||
				pCurrTex->m_CrC32 == 0x5BAB2F7C ||
				pCurrTex->m_CrC32 == 0xD8DB421B ||
				pCurrTex->m_CrC32 == 0xB3507CF3 ||

				pCurrTex->m_CrC32 == 0xED26D815 ||
				pCurrTex->m_CrC32 == 0x58AA0FE4 ||
				pCurrTex->m_CrC32 == 0x62E4F33A||
				pCurrTex->m_CrC32 == 0xD8EFD059 ||

				pCurrTex->m_CrC32 == 0x52D758D9)
			{
				DWORD dwOldZEnable = D3DZB_TRUE;

				if(pCVar->Settings.bChams)
				{
					m_pD3Ddev->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //disable the Z buffer (wallhack)
					for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i, yellow); // colour model green
					m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable); //re-enable Z buffer
					m_pD3Ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
					for(i=0; i<10; i++)m_pD3Ddev->SetTexture(i, texTeamB);

					return m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

				}
				if(pCVar->Settings.bXQZWH)
				{
					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
					m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );

					m_pD3Ddev->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);
					return m_pD3Ddev->DrawIndexedPrimitive( Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
				}
			}
		}
	}

	return m_pD3Ddev->DrawIndexedPrimitive(Type,BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinIndex, UINT NumVertices, UINT PrimitiveCount, CONST void *pIndexData, D3DFORMAT IndexDataFormat, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) 
{	
	return m_pD3Ddev->DrawIndexedPrimitiveUP(PrimitiveType, MinIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}
int ix=0;
HRESULT APIENTRY hkIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) 
{
	
	if(GetAsyncKeyState(VK_F8)&1) ix++;
	if(pCVar->Settings.bSmoke && m_Stride==64)
	{
		return D3D_OK;
	}
	
	if(colstr)
	{
		if(m_Stride == strd)
			for(int i=0; i<10; i++)m_pD3Ddev->SetTexture(i,texTeamB); 
	}

	if(pCVar->Settings.bNoFlare && m_Stride==48)
	{
		return D3D_OK;
	}
int i=0;
	if(m_Stride == strd && !colstr)
	{
		
		if (next1)
		{
			if(pCurrTex->m_CrC32 != 0)
			{
				if(pCurrTex->m_CrC32 > 0x1000)
				{
					next1 = false;
					for(i = 0; i < ctr; i++)
					{
						if( list[i] == pCurrTex->m_CrC32)
						{
							next1 = true;
						}
					}
					for(i = 0; i < pctr; i++)
					{
						if( pass[i] == pCurrTex->m_CrC32)
						{
							next1 = true;
						}
					}
					if(!next1)
					{
						/*if(pCurrTex->m_CrC32 == 0xFFFFFFFF)
						{
							Typ = Type;
							Base = BaseVertexIndex;
							Min =  MinVertexIndex;
							Num =  NumVertices;
							start = startIndex;
							prim = primCount;
							
						}/////*/
						
						curtex = pCurrTex->m_CrC32;
					}
				}
			}
		}


		if(GetAsyncKeyState(VK_NUMPAD3)&1)	
		{
			
			if(pCurrTex->m_CrC32 != 0)
			{
				if(pCurrTex->m_CrC32 > 0x0000)
				{
					for(i = 0; i < ctr; i++)
					{
						if( list[i] == pCurrTex->m_CrC32)
						{
							next1 = true;
						}
					}
					for(i = 0; i < pctr; i++)
					{
						if( pass[i] == pCurrTex->m_CrC32)
						{
							next1 = true;
						}
					}

					if(!next)
					{
						/*if(pCurrTex->m_CrC32 == 0xFFFFFFFF)
						{
							Typ = Type;
							Base = BaseVertexIndex;
							Min =  MinVertexIndex;
							Num =  NumVertices;
							start = startIndex;
							prim = primCount;
							
						}///////*/
						
						curtex = pCurrTex->m_CrC32;
					}
				}
				else
					next1 = true;
			}
			else
				next1 = true;
		}
		if(curtex == pCurrTex->m_CrC32)
		m_pD3Ddev->SetTexture(ix, texWeapon);
	}




	return m_pD3Ddev->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride) 
{
	return m_pD3Ddev->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT APIENTRY hkIDirect3DDevice9::DrawRectPatch(UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo) 
{
	return m_pD3Ddev->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}
int devp=0;
HRESULT APIENTRY hkIDirect3DDevice9::DrawTriPatch(UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo)
{
	return m_pD3Ddev->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

extern DWORD team1pts;
extern DWORD team2pts;
float lstpos = 0;
char logbuf[256];
//extern bool crtsshit;
int clpass = 0;
int refpass=0;

HRESULT APIENTRY hkIDirect3DDevice9::EndScene()
{
	_asm pushad;

	/*if(GetAsyncKeyState(VK_F7))
	{
		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
		//if(!lstpos) lstpos = locPlayer->Info->PlayerInfo->Matrix._42;
		float fltmp = locPlayer->Info->PlayerInfo->Matrix._42 - lstpos;
		if(pCVar->Settings.fps && lstpos)
			fltmp = (1000 / pCVar->Settings.fps) / fltmp; 

		lstpos = locPlayer->Info->PlayerInfo->Matrix._42;
		
		add_log("Fall Speed: %f", fltmp);
		PrintText(m_font,300, 40, 0xFF, 0xFF, 0xFF, 0xFF, "Fall Speed: %f", fltmp) ;
	}
	if(GetAsyncKeyState(VK_F8))
	{
		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
		//if(!lstpos) lstpos = locPlayer->Info->PlayerInfo->Matrix._42;
		float fltmp = locPlayer->Info->PlayerInfo->Matrix._42 - lstpos;
		if(pCVar->Settings.fps && lstpos)
			fltmp = (1000 / pCVar->Settings.fps) / fltmp; 

		lstpos = locPlayer->Info->PlayerInfo->Matrix._42;
		
		add_log("Fall Speed 22222222222222: %f", fltmp);
		PrintText(m_font,300, 40, 0xFF, 0xFF, 0xFF, 0xFF, "Fall Speed 22222222: %f", fltmp) ;
	}*/



	static float cy = 0.0f;
	static float ystand = 0.46f;
	static float cx = 0.0f;
	static float cz = 0.06f;

	static bool kup = true;
		static bool ksel = false;

	static bool keyd = false;
	static bool stopfr = false;
	static bool tptsnullcv = false;
	static bool oldfake = false;

	if(!cleanpass){
		/*if(team1pts == 0 || team2pts == 0)
		{
			if(!tptsnullcv)
			{
				tptsnullcv = true;
				oldfake = fake;
				fake = false;
				pMenu->DisableESP();
				memcpy(pCVtmp, pCVar, sizeof(CCVAR));
				memcpy(pCVar, pCVnull, sizeof(CCVAR));
			}
			_asm popad;
			return m_pD3Ddev->EndScene();
		} else if(tptsnullcv)
		{
			tptsnullcv = false;			
			fake = oldfake;
			memcpy(pCVar, pCVtmp, sizeof(CCVAR));
		}*/



	if(pCVar->Settings.recon && !pCVar->Settings.Aim && GetAsyncKeyState(VK_LBUTTON) != 0)
	{
		pCVar->Settings.recoil = true;
		if(pCVar->Settings.recfpas)
		{
			pCVar->Settings.recfpas = false;
			D3DXMATRIX View = world[1];
			D3DVECTOR Angles;

			float hyp = sqrtf(View._33 * View._33 );

			Angles.x = atan2f( View._13, View._33 ) * 180 / M_PI;

				
					 //Extract pitch from m23, adjust for domain errors
			 float sp=-View._23;
			 if (sp<=-1.0f)
			 {
				Angles.y=-1.570796f;   //-pi/2
			  } 
			  else if (sp>=1.0f)
			 {
				Angles.y=1.570796f;   //pi/2
			  }  
			  else
			  {
				Angles.y=asin(sp);
			  }
				  Angles.y = Angles.y * 180 / M_PI;
					
				Angles.z = 0.0f;
				pCVar->Settings.recvec = Angles;
		}
	} else if(pCVar->Settings.recoil)
	{
		pCVar->Settings.recoil = false;
		pCVar->Settings.recfpas = true;
		
	}

	if( pCVar->Settings.ZoomIn ) 
	{
		switch(pCVar->Settings.zkey)
		{
		case 1:
			if(pCVar->Settings.zclick)
			{
				if(GetAsyncKeyState(VK_RBUTTON)&1)
					if(pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = false;
						ZoomOut();
					}else
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}
			}else
			{
				if(GetAsyncKeyState(VK_RBUTTON))
				{
					if(!pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}

				}else if(pCVar->Settings.zoomed)
				{
					pCVar->Settings.zoomed = false;
					ZoomIn();
				}
			}
		case 2:
			if(pCVar->Settings.zclick)
			{
				if(GetAsyncKeyState(VK_MBUTTON)&1)
					if(pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = false;
						ZoomOut();
					}else
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}
			}else
			{
				if(GetAsyncKeyState(VK_MBUTTON))
				{
					if(!pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}

				}else if(pCVar->Settings.zoomed)
				{
					pCVar->Settings.zoomed = false;
					ZoomOut();
				}
			}
			break;
		case 3:
			if(pCVar->Settings.zclick)
			{
				if(GetAsyncKeyState(VK_LSHIFT)&1 || GetAsyncKeyState(VK_RSHIFT)&1)
					if(pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = false;
						ZoomOut();
					}else
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}
			}else
			{
				if(GetAsyncKeyState(VK_MBUTTON))
				{
					if(!pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}

				}else if(pCVar->Settings.zoomed)
				{
					pCVar->Settings.zoomed = false;
					ZoomOut();
				}
			}
			break;
		case 4:
			if(pCVar->Settings.zclick)
			{
				if(GetAsyncKeyState(VK_MBUTTON)&1)
					if(pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = false;
						ZoomOut();
					}else
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}
			}else
			{
				if(GetAsyncKeyState(VK_MBUTTON))
				{
					if(!pCVar->Settings.zoomed)
					{
						pCVar->Settings.zoomed = true;
						ZoomIn();
					}

				}else if(pCVar->Settings.zoomed)
				{
					pCVar->Settings.zoomed = false;
					ZoomOut();
				}
			}
			break;
		}
			

	}




	switch(pCVar->Settings.AKey)
	{
	case 1:
		if(GetAsyncKeyState(VK_MBUTTON) != 0)
			{
				pCVar->Settings.Aim = true;
				pCVar->Settings.stopm = true;
			}
			else 
			{
				if(pCVar->Settings.Aim == true){
					if(!pCVar->Settings.KAim){
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
					pCVar->Settings.Aim = false;
					kup = true;
					ksel = false;
					pCVar->Settings.KAim = false;
					pCVar->Settings.AimFPass = true; }
					pCVar->Settings.stopm = false;
			}
			break;
	case 2:
		if(GetAsyncKeyState(VK_LBUTTON) != 0)
			{
				pCVar->Settings.Aim = true;
				pCVar->Settings.stopm = true;
			}
			else 
			{
				if(pCVar->Settings.Aim == true){
					if(!pCVar->Settings.KAim){
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
					pCVar->Settings.Aim = false;
					kup = true;
					ksel = false;
					pCVar->Settings.KAim = false;
					pCVar->Settings.AimFPass = true; }
					pCVar->Settings.stopm = false;
			}
			break;
	case 3:
		if(GetAsyncKeyState(VK_RBUTTON) != 0)
			{
				pCVar->Settings.Aim = true;
				pCVar->Settings.stopm = true;
			}
			else 
			{
				if(pCVar->Settings.Aim == true){
					if(!pCVar->Settings.KAim){
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
					pCVar->Settings.Aim = false;
					kup = true;
					ksel = false;
					pCVar->Settings.KAim = false;
					pCVar->Settings.AimFPass = true; }
					pCVar->Settings.stopm = false;
			}
			break;
	}
	
	m_pd = m_pD3Ddev;
	static bool tmpon=false;
	if(GetAsyncKeyState(VK_F12)&1)
	{
		if(!tmpon)
		{
			tmpon = true;
			memcpy(pCVtmp, pCVar, sizeof(CCVAR));
			memcpy(pCVar, pCVnull, sizeof(CCVAR));
		} else 
		{
			tmpon = false;
			memcpy(pCVar, pCVtmp, sizeof(CCVAR));
		}
	}
		
		//if(GetAsyncKeyState(VK_F7)&1)
		//{
		//	BYTE vk = (char)MapVirtualKey(49, 0);
		//	keybd_event(49, vk, 0, 0);
		//}

		//if(GetAsyncKeyState(VK_F9)&1)
	//	{
	//		BYTE vk = (char)MapVirtualKey(49, 0);
	//		keybd_event(49, vk, KEYEVENTF_KEYUP, 0);
	//	}

		


		/*if(GetAsyncKeyState(VK_F8) != 0)
		{
			if(kup)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				kup = false;
			} else
			{
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				kup = true;
			}
		}*/
	/*
static int selv=0;
static float mdv=1.5;
static float mdz=1.5;
static float mdx=1.5;
if(GetAsyncKeyState(VK_F3)&1){
	if(selv<6) selv++; 
	else selv = 0;
}

if(GetAsyncKeyState(VK_F4)&1)mdx -= 0.1;
if(GetAsyncKeyState(VK_F6)&1)mdx += 0.1;

if(GetAsyncKeyState(VK_F9)&1)mdv -= 0.1;
if(GetAsyncKeyState(VK_F10)&1)mdv += 0.1;

if(GetAsyncKeyState(VK_F7)&1)mdz -= 0.1;
if(GetAsyncKeyState(VK_F8)&1)mdz += 0.1;
*/

	/*	if(GetAsyncKeyState(VK_F10)&1){
			while(GetAsyncKeyState(VK_END) == 0){
			}
			TagsOn1();
		}*/


//	if(GetAsyncKeyState(VK_F9)&1){
//		DWORD reciv;
//		ReadProcessMemory(GetCurrentProcess(), (void*)0x24e0024, &reciv, 4, NULL); 
//		add_log("Class Manager: 0x%x", reciv);
//	}

/*	if(GetAsyncKeyState(VK_F9)&1)
		modd -= 0.05f;*/

	/*if(GetAsyncKeyState(VK_F10) != 0)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}

	//	ystand += 0.01f;

	

	if(GetAsyncKeyState(VK_F9) != 0)
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	/*if(GetAsyncKeyState(VK_F11)&1)
		cz += 0.01f;

	if(GetAsyncKeyState(VK_F12)&1)
		cz -= 0.01f;*/
	static bool pstm = false;
	static int cfr = 0;
	if(pstm)
	{
		if(cfr > 100)
		{
			cfr = 0;
			pstm = false;
		}
		else
		{
			cfr++;
			g_tD3Dfont->Print(ScreenCenterX, ScreenCenterY, 0xFF0000FF, "Screen Shot Cleaned!", FT_CENTER);
		}
	}


/*	if(pCVar->Settings.ssnote && crtsshit)
	{
		crtsshit = false;
		pstm = true;
	}*/
	if(pCVar->Settings.drTime)
	{
		struct tm * curtime;
		time_t current_time;


   		time( &current_time );
		curtime = localtime( &current_time );
    		
		sprintf( logbuf, "%02d:%02d:%02d ", curtime->tm_hour, curtime->tm_min, curtime->tm_sec );

		g_tD3Dfont->Print(5.0f, ScreenCenterY, 0xFF0000FF, logbuf, 0);
	}
	if(pCVar->Settings.drFPS)
	{
		sprintf( logbuf, "FPS: %f", pCVar->Settings.fps);
		g_tD3Dfont->Print(5.0f, ScreenCenterY+10.0f, 0xFF0000FF, logbuf, 0);
	}
	if(pCVar->Settings.drPing)
	{
		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
		if(locPlayer != NULL)
		{
			sprintf( logbuf, "Ping: %i", locPlayer->Ping);
			g_tD3Dfont->Print(5.0f, ScreenCenterY+20.0f, 0xFF0000FF, logbuf, 0);
		}
	}

	
static bool kdwn = false;
	
	if(kdwn){
		BYTE vk = (char)MapVirtualKey(49, 0);
		keybd_event(49, vk, KEYEVENTF_KEYUP, 0);
	//	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		kdwn = false; 
	}


	//if(GetAsyncKeyState(VK_F8)){
//	DWORD tpts[1];
//	tpts[1] = 0;
//	tpts[0] = 0;DWORD team1pts = 0;
//DWORD team2pts = 0;
//	TeamPts((DWORD*)&tpts);
//	PrintText(m_font,300, 40, 0xFF, 0xFF, 0xFF, 0xFF, "Team 1: %i Team 2: %i", team1pts, team2pts) ;
//	}
//	PrintText(m_font,300, 20, 0xFF, 0xFF, 0xFF, 0xFF, "Aim lock X Y: %f %f", pCVar->Settings.recvec.x, pCVar->Settings.recvec.y) ;
//	PrintText(m_font,300, 40, 0xFF, 0xFF, 0xFF, 0xFF, "Offset   X Y: %f %f", trec[0], trec[1]) ;


	//PrintText(m_font,300, 40, 0xFF, 0xFF, 0xFF, 0xFF, "Stand Y: %f", ystand) ;


/*

if(GetAsyncKeyState(VK_F5)&1)
{
	pCVar->Settings.nDir =! pCVar->Settings.nDir;
	pCVar->Settings.fDir =! pCVar->Settings.fDir;
	dESP = true;
	pCVar->Settings.smartTarg =! pCVar->Settings.smartTarg;
}


	PrintText(m_font,300, 40, 0xFF, 0xFF, 0xFF, 0xFF, "selv: %i mdv: %f", selv, mdv) ;
*/


	if(world != 0)
	{
		if(refpass < 250) refpass++;
		else
		{
			refpass=0;
			float tmpx=0;float tmpy=0;
			_asm{
				push ebx;
				mov eax, world;
				sub eax, 0x30;
				add eax, 4;
				mov ebx, [eax];
				mov tmpx, ebx;
				add eax, 4;
				mov ebx, [eax];
				mov tmpy, ebx;
				pop ebx;
			}
			if(tmpx != 0 && tmpy != 0)
			{
				ScreenCenterX = tmpx / 2.0f;
				ScreenCenterY = tmpy / 2.0f;
			}			
		}
	}

	if(!eInitD3D)
	{
		g_pRender->Initialize(m_pD3Ddev);
		g_pD3Dfont->Initialize(m_pD3Ddev);
		g_rD3Dfont->Initialize(m_pD3Ddev);
		g_tD3Dfont->Initialize(m_pD3Ddev);

		static bool initmenu = false;
		if(!initmenu)
		{
			

			pMenu->InitMenu();
			initmenu = true;
			
		}
		
		eInitD3D = true;
	}
	if(colstr)
	{
		PrintText(m_font,300, 20, 0xFF, 0xFF, 0xFF, 0xFF, "Stride: %i", strd) ;
	}

	if(pCVar->Settings.drawvec)
	{
		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();

		DWORD cond = pPlayerManager->pGetPlayersConnected();
		int health;
		if(locPlayer != NULL && cond > 1)
		{
			//if(GetAsyncKeyState(VK_F8)&1)
			//	locPlayer->Info->PlayerInfo->Stamina = 1.0f;



		//	PrintText(m_font,300, 20, 0xFF, 0xFF, 0xFF, 0xFF, "Local Player: 0x%x Ping: %i Position: %i Modify D: %f", locPlayer, locPlayer->Ping, locPlayer->Info->PlayerInfo->Stamina, cy) ;
		//	PrintText(m_font,300, 35, 0xFF, 0xFF, 0xFF, 0xFF, "View Port in DEG x: %f  y: %f  z: %f", viewprt.x,viewprt.y,viewprt.z) ;
		//	PrintText(m_font,300, 50, 0xFF, 0xFF, 0xFF, 0xFF, "Matrix World Pos XYZ: %f %f %f", locPlayer->ViewMatrix->Matrix._41,locPlayer->ViewMatrix->Matrix._42,locPlayer->ViewMatrix->Matrix._43) ;

			//bool sfty = false;
			for(int i = 0; i < 255; i++)
			{
				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( i ); 
				if(pPlayer != NULL && pPlayer->Spawned == 0 && pPlayer->Team != 0)
				{
					D3DXVECTOR3 vecScreen;

					D3DXVECTOR3 coords;

					
					coords.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._31 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._21 * pCVar->Settings.cy);
					coords.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._32 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._22 * pCVar->Settings.cy);
					coords.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * pCVar->Settings.cx) + (pPlayer->Info->PlayerInfo->Matrix._33 * pCVar->Settings.cz) + (pPlayer->Info->PlayerInfo->Matrix._23 * pCVar->Settings.cy);
					
					if(pCVar->Settings.AHead)
					{
						if( pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y -= 0.09f;
						else if(pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.46f;
						else if( pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 1.23f;
						//else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 2 )
						//	coords.y -= 0.73f;
						//else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 1 )
						//	coords.y += 0.61f;
						//else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
						//	coords.y += 1.11f;
					}
					else
					{
						if(pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y -= 0.26f;
						else if(pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.70f;
						else if( pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 1.23f;
					}
					coords.y += ystand;
					//locPlayer->Info->PlayerInfo->Matrix._42 

					if ( bWorldtoScreenx1( m_pD3Ddev, pPlayer, &coords, locPlayer, &vecScreen , true) )
					{

						if(pPlayer->Info->PlayerInfo->Health != 0 && pPlayer->Info->PlayerInfo->Health->Health > 0.0f)
						{
							DrawBox(vecScreen, pPlayer->Team, 0.5f);
						}
					}
					//locPlayer->Info->PlayerInfo->Matrix._42 -= ystand;
				}
			}
		}
	}




	if(dESP)
	{
		char szFormatString[100] = { 0 };
		char szFormatString2[100] = { 0 };

		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();

		DWORD cond = pPlayerManager->pGetPlayersConnected();
		int health;
		if(locPlayer != NULL && cond > 1)
		{
			//if(GetAsyncKeyState(VK_F8)&1)
			//	locPlayer->Info->PlayerInfo->Stamina = 1.0f;



		//	PrintText(m_font,300, 20, 0xFF, 0xFF, 0xFF, 0xFF, "Local Player: 0x%x Ping: %i Position: %i Modify D: %f", locPlayer, locPlayer->Ping, locPlayer->Info->PlayerInfo->Stamina, cy) ;
		//	PrintText(m_font,300, 35, 0xFF, 0xFF, 0xFF, 0xFF, "View Port in DEG x: %f  y: %f  z: %f", viewprt.x,viewprt.y,viewprt.z) ;
		//	PrintText(m_font,300, 50, 0xFF, 0xFF, 0xFF, 0xFF, "Matrix World Pos XYZ: %f %f %f", locPlayer->ViewMatrix->Matrix._41,locPlayer->ViewMatrix->Matrix._42,locPlayer->ViewMatrix->Matrix._43) ;

			//bool sfty = false;
			for(int i = 0; i < 255; i++)
			{
				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( i );
				/*if(pPlayer != NULL)
				{
					D3DXVECTOR3 vecScreen;

				//	D3DXVECTOR3 wvec;
				//	wvec.x = pPlayer->Info->PlayerInfo->Matrix._41
					if ( bWorldtoScreenx12( m_pD3Ddev, pPlayer, locPlayer, &vecScreen , true ) )
					{
						sprintf( szFormatString2, "%i", i);
						g_tD3Dfont->Print(vecScreen.x, vecScreen.y , 0xFFFF0000, szFormatString2, FT_CENTER);
					}
				}*/


				

				if(pPlayer != NULL && pPlayer->Spawned == 0 && pPlayer->Team != 0)
				{
					D3DXVECTOR3 vecScreen;
					if ( bWorldtoScreenx( m_pD3Ddev, pPlayer, locPlayer, &vecScreen , true) )
					{

						if(pPlayer->Info->PlayerInfo->Health->Health > 0.0f)
						{

							double DistX = fabs(vecScreen.x - ScreenCenterX);
							double DistY = fabs(vecScreen.y - ScreenCenterY);
							double DistDiag = sqrt(pow(DistX, 2) + pow(DistY, 2));

							float ang[3];
							ang[0] = locPlayer->Info->PlayerInfo->Matrix._41 - pPlayer->Info->PlayerInfo->Matrix._41;
							ang[1] = locPlayer->Info->PlayerInfo->Matrix._42 - pPlayer->Info->PlayerInfo->Matrix._42;
							ang[2] = locPlayer->Info->PlayerInfo->Matrix._43 - pPlayer->Info->PlayerInfo->Matrix._43;
							float Distance = sqrt(ang[0] * ang[0] + ang[1] * ang[1] + ang[2] * ang[2]);

							if(Distance == 0.0f )
								Distance = 1.0f;

							if(Distance < 2.0f && pCVar->Settings.AKnife && pPlayer->Team != locPlayer->Team)
							{
								pCVar->Settings.Aim = true;
								pCVar->Settings.ATarg = i;
								pCVar->Settings.AimFPass = false ;
								/*if(!pCVar->Settings.KAim)*/ BYTE vk = (char)MapVirtualKey(49, 0);
								
								pCVar->Settings.ALastCoords.x = pPlayer->Info->PlayerInfo->Matrix._41;
								pCVar->Settings.ALastCoords.y = pPlayer->Info->PlayerInfo->Matrix._42;
								pCVar->Settings.ALastCoords.z = pPlayer->Info->PlayerInfo->Matrix._43;
								
								pCVar->Settings.KAim = true;
								
								if( !ksel)
								{
									ksel = true;
									kdwn = true;
									keybd_event(49, vk, 0, 0);
								}
								//keybd_event(49, vk, KEYEVENTF_KEYUP, 0);
							//	keyd = true;
							}// else if(pCVar->Settings.AKnife && keyd)
							//{
							//	pCVar->Settings.KAim = false;
							//	keyd = false;
							//	stopfr = true;
						//	}

D3DXVECTOR3 fwrd, sctmp;


						/*	switch(selv)
							{
							case 1:
								
									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * mdv);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);
									break;
							case 2:

									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._21 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._22 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._23 * mdv);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);
									break;
							case 3:

									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._31 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._32 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._33 * mdv);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);
									break;
							case 4:

									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * mdv);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);

									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._21 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._22 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._23 * mdv);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);

									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._31 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._32 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._33 * mdv);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);
									break;
								case 5:
									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._31 * mdz) + (pPlayer->Info->PlayerInfo->Matrix._11 * mdx) + (pPlayer->Info->PlayerInfo->Matrix._21 * mdv);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._32 * mdz) + (pPlayer->Info->PlayerInfo->Matrix._12 * mdx) + (pPlayer->Info->PlayerInfo->Matrix._22 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._33 * mdz) + (pPlayer->Info->PlayerInfo->Matrix._13 * mdx) + (pPlayer->Info->PlayerInfo->Matrix._23 * mdv);
									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);
									break;
								case 6:
									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._31 * mdx) + (pPlayer->Info->PlayerInfo->Matrix._11 * mdx);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._32 * mdv) + (pPlayer->Info->PlayerInfo->Matrix._12 * mdv);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._33 * mdz) + (pPlayer->Info->PlayerInfo->Matrix._13 * mdz);
									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);
									break;
							}*/




							if(locPlayer->FOV == 0.0f)
								locPlayer->FOV = 1.1f;

							float fRadius = ((( 300.0f * 90.0f ) / ( Distance * 90.0f)) / locPlayer->FOV) * 1.8f; 

							if(DistDiag < fRadius * modd)
							{
								health = (int)pPlayer->Info->PlayerInfo->Health->Health;

								if(pCVar->Settings.nName && pCVar->Settings.nClass){
									sprintf( szFormatString, "%s [%s]", pPlayer->Name , g_szClassList[ pPlayer->Kit ] );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								}
								else if(pCVar->Settings.nName ){
									sprintf( szFormatString, "%s", pPlayer->Name );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								}
								else if(pCVar->Settings.nClass ){
									sprintf( szFormatString, "[%s]", g_szClassList[ pPlayer->Kit ] );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								}

								if(pCVar->Settings.nHealth && pCVar->Settings.nAmmo){
									sprintf( szFormatString2, "%i%% Health  %i Ammo", health ,  pPlayer->Ammo );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
								}
								else if(pCVar->Settings.nHealth ){
									sprintf( szFormatString2, "%i%% Health", health);
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
								}
								else if(pCVar->Settings.nAmmo ){
									sprintf( szFormatString2, "%i Ammo", pPlayer->Ammo );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
								}

								if(pCVar->Settings.nBox)
								{
									if(pPlayer->Team == locPlayer->Team)
										DrawBox(vecScreen, 2, fRadius);
									else DrawBox(vecScreen, 1, fRadius);
								}
								/*if(pCVar->Settings.nDir)
								{
									D3DXVECTOR3 fwrd, sctmp;
									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * 25);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * 25);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * 25);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true);
									DrawBox(sctmp, pPlayer->Team, 0.5f);

									fwrd.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._21 * 25);
									fwrd.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._22 * 25);
									fwrd.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._23 * 25);

									bWorldtoScreenx1( m_pD3Ddev, pPlayer, &fwrd, locPlayer, &sctmp , true) ;
									DrawBox(sctmp, pPlayer->Team, 0.5f);
								}*/

									
								//g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								//g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
							}
							else
							{
								health = (int)pPlayer->Info->PlayerInfo->Health->Health;

								if(pCVar->Settings.fName && pCVar->Settings.fClass){
									sprintf( szFormatString, "%s [%s]", pPlayer->Name , g_szClassList[ pPlayer->Kit ] );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								}
								else if(pCVar->Settings.fName ){
									sprintf( szFormatString, "%s", pPlayer->Name );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								}
								else if(pCVar->Settings.fClass ){
									sprintf( szFormatString, "[%s]", g_szClassList[ pPlayer->Kit ] );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString, FT_CENTER);
								}

								if(pCVar->Settings.fHealth && pCVar->Settings.fAmmo){
									sprintf( szFormatString2, "%i%% Health  %i Ammo", health ,  pPlayer->Ammo );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
								}
								else if(pCVar->Settings.fHealth ){
									sprintf( szFormatString2, "%i%% Health", health);
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
								}
								else if(pCVar->Settings.fAmmo ){
									sprintf( szFormatString2, "%i Ammo", pPlayer->Ammo );
									g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xD0FF0000: 0xD00000FF, szFormatString2, FT_CENTER);
								}

								if(pCVar->Settings.fBox)
								{
									if(pPlayer->Team == locPlayer->Team)
										DrawBox(vecScreen, 2, fRadius);
									else DrawBox(vecScreen, 1, fRadius);
								}

								/*if(pCVar->Settings.fDir)
								{
								
								}*/

								
								//int ifRaidus = (int) fRadius;
								//fRadius = ifRaidus << 1; 
								//DrawBox(vecScreen, pPlayer->Team, fRadius);
							

								//	sprintf( szFormatString, "%s [%s]", pPlayer->Name , g_szClassList[ pPlayer->Kit ] );
								//if(vecScreen.z > 1.0)
								//	g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team == 1 )? 0xFFFFFF00: 0xFF00BFFF, szFormatString, FT_CENTER);
								//else
							//	g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team == 1 )? 0x66FF0000: 0x660000FF, szFormatString, FT_CENTER);
						
							}
						}
						else
						{
							
							/*	sprintf( szFormatString, "-DEAD-");
								
								//if(vecScreen.z > 1.0)
								//	g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team == 1 )? 0xFFFFFF00: 0xFF00BFFF, szFormatString, FT_CENTER);
								//else
								g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team == 1 )? 0x60FF0000: 0x660000FF, szFormatString, FT_CENTER);
								*/
						
								health = (long)pPlayer->Info->PlayerInfo->Health->Health;
								sprintf( szFormatString, "-DEAD- [%s]", g_szClassList[ pPlayer->Kit ] );
								sprintf( szFormatString2, "%i%% Health  %i Ammo", health ,  pPlayer->Ammo );
								//if(vecScreen.z > 1.0)
								//	g_tD3Dfont->Print(vecScreen.x, vecScreen.y, ( pPlayer->Team == 1 )? 0xFFFFFF00: 0xFF00BFFF, szFormatString, FT_CENTER);
								//else
								g_tD3Dfont->Print(vecScreen.x, vecScreen.y, (  pPlayer->Team != locPlayer->Team )? 0x60FF0000: 0x660000FF, szFormatString, FT_CENTER);
								g_tD3Dfont->Print(vecScreen.x, vecScreen.y + 8.0f, (  pPlayer->Team != locPlayer->Team )? 0x60FF0000: 0x660000FF, szFormatString2, FT_CENTER);
						}
					}
				}
			}
		}
	}

static DWORD ltick, ttick, dti, tc = 100;
static float fps, btw;

//	if(pCVar->Settings.APing)
//	{
		if(tc < 9)
		{
			tc++;
		}
		else
		{
			tc = 0;
			ttick = GetTickCount();
			//float cti = (float)ttick;
			dti = ttick - ltick;
			if(dti > 0)
			{
				//	btw =(float) 1000 / dti;
				btw =(float)dti / 10;
				//fps = btw * 10.0f;
				fps = 1000 / btw;
				pCVar->Settings.fps = fps;
			}
			ltick = ttick;
		}
//	}
		if(pCVar->Settings.bXhair)
		DrawX();

		pRadar->DrawRadar();


//	PrintText(m_font,300, 85, 0xFF, 0xFF, 0xFF, 0xFF, "X: %f Y: %f Z: %f", cx, cy, cz) ;
//
	//PrintText(m_font,300, 100, 0xFF, 0xFF, 0xFF, 0xFF, "FPS: %f", fps) ;






/*	if(pCVar->Settings.Aim)
	{
		int cond = pPlayerManager->pGetPlayersConnected();
		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();

		if(!pCVar->Settings.AimFPass)
		{
			/*CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( pCVar->Settings.ATarg ); 
			if(pPlayer != NULL && pPlayer->Spawned == 0 && locPlayer->Team != pPlayer->Team && pPlayer->Info->PlayerInfo->Health != 0 && pPlayer->Info->PlayerInfo->Health->Health > 0.0f )
			{
				D3DXVECTOR3 coords;

				if(pCVar->Settings.AHead)
				{

				coords.x = pPlayer->Info->PlayerInfo->Matrix._41 + (pPlayer->Info->PlayerInfo->Matrix._11 * cz) + (pPlayer->Info->PlayerInfo->Matrix._21 * cx);
				coords.y = pPlayer->Info->PlayerInfo->Matrix._42 + (pPlayer->Info->PlayerInfo->Matrix._12 * cz) + (pPlayer->Info->PlayerInfo->Matrix._22 * cx) + cy;
				coords.z = pPlayer->Info->PlayerInfo->Matrix._43 + (pPlayer->Info->PlayerInfo->Matrix._13 * cz) + (pPlayer->Info->PlayerInfo->Matrix._23 * cx);
				}
				else
				{
				coords.x = pPlayer->Info->PlayerInfo->Matrix._41;
				coords.y = pPlayer->Info->PlayerInfo->Matrix._42 + cy;
				coords.z = pPlayer->Info->PlayerInfo->Matrix._43;
				}
			

				pCVar->Settings.ADelta = coords -  pCVar->Settings.ALastCoords;

				D3DXVECTOR3 vecScreen;
			//	if ( bWorldtoScreenx( m_pD3Ddev, pPlayer, locPlayer, &vecScreen ) )
			//	{
					pCVar->Settings.ALastCoords = coords;

					coords += pCVar->Settings.ADelta;

					if(pCVar->Settings.APred > 0 )
						coords += (pCVar->Settings.ADelta * pCVar->Settings.APred);
					 


					if(pCVar->Settings.APing)
					{
						if(locPlayer->Ping > 0 )
						{
							float modif = fps / (1000 / locPlayer->Ping) ;
							pCVar->Settings.ADelta.x = pCVar->Settings.ADelta.x * modif;
							pCVar->Settings.ADelta.y = pCVar->Settings.ADelta.y * modif;
							pCVar->Settings.ADelta.z = pCVar->Settings.ADelta.z * modif;

							coords += pCVar->Settings.ADelta;
						}
					}

					
					coords += pCVar->Settings.ADelta;

					if(pCVar->Settings.AHead)
					{
						if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y -= 0.08f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.46f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 0 )//??????
							coords.y += 0.46f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.08f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 1.23f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 0.73f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y += 0.61f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y += 1.11f;
					}
					else
					{
						if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y -= 0.26f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.70f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 0 )//??????
							coords.y += 0.20f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 1 )
							coords.y -= 0.26f;
						else if(locPlayer->Info->PlayerInfo->Posture == 0 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 1.23f;
						else if(locPlayer->Info->PlayerInfo->Posture == 1 && pPlayer->Info->PlayerInfo->Posture == 2 )
							coords.y -= 0.73f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y += 0.80f;
						else if(locPlayer->Info->PlayerInfo->Posture == 2 && pPlayer->Info->PlayerInfo->Posture == 0 )
							coords.y += 0.43f;

					}

					

					D3DXVECTOR3 sorc, angles, up, newaim;
					sorc.x = locPlayer->Info->PlayerInfo->Matrix._41;
					sorc.y = locPlayer->Info->PlayerInfo->Matrix._42;
					sorc.z = locPlayer->Info->PlayerInfo->Matrix._43;

					up.x = 0.0f;
					up.y = 1.0f;
					up.z = 0.0f;
					D3DXMATRIX aim ;

					D3DXMatrixLookAtLH(&aim, &sorc, &coords, &up);



					D3DXMATRIX View = world[1];
					D3DVECTOR Angles;

					float hyp = sqrtf(View._33 * View._33 );

					Angles.x = atan2f( View._13, View._33 ) * 180 / M_PI;

				
					 //Extract pitch from m23, adjust for domain errors
					  float sp=-View._23;
					  if (sp<=-1.0f)
					  {
						Angles.y=-1.570796f;   //-pi/2
					  } 
					  else if (sp>=1.0f)
					 {
						Angles.y=1.570796f;   //pi/2
					  }  
					  else
					  {
						Angles.y=asin(sp);
					  }
					  Angles.y = Angles.y * 180 / M_PI;
					
					Angles.z = 0.0f;


				//	PrintText(m_font,300, 85, 0xFF, 0xFF, 0xFF, 0xFF, "ANGLE in DEG x: %f  y: %f  z: %f", ang[0], ang[1], ang[2]) ;


/*

			PrintText(m_font,300, 85, 0xFF, 0xFF, 0xFF, 0xFF, "ANGLE in DEG x: %f  y: %f  z: %f", dRotateX, dRotateY, dRotateZ) ;

//




//					PrintText(m_font,300, 50, 0xFF, 0xFF, 0xFF, 0xFF, "NM ANGLE in DEG x: %f  y: %f  z: %f", Angles.x, Angles.y, Angles.z) ;

					D3DVECTOR nm;

					float hyp1 = sqrtf(aim._33 * aim._33 );

					nm.x = atan2f( aim._13, aim._33 ) * 180 / M_PI;
					//nm.y = atan2f( aim._23, hyp1) * 180 / M_PI;

					sp = 0.0f;
					sp=-aim._23;
					  if (sp<=-1.0f)
					  {
						nm.y=-1.570796f;   //-pi/2
					  } 
					  else if (sp>=1.0f)
					 {
						nm.y=1.570796f;   //pi/2
					  }  
					  else
					  {
						nm.y=asin(sp);
					  }
					  nm.y = nm.y * 180 / M_PI;

					nm.z = 0.0f;
					
					newaim.x = nm.x - Angles.x;
					newaim.y = nm.y - Angles.y;
					newaim.z = 0.0f;

					

					
					/*dst[0] = coords.x;
					dst[1] = coords.y;
					dst[2] = coords.z;

					CalcAngle(sorc, dst, angles);//

				//	PrintText(m_font,300, 65, 0xFF, 0xFF, 0xFF, 0xFF, "NM ANGLE in DEG x: %f  y: %f  z: %f  XAngle: %f YAngle: %f", newaim.x,newaim.y,newaim.z, locPlayer->Info->PlayerInfo->XAngle, locPlayer->Info->PlayerInfo->YAngle) ;
				
					if (newaim.x>180)  newaim.x-=360;
					if (newaim.x<-180) newaim.x+=360;

//	if(GetAsyncKeyState(VK_F9) != 0)
//					{
					locPlayer->Info->PlayerInfo->XAngle += newaim.x;
					locPlayer->Info->PlayerInfo->YAngle += newaim.y;
//					}
	
	//SetCursorPos(vecScreen.x, vecScreen.y);
				//} else
				//	pCVar->Settings.AimFPass = true;

					if(pCVar->Settings.AFire)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}

			} else
				if(pCVar->Settings.ASwitch)
					pCVar->Settings.AimFPass = true;
////
		} else
		{
			int NearestPlayer = -1;
			double LastDistance = 0xFFFFFFFF;
			for(int i = 0; i < 255; i++)
			{
				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( i ); 
				if(pPlayer != NULL && pPlayer->Spawned == 0 && locPlayer->Team != pPlayer->Team )
				{
					D3DXVECTOR3 vecScreen;
					if ( bWorldtoScreenx( m_pD3Ddev, pPlayer, locPlayer, &vecScreen ) )
					{

						if(pPlayer->Info->PlayerInfo->Health != 0 && pPlayer->Info->PlayerInfo->Health->Health > 0.0f)
						{

							double DistX = fabs(vecScreen.x - ScreenCenterX);
							double DistY = fabs(vecScreen.y - ScreenCenterY);
							double DistDiag = sqrt(pow(DistX, 2) + pow(DistY, 2));

							//float ang[3];
							//ang[0] = locPlayer->Info->PlayerInfo->Matrix._41 - pPlayer->Info->PlayerInfo->Matrix._41;
							//ang[1] = locPlayer->Info->PlayerInfo->Matrix._42 - pPlayer->Info->PlayerInfo->Matrix._42;
							//ang[2] = locPlayer->Info->PlayerInfo->Matrix._43 - pPlayer->Info->PlayerInfo->Matrix._43;
							//float Distance = sqrt(ang[0] * ang[0] + ang[1] * ang[1] + ang[2] * ang[2]);

							if(DistDiag < LastDistance)
							{
								LastDistance = DistDiag;
								NearestPlayer = i;
								pCVar->Settings.ATarg = i;
								/*static bool intmaxang = false;
								if(!intmaxang)
								{
									float maxang = 360.0f;
									HANDLE hnd = GetCurrentProcess();
									DWORD maxadr;
									ReadProcessMemory(hnd, (void*) 0x9AE614, &maxadr, 4, 0);
									WriteProcessMemory(hnd, (void*) maxadr, &maxang, 4, 0);
									intmaxang = false;

									/*_asm
									{
										push eax;
										push ebx;
										mov eax, [0x9AE614];
										mov ebx, maxang;
										mov [eax], ebx;
										pop ebx;
										pop eax;
									}////
								//}
							}
						}
					}
				}
			}
			if(NearestPlayer != -1)
			{
				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( pCVar->Settings.ATarg );
				pCVar->Settings.AimFPass = false;
				pCVar->Settings.ALastCoords.x = pPlayer->Info->PlayerInfo->Matrix._41;
				pCVar->Settings.ALastCoords.y = pPlayer->Info->PlayerInfo->Matrix._42;
				pCVar->Settings.ALastCoords.z = pPlayer->Info->PlayerInfo->Matrix._43;

			}
		}
	}//*/

	pCVar->Settings.aimok = true;



/*	if(keyd)
	{
		if(kup)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				kup = false;
			} else
			{
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				kup = true;
			}
	}*/
	//	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

	pMenu->DrawMenu();


	} else
	{
		cleanpass = false;
		
	}



	_asm popad;


	return m_pD3Ddev->EndScene();
}

HRESULT APIENTRY hkIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB) 
{
	return m_pD3Ddev->EndStateBlock(ppSB);
}

HRESULT APIENTRY hkIDirect3DDevice9::EvictManagedResources() 
{
	return m_pD3Ddev->EvictManagedResources();
}

UINT APIENTRY hkIDirect3DDevice9::GetAvailableTextureMem() 
{
	return m_pD3Ddev->GetAvailableTextureMem();
}

HRESULT APIENTRY hkIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) 
{
	return m_pD3Ddev->GetBackBuffer(iSwapChain,iBackBuffer, Type, ppBackBuffer);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetClipPlane(DWORD Index, float *pPlane) 
{
	return m_pD3Ddev->GetClipPlane(Index, pPlane);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9 *pClipStatus) 
{
	return m_pD3Ddev->GetClipStatus(pClipStatus);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) 
{
	return m_pD3Ddev->GetCreationParameters(pParameters);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetCurrentTexturePalette(UINT *pPaletteNumber)
{
	return m_pD3Ddev->GetCurrentTexturePalette(pPaletteNumber);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9 **ppZStencilSurface) 
{
	return m_pD3Ddev->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetDeviceCaps(D3DCAPS9 *pCaps) 
{
	return m_pD3Ddev->GetDeviceCaps(pCaps);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetDirect3D(IDirect3D9 **ppD3D9) 
{
	HRESULT hRet = m_pD3Ddev->GetDirect3D(ppD3D9);
	if( SUCCEEDED(hRet) )
		*ppD3D9 = m_pD3Dint;
	return hRet;
}

HRESULT APIENTRY hkIDirect3DDevice9::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode) 
{
	return m_pD3Ddev->GetDisplayMode(iSwapChain,pMode);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface) 
{
	return m_pD3Ddev->GetFrontBufferData(iSwapChain,pDestSurface);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetFVF(DWORD* pFVF) 
{
	return m_pD3Ddev->GetFVF(pFVF);
}

void APIENTRY hkIDirect3DDevice9::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp) 
{
	m_pD3Ddev->GetGammaRamp(iSwapChain,pRamp);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData) 
{
	return m_pD3Ddev->GetIndices(ppIndexData);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetLight(DWORD Index, D3DLIGHT9 *pLight) 
{
	return m_pD3Ddev->GetLight(Index, pLight);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetLightEnable(DWORD Index, BOOL *pEnable) 
{
	return m_pD3Ddev->GetLightEnable(Index, pEnable);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetMaterial(D3DMATERIAL9 *pMaterial) 
{
	return m_pD3Ddev->GetMaterial(pMaterial);
}

float APIENTRY hkIDirect3DDevice9::GetNPatchMode() 
{
	return m_pD3Ddev->GetNPatchMode();
}

unsigned int APIENTRY hkIDirect3DDevice9::GetNumberOfSwapChains() 
{
	return m_pD3Ddev->GetNumberOfSwapChains();
}

HRESULT APIENTRY hkIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries)
{
	return m_pD3Ddev->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader) 
{
	return m_pD3Ddev->GetPixelShader(ppShader);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) 
{
	return m_pD3Ddev->GetPixelShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) 
{
	return m_pD3Ddev->GetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
	return m_pD3Ddev->GetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) 
{
	return m_pD3Ddev->GetRasterStatus(iSwapChain,pRasterStatus);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue) 
{
	return m_pD3Ddev->GetRenderState(State, pValue);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) 
{
	return m_pD3Ddev->GetRenderTarget(RenderTargetIndex,ppRenderTarget);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) 
{
	return m_pD3Ddev->GetRenderTargetData(pRenderTarget,pDestSurface);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) 
{
	return m_pD3Ddev->GetSamplerState(Sampler,Type,pValue);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetScissorRect(RECT* pRect) 
{
	return m_pD3Ddev->GetScissorRect(pRect);
}

BOOL APIENTRY hkIDirect3DDevice9::GetSoftwareVertexProcessing() 
{
	return m_pD3Ddev->GetSoftwareVertexProcessing();
}

HRESULT APIENTRY hkIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride) 
{
	return m_pD3Ddev->GetStreamSource(StreamNumber, ppStreamData,OffsetInBytes, pStride);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber,UINT* Divider) 
{
	return m_pD3Ddev->GetStreamSourceFreq(StreamNumber,Divider);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{
	return m_pD3Ddev->GetSwapChain(iSwapChain,pSwapChain);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetTexture(DWORD Stage, IDirect3DBaseTexture9 **ppTexture) 
{
	return m_pD3Ddev->GetTexture(Stage, ppTexture);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue) 
{
	return m_pD3Ddev->GetTextureStageState(Stage, Type, pValue);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix) 
{
	return m_pD3Ddev->GetTransform(State, pMatrix);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) 
{
	return m_pD3Ddev->GetVertexDeclaration(ppDecl);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader) 
{
	return m_pD3Ddev->GetVertexShader(ppShader);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
	return m_pD3Ddev->GetVertexShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) 
{
	return m_pD3Ddev->GetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
	return m_pD3Ddev->GetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::GetViewport(D3DVIEWPORT9 *pViewport) 
{
	return m_pD3Ddev->GetViewport(pViewport);
}

HRESULT APIENTRY hkIDirect3DDevice9::LightEnable(DWORD LightIndex, BOOL bEnable) 
{
	return m_pD3Ddev->LightEnable(LightIndex, bEnable);
}

HRESULT APIENTRY hkIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix) 
{
	return m_pD3Ddev->MultiplyTransform(State, pMatrix);
}

HRESULT APIENTRY hkIDirect3DDevice9::Present(CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion) 
{	
	return m_pD3Ddev->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT APIENTRY hkIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) 
{
	return m_pD3Ddev->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer,pVertexDecl, Flags);
}

ULONG APIENTRY hkIDirect3DDevice9::Release() 
{
	//if( --m_refCount == 0 )
		m_pManager->Release();
		m_pD3Ddev->Release();
		//pFont->OnLostDevice();
		bInitD3D = false;
	return S_OK;
}

HRESULT APIENTRY hkIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS *pPresentationParameters) 
{
	
	
	m_pManager->PreReset();

	if(eInitD3D == true)
	{
pLine->OnLostDevice();
		g_pD3Dfont->Invalidate();
		g_rD3Dfont->Invalidate();
		g_tD3Dfont->Invalidate();
		g_pRender->Invalidate();

		
	}
	//m_font->OnLostDevice();

	HRESULT hRet = m_pD3Ddev->Reset(pPresentationParameters);
	

	if( SUCCEEDED(hRet) )
	{
		m_PresentParam = *pPresentationParameters;
		m_pManager->PostReset();
		if(eInitD3D == true)
	{
			eInitD3D = false;
		pLine->OnResetDevice();
		}
	//	m_font->OnResetDevice();
		bInitD3D = false;
	}

	return hRet;
}

HRESULT APIENTRY hkIDirect3DDevice9::SetClipPlane(DWORD Index, CONST float *pPlane) 
{
	return m_pD3Ddev->SetClipPlane(Index, pPlane);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9 *pClipStatus) 
{
	return m_pD3Ddev->SetClipStatus(pClipStatus);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber) 
{
	return m_pD3Ddev->SetCurrentTexturePalette(PaletteNumber);
}

void APIENTRY hkIDirect3DDevice9::SetCursorPosition(int X, int Y, DWORD Flags) 
{
	m_pD3Ddev->SetCursorPosition(X, Y, Flags);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap) 
{
	return m_pD3Ddev->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) 
{
	return m_pD3Ddev->SetDepthStencilSurface(pNewZStencil);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs) 
{
	return m_pD3Ddev->SetDialogBoxMode(bEnableDialogs);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetFVF(DWORD FVF) 
{
	return m_pD3Ddev->SetFVF(FVF);
}

void APIENTRY hkIDirect3DDevice9::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{
	m_pD3Ddev->SetGammaRamp(iSwapChain,Flags, pRamp);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData) 
{
	return m_pD3Ddev->SetIndices(pIndexData);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetLight(DWORD Index, CONST D3DLIGHT9 *pLight) 
{
	return m_pD3Ddev->SetLight(Index, pLight);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9 *pMaterial) 
{	
	return m_pD3Ddev->SetMaterial(pMaterial);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetNPatchMode(float nSegments) 
{	
	return m_pD3Ddev->SetNPatchMode(nSegments);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY *pEntries) 
{
	return m_pD3Ddev->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader) 
{
	return m_pD3Ddev->SetPixelShader(pShader);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) 
{
	return m_pD3Ddev->SetPixelShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) 
{
	return m_pD3Ddev->SetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) 
{
	return m_pD3Ddev->SetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) 
{
	return m_pD3Ddev->SetRenderState(State, Value);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) 
{
	return m_pD3Ddev->SetRenderTarget(RenderTargetIndex,pRenderTarget);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) 
{
	return m_pD3Ddev->SetSamplerState(Sampler,Type,Value);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetScissorRect(CONST RECT* pRect) 
{
	return m_pD3Ddev->SetScissorRect(pRect);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware) 
{
	return m_pD3Ddev->SetSoftwareVertexProcessing(bSoftware);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) 
{
	if( StreamNumber == 0 )
	m_Stride = Stride;
	return m_pD3Ddev->SetStreamSource(StreamNumber, pStreamData,OffsetInBytes, Stride);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber,UINT Divider)
{	
	return m_pD3Ddev->SetStreamSourceFreq(StreamNumber,Divider);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetTexture(DWORD Stage, IDirect3DBaseTexture9 *pTexture) 
{
#ifdef crc

	
	
#endif

//#ifdef D3DHOOK_TEXTURES
	try
	{
	IDirect3DDevice9 *dev = NULL;
	if(pTexture != NULL && ((hkIDirect3DTexture9*)(pTexture))->GetDevice(&dev) == D3D_OK)
	{
		if(dev == this)
		{
			hkIDirect3DTexture9 *pD3D9Tex = ( hkIDirect3DTexture9* )pTexture;
			pCurrTex = ( hkIDirect3DTexture9* )pTexture;

			if( pCurrTex->m_CrC32 == 0 )
				{
					D3DLOCKED_RECT dLockedRect;

					pCurrTex->LockRect( 0, &dLockedRect, NULL, D3DLOCK_NOOVERWRITE | D3DLOCK_READONLY );	

					PBYTE pData	= ( PBYTE )dLockedRect.pBits;

					switch( pCurrTex->m_Format )
					{
					case 21:
						pCurrTex->m_CrC32 = pCrC->GetCrc32( pData, 4 * pCurrTex->m_Width * pCurrTex->m_Height );
						break;
					case 22:
						pCurrTex->m_CrC32 = pCrC->GetCrc32( pData, 4 * pCurrTex->m_Width * pCurrTex->m_Height );
						break;
					case 894720068:
						pCurrTex->m_CrC32 = pCrC->GetCrc32( pData, 1 * pCurrTex->m_Width * pCurrTex->m_Height );
						break;
					default:
						pCurrTex->m_CrC32 = pCrC->GetCrc32( pData, 0.5 * pCurrTex->m_Width * pCurrTex->m_Height );
						break;
					}
					pCurrTex->UnlockRect( 0 );
				}
			//add_log("Format: %i Hight: %i Width: %i Crc: 0x%x", pCurrTex->m_Format, pCurrTex->m_Height, pCurrTex->m_Width, pCurrTex->m_CrC32);
			//pCurrTex = pD3D9CurrTex;

				return m_pD3Ddev->SetTexture( Stage, pD3D9Tex->pD3DTexture9 );
			
			
			
			
		//	return m_pD3Ddev->SetTexture(Stage, ((hkIDirect3DTexture9*)(pTexture))->m_D3Dtex);
		}
	}
	}
	catch( ... )
	{
		add_log( "Exception Caught in SetTexture!" );
	}
//#endif
	
	return m_pD3Ddev->SetTexture(Stage, pTexture);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) 
{
	return m_pD3Ddev->SetTextureStageState(Stage, Type, Value);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix) 
{

	return m_pD3Ddev->SetTransform(State, pMatrix);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) 
{
	return m_pD3Ddev->SetVertexDeclaration(pDecl);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader) 
{
	return m_pD3Ddev->SetVertexShader(pShader);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) 
{
	return m_pD3Ddev->SetVertexShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) 
{
	return m_pD3Ddev->SetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) 
{
	return m_pD3Ddev->SetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT APIENTRY hkIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9 *pViewport) 
{
	if( !IsBadReadPtr( pViewport, sizeof( D3DVIEWPORT9 ) ) ){

		//mview = *pViewport;
	//	 ScreenCenterX = ( float )pViewport->Width / 2;
	//	 ScreenCenterY = ( float )pViewport->Height / 2; 
			
		
   }   
	return m_pD3Ddev->SetViewport(pViewport);
}

BOOL APIENTRY hkIDirect3DDevice9::ShowCursor(BOOL bShow) 
{
	return m_pD3Ddev->ShowCursor(bShow);
}

HRESULT APIENTRY hkIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) 
{
	return m_pD3Ddev->StretchRect(pSourceSurface,pSourceRect,pDestSurface,pDestRect,Filter);
}

HRESULT APIENTRY hkIDirect3DDevice9::TestCooperativeLevel() 
{
	return m_pD3Ddev->TestCooperativeLevel();
}

HRESULT APIENTRY hkIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) 
{
	return m_pD3Ddev->UpdateSurface(pSourceSurface,pSourceRect,pDestinationSurface,pDestPoint);
}

HRESULT APIENTRY hkIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9 *pSourceTexture, IDirect3DBaseTexture9 *pDestinationTexture) 
{
	return m_pD3Ddev->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT APIENTRY hkIDirect3DDevice9::ValidateDevice(DWORD *pNumPasses) 
{
	return m_pD3Ddev->ValidateDevice(pNumPasses);
}
