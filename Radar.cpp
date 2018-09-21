// Radar.cpp: implementation of the Radar class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h> 

#include "Radar.h"
#include "Hooks.h"
#include "CVAR.h"

extern CPlayerManager*	pPlayerManager;
extern CCVAR			*pCVar;
extern CD3DFont			*g_pD3Dfont;
extern CD3DFont			*g_rD3Dfont;
extern CD3DFont			*g_tD3Dfont;
extern CD3DRender		*g_pRender;

extern float ScreenCenterX;
extern float ScreenCenterY;
extern ID3DXLine *pLine;
extern D3DMATRIX *world;

D3DXVECTOR3 sall[100];
//D3DXVECTOR3 sax[50];
int hall[100];
int tall[100];
int allc=0;
//int axc=0;
char tstr[50];
bool Radar::DrawRadar()
{
	if(!pCVar->Settings.Radar) return false;
	if(ScreenCenterX && ScreenCenterY)
	{
		if(GetAsyncKeyState(VK_F7)&1) pCVar->Settings.rotateRadar = !pCVar->Settings.rotateRadar;
		
		allc=0;
		menx = 0.0f;meny = ScreenCenterY - (menh*0.5f);menw = 200.0f;menh = 200.0f;
		g_pRender->Begin(D3DPT_TRIANGLELIST);

		if(!pCVar->Settings.rotateRadar)
			g_rD3Dfont->Print(menx + (menw*0.5f), meny-11.0f, 0xFF000000, "N", FT_CENTER);

		D3DAddQuad(g_pRender, menx, meny, menw, menh, 0xD0000000);
		D3DAddQuad(g_pRender, menx, meny-1.0f, menw+1.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw, meny-1.0f, 1.0f, menh+1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx, meny+menh, menw+1.0f, 1.0f, 0xFF000000);
		

		CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();

		DWORD cond = pPlayerManager->pGetPlayersConnected();
		int health;
		if(locPlayer != NULL && cond > 1)
		{
			g_pRender->End();

			
		//	sprintf( tstr, "locPlayer: 0x%x", locPlayer );
		//	g_tD3Dfont->Print(ScreenCenterX, 15.0f, 0xFF000000, tstr, FT_CENTER);

			D3DXMATRIX View = world[1];

		//	worldCV.x = locPlayer->Info->PlayerInfo->Matrix._41;
		//	worldCV.y = locPlayer->Info->PlayerInfo->Matrix._43;

			worldCV.x = locPlayer->Info->PlayerInfo->Matrix._41;
			worldCV.y = locPlayer->Info->PlayerInfo->Matrix._43;

			screenCV.x = menx + (menw*0.5f);
			screenCV.y = meny + (menh*0.5f);

			D3DXVECTOR2 a[3];

			pLine->SetWidth( 1.0 ); 
			pLine->SetAntialias( true );    
			pLine->SetGLLines( true );    


				

				modr = sqrt((View._31 * 100.0f) * (View._31 * 100.0f) + (View._33 * 100.0f) * (View._33 * 100.0f)); 
				if(modr) modr = 100.0f / modr;
				else modr = 1.0f;

			if(!pCVar->Settings.rotateRadar)
			{
				a[0].x = screenCV.x-1.0f;
				a[0].y = screenCV.y-1.0f;
				a[1].x = screenCV.x - ((View._31 * 100.0f) * modr);
				a[1].y = screenCV.y - ((View._33 * 100.0f) * modr);
				pLine->Begin( );
				pLine->Draw( a, 2, D3DCOLOR_ARGB(255,255,20,147) );
				pLine->End( );
			} else
			{
				a[0].x = screenCV.x-1.0f;
				a[0].y = screenCV.y-1.0f;
				a[1].x = menx;
				a[1].y = meny;

				pLine->Begin( );
				pLine->Draw( a, 2, D3DCOLOR_ARGB(255,255,20,147) );
				pLine->End( );

				a[0].x = screenCV.x-1.0f;
				a[0].y = screenCV.y-1.0f;
				a[1].x = menx+menw;
				a[1].y = meny;

				pLine->Begin( );
				pLine->Draw( a, 2, D3DCOLOR_ARGB(255,255,20,147) );
				pLine->End( );
			}


			g_pRender->Begin(D3DPT_TRIANGLELIST);

			D3DAddQuad(g_pRender, menx + (menw*0.5f)-1.0f, meny, 1.0f, menh, 0xFF00FF00);
		D3DAddQuad(g_pRender, menx, meny + (menh*0.5f)-1.0f, menw, 1.0f, 0xFF00FF00);

			for(int i = 0; i < 255; i++)
			{
				CPlayer *pPlayer = pPlayerManager->pGetPlayerByIndex( i ); 
				if(pPlayer != NULL && pPlayer->Spawned == 0 && pPlayer->Team != 0)
				{
					if(pCVar->Settings.rotateRadar) 
					{
						curw.x = (pPlayer->Info->PlayerInfo->Matrix._41 * View._31) * modr;
						curw.y = (pPlayer->Info->PlayerInfo->Matrix._43 * View._33) * modr;
					} else
					{
						curw.x = pPlayer->Info->PlayerInfo->Matrix._41;
						curw.y = pPlayer->Info->PlayerInfo->Matrix._43;

					}

					if(WorldToMap())
					{
						if(pCVar->Settings.rotateP)
						{
							a[0].x = curs.x;
							a[0].y = curs.y;
							if(!pCVar->Settings.rotateRadar)
							{
								a[1].x = curs.x + (pPlayer->Info->PlayerInfo->Matrix._31 * 10.0f);
								a[1].y = curs.y - (pPlayer->Info->PlayerInfo->Matrix._33 * 10.0f);
							} else
							{
								a[1].x = curs.x + ((pPlayer->Info->PlayerInfo->Matrix._31 * View._31) * 10.0f);
								a[1].y = curs.y - ((pPlayer->Info->PlayerInfo->Matrix._33 * View._33) * 10.0f);
							}

							pLine->Begin( );
							pLine->Draw( a, 2, ( pPlayer->Team != locPlayer->Team  )? 0xFFFF0000: 0xFF0000FF);
							pLine->End( );
							
						}

						if(pCVar->Settings.radHealth && pPlayer->Info->PlayerInfo->Health)
						{
							tall[allc] = pPlayer->Team;
							hall[allc] = (int)pPlayer->Info->PlayerInfo->Health->Health;
						}

						D3DAddQuad(g_pRender, curs.x-3.0f, curs.y-3.0f, 7.0f, 8.0f, ( pPlayer->Team != locPlayer->Team  )? 0xFFFF0000: 0xFF0000FF);
						sall[allc] = curs;
						if(!strcmp(pPlayer->Info->PlayerInfo->Vehicle->VehicleName, "Soldier"))
							sall[allc].z = 1.0f;
						else sall[allc].z = 2.0f;
						allc++;

					}
				}
			}	
		}
	}
	g_pRender->End();
	if(allc)for(int i = 0; i < allc; i++)
	{
		if(sall[i].z == 1.0f)
		{
			g_tD3Dfont->Print(sall[i].x-2.0f,  sall[i].y-4.0f, 0xFF000000, "S", 0);
		}
		else
		{
			g_tD3Dfont->Print(sall[i].x-2.0f,  sall[i].y-4.0f, 0xFF000000, "V", 0);
		}
		if(pCVar->Settings.radHealth && hall[i])
		{
			CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
			sprintf( tstr, "%i", hall[i] );
			g_tD3Dfont->Print(sall[i].x, sall[i].y+5.0f, ( tall[i] != locPlayer->Team  )? 0xFFFF0000: 0xFF0000FF, tstr, FT_CENTER);
		}

	}
	return true;
}

bool Radar::WorldToMap()
{
	D3DXVECTOR3 tmp;
	long tmpf=0;

	tmp = curw - worldCV;

/*	if(pCVar->Settings.rotateRadar) 
	{
		D3DXMATRIX View = world[1];
		tmp.x = (tmp.x * View._31) * modr;
		tmp.y = (tmp.y * View._33) * modr;
	}*/

	if(tmp.x > 100.0f || tmp.y > 100.0f || tmp.x < -100.0f || tmp.y < -100.0f) return false;

	tmp.y = -tmp.y;
	tmp += screenCV;

	tmpf = (long)tmp.x;
	curs.x = (float)tmpf;
	tmpf = (long)tmp.y;
	curs.y = (float)tmpf;

	return true;

}
