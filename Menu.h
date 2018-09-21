#ifndef _MENU_H
#define _MENU_H

#include "d3d9.h"

#define SWITCH_STAT( index ) sMenu->mEntry[index].bEnabled = !sMenu->mEntry[index].bEnabled;
#define SWITCH_STAT_TAGS( index ) sTagsMenu->mTagsEntry[index].bTagsEnabled = !sTagsMenu->mTagsEntry[index].bTagsEnabled;
//#define SWITCH_STAT_VIEW( index ) sViewMenu->mViewEntry[index].bViewEnabled = !sVeiwMenu->mVeiwEntry[index].bVeiwEnabled;
#define SWITCH_STAT_WALL( index ) sWallMenu->mWallEntry[index].bWallEnabled = !sWallMenu->mWallEntry[index].bWallEnabled;
#define SWITCH_STAT_VIEW( index ) sViewMenu->mViewEntry[index].bViewEnabled = !sViewMenu->mViewEntry[index].bViewEnabled;
#define SWITCH_STAT_REM( index ) sRemMenu->mRemEntry[index].bRemEnabled = !sRemMenu->mRemEntry[index].bRemEnabled;
#define SWITCH_STAT_AIM( index ) sAimMenu->mAimEntry[index].bAimEnabled = !sAimMenu->mAimEntry[index].bAimEnabled;
#define SWITCH_STAT_ESP( index ) sEspMenu->mEspEntry[index].bEspEnabled = !sEspMenu->mEspEntry[index].bEspEnabled;
#define SWITCH_STAT_A( index ) sAMenu->mAEntry[index].bAEnabled = !sAMenu->mAEntry[index].bAEnabled;
#define SWITCH_STAT_SS( index ) sssMenu->mssEntry[index].bssEnabled = !sssMenu->mssEntry[index].bssEnabled;
#define SWITCH_STAT_OP( index ) sopMenu->mopEntry[index].bopEnabled = !sopMenu->mopEntry[index].bopEnabled;
#define SWITCH_STAT_Z( index ) szMenu->mzEntry[index].bzEnabled = !szMenu->mzEntry[index].bzEnabled;
#define SWITCH_STAT_RAD( index ) sRadMenu->mRadEntry[index].bRadEnabled = !sRadMenu->mRadEntry[index].bRadEnabled;

#define MARK_NAME1( name, index ) strcpy( sMenu->mEntry[index].cName, name );
#define MARK_NAME2( name, index ) strcpy( sTagsMenu->mTagsEntry[index].cTagsName, name );
#define MARK_NAME3( name, index ) strcpy( sWallMenu->mWallEntry[index].cWallName, name );
#define MARK_NAME4( name, index ) strcpy( sViewMenu->mViewEntry[index].cViewName, name );
#define MARK_NAME5( name, index ) strcpy( sRemMenu->mRemEntry[index].cRemName, name );
#define MARK_NAME6( name, index ) strcpy( sLogMenu->mLogEntry[index].cLogName, name );
#define MARK_NAME7( name, index ) strcpy( sAimMenu->mAimEntry[index].cAimName, name );
#define MARK_NAME8( name, index ) strcpy( sEspMenu->mEspEntry[index].cEspName, name );
#define MARK_NAME9( name, index ) strcpy( sAMenu->mAEntry[index].cAName, name );
#define MARK_NAME10( name, index ) strcpy( sssMenu->mssEntry[index].cssName, name );
#define MARK_NAME11( name, index ) strcpy( sopMenu->mopEntry[index].copName, name );
#define MARK_NAME12( name, index ) strcpy( szMenu->mzEntry[index].czName, name );
#define MARK_NAME13( name, index ) strcpy( sRadMenu->mRadEntry[index].cRadName, name );


class CMenu
{
public:
	CMenu(IDirect3DDevice9 *pIDirect3DDevice9);
	~CMenu( );
	
	void popmenu	( void );
	void LogMenu	( void );
	void MainMenu	( void );
	void TagsMenu	( void );
	void WallMenu	( void );
	void ViewMenu	( void );
	void RemMenu	( void );
	void AimMenu	( void );
	void ssMenu	( void );
	void opMenu	( void );
	void zMenu	( void );
	void RadMenu	( void );
	void InitMenu   ( void );
	void EspMenu   ( void );
	void AMenu   ( void );
	void MenuSelection( void );
	void DrawMenu  ( void );
	void DrawTimeDate(void);
	void DisableESP(void);

