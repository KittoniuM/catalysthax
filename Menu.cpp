#include <windows.h>
#include <stdio.h> 

#include "Menu.h"
#include "CVAR.h"
#include "d3d9dev.h"
#include "Hooks.h"
#include "Login.h"
//#include "AddLog.h"
#include "AmHttpSocket.h"
#include "MemHacks.h"

TCHAR szRoot[4] = "C:\\";


int userOrPass = 0;
//using namespace std;

extern CCVAR				*pCVar;
extern CD3DFont				*g_pD3Dfont;
extern CD3DFont				*g_rD3Dfont;
extern CD3DRender			*g_pRender;

extern float ScreenCenterX;
extern float ScreenCenterY;
extern bool dESP;

extern char szBuffer[100];
extern char szBuffer2[100];
extern char szBuffer4[100];
extern char szBuffer3[100];
extern char szBuffer5[100];
extern char szBuffer10[100];

float *faded = (float*)0x3F47A2C;
float viewMod;

D3DVECTOR vec;

LONG lRet;

LONG lRet1;


HKEY hkey;
HKEY hkey1;
DWORD dwFunc;



char szBuffer6[100];
extern int b1;
extern int b2;

float menx, meny, menw, menh;

bool Hookd = false;
bool auth = false;

CAmHttpSocket http;
char *s;
char *sb;
char waiting[15] = {"Waiting..."};

void CMenu::popmenu(void)
{
	sMenu->mEntry[7].bEnabled = pCVar->Settings.bXhair;
	sMenu->mEntry[8].bEnabled = pCVar->Settings.bCommander;
	///////////////////Main//////////////////////////////
	sTagsMenu->mTagsEntry[0].bTagsEnabled = pCVar->Settings.bNametags;
	sTagsMenu->mTagsEntry[1].bTagsEnabled = pCVar->Settings.b3DMap; 
	sTagsMenu->mTagsEntry[2].bTagsEnabled = pCVar->Settings.bHealthTags;
	sTagsMenu->mTagsEntry[3].bTagsEnabled = pCVar->Settings.Dist;
	sTagsMenu->mTagsEntry[4].bTagsEnabled =pCVar->Settings.bKit;
	sTagsMenu->mTagsEntry[5].bTagsEnabled =pCVar->Settings.bMines;
	sTagsMenu->mTagsEntry[6].bTagsEnabled =pCVar->Settings.bRadar;
		///////////////////Tags//////////////////////////////
	sViewMenu->mViewEntry[0].bViewEnabled = pCVar->Settings.bNoFog;
	///////////////////View//////////////////////////////
	sWallMenu->mWallEntry[0].bWallEnabled = pCVar->Settings.bChams; 
	sWallMenu->mWallEntry[1].bWallEnabled = pCVar->Settings.bXQZWH; 
	sWallMenu->mWallEntry[2].bWallEnabled = pCVar->Settings.bAsus; 
	sWallMenu->mWallEntry[3].bWallEnabled = pCVar->Settings.bWireframe; 
	sWallMenu->mWallEntry[4].bWallEnabled = pCVar->Settings.bWhiteWalls; 
		///////////////////Walls//////////////////////////////
	sRemMenu->mRemEntry[0].bRemEnabled = pCVar->Settings.recon;
		sRemMenu->mRemEntry[1].bRemEnabled = pCVar->Settings.bSky; 
		sRemMenu->mRemEntry[2].bRemEnabled = pCVar->Settings.bSmoke; 
		sRemMenu->mRemEntry[3].bRemEnabled = pCVar->Settings.bNoFlash; 
		sRemMenu->mRemEntry[4].bRemEnabled = pCVar->Settings.bNoScope; 
		sRemMenu->mRemEntry[5].bRemEnabled = pCVar->Settings.bNoFlare; 
		//sRemMenu->mRemEntry[6].bRemEnabled = pCVar->Settings.bNoFlare; 
		//sRemMenu->mRemEntry[7].bRemEnabled = pCVar->Settings.bNoGrass; 
	//	sRemMenu->mRemEntry[8].bRemEnabled = 
	//	sRemMenu->mRemEntry[9].bRemEnabled = 

		///////////////////Removals//////////////////////////////
	//	pCVar->Settings.intaim = 1;
		AimKey = pCVar->Settings.AKey;
		switch(pCVar->Settings.AKey)
		{
		case 0:
			MARK_NAME7( "Aim Key - None"		, 1		)
				break;
		case 1:
			MARK_NAME7( "Aim Key - Mouse Middle"		, 1		)
				break;
		case 2:
			MARK_NAME7( "Aim Key - Mouse Left"		, 1		)
				break;
		case 3:
			MARK_NAME7( "Aim Key - Mouse Right"		, 1		)
				break;
		}
		if(pCVar->Settings.AHead)
		{
			MARK_NAME7( "Aim Vec - Head"		, 2		)
			
		} else
		{
			MARK_NAME7( "Aim Vec - Chest"		, 2		)
			
		}
		sAimMenu->mAimEntry[3].bAimEnabled = pCVar->Settings.AFire;

		sAimMenu->mAimEntry[4].bAimEnabled = pCVar->Settings.ASwitch;
		sAimMenu->mAimEntry[5].bAimEnabled = pCVar->Settings.APing;
		sAimMenu->mAimEntry[8].bAimEnabled = pCVar->Settings.AKnife;
		sAimMenu->mAimEntry[9].bAimEnabled = pCVar->Settings.smartTarg;

		switch(pCVar->Settings.APred)
		{
		case 0:
			MARK_NAME7("Prediction - 0", 7);
			break;
		case 1:
			MARK_NAME7("Prediction - 1", 7);
			break;
		case 2:
			MARK_NAME7("Prediction - 2", 7);
			break;
		case 3:
			MARK_NAME7("Prediction - 3", 7);
			break;
		case 4:
			MARK_NAME7("Prediction - 4", 7);
			break;
		case 5:
			MARK_NAME7("Prediction - 5", 7);
			break;
		case 6:
			MARK_NAME7("Prediction - 6", 7);
			break;
		case 7:
			MARK_NAME7("Prediction - 7", 7);
			break;
		case 8:
			MARK_NAME7("Prediction - 8", 7);
			break;
		case 9:
			MARK_NAME7("Prediction - 9", 7);
			break;
		case 10:
			MARK_NAME7("Prediction - 10", 7);
			break;
		}
		///////////////////Aim//////////////////////////////

		sssMenu->mssEntry[0].bssEnabled = pCVar->Settings.css;


		switch(pCVar->Settings.ssec)
		{
		case 0:
			MARK_NAME10( "Update SS Interval: 0s"		, 1		)
			break;
		case 10000:
			MARK_NAME10( "Update SS Interval: 10s"		, 1		)
			break;
		case 30000:
			MARK_NAME10( "Update SS Interval: 30s"		, 1		)
			break;
		case 60000:
			MARK_NAME10( "Update SS Interval: 1m"		, 1		)
			break;
		case 300000:
			MARK_NAME10( "Update SS Interval: 5m"		, 1		)
			break;
		}
			sAMenu->mAEntry[3].bAEnabled = pCVar->Settings.ssnote ;
		sAMenu->mAEntry[0].bAEnabled = pCVar->Settings.drawvec;
		///////////////////Screen Shot//////////////////////////////
		sopMenu->mopEntry[8].bopEnabled = pCVar->Settings.drTime;
			sopMenu->mopEntry[9].bopEnabled = pCVar->Settings.drFPS;
			sopMenu->mopEntry[10].bopEnabled = pCVar->Settings.drPing;

			///////////////////Options//////////////////////////////
		//	sEspMenu->mEspEntry[0].bEspEnabled = pCVar->Settings.n
				sEspMenu->mEspEntry[2].bEspEnabled = pCVar->Settings.nName; 
				sEspMenu->mEspEntry[3].bEspEnabled = pCVar->Settings.nClass; 
				sEspMenu->mEspEntry[4].bEspEnabled = pCVar->Settings.nHealth; 
				sEspMenu->mEspEntry[5].bEspEnabled = pCVar->Settings.nAmmo; 
				sEspMenu->mEspEntry[6].bEspEnabled = pCVar->Settings.nBox; 
				sEspMenu->mEspEntry[8].bEspEnabled = pCVar->Settings.fName; 
				sEspMenu->mEspEntry[9].bEspEnabled = pCVar->Settings.fClass; 
				sEspMenu->mEspEntry[10].bEspEnabled = pCVar->Settings.fHealth; 
				sEspMenu->mEspEntry[11].bEspEnabled = pCVar->Settings.fAmmo; 
				sEspMenu->mEspEntry[12].bEspEnabled = pCVar->Settings.fBox; 

			if(pCVar->Settings.nName == true ||
					pCVar->Settings.nClass == true ||
					pCVar->Settings.nHealth == true ||
					pCVar->Settings.nAmmo == true ||
					pCVar->Settings.nBox == true ||
					pCVar->Settings.fName == true ||
					pCVar->Settings.fClass == true ||
					pCVar->Settings.fHealth == true ||
					pCVar->Settings.fAmmo == true ||
					pCVar->Settings.AKnife == true ||
					pCVar->Settings.fBox == true )
					dESP = true;
			else
				dESP = false;

}
CMenu::CMenu(IDirect3DDevice9 *pIDirect3DDevice9)
{
	m_pD3Ddev			= pIDirect3DDevice9;
	bMenu				= false;
	bTagsMenu			= false;
	bWallMenu			= false;
	bViewMenu			= false;
	bRemMenu			= false;
	bLogMenu			= false;
	bAimMenu			= false;
	bAMenu			= false;
	bssMenu			= false;
	bopMenu			= false;
	bEspMenu			= false;
	bzMenu			= false;
	bRadMenu			= false;
	menuon=false;
	bMenuSelection		= 0;
	bTagsMenuSelection	= 0;
	bWallMenuSelection	= 0;
	bViewMenuSelection	= 0;
	bRemMenuSelection	= 0;
	bLogMenuSelection	= 0;
	bAimMenuSelection	= 0;
	bRadMenuSelection	= 0;
	bssMenuSelection	= 0;
	bopMenuSelection	= 0;
	bzMenuSelection	= 0;
	bAMenuSelection	= 0;
	bEspMenuSelection	= 0;
	iMenuX				= 0;
	iMenuY				= 100;
	iClockX				= 5;
	iClockY				= 20;
	iTx					= 1;
	sMenu				= new s_Menu;
	sViewMenu			= new s_ViewMenu;
	sWallMenu			= new s_WallMenu;
	sTagsMenu			= new s_TagsMenu;
	sAimMenu			= new s_AimMenu;
	szMenu			= new s_zMenu;
	sAMenu			= new s_AMenu;
	sssMenu			= new s_ssMenu;
	sopMenu			= new s_opMenu;
	sEspMenu			= new s_EspMenu;
	sRadMenu			= new s_RadMenu;

	AimKey = 0;

auth = true;

	sLogMenu			= new s_LogMenu;

	sRemMenu			= new s_RemMenu;
};
void CMenu::MainMenu( )
{
	for( int x = 0; x < 11; x++ )
		sMenu->mEntry[x].bEnabled = false;

#ifdef PREM
		MARK_NAME1( "Aimbot->"	, 0		)
		MARK_NAME1( "ESP->"	, 1		)
		MARK_NAME1( "Wallhacks->"	, 2		)
		MARK_NAME1( "Name Tags->"		, 3		)
		MARK_NAME1( "View Distance->"			, 4		)
		MARK_NAME1( "Removals->"		, 5	)
		MARK_NAME1( "Screen Shot Cleaner->"		, 6	)
		MARK_NAME1( "Options->"		, 7	)
		MARK_NAME1( "Zoom->"		, 8	)
		MARK_NAME1( "Crosshair"		, 9		)
		MARK_NAME1( "Commander Hack"		, 10		)
#else 
		MARK_NAME1( "Aimbot->"	, 0		)
		MARK_NAME1( "ESP->"	, 1		)
		MARK_NAME1( "Wallhacks->"	, 2		)
		MARK_NAME1( "Name Tags->"		, 3		)
		MARK_NAME1( "View Distance->"			, 4		)
		MARK_NAME1( "Removals->"		, 5	)
		MARK_NAME1( "Radar->"		, 6	)
		MARK_NAME1( "Crosshair"		, 7		)
		MARK_NAME1( "Commander Hack"		, 8		)
#endif
		/*MARK_NAME1( "Asus Wallhack"	, 6		)
		MARK_NAME1( "ViewDistance"	, 7		)
		MARK_NAME1( "MiniMap"		, 8		)
		MARK_NAME1( "Tags/Esp Menu"	, 9		)
		MARK_NAME1( "Date-Time"		, 10	)*/
}

