#include <windows.h>
#include "d3d9.h"
#include "Zoom.h"
#include "CVAR.h"
#include "Hooks.h"

extern CCVAR			*pCVar;
extern CPlayerManager*	pPlayerManager;


VOID addZoom(void)
{
	CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
	if(locPlayer && locPlayer->FOV) locPlayer->FOV -= 0.1f;
}
VOID subZoom(void)
{
	CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
	if(locPlayer && locPlayer->FOV) locPlayer->FOV += 0.1f;
}
VOID ZoomIn(void)
{
	CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
	if(locPlayer && locPlayer->FOV) locPlayer->FOV = pCVar->Settings.zoomInFloat;
}
VOID ZoomOut(void)
{
	CPlayer *locPlayer = pPlayerManager->pGetLocalePlayer();
	if(locPlayer && locPlayer->FOV) locPlayer->FOV = 1.1f;
}