	struct s_MenuEntry
	{
		bool	bEnabled;
		char	cName[40];
	};
	struct s_MenuLogEntry
	{
		bool	bLogEnabled;
		char	cLogName[40];
	};

	struct s_MenuTagsEntry
	{
		bool	bTagsEnabled;
		char	cTagsName[40];
	};

	struct s_MenuWallEntry
	{
		bool	bWallEnabled;
		char	cWallName[40];
	};

	struct s_MenuViewEntry
	{
		bool	bViewEnabled;
		char	cViewName[40];
	};
	struct s_MenuRadEntry
	{
		bool	bRadEnabled;
		char	cRadName[40];
	};
	struct s_MenuRemEntry
	{
		bool	bRemEnabled;
		char	cRemName[80];
	};
	struct s_MenuAimEntry
	{
		bool	bAimEnabled;
		char	cAimName[80];
	};
	struct s_MenuAEntry
	{
		bool	bAEnabled;
		char	cAName[80];
	};
	struct s_MenuEspEntry
	{
		bool	bEspEnabled;
		char	cEspName[80];
	};
	struct s_MenussEntry
	{
		bool	bssEnabled;
		char	cssName[80];
	};
	struct s_MenuopEntry
	{
		bool	bopEnabled;
		char	copName[80];
	};
	struct s_MenuzEntry
	{
		bool	bzEnabled;
		char	czName[40];
	};


	struct s_Menu
	{
		s_MenuEntry mEntry[30];
	};

	struct s_TagsMenu
	{
		s_MenuTagsEntry mTagsEntry[30];
	};
	struct s_LogMenu
	{
		s_MenuLogEntry mLogEntry[30];
	};

	struct s_WallMenu
	{
		s_MenuWallEntry mWallEntry[30];
	};

	struct s_ViewMenu
	{
		s_MenuViewEntry mViewEntry[30];
	};
	struct s_RadMenu
	{
		s_MenuRadEntry mRadEntry[30];
	};
	struct s_RemMenu
	{
		s_MenuRemEntry mRemEntry[50];
	};
	struct s_AimMenu
	{
		s_MenuAimEntry mAimEntry[50];
	};
	struct s_AMenu
	{
		s_MenuAEntry mAEntry[50];
	};
	struct s_ssMenu
	{
		s_MenussEntry mssEntry[50];
	};
	struct s_opMenu
	{
		s_MenuopEntry mopEntry[50];
	};
	struct s_EspMenu
	{
		s_MenuEspEntry mEspEntry[50];
	};
		struct s_zMenu
	{
		s_MenuzEntry mzEntry[30];
	};

	s_Menu			*sMenu;
	s_LogMenu		*sLogMenu;
	s_TagsMenu		*sTagsMenu;
	s_WallMenu		*sWallMenu;
	s_ViewMenu		*sViewMenu;
	s_RemMenu		*sRemMenu;
	s_AimMenu		*sAimMenu;
	s_AMenu		*sAMenu;
	s_ssMenu		*sssMenu;
	s_opMenu		*sopMenu;
	s_EspMenu		*sEspMenu;
	s_zMenu		*szMenu;
	s_RadMenu		*sRadMenu;
	
	bool bMenu;
	bool bLogMenu;
	bool bTagsMenu;
	bool bWallMenu;
	bool bViewMenu;
	bool bRemMenu;
	bool bAimMenu;
	bool bAMenu;
	bool bssMenu;
	bool bopMenu;
	bool bEspMenu;
	bool bzMenu;
	bool bRadMenu;

	bool menuon;

	int iClockX;
	int iClockY;
	int iMenuX;
	int iMenuY;

	int AimKey;

	int iTx ;

	int bMenuSelection;
	int bTagsMenuSelection;
	int bWallMenuSelection;
	int bViewMenuSelection;
	int bRemMenuSelection;
	int bLogMenuSelection;
	int bAimMenuSelection;
	int bAMenuSelection;
	int bssMenuSelection;
	int bopMenuSelection;
	int bEspMenuSelection;
	int bzMenuSelection;
	int bRadMenuSelection;
private:
	IDirect3DDevice9 *m_pD3Ddev;

};
#endif; //_MENU_H