void CMenu::TagsMenu( )
{
	for( int x = 0; x < 9; x++ )
		sTagsMenu->mTagsEntry[x].bTagsEnabled = false;

		MARK_NAME2( "Name Tags"		, 0		)
		MARK_NAME2( "3D Map"	, 1		)
		MARK_NAME2( "Health Tags"			, 2		)
		MARK_NAME2( "Distance"	, 3		)
		MARK_NAME2(	"Kit Icons"	, 4		)
		MARK_NAME2(	"Mine Warning"	, 5		)
		MARK_NAME2(	"Radar / Bridge Icons"	, 6		)
		MARK_NAME2(	"Fade Distance +"	, 7		)
		MARK_NAME2(	"Fade Distance -"	, 8		)
}

void CMenu::LogMenu( )
{
	for( int x = 0; x < 6; x++ )
		sLogMenu->mLogEntry[x].bLogEnabled = false;

		MARK_NAME6( "Enter Username:"	, 0		)
		MARK_NAME6( ""	, 1		)
		MARK_NAME6( "Enter Password:", 2		)
		MARK_NAME6( ""	, 3		)
		MARK_NAME6( "Login->", 4		)
		MARK_NAME6( "Cancel", 5		)
}

void CMenu::ViewMenu( )
{
	for( int x = 0; x < 3; x++ )
		sViewMenu->mViewEntry[x].bViewEnabled = false;

		MARK_NAME4( "Disable Fog"	, 0		)
		MARK_NAME4( "View Distance +", 1		)
		MARK_NAME4( "View Distance -", 2		)
}

void CMenu::WallMenu()
{
	for( int x = 0; x < 5; x++ )
		sWallMenu->mWallEntry[x].bWallEnabled = false;

		MARK_NAME3( "Chams"		, 0		)
		MARK_NAME3( "XQZ Wallhack"	, 1		)
		MARK_NAME3( "Asus Wallhack"			, 2		)
		MARK_NAME3( "Wireframe"	, 3		)
		MARK_NAME3(	"White Walls"	, 4		)
}


void CMenu::RadMenu()
{
	for( int x = 0; x < 5; x++ )
		sRadMenu->mRadEntry[x].bRadEnabled = false;

		MARK_NAME13( "Enable Radar"		, 0		)
		MARK_NAME13( "Show Rotation"	, 1		)
		MARK_NAME13( "Show Health"			, 2		)
//		MARK_NAME13( "Wireframe"	, 3		)
//		MARK_NAME13(	"White Walls"	, 4		)
}

void CMenu::RemMenu()
{
	for( int x = 0; x < 9; x++ )
		sRemMenu->mRemEntry[x].bRemEnabled = false;
#ifdef PREM

		MARK_NAME5( "No Recoil"		, 0		)
		MARK_NAME5( "No Sky"		, 1		)
		MARK_NAME5( "No Smoke"	, 2		)
		MARK_NAME5( "No Flash"			, 3		)
		MARK_NAME5( "No Scope"			, 4		)
		MARK_NAME5( "No Muzzle Flare"			, 5		)
		MARK_NAME5( "No Shell Shock"	, 6		)
		MARK_NAME5(	"No Tear Gas"	, 7		)
		MARK_NAME5(	"No Terrian"	, 8		)
		MARK_NAME5(	"Night Vision"	, 9		)
#else
		//MARK_NAME5( "No Recoil"		, 0		)
		MARK_NAME5( "No Sky"		, 0		)
		MARK_NAME5( "No Smoke"	, 1		)
		MARK_NAME5( "No Flash"			, 2		)
		MARK_NAME5( "No Scope"			, 3		)
		MARK_NAME5( "No Muzzle Flare"			, 4		)
		MARK_NAME5( "No Shell Shock"	, 5		)
		MARK_NAME5(	"No Tear Gas"	, 6		)
		MARK_NAME5(	"No Terrian"	, 7		)
		MARK_NAME5(	"Night Vision"	, 8		)
#endif
}
void CMenu::AimMenu()
{
	for( int x = 0; x < 10; x++ )
		sAimMenu->mAimEntry[x].bAimEnabled = false;

#ifdef PREM
		MARK_NAME7( "Initialize Aimbot"		, 0		)
		MARK_NAME7( "Aim Key - None"		, 1		)
		MARK_NAME7( "Aim Vec - Head"		, 2		)
		MARK_NAME7( "Auto Fire"				, 3		)
		MARK_NAME7( "Switch After Kill"		, 4		)
		MARK_NAME7( "Ping Correction"		, 5		)
		//MARK_NAME7( "Disable Max Angle"		, 6		)
		MARK_NAME7( "Create Vecs->"		, 6		)
		MARK_NAME7( "Prediction - 0"		, 7		)
		MARK_NAME7( "Auto Knife"		, 8		)
		MARK_NAME7( "Smart Targeting"		, 9		)
#else
		MARK_NAME7( "Initialize Aimbot"		, 0		)
		MARK_NAME7( "Aim Key - None"		, 1		)
		MARK_NAME7( "Aim Vec - Head"		, 2		)
		MARK_NAME7( "Auto Fire"				, 3		)
		MARK_NAME7( "Switch After Kill"		, 4		)
		MARK_NAME7( "Ping Correction"		, 5		)
		//MARK_NAME7( "Disable Max Angle"		, 6		)
		MARK_NAME7( "Create Vecs->"		, 6		)
		MARK_NAME7( "Prediction - 0"		, 7		)
		MARK_NAME7( "Auto Knife"		, 8		)
#endif

}
void CMenu::AMenu()
{
	for( int x = 0; x < 13; x++ )
		sAMenu->mAEntry[x].bAEnabled = false;

		MARK_NAME9( "Draw Vec"		, 0		)
		MARK_NAME9( "Raise Vec"		, 1		)
		MARK_NAME9( "Lower Vec"		, 2		)
		MARK_NAME9( "Move Right"				, 3		)
		MARK_NAME9( "Move Left"		, 4		)
		MARK_NAME9( "Move Forword"		, 5		)
		MARK_NAME9( "Move Back"		, 6		)
		MARK_NAME9( "Load Vec 1"		, 7		)
		MARK_NAME9( "Load Vec 2"		, 8		)
		MARK_NAME9( "Load Vec 3"		, 9		)
		MARK_NAME9( "Save Vec 1"		, 10		)
		MARK_NAME9( "Save Vec 2"		, 11	)
		MARK_NAME9( "Save Vec 3"		, 12	)
}
void CMenu::zMenu()
{
	for( int x = 0; x < 6; x++ )
		szMenu->mzEntry[x].bzEnabled = false;

		MARK_NAME12( "Zoom Key - None"		, 0		)
		MARK_NAME12( "Click On/Off"		, 1		)
		MARK_NAME12( "Zoom more"		, 2		)
		MARK_NAME12( "Zoom less"				, 3		)
	//	MARK_NAME9( "Move Left"		, 4		)
	//	MARK_NAME9( "Move Forword"		, 5		)
	//	MARK_NAME9( "Move Back"		, 6		)
	//	MARK_NAME9( "Load Vec 1"		, 7		)
	//	MARK_NAME9( "Load Vec 2"		, 8		)
	//	MARK_NAME9( "Load Vec 3"		, 9		)
	//	MARK_NAME9( "Save Vec 1"		, 10		)
	//	MARK_NAME9( "Save Vec 2"		, 11	)
	//	MARK_NAME9( "Save Vec 3"		, 12	)
}
//
void CMenu::ssMenu()
{
	for( int x = 0; x < 4; x++ )
		sssMenu->mssEntry[x].bssEnabled = false;
#ifdef PREM

		MARK_NAME10( "Enable SS Cleaner"		, 0		)
		MARK_NAME10( "Update SS Interval: 10s"		, 1		)
		MARK_NAME10( "Manual Update"		, 2		)
		MARK_NAME10( "Notify Me On SS"				, 3		)
	//	MARK_NAME9( "Move Left"		, 4		)
	//	MARK_NAME9( "Move Forword"		, 5		)
	//	MARK_NAME9( "Move Back"		, 6		)
		//MARK_NAME7( "Prediction - 0"		, 7		)

#endif

}
//
void CMenu::opMenu()
{
	for( int x = 0; x < 11; x++ )
		sopMenu->mopEntry[x].bopEnabled = false;

		MARK_NAME11( "Load Slot 1"		, 0		)
		MARK_NAME11( "Load Slot 2"		, 1		)
		MARK_NAME11( "Load Slot 3"		, 2		)
		MARK_NAME11( "Load Slot 4"				, 3		)
		MARK_NAME11( "Save Slot 1"		, 4		)
		MARK_NAME11( "Save Slot 2"		, 5		)
		MARK_NAME11( "Save Slot 3"		, 6		)
		MARK_NAME11( "Save Slot 4"				, 7		)
		MARK_NAME11( "Show Time"		, 8		)
		MARK_NAME11( "Show FPS"		, 9		)
		MARK_NAME11( "Show Ping"		, 10		)
		//MARK_NAME7( "Prediction - 0"		, 7		)
}
void CMenu::EspMenu()
{
	for( int x = 0; x < 13; x++ )
		sEspMenu->mEspEntry[x].bEspEnabled = false;

		MARK_NAME8( "Smart Esp Preset"		, 0		)
		MARK_NAME8( "-When Near-"	, 1		)
		MARK_NAME8( "Names"			, 2		)
		MARK_NAME8( "Class"			, 3		)
		MARK_NAME8( "Health"			, 4		)
		MARK_NAME8( "Ammo"	, 5		)
		MARK_NAME8(	"Boxes"	, 6		)
		MARK_NAME8(	"-When Far-"	, 7		)
		MARK_NAME8(	"Names"	, 8		)
		MARK_NAME8(	"Class"	, 9		)
		MARK_NAME8(	"Health"	, 10		)
		MARK_NAME8(	"Ammo"	, 11		)
		MARK_NAME8(	"Boxes"	, 12		)
}



