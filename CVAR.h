#ifndef _CVAR_H
#define _CVAR_H

#include <windows.h>
#include "main.h"
#include "d3d9.h"

typedef struct
{
	bool bXQZWH;
	bool bSkinHack;
	bool bChams;
	bool bNoFlash;
	bool bNoSmoke;
	bool bNoFog;	
	bool bXhair;
	bool bWireframe;
	bool bAsus;
	bool bWhiteWalls;
	bool bDateAndTime;
	bool bNoGrass;
	bool bAccuracy;
	bool bNametags;
	bool bHealthTags;
	bool bVehOverlay;
	bool bMines;
	bool bMinimap;
	bool bScreenShake;
	bool bConsole;
	bool bBlur;
	bool b3DMap;
	bool bCommander;
	bool Dist;
	bool bKit;
	bool bRadar;
	bool bWall;
	bool bSky;
	bool bSmoke;
	bool bShell;
	bool bNoScope;
	bool bNoFlare;
	bool nName;
	bool nClass;
	bool nHealth;
	bool nAmmo;
	bool nBox;
	bool nDir;
	bool fName;
	bool fClass;
	bool fHealth;
	bool fAmmo;
	bool fBox;
	bool fDir;
	bool Aim; bool AimFPass; int ATarg; D3DXVECTOR3 ALastCoords; D3DXVECTOR3 ADelta;
	bool AHead;
	bool ASwitch;
	bool APing;
	int AKey;
	bool AFire;
	bool KAim;
	bool ASpeed;
	bool AKnife;
	int APred;
	float fps; float cfov;
	long camX; long camY; long movX; long movY; bool stopm; int intaim; bool aimok;
	float cy;
	float cx;
	float cz;
	bool drawvec;
	D3DVECTOR recvec;
	bool recoil;
	bool recon;	bool recfpas;
	float rfov;
	float zoomInFloat; bool ZoomIn; bool ZoomAdd; bool zoomed;
	bool css;
	bool ssnow;
	bool skipmenu;
	bool smartTarg;
	bool drTime; bool drFPS; bool drPing;
	bool ssnote;
	bool zclick;
	long ssec;
	bool Radar; bool rotateP; bool rotateRadar; bool radHealth;
	int zkey;
	DWORD comArtRdy;
}Cvar_t;


class CCVAR 
{
public:
	CCVAR( )
	{
		Settings.bXQZWH			= false;
		Settings.bSkinHack		= false;
		Settings.bChams			= false;
		Settings.bNoFlash		= false;
		Settings.bNoSmoke		= false;
		Settings.bNoFog			= false;
		Settings.bXhair			= false;
		Settings.bWireframe		= false;
		Settings.bAsus			= false;
		Settings.bWhiteWalls	= false;
		Settings.bDateAndTime	= false;
		Settings.bNoGrass		= false;
		Settings.bAccuracy		= false;
		Settings.bHealthTags	= false;
		Settings.bMines			= false;
		Settings.bVehOverlay	= false;
		Settings.bMinimap		= false;
		Settings.bScreenShake	= false;
		Settings.bNametags		= false;
		Settings.bConsole		= false;
		Settings.bBlur			= false;
		Settings.b3DMap			= false;
		Settings.bCommander		= false;
		Settings.Dist			= false;
		Settings.bKit			= false;
		Settings.bRadar			= false;
		Settings.bWall			= false;
		Settings.bSky			= false;
		Settings.bSmoke			= false;
		Settings.bShell			= false;
		Settings.bNoScope			= false;
		Settings.bNoFlare			= false;
		Settings.Aim			= false;
		Settings.AimFPass			= true;
		Settings.ATarg			= 0;
		Settings.nName			= false;
		Settings.nClass			= false;
		Settings.nHealth			= false;
		Settings.nAmmo			= false;
		Settings.nBox			= false;
		Settings.nDir			= false;
		Settings.fName			= false;
		Settings.fClass			= false;
		Settings.fHealth			= false;
		Settings.fAmmo			= false;
		Settings.fBox			= false;
		Settings.fDir			= false;
		Settings.AHead			= true;
		Settings.ASwitch			= false;
		Settings.APing			= false;
		Settings.AFire			= false;
		Settings.AKey			= 0;
		Settings.ASpeed			= false;
		Settings.KAim			= false;
		Settings.AKnife			= false;
		Settings.APred			= 0;
		Settings.camX			= 0;
		Settings.camY			= 0;
		Settings.movX			= 0;
		Settings.movY			= 0;
		Settings.cfov			= 0;
		Settings.intaim			= 0;
		Settings.stopm			= false;
		Settings.aimok			= false;
		Settings.drawvec			= false;
		Settings.fps			= 0;
		Settings.cy = 0.02f;
		Settings.cx = 0.05f;
		Settings.cz = 0.11f;
		Settings.recoil			= false;
		Settings.recon			= false;
		Settings.recfpas			= true;
		Settings.css			= false;
		Settings.ssnow			= false;
		Settings.skipmenu			= false;
		Settings.drTime			= false;
		Settings.drPing			= false;
		Settings.drFPS			= false;
		Settings.smartTarg			= false;
		Settings.ssnote			= false;
		Settings.zoomInFloat			= 0.7f;
		Settings.ZoomIn			= false;
		Settings.ZoomAdd		= false;
		Settings.zoomed		= false;
		Settings.zclick		= false;
		Settings.ssec			= 10000;
		Settings.zkey			= 0;
		Settings.comArtRdy		= 0;
		Settings.Radar=false; Settings.rotateP=false; Settings.rotateRadar=false;
		Settings.radHealth = false;
	}

	Cvar_t Settings;
};


#endif