void CMenu::InitMenu()
{
	TagsMenu();
	ViewMenu();
	MainMenu();
	WallMenu();
	RemMenu();
	LogMenu();
	AimMenu();
	AMenu();
	zMenu();
	ssMenu();
	opMenu();
	EspMenu();
	RadMenu();
}
void CMenu::MenuSelection()
{
	if(pCVar->Settings.bCommander) setCommander();

	if (GetAsyncKeyState(VK_INSERT)&1)
	{
		if(!menuon)
		{
			if(!auth)
			{
				bLogMenu = true;
				bMenu = false;
				bWallMenu = false;
				bTagsMenu = false;
				bViewMenu = false;
				bAimMenu = false;
				bEspMenu = false;
				menuon=true;
			}
			else
			{
				bMenu = !bMenu;
				bLogMenu = false;
				bWallMenu = false;
				bTagsMenu = false;
				bViewMenu = false;
				bAimMenu = false;
				bEspMenu = false;
				bssMenu = false;
				bopMenu = false;
				bzMenu = false;
				bRadMenu = false;
				menuon=true;
			}
		}
		else
		{
			bMenu = false;
			bWallMenu = false;
			bTagsMenu = false;
			bViewMenu = false;
			bLogMenu = false;
			bRemMenu = false;
			bAimMenu = false;
			bAMenu = false;
			bEspMenu = false;
			bssMenu = false;
			bopMenu = false;
			bzMenu = false;
			bRadMenu = false;

			menuon=false;
		}
	}
	if( GetAsyncKeyState( VK_UP ) & 1 ) 
	{	
		if (bMenu)
		{
			if( bMenuSelection > 0 )
				bMenuSelection--;
		}
		if (bTagsMenu)
		{
			if( bTagsMenuSelection > 0 )
				bTagsMenuSelection--;
		}
		if (bViewMenu)
		{
			if(bViewMenuSelection > 0)
				bViewMenuSelection --;
		}
		if (bWallMenu)
		{
			if(bWallMenuSelection > 0)
				bWallMenuSelection --;
		}
		if (bRemMenu)
		{
			if(bRemMenuSelection > 0)
				bRemMenuSelection --;
		}
		if (bAimMenu)
		{
			if(bAimMenuSelection > 0)
				bAimMenuSelection --;
		}
		if (bRadMenu)
		{
			if(bRadMenuSelection > 0)
				bRadMenuSelection --;
		}
		if (bAMenu)
		{
			if(bAMenuSelection > 0)
				bAMenuSelection --;
		}
		if (bzMenu)
		{
			if(bzMenuSelection > 0)
				bzMenuSelection --;
		}
		if (bssMenu)
		{
			if(bssMenuSelection > 0)
				bssMenuSelection --;
		}
		if (bopMenu)
		{
			if(bopMenuSelection > 0)
				bopMenuSelection --;
		}
		if (bEspMenu)
		{
			if(bEspMenuSelection > 0)
				bEspMenuSelection --;
			if(bEspMenuSelection == 1 || bEspMenuSelection == 7)
				bEspMenuSelection --;
		}
		if (bLogMenu)
		{
			if(bLogMenuSelection > 0)
				bLogMenuSelection --;
			if(bLogMenuSelection == 1 || bLogMenuSelection == 3)
				bLogMenuSelection --;
		}

	}
	if(GetAsyncKeyState( VK_DOWN ) & 1 )
	{
		if (bMenu)
		{
			if( bMenuSelection < 8 )
				bMenuSelection++;
		}
		if (bTagsMenu)
		{
			if( bTagsMenuSelection < 8 )
				bTagsMenuSelection++;
		}
		if (bViewMenu)
		{
			if(bViewMenuSelection < 2)
				bViewMenuSelection ++;
		}
		if (bWallMenu)
		{
			if(bWallMenuSelection < 4)
				bWallMenuSelection ++;
		}
		if (bRadMenu)
		{
			if(bRadMenuSelection < 2)
				bRadMenuSelection ++;
		}
		if (bRemMenu)
		{
			if(bRemMenuSelection < 6)
				bRemMenuSelection ++;
		}
		if (bssMenu)
		{
			if(bssMenuSelection < 3)
				bssMenuSelection ++;
		}
		if (bzMenu)
		{
			if(bzMenuSelection < 3)
				bzMenuSelection ++;
		}
		if (bopMenu)
		{
			if(bopMenuSelection < 10)
				bopMenuSelection ++;
		}
		if (bAimMenu)
		{
			if(bAimMenuSelection < 8 && pCVar->Settings.intaim != 0)
				bAimMenuSelection ++;
		}
		if (bAMenu)
		{
			if(bAMenuSelection < 12)
				bAMenuSelection ++;
		}
		if (bLogMenu)
		{
			if(bLogMenuSelection < 5)
				bLogMenuSelection ++;
			if(bLogMenuSelection == 1 || bLogMenuSelection == 3)
				bLogMenuSelection ++;
		}
		if (bEspMenu)
		{
			if(bEspMenuSelection < 12)
				bEspMenuSelection ++;
			if(bEspMenuSelection == 1 || bEspMenuSelection == 7)
				bEspMenuSelection ++;
		}

	}
	if(GetAsyncKeyState( VK_LEFT) & 1 )
	{
		if(menuon)
		{
			if(!bMenu && auth)
			{
				if(bAMenu)
				{
					bTagsMenu = false;
					bMenu = false;
					bViewMenu = false;
					bWallMenu = false;
					bRemMenu = false;
					bAMenu = false;
					bAimMenu = true;
					bEspMenu = false;
					bssMenu = false;
					bzMenu = false;
					bopMenu = false;
					bRadMenu = false;
				} else
				{
					bTagsMenu = false;
					bMenu = true;
					bViewMenu = false;
					bWallMenu = false;
					bRemMenu = false;
					bAimMenu = false;
					bAMenu = false;
					bEspMenu = false;
					bssMenu = false;
					bopMenu = false;
					bRadMenu = false;
				}
			}
			else
			{
				bTagsMenu = false;
					bMenu = false;
					bViewMenu = false;
					bWallMenu = false;
					bRemMenu = false;
					bLogMenu = false;
					bEspMenu = false;
					bAimMenu = false;
					bAMenu = false;
					bssMenu = false;
					bopMenu = false;
					bRadMenu = false;
					menuon=false;
			}
		}
	}

	if(GetAsyncKeyState( VK_RIGHT ) & 1 )
	{
		if(!menuon)
		{
			if(!auth)
			{
				bLogMenu = true;
				bMenu = false;
				bWallMenu = false;
				bTagsMenu = false;
				bViewMenu = false;
				bAimMenu = false;
				bEspMenu = false;
				menuon=true;
			}
			else
			{
				bMenu = true;
				bLogMenu = false;
				bWallMenu = false;
				bTagsMenu = false;
				bViewMenu = false;
				bAimMenu = false;
				bEspMenu = false;
				bssMenu = false;
				bopMenu = false;
				bzMenu = false;
				menuon=true;
			}
		} else if( bMenu )
		{
#ifdef PREM
			switch( bMenuSelection )
			{
			case 0:
				bAimMenu = true;
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				break;
			case 1:
				bEspMenu = true;
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				break;
			case 2:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = !bWallMenu;
				bRemMenu = false;
				break;
			case 3:
				bTagsMenu = !bTagsMenu;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				
				break;
			case 4:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = !bViewMenu;
				bWallMenu = false;
				bRemMenu = false;
				break;
			case 5:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = !bRemMenu;
				break;
			case 6:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				bssMenu = true;
				break;
			case 7:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				bopMenu = true;
				break;
			case 8:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				bopMenu = false;
				bzMenu = true;
				break;
			case 9:
				pCVar->Settings.bXhair = !pCVar->Settings.bXhair;
				SWITCH_STAT( 9 );
				break;
			case 10:
				if(!pCVar->Settings.bCommander)
					setCommander();
				else
					setCommanderoff();
				pCVar->Settings.bCommander = !pCVar->Settings.bCommander;
				SWITCH_STAT( 10 );
				break;
			/*case 6:
				pCVar->Settings.bAsus = !pCVar->Settings.bAsus;
				SWITCH_STAT( 6 );
				break;
			case 7:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = !bViewMenu;
				bWallMenu = false;
				break;
			case 8:
				pCVar->Settings.bMinimap=!pCVar->Settings.bMinimap;
				pMem->MiniMap();
				SWITCH_STAT( 8 );
				break;
			case 9:
				bTagsMenu = !bTagsMenu;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				break;
			case 10:
				pCVar->Settings.bDateAndTime = !pCVar->Settings.bDateAndTime;
				SWITCH_STAT( 10 );
				break;
			default:
				break;*/
			}
#else
			switch( bMenuSelection )
			{
			case 0:
				bAimMenu = true;
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				break;
			case 1:
				bEspMenu = true;
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				break;
			case 2:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = !bWallMenu;
				bRemMenu = false;
				break;
			case 3:
				bTagsMenu = !bTagsMenu;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = false;
				
				break;
			case 4:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = !bViewMenu;
				bWallMenu = false;
				bRemMenu = false;
				break;
			case 5:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRemMenu = !bRemMenu;
				break;
			case 6:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				bRadMenu = !bRadMenu;
				break;
			case 7:
				pCVar->Settings.bXhair = !pCVar->Settings.bXhair;
				SWITCH_STAT( 7 );
				break;
			case 8:
				if(!pCVar->Settings.bCommander)
					setCommander();
				else
					setCommanderoff();
				pCVar->Settings.bCommander = !pCVar->Settings.bCommander;
				SWITCH_STAT( 8 );
				break;
			case 9:
				if(!pCVar->Settings.bCommander)
					setCommander();
				else
					setCommanderoff();
				pCVar->Settings.bCommander = !pCVar->Settings.bCommander;
				SWITCH_STAT( 9 );
				break;
		/*	case 9:
				if(!pCVar->Settings.bCommander)
					setCommander();
				else
					setCommanderoff();
				pCVar->Settings.bCommander = !pCVar->Settings.bCommander;
				SWITCH_STAT( 9 );
				break;
			/*case 6:
				pCVar->Settings.bAsus = !pCVar->Settings.bAsus;
				SWITCH_STAT( 6 );
				break;
			case 7:
				bTagsMenu = false;
				bMenu = false;
				bViewMenu = !bViewMenu;
				bWallMenu = false;
				break;
			case 8:
				pCVar->Settings.bMinimap=!pCVar->Settings.bMinimap;
				pMem->MiniMap();
				SWITCH_STAT( 8 );
				break;
			case 9:
				bTagsMenu = !bTagsMenu;
				bMenu = false;
				bViewMenu = false;
				bWallMenu = false;
				break;
			case 10:
				pCVar->Settings.bDateAndTime = !pCVar->Settings.bDateAndTime;
				SWITCH_STAT( 10 );
				break;
			default:
				break;*/
			}
#endif

		}

		else if (bTagsMenu)
		{
			float fade=0;
			DWORD addt=0;
			
			switch(bTagsMenuSelection)
			{
			case 0:
				pCVar->Settings.bNametags=!pCVar->Settings.bNametags;
				/*if(pCVar->Settings.bNametags){
					_asm pushad;
					TagsOn1();
					_asm popad;
				}
				else
					TagsOff1();*/
				
				SWITCH_STAT_TAGS( 0 );
				break;
			case 1:
				pCVar->Settings.b3DMap=!pCVar->Settings.b3DMap;
				/*if(pCVar->Settings.b3DMap){
					_asm pushad;
					dTags1();
					_asm popad;
				}
				else
					doff1();*/
				
				SWITCH_STAT_TAGS( 1 );
				
				break;
			case 2:
				pCVar->Settings.bHealthTags=!pCVar->Settings.bHealthTags;
				/*if(pCVar->Settings.bHealthTags){
					_asm pushad;
					Health1();
					_asm popad;
				}
				else
					Healthoff1();*/
				
				SWITCH_STAT_TAGS( 2 );
				break;
			case 3:
				pCVar->Settings.Dist = !pCVar->Settings.Dist;
				SWITCH_STAT_TAGS( 3 );
				break;
			case 4:
				pCVar->Settings.bKit = !pCVar->Settings.bKit;
				/*if(pCVar->Settings.bKit){
					_asm pushad;
					kits1();
					_asm popad;
				}
				else
					kitsoff1();*/
				SWITCH_STAT_TAGS( 4 );
				break;
			case 5:
				pCVar->Settings.bMines = !pCVar->Settings.bMines;
				SWITCH_STAT_TAGS( 5 );

				break;
			case 6:
				pCVar->Settings.bRadar = !pCVar->Settings.bRadar;
				/*if(pCVar->Settings.bRadar)
				{
					_asm pushad;
					radar1();
					_asm popad;
				}
				else
					radoff1();*/

				SWITCH_STAT_TAGS( 6 );
				
				break;
			/*case 7:
				*faded += 50.0f;
				break;
			case 8:
				*faded -= 50.0f;
				break;*/
			case 7:
				fade=0;
				addt = (DWORD)GetModuleHandle("RendDX9.dll") + 0x237A2C;
				_asm{
					mov eax, addt;
					mov eax, [eax];
					mov fade, eax;
				}
				fade += 50.0f;
				_asm{
					push ebx;
					mov eax, addt;
					mov ebx, fade;
					mov [eax], ebx;
					pop ebx;
				}

				break;
			case 8:
				fade=0;
				addt = (DWORD)GetModuleHandle("RendDX9.dll") + 0x237A2C;
				_asm{
					mov eax, addt;
					mov eax, [eax];
					mov fade, eax;
				}
				fade -= 50.0f;
				_asm{
					push ebx;
					mov eax, addt;
					mov ebx, fade;
					mov [eax], ebx;
					pop ebx;
				}
				break;
			default:
				break;
			}
		}
		else if (bViewMenu)
		{
			DWORD adr;
			
			switch(bViewMenuSelection)
			{
			case 0:
				pCVar->Settings.bNoFog = !pCVar->Settings.bNoFog; 
				SWITCH_STAT_VIEW( 0 );
				break;
			case 1:
			//	pCVar->Settings.bNoFog = !pCVar->Settings.bNoFog; 
				adr = (DWORD)GetModuleHandle("RendDX9.dll") + 0x239960;
				viewMod=0;
				_asm{
					mov eax, adr;
					mov eax, [eax];
					add eax, 0x4F8;
					mov adr, eax;
					mov eax, [eax];
					mov viewMod, eax;
				}
				if(viewMod && viewMod < 5.0f)
				{
					viewMod += 0.25;
					_asm{
						push ebx;
						mov eax, viewMod;
						mov ebx, adr;
						mov [ebx], eax;
						pop ebx;
					}
				}
				break;
			case 2:
				adr = (DWORD)GetModuleHandle("RendDX9.dll") + 0x239960;
				viewMod=0;
				_asm{
					mov eax, adr;
					mov eax, [eax];
					add eax, 0x4F8;
					mov adr, eax;
					mov eax, [eax];
					mov viewMod, eax;
				}
				if(viewMod)
				{
					viewMod -= 0.25;
					_asm{
						push ebx;
						mov eax, viewMod;
						mov ebx, adr;
						mov [ebx], eax;
						pop ebx;
					}
				}
				
				break;
			case 3:
				
				break;
			default:
				break;
			}
		}

		else if (bssMenu)
		{
			switch(bssMenuSelection)
			{
			case 0:
					pCVar->Settings.css = !pCVar->Settings.css;
					SWITCH_STAT_SS( 0 );
					break;
			case 1:
				switch(pCVar->Settings.ssec)
				{
				case 0:
					pCVar->Settings.ssec = 10000;
					MARK_NAME10( "Update SS Interval: 10s"		, 1		)
					break;
				case 10000:
					pCVar->Settings.ssec = 30000;
					MARK_NAME10( "Update SS Interval: 30s"		, 1		)
					break;
				case 30000:
					pCVar->Settings.ssec = 60000;
					MARK_NAME10( "Update SS Interval: 1m"		, 1		)
					break;
				case 60000:
					pCVar->Settings.ssec = 300000;
					MARK_NAME10( "Update SS Interval: 5m"		, 1		)
					break;
				case 300000:
					pCVar->Settings.ssec = 0;
					MARK_NAME10( "Update SS Interval: 0s"		, 1		)
					break;
				}
				break;
			case 2:
				pCVar->Settings.ssnow = true;
				break;
			case 3:
				pCVar->Settings.ssnote =! pCVar->Settings.ssnote ;
				SWITCH_STAT_SS( 3 );
				break;
			}
		}
		else if (bopMenu)
		{
			switch(bopMenuSelection)
			{
			case 0:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					RegQueryValueEx(hkey1, "Slot1", 0, NULL, (LPBYTE)pCVar, (DWORD*)&sze);
					popmenu();
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 1:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					RegQueryValueEx(hkey1, "Slot2", 0, NULL, (LPBYTE)pCVar, (DWORD*)&sze);
					popmenu();
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 2:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					RegQueryValueEx(hkey1, "Slot3", 0, NULL, (LPBYTE)pCVar, (DWORD*)&sze);
					popmenu();
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 3:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					RegQueryValueEx(hkey1, "Slot4", 0, NULL, (LPBYTE)pCVar, (DWORD*)&sze);
					popmenu();
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 4:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Slot1", 0, REG_SZ, (CONST BYTE*)pCVar, sizeof(CCVAR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 5:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Slot2", 0, REG_SZ, (CONST BYTE*)pCVar, sizeof(CCVAR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 6:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Slot3", 0, REG_SZ, (CONST BYTE*)pCVar, sizeof(CCVAR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 7:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Slot4", 0, REG_SZ, (CONST BYTE*)pCVar, sizeof(CCVAR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 8:
				pCVar->Settings.drTime =! pCVar->Settings.drTime ;
				SWITCH_STAT_AIM( 8 );
				break;
			case 9:
				pCVar->Settings.drFPS =! pCVar->Settings.drFPS ;
				SWITCH_STAT_AIM( 9 );
				break;
			case 10:
				pCVar->Settings.drPing =! pCVar->Settings.drPing ;
				SWITCH_STAT_AIM( 10 );
				break;
			}
		}
		else if (bAimMenu)
		{
			switch(bAimMenuSelection)
			{
			case 0:
					pCVar->Settings.intaim = 1;
					break;
			case 1:
				if(AimKey < 3)
				{
					AimKey++;
					pCVar->Settings.AKey = AimKey;
					switch(AimKey)
					{
					case 1:
						MARK_NAME7( "Aim Key - Mouse Middle"		, 1		)
							break;
					case 2:
						MARK_NAME7( "Aim Key - Mouse Left"		, 1		)
							break;
					case 3:
						MARK_NAME7( "Aim Key - Mouse Right"		, 1		)
							break;
					}

				}else
				{
					AimKey = 0;
					pCVar->Settings.AKey = 0 ;
					MARK_NAME7( "Aim Key - None"		, 1		)
				}
			//	pCVar->Settings.bNoFog = !pCVar->Settings.bNoFog; 
			//	SWITCH_STAT_VIEW( 0 );
				break;
			case 2:
				if(pCVar->Settings.AHead)
				{
					pCVar->Settings.AHead = !pCVar->Settings.AHead;
					MARK_NAME7( "Aim Vec - Chest"		, 2		)
				} else
				{
					pCVar->Settings.AHead = !pCVar->Settings.AHead;
					MARK_NAME7( "Aim Vec - Head"		, 2		)
				}
				break;
			case 3:
				pCVar->Settings.AFire = !pCVar->Settings.AFire;
				SWITCH_STAT_AIM( 3 );
				break;
			case 4:
				pCVar->Settings.ASwitch = !pCVar->Settings.ASwitch;
				SWITCH_STAT_AIM( 4 );
				break;
			case 5:
				pCVar->Settings.APing = !pCVar->Settings.APing;
				SWITCH_STAT_AIM( 5 );
				break;
			case 6:
				bAimMenu = false;
				bAMenu = !bRemMenu;
				break;
				/*if(!pCVar->Settings.ASpeed)
				{
					pCVar->Settings.ASpeed = !pCVar->Settings.ASpeed;

					float maxang = 360.0f;
					HANDLE hnd = GetCurrentProcess();
					DWORD maxadr;
					ReadProcessMemory(hnd, (void*) 0x9AE614, &maxadr, 4, 0);
					WriteProcessMemory(hnd, (void*) maxadr, &maxang, 4, 0);
				} else
				{
					pCVar->Settings.ASpeed = !pCVar->Settings.ASpeed;

					float maxang = 40.0f;
					HANDLE hnd = GetCurrentProcess();
					DWORD maxadr;
					ReadProcessMemory(hnd, (void*) 0x9AE614, &maxadr, 4, 0);
					WriteProcessMemory(hnd, (void*) maxadr, &maxang, 4, 0);
				}
				SWITCH_STAT_AIM( 6 );*/

				break;
			case 7:
				if(pCVar->Settings.APred < 10)
				{
					pCVar->Settings.APred++;
					switch(pCVar->Settings.APred)
					{
					case 1:
						MARK_NAME7("Prediction - 1", 7);
						break;
					case 2:
						MARK_NAME7("Prediction - 2", 7);
						break;
					case 3:
						MARK_NAME7("Prediction - 3", 7);
						break;
					case 4:
						MARK_NAME7("Prediction - 4", 7);
						break;
					case 5:
						MARK_NAME7("Prediction - 5", 7);
						break;
					case 6:
						MARK_NAME7("Prediction - 6", 7);
						break;
					case 7:
						MARK_NAME7("Prediction - 7", 7);
						break;
					case 8:
						MARK_NAME7("Prediction - 8", 7);
						break;
					case 9:
						MARK_NAME7("Prediction - 9", 7);
						break;
					case 10:
						MARK_NAME7("Prediction - 10", 7);
						break;
					}					
				} else
				{
					pCVar->Settings.APred = 0;
					MARK_NAME7( "Prediction - 0"		, 7		)
				}

				//pCVar->Settings.AKnife = !pCVar->Settings.AKnife;
				//SWITCH_STAT_AIM( 6 );
				break;
			case 8:
				pCVar->Settings.AKnife = !pCVar->Settings.AKnife;
				SWITCH_STAT_AIM( 8 );
				break;
			case 9:
#ifdef PREM
				pCVar->Settings.smartTarg = !pCVar->Settings.smartTarg;
				SWITCH_STAT_AIM( 9 );
#endif
				break;
			}
		}
		else if (bAMenu)
		{
			switch(bAMenuSelection)
			{
			case 0:
					pCVar->Settings.drawvec = !pCVar->Settings.drawvec;
					SWITCH_STAT_A( 0 );
					break;
			case 1:
				pCVar->Settings.cy += 0.01f;
				break;
			case 2:
				pCVar->Settings.cy -= 0.01f;
				break;
			case 3:
				pCVar->Settings.cx += 0.01f;
				break;
			case 4:
				pCVar->Settings.cx -= 0.01f;
				break;
			case 5:
				pCVar->Settings.cz += 0.01f;
				break;
			case 6:
				pCVar->Settings.cz -= 0.01f;
				break;
			case 7:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					
					RegQueryValueEx(hkey1, "Vec1", 0, NULL, (LPBYTE)&vec, (DWORD*)&sze);
					pCVar->Settings.cx = vec.x ;
					pCVar->Settings.cy = vec.y ;
					pCVar->Settings.cz = vec.z;
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 8:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					
					RegQueryValueEx(hkey1, "Vec2", 0, NULL, (LPBYTE)&vec, (DWORD*)&sze);
					pCVar->Settings.cx = vec.x ;
					pCVar->Settings.cy = vec.y ;
					pCVar->Settings.cz = vec.z;
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 9:
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					DWORD sze;
					
					RegQueryValueEx(hkey1, "Vec3", 0, NULL, (LPBYTE)&vec, (DWORD*)&sze);
					pCVar->Settings.cx = vec.x ;
					pCVar->Settings.cy = vec.y ;
					pCVar->Settings.cz = vec.z;
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 10:
				
				vec.x = pCVar->Settings.cx;
				vec.y = pCVar->Settings.cy;
				vec.z = pCVar->Settings.cz;
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Vec1", 0, REG_SZ, (CONST BYTE*)&vec, sizeof(D3DVECTOR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 11:
				
				vec.x = pCVar->Settings.cx;
				vec.y = pCVar->Settings.cy;
				vec.z = pCVar->Settings.cz;
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Vec2", 0, REG_SZ, (CONST BYTE*)&vec, sizeof(D3DVECTOR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			case 12:
				
				vec.x = pCVar->Settings.cx;
				vec.y = pCVar->Settings.cy;
				vec.z = pCVar->Settings.cz;
				lRet = RegCreateKeyEx(HKEY_CURRENT_USER, "Software", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hkey, &dwFunc);
				lRet1 = RegCreateKeyEx(hkey, "Catalyst", 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hkey1, &dwFunc);
				if( lRet == ERROR_SUCCESS && lRet1 == ERROR_SUCCESS )
				{
					RegSetValueEx(hkey1, "Vec3", 0, REG_SZ, (CONST BYTE*)&vec, sizeof(D3DVECTOR));
				}
				RegCloseKey(hkey);
				RegCloseKey(hkey1);
				break;
			}
		}
		else if (bWallMenu)
		{
			switch(bWallMenuSelection)
			{
			case 0:
				pCVar->Settings.bChams = !pCVar->Settings.bChams; 
				SWITCH_STAT_WALL( 0 );
				break;
			case 1:
				pCVar->Settings.bXQZWH = !pCVar->Settings.bXQZWH; 
				SWITCH_STAT_WALL( 1 );
				break;
			case 2:
				pCVar->Settings.bAsus = !pCVar->Settings.bAsus; 
				SWITCH_STAT_WALL( 2 );
				break;
			case 3:
				pCVar->Settings.bWireframe = !pCVar->Settings.bWireframe; 
				SWITCH_STAT_WALL( 3 );
				break;
			case 4:
				pCVar->Settings.bWhiteWalls = !pCVar->Settings.bWhiteWalls; 
				SWITCH_STAT_WALL( 4 );
			default:
				break;
			}
		}
		else if (bRadMenu)
		{
			switch(bRadMenuSelection)
			{
			case 0:
				pCVar->Settings.Radar = !pCVar->Settings.Radar; 
				SWITCH_STAT_RAD( 0 );
				break;
			case 1:
				pCVar->Settings.rotateP = !pCVar->Settings.rotateP; 
				SWITCH_STAT_RAD( 1 );
				break;
			case 2:
				pCVar->Settings.radHealth = !pCVar->Settings.radHealth; 
				SWITCH_STAT_RAD( 2 );
				break;
			}
		}
		else if (bzMenu)
		{
			switch(bzMenuSelection)
			{
			case 0:
				if(pCVar->Settings.zkey > 4)
				{
					pCVar->Settings.ZoomIn = false;
					pCVar->Settings.zkey = 0;
				}
				else
				{
					pCVar->Settings.ZoomIn = true;
					pCVar->Settings.zkey++;
				}

				switch(pCVar->Settings.zkey)
				{
				case 0:
					MARK_NAME12( "Zoom Key - None"		, 0		)
					break;
				case 1:
					MARK_NAME12( "Zoom Key - Right Mouse"		, 0		)
					break;
				case 2:
					MARK_NAME12( "Zoom Key - Middle Mouse"		, 0		)
					break;
				case 3:
					MARK_NAME12( "Zoom Key - X"		, 0		)
					break;
				case 4:
					MARK_NAME12( "Zoom Key - C"		, 0		)
					break;
				}
				break;
			case 1:
				pCVar->Settings.zclick  = !pCVar->Settings.zclick ; 
				SWITCH_STAT_Z( 1 );
				break;
			case 2:
				pCVar->Settings.zoomInFloat -= 0.1f; 
				break;
			case 3:
				pCVar->Settings.zoomInFloat += 0.1f; 
				break;
			//case 4:
			//	pCVar->Settings.bWhiteWalls = !pCVar->Settings.bWhiteWalls; 
			//	SWITCH_STAT_WALL( 4 );
			//default:
			//	break;
			}
		}
		else if (bRemMenu)
		{
#ifdef PREM
			switch(bRemMenuSelection)
			{
			case 0:
				pCVar->Settings.recon  = !pCVar->Settings.recon;
				if(pCVar->Settings.cfov == 0) pCVar->Settings.intaim = 1;
				SWITCH_STAT_REM( 0 );
				break;
			case 1:
				pCVar->Settings.bSky = !pCVar->Settings.bSky; 
				SWITCH_STAT_REM( 1 );
				break;
			case 2:
				pCVar->Settings.bSmoke = !pCVar->Settings.bSmoke; 
				SWITCH_STAT_REM( 2 );
				break;
			case 3:
				pCVar->Settings.bNoFlash = !pCVar->Settings.bNoFlash; 
				SWITCH_STAT_REM( 3 );
				break;
			case 4:
				pCVar->Settings.bNoScope = !pCVar->Settings.bNoScope; 
				SWITCH_STAT_REM( 4 );
				break;
			case 5:
				pCVar->Settings.bNoFlare = !pCVar->Settings.bNoFlare; 
				SWITCH_STAT_REM( 5 );
				break;
			case 6:
				pCVar->Settings.bNoFlare = !pCVar->Settings.bNoFlare; 
				SWITCH_STAT_REM( 6 );
				break;
			case 7:
				pCVar->Settings.bNoGrass = !pCVar->Settings.bNoGrass; 
				SWITCH_STAT_REM( 7 );
				break;
				
			default:
				break;
			}
#else
			switch(bRemMenuSelection)
			{
			//case 0:
		//		pCVar->Settings.recon  = !pCVar->Settings.recon;
	//			if(pCVar->Settings.cfov == 0) pCVar->Settings.intaim = 1;
	//			SWITCH_STAT_REM( 0 );
	//			break;
			case 0:
				pCVar->Settings.bSky = !pCVar->Settings.bSky; 
				SWITCH_STAT_REM( 0 );
				break;
			case 1:
				pCVar->Settings.bSmoke = !pCVar->Settings.bSmoke; 
				SWITCH_STAT_REM( 1 );
				break;
			case 2:
				pCVar->Settings.bNoFlash = !pCVar->Settings.bNoFlash; 
				SWITCH_STAT_REM( 2 );
				break;
			case 3:
				pCVar->Settings.bNoScope = !pCVar->Settings.bNoScope; 
				SWITCH_STAT_REM( 3 );
				break;
			case 4:
				pCVar->Settings.bNoFlare = !pCVar->Settings.bNoFlare; 
				SWITCH_STAT_REM( 4 );
				break;
			case 5:
				pCVar->Settings.bNoFlare = !pCVar->Settings.bNoFlare; 
				SWITCH_STAT_REM( 5);
				break;
			case 6:
				pCVar->Settings.bNoGrass = !pCVar->Settings.bNoGrass; 
				SWITCH_STAT_REM( 6 );
				break;
				
			default:
				break;
			}
#endif
		}
		else if (bEspMenu)
		{
			switch(bEspMenuSelection)
			{
			case 0:
				if(sEspMenu->mEspEntry[0].bEspEnabled == false)
				{
					pCVar->Settings.nName = true; 
					pCVar->Settings.nClass = true;
					pCVar->Settings.nHealth = true;
					pCVar->Settings.nAmmo = true;
					pCVar->Settings.nBox = false;

					pCVar->Settings.fName = false; 
					pCVar->Settings.fClass = false;
					pCVar->Settings.fHealth = false;
					pCVar->Settings.fAmmo = false;
					pCVar->Settings.fBox = true;

					sEspMenu->mEspEntry[0].bEspEnabled = true;
					sEspMenu->mEspEntry[2].bEspEnabled = true;
					sEspMenu->mEspEntry[3].bEspEnabled = true;
					sEspMenu->mEspEntry[4].bEspEnabled = true;
					sEspMenu->mEspEntry[5].bEspEnabled = true;
					sEspMenu->mEspEntry[6].bEspEnabled = false;

					sEspMenu->mEspEntry[8].bEspEnabled = false;
					sEspMenu->mEspEntry[9].bEspEnabled = false;
					sEspMenu->mEspEntry[10].bEspEnabled = false;
					sEspMenu->mEspEntry[11].bEspEnabled = false;
					sEspMenu->mEspEntry[12].bEspEnabled = true;
				} else
				{
					pCVar->Settings.nName = false; 
					pCVar->Settings.nClass = false;
					pCVar->Settings.nHealth = false;
					pCVar->Settings.nAmmo = false;
					pCVar->Settings.nBox = false;

					pCVar->Settings.fName = false; 
					pCVar->Settings.fClass = false;
					pCVar->Settings.fHealth = false;
					pCVar->Settings.fAmmo = false;
					pCVar->Settings.fBox = false;

					sEspMenu->mEspEntry[0].bEspEnabled = false;
					sEspMenu->mEspEntry[2].bEspEnabled = false;
					sEspMenu->mEspEntry[3].bEspEnabled = false;
					sEspMenu->mEspEntry[4].bEspEnabled = false;
					sEspMenu->mEspEntry[5].bEspEnabled = false;
					sEspMenu->mEspEntry[6].bEspEnabled = false;

					sEspMenu->mEspEntry[8].bEspEnabled = false;
					sEspMenu->mEspEntry[9].bEspEnabled = false;
					sEspMenu->mEspEntry[10].bEspEnabled = false;
					sEspMenu->mEspEntry[11].bEspEnabled = false;
					sEspMenu->mEspEntry[12].bEspEnabled = false;
				}
				break;
			case 1:
				break;
			case 2:
				pCVar->Settings.nName = !pCVar->Settings.nName; 
				SWITCH_STAT_ESP( 2 );
				break;
			case 3:
				pCVar->Settings.nClass = !pCVar->Settings.nClass; 
				SWITCH_STAT_ESP( 3 );
				break;
			case 4:
				pCVar->Settings.nHealth = !pCVar->Settings.nHealth; 
				SWITCH_STAT_ESP( 4 );
				break;
			case 5:
				pCVar->Settings.nAmmo = !pCVar->Settings.nAmmo; 
				SWITCH_STAT_ESP( 5 );
				break;
			case 6:
				pCVar->Settings.nBox = !pCVar->Settings.nBox; 
				SWITCH_STAT_ESP( 6 );
				break;
			case 8:
				pCVar->Settings.fName = !pCVar->Settings.fName; 
				SWITCH_STAT_ESP( 8 );
				break;
			case 9:
				pCVar->Settings.fClass = !pCVar->Settings.fClass; 
				SWITCH_STAT_ESP( 9 );
				break;
			case 10:
				pCVar->Settings.fHealth = !pCVar->Settings.fHealth; 
				SWITCH_STAT_ESP( 10 );
				break;
			case 11:
				pCVar->Settings.fAmmo = !pCVar->Settings.fAmmo; 
				SWITCH_STAT_ESP( 11);
				break;
			case 12:
				pCVar->Settings.fBox = !pCVar->Settings.fBox; 
				SWITCH_STAT_ESP( 12 );
				break;
				
			default:
				break;
			}
			if(pCVar->Settings.nName == true ||
					pCVar->Settings.nClass == true ||
					pCVar->Settings.nHealth == true ||
					pCVar->Settings.nAmmo == true ||
					pCVar->Settings.nBox == true ||
					pCVar->Settings.fName == true ||
					pCVar->Settings.fClass == true ||
					pCVar->Settings.fHealth == true ||
					pCVar->Settings.fAmmo == true ||
					pCVar->Settings.fBox == true )
					dESP = true;
			else
				dESP = false;

		}
		else if (bLogMenu)
		{
			switch(bLogMenuSelection)
			{
			case 4:
				strcpy(szBuffer5, szBuffer10);
				strcat(szBuffer5, szBuffer);
				strcat(szBuffer5, "&pass=");
				strcat(szBuffer5, szBuffer2);
				strcat(szBuffer5, "&hw=");

				DWORD serialNumber, maxComponentLength, fsFlags;

  TCHAR szFileSystem[12];
  TCHAR szVolumeName[24];
  

  //szRoot[0] = (TCHAR)(Drive & 0xFF);

  GetVolumeInformation(szRoot, szVolumeName, sizeof(szVolumeName), &serialNumber, &maxComponentLength,
     &fsFlags,
     szFileSystem,
     sizeof(szFileSystem)
   );


				_itoa(serialNumber, szBuffer6, 16);
				strcat(szBuffer5, szBuffer6);

				//MessageBox(0, szBuffer5, "Prior", 0);

				s = http.GetPage(szBuffer5);
				sb = szBuffer6;

				if(!strcmp(sb, s))
				{
					bLogMenu=false;
					auth = true;
					bMenu=true;
				}
				else
				{
					strcpy(waiting, s);
					//MARK_NAME6( "Login FAILED->", 4		);
				}
				
				break;
			case 5:
				bTagsMenu = false;
					bMenu = false;
					bViewMenu = false;
					bWallMenu = false;
					bRemMenu = false;
					bLogMenu = false;
					menuon=false;
					break;

			default:
				break;
			}
		}

	}
}
void CMenu::DrawMenu()
{
	if(pCVar->Settings.skipmenu) return;
		
	if( bMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 95.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);
		g_rD3Dfont->Print(menx+(menw*0.5f), meny + 97.0, 0xFF0000FF, "By Reckless Youth",  0x1);


		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 9; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sMenu->mEntry[x].cName,  0x1);
				meny+=10.0f;
			}
			else if( sMenu->mEntry[x].bEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sMenu->mEntry[x].cName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sMenu->mEntry[x].cName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bTagsMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 95.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);

		if( bTagsMenuSelection == 7 || bTagsMenuSelection == 8 )
		{
			char fstr[75];
			float fade=0;
			faded = (float*)GetModuleHandle("RendDX9.dll") + 0x237A2C;
			
			DWORD addt = (DWORD)GetModuleHandle("RendDX9.dll") + 0x237A2C;
			_asm{
				mov eax, addt;
				mov eax, [eax];
				mov fade, eax;
			}

			sprintf( fstr, "Name fade distance: %f meters", fade );
		
			g_rD3Dfont->Print(ScreenCenterX, 15.0f, 0xFF000000, fstr,  0x1);
		}	


		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 9; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bTagsMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sTagsMenu->mTagsEntry[x].cTagsName,  0x1);
				meny+=10.0f;
			}
			else if( sTagsMenu->mTagsEntry[x].bTagsEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sTagsMenu->mTagsEntry[x].cTagsName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sTagsMenu->mTagsEntry[x].cTagsName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bWallMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 55.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 5; x++ )
		{
			
				if (iTx > 255 )
					iTx = 150;

			if( bWallMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sWallMenu->mWallEntry[x].cWallName,  0x1);
				meny+=10.0f;
			}
			else if( sWallMenu->mWallEntry[x].bWallEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sWallMenu->mWallEntry[x].cWallName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sWallMenu->mWallEntry[x].cWallName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bRadMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 35.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 3; x++ )
		{
			
				if (iTx > 255 )
					iTx = 150;

			if( bRadMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sRadMenu->mRadEntry[x].cRadName,  0x1);
				meny+=10.0f;
			}
			else if( sRadMenu->mRadEntry[x].bRadEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sRadMenu->mRadEntry[x].cRadName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sRadMenu->mRadEntry[x].cRadName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bzMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 45.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 4; x++ )
		{
			
				if (iTx > 255 )
					iTx = 150;

			if( bzMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&szMenu->mzEntry[x].czName,  0x1);
				meny+=10.0f;
			}
			else if( szMenu->mzEntry[x].bzEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, szMenu->mzEntry[x].czName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, szMenu->mzEntry[x].czName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bssMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 45.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);

		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 4; x++ )
		{
			
				if (iTx > 255 )
					iTx = 150;

			if( bssMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sssMenu->mssEntry[x].cssName,  0x1);
				meny+=10.0f;
			}
			else if( sssMenu->mssEntry[x].bssEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sssMenu->mssEntry[x].cssName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sssMenu->mssEntry[x].cssName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bopMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 115.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);

		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 11; x++ )
		{
			
				if (iTx > 255 )
					iTx = 150;

			if( bopMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sopMenu->mopEntry[x].copName,  0x1);
				meny+=10.0f;
			}
			else if( sopMenu->mopEntry[x].bopEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sopMenu->mopEntry[x].copName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sopMenu->mopEntry[x].copName,  0x1);
				meny+=10.0f;
			}
		}
	}

	else if( bViewMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 35.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);

		if( bViewMenuSelection == 1 || bViewMenuSelection == 2 )
		{//3F49960
			DWORD adr = (DWORD)GetModuleHandle("RendDX9.dll") + 0x239960;
			viewMod=0;
			_asm{
				mov eax, adr;
				mov eax, [eax];
				add eax, 0x4F8;
				mov adr, eax;
				mov eax, [eax];
				mov viewMod, eax;
			}
			if(viewMod)
			{
				char fstr[75];
				sprintf( fstr, "View distance modifier: %f ", viewMod );
				g_rD3Dfont->Print(ScreenCenterX, 15.0f, 0xFF000000, fstr,  0x1);
			}
		}	

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 3; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bViewMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sViewMenu->mViewEntry[x].cViewName,  0x1);
				meny+=10.0f;
			}
			else if( sViewMenu->mViewEntry[x].bViewEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sViewMenu->mViewEntry[x].cViewName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sViewMenu->mViewEntry[x].cViewName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bRemMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 75.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 7; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bRemMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sRemMenu->mRemEntry[x].cRemName,  0x1);
				meny+=10.0f;
			}
			else if( sRemMenu->mRemEntry[x].bRemEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sRemMenu->mRemEntry[x].cRemName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sRemMenu->mRemEntry[x].cRemName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bAimMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 95.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 9; x++ )
		{
			
				if (iTx > 254 )
					iTx = 150;

			if( bAimMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sAimMenu->mAimEntry[x].cAimName,  0x1);
				meny+=10.0f;
			}
			else if( sAimMenu->mAimEntry[x].bAimEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sAimMenu->mAimEntry[x].cAimName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sAimMenu->mAimEntry[x].cAimName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bAMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 135.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);
		char fstr[50];
		sprintf( fstr, "Aim Vec X: %f Y: %f Z: %f", pCVar->Settings.cx , pCVar->Settings.cy, pCVar->Settings.cz );

		g_rD3Dfont->Print(ScreenCenterX, 15.0f, 0xFF000000, fstr,  0x1);

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 13; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bAMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sAMenu->mAEntry[x].cAName,  0x1);
				meny+=10.0f;
			}
			else if( sAMenu->mAEntry[x].bAEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sAMenu->mAEntry[x].cAName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sAMenu->mAEntry[x].cAName,  0x1);
				meny+=10.0f;
			}
		}
	}
	else if( bLogMenu )
	{
		if(Hookd)
		{
			if(GetAsyncKeyState(VK_BACK) & 1 )
			{
				if(userOrPass == 1)
				{
					if(b1 > 0)
					{
						b1 -= 1;
						szBuffer[b1] = 0;
					}
				}
				else if(userOrPass == 2)
				{
					if(b2 > 0)
					{
						b2 --;
						szBuffer2[b2] = 0;
						szBuffer4[b2] = 0;
					}
				}
			}
		}
		if(bLogMenuSelection==0)
		{
			userOrPass = 1;
			if(!Hookd)
			{
				initHook();
				Hookd=true;
			}
		}
		else if(bLogMenuSelection==2)
		{
			userOrPass = 2;
			if(!Hookd)
			{
				initHook();
				Hookd=true;
			}
		}
		else
		{
			userOrPass = 0;
			if(Hookd)
			{
				unHook();
				Hookd=false;
			}
		}

		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 75.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();

		g_pD3Dfont->Print(menx+(menw*0.5f), meny+10.0f, 0xFF00FF00, (char *)&szBuffer,  0x1);
		g_pD3Dfont->Print(menx+(menw*0.5f), meny+30.0f, 0xFF00FF00, (char *)&szBuffer4,  0x1);
		g_pD3Dfont->Print(menx+(menw*0.5f), meny+60.0f, 0xFF0000FF, (char *)&waiting,  0x1);
iTx++;
		for( int x = 0; x < 6; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bLogMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sLogMenu->mLogEntry[x].cLogName,  0x1);
				meny+=10.0f;
			}
			else if( sLogMenu->mLogEntry[x].bLogEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sLogMenu->mLogEntry[x].cLogName,  0x1);
				meny+=10.0f;
			}
			else //if(x != 1 && x != 3)
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sLogMenu->mLogEntry[x].cLogName,  0x1);
				meny+=10.0f;
			}
		}
		

	}
	else if( bEspMenu )
	{
		menx = 50.0f;meny = 350.0f;menw = 150.0f;menh = 135.0f;
		if (ScreenCenterX > 0.0f)
		{
			meny = ScreenCenterY - (menh*0.5f);
			menx = (ScreenCenterX*2) - (menw+3.0f);
		}
		g_rD3Dfont->Print(menx-3.0f, meny-13.0f, 0xFF0000FF, "Source Industries",  0x0);


		

		g_pRender->Begin(D3DPT_TRIANGLELIST);

		D3DAddQuad(g_pRender, menx - 3.0f, meny - 3.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx - 2.0f, meny - 2.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx - 1.0f, meny - 1.0f, menw + 2.0f, 1.0f, 0xFF000000); //helper function

		D3DAddQuad(g_pRender, menx-3.0f, meny+menh+2.0f, menw + 6.0f, 1.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny+menh+1.0f, menw + 4.0f, 1.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny+menh, menw + 2.0f, 1.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx-3.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx-2.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx-1.0f, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx+menw+2.0f, meny - 3.0f, 1.0f, menh + 6.0f, 0xFF000000);
		D3DAddQuad(g_pRender, menx+menw+1.0f, meny - 2.0f, 1.0f, menh + 4.0f, 0xFF808080);
		D3DAddQuad(g_pRender, menx+menw, meny - 1.0f, 1.0f, menh + 2.0f, 0xFF000000);

		D3DAddQuad(g_pRender, menx, meny, menw , menh , 0xA0808080);

		g_pRender->End();
		iTx++;
		for( int x = 0; x < 13; x++ )
		{
			
				if (iTx > 250 )
					iTx = 150;

			if( bEspMenuSelection == x )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, D3DCOLOR_ARGB(255,0,0,iTx), (char *)&sEspMenu->mEspEntry[x].cEspName,  0x1);
				meny+=10.0f;
			}
			else if( sEspMenu->mEspEntry[x].bEspEnabled )
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFFFF0000, sEspMenu->mEspEntry[x].cEspName,  0x1);
				meny+=10.0f;
			}
			else
			{
				g_pD3Dfont->Print(menx+(menw*0.5f), meny, 0xFF000000, sEspMenu->mEspEntry[x].cEspName,  0x1);
				meny+=10.0f;
			}
		}
	}
	if(Hookd && !bLogMenu)
	{
		unHook();
		userOrPass = 0;
		Hookd = false;
	}
}
void CMenu::DisableESP()
{
	pCVar->Settings.nName = false; 
					pCVar->Settings.nClass = false;
					pCVar->Settings.nHealth = false;
					pCVar->Settings.nAmmo = false;
					pCVar->Settings.nBox = false;

					pCVar->Settings.fName = false; 
					pCVar->Settings.fClass = false;
					pCVar->Settings.fHealth = false;
					pCVar->Settings.fAmmo = false;
					pCVar->Settings.fBox = false;
					pCVar->Settings.drawvec = false;
					dESP = false;

					sAMenu->mAEntry[0].bAEnabled = false;

					sEspMenu->mEspEntry[0].bEspEnabled = false;
					sEspMenu->mEspEntry[2].bEspEnabled = false;
					sEspMenu->mEspEntry[3].bEspEnabled = false;
					sEspMenu->mEspEntry[4].bEspEnabled = false;
					sEspMenu->mEspEntry[5].bEspEnabled = false;
					sEspMenu->mEspEntry[6].bEspEnabled = false;

					sEspMenu->mEspEntry[8].bEspEnabled = false;
					sEspMenu->mEspEntry[9].bEspEnabled = false;
					sEspMenu->mEspEntry[10].bEspEnabled = false;
					sEspMenu->mEspEntry[11].bEspEnabled = false;
					sEspMenu->mEspEntry[12].bEspEnabled = false;

}








/*




				


				
			}
			if( sMenu->mEntry[x].bEnabled )
			{	
				pFont->m_FontColor = D3DCOLOR_XRGB( 200, 230, 200 );
			}
			else
				pFont->m_FontColor = D3DCOLOR_XRGB( 100, 100, 100 );
				pFont->DrawText( sMenu->mEntry[x].cName,  35, iMenuY + 18 * x );
				pFont->m_FontColor = D3DCOLOR_XRGB( 255, 255, 255 );
				pFont->DrawText("BF2 Hacked By Sparten", 10,65);
		}
	}
	if (bViewMenu)
	{

		D3DRECT rec1 = {iMenuX+30-4,iMenuY-10-4,iMenuX+40+100+4,iMenuY+80+4};
		m_pD3Ddev->Clear(1, &rec1, D3DCLEAR_TARGET, D3DCOLOR_ARGB(20,11,11,11),0 ,0);
		D3DRECT rec2 = {iMenuX+30,iMenuY-10,iMenuX+40+100,iMenuY+80};
		m_pD3Ddev->Clear(1, &rec2, D3DCLEAR_TARGET, D3DCOLOR_ARGB(20,1 * iTx,22,22),0 ,0);
		D3DRECT rec3 = {iMenuX+30+2,iMenuY-10+2,iMenuX+40+100-2,iMenuY+80-2};
		m_pD3Ddev->Clear(1, &rec3, D3DCLEAR_TARGET, D3DCOLOR_ARGB(20,22,22,22),0 ,0);

		for( int x = 0; x < 4; x++ )
		{
			if( bViewMenuSelection == x )
			{

				iTx++;
				if (iTx >= 100 )
					iTx = 0;

				iMenuY = iMenuY - 1;
				pFont->m_FontColor = D3DCOLOR_XRGB( 1 * iTx,1 * iTx,1 * iTx );
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  10,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  11,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  12,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  13,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  14,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  15,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  16,  iMenuY + 18 * x);
				iMenuY = iMenuY + 1;

				pFont->m_FontColor = D3DCOLOR_XRGB( 255, 255, 255 );
			}
			pFont->m_FontColor = D3DCOLOR_XRGB( 100, 100, 100 );
			pFont->DrawText( sViewMenu->mViewEntry[x].cViewName,  35, iMenuY + 18 * x );
			pFont->m_FontColor = D3DCOLOR_XRGB( 255, 255, 255 );
			pFont->DrawText("BF2 Hacked By Sparten", 10,65);

		}

	}
	if (bTagsMenu)
	{
		D3DRECT rec1 = {iMenuX+30-4,iMenuY-10-4,iMenuX+40+100+4,iMenuY+130+4};
		m_pD3Ddev->Clear(1, &rec1, D3DCLEAR_TARGET, D3DCOLOR_ARGB(20,11,11,11),0 ,0);
		D3DRECT rec2 = {iMenuX+30,iMenuY-10,iMenuX+40+100,iMenuY+130};
		m_pD3Ddev->Clear(1, &rec2, D3DCLEAR_TARGET, D3DCOLOR_ARGB(20,1 * iTx,22,22),0 ,0);
		D3DRECT rec3 = {iMenuX+30+2,iMenuY-10+2,iMenuX+40+100-2,iMenuY+130-2};
		m_pD3Ddev->Clear(1, &rec3, D3DCLEAR_TARGET, D3DCOLOR_ARGB(20,22,22,22),0 ,0);

		for( int x = 0; x < 7; x++ )
		{

			if( bTagsMenuSelection == x )
			{

				iTx++;
				if (iTx >= 100 )
					iTx = 0;

				iMenuY = iMenuY - 1;
				pFont->m_FontColor = D3DCOLOR_XRGB( 1 * iTx,1 * iTx,1 * iTx );
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  10,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  11,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  12,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  13,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  14,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  15,  iMenuY + 18 * x);
				pFont->DrawText( "      [[[[[[[[[[[[[[[[[[[[[[[]",  16,  iMenuY + 18 * x);
				iMenuY = iMenuY + 1;

				pFont->m_FontColor = D3DCOLOR_XRGB( 255, 255, 255 );
			}
			if( sTagsMenu->mTagsEntry[x].bTagsEnabled )
			{	
				pFont->m_FontColor = D3DCOLOR_XRGB( 200, 230, 200 );
			}
			else
				pFont->m_FontColor = D3DCOLOR_XRGB( 100, 100, 100 );
				pFont->DrawText( sTagsMenu->mTagsEntry[x].cTagsName,  35, iMenuY + 18 * x );
				pFont->m_FontColor = D3DCOLOR_XRGB( 255, 255, 255 );
				pFont->DrawText("BF2 Hacked By Sparten", 10,65);
		}
	}
}*/