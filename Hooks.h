#define WIN32_LEAN_AND_MEAN
//typedef IDirect3D9 *(APIENTRY *tDirect3DCreate9)(UINT);
//extern tGetProcAddress oGetProcAddress;
class CPlayerManager;
//class CNameTagManager;

class CPlayer;
class CViewMatrix;
class CInfo;
class CPlayerInfo;
class CVehicle;
class CVTable;
class class6;
class class7;
class CHealth;

void MakeDelta(float *src, float *dst, float *vec) ;

void MakeAngle(float *vec, float *angle) ;

bool bWorldtoScreenx( IDirect3DDevice9* pDevice, CPlayer* pPlayer, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch);

bool bWorldtoScreenx1( IDirect3DDevice9* pDevice, CPlayer* pPlayer, D3DXVECTOR3 *PlayerV, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch);

bool bWorldtoScreenx12( IDirect3DDevice9* pDevice, CPlayer* pPlayer, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch);


bool bWorldtoScreenxall( IDirect3DDevice9* pDevice, CPlayer* pPlayer, D3DXVECTOR3 *PlayerW, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch);

void CalcAngle( const float* vSource, const float* vDest, float* vAngles );

typedef struct 
{
	void (__stdcall * pFunc0 )( void );
	void (__stdcall * pFunc1 )( void );
	void (__stdcall * pFunc2 )( void );
	void (__stdcall * pFunc3 )( void );
	void (__stdcall * pFunc4 )( void );
	void (__stdcall * pFunc5 )( void );
	void (__stdcall * pFunc6 )( void );
	void (__stdcall * pFunc7 )( void );
	void (__stdcall * pFunc8 )( void );
	void (__stdcall * pFunc9 )( void );
	void (__stdcall * pFunc10 )( void );
	void (__stdcall * pFunc11 )( void );
	void (__stdcall * pFunc12 )( void );
	void (__stdcall * pFunc13 )( void );
	void (__stdcall * pFunc14 )( void );
	void (__stdcall * pFunc15 )( void );
	void (__stdcall * pFunc16 )( void );
	void (__stdcall * pFunc17 )( void );
	PDWORD* (__stdcall * pImportClassbyName )( DWORD* strClassName );
	void (__stdcall * pFunc19 )( void );
	void (__stdcall * pFunc20 )( void );
	void (__stdcall * pFunc21 )( void );
	void (__stdcall * pFunc22 )( void );
} CClassManager;


class CPlayerManager
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual CPlayer* pGetPlayerByIndex( int Index );
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual CPlayer* pGetLocalePlayer();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual DWORD pGetPlayersConnected();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
};

class CNameTagManager
{
public:
	virtual int iGetNextIndex () = 0;
	virtual int iGetCurrentIndex () = 0;
	virtual void Destructor () = 0;
	virtual BOOL bCheck ( DWORD dwArgument ) = 0;	
	virtual void MiniMapMSG ( DWORD dwArgument, DWORD dwArgument1 ) = 0;
	virtual void FuncDrawTAGS ( BYTE bDrawn, int Index, float flValue, float flValue2 ) = 0;
	virtual void Function6() = 0;
	virtual void Function7() = 0;
	virtual void Function8() = 0;
	virtual void Function9() = 0;
	virtual void Function10() = 0;
	virtual void Function11() = 0;
	virtual void Function12() = 0;
	virtual void Function13() = 0;
	virtual void Function14() = 0;
	virtual void Function15() = 0;
	virtual void Function16() = 0;
	virtual void Function17() = 0;
	virtual void Function18() = 0;
	virtual void Function19() = 0;
	virtual void Function20() = 0;
	virtual void Function21() = 0;
	virtual void Function22() = 0;
	virtual void Function23() = 0;
	virtual void Function24() = 0;
	virtual void Function25() = 0;
	virtual void Function26() = 0;
	virtual void Function27() = 0;
	//void setTags(DWORD *pFunct){FuncDrawTAGS = pFunct;}
};

class CDTagManager : public CNameTagManager
{
public:
	virtual int iGetNextIndex ()=0;
	int iGetCurrentIndex ()=0;
	virtual void Destructor ()=0;
	virtual BOOL bCheck ( DWORD dwArgument )=0;	
	virtual void MiniMapMSG ( DWORD dwArgument, DWORD dwArgument1 )=0;
	void FuncDrawTAGS ( BYTE bDrawn, int Index, float flValue, float flValue2 )=0;
	virtual void Function6()=0;
	virtual void Function7()=0;
	virtual void Function8()=0;
	virtual void Function9()=0;
	virtual void Function10()=0;
	virtual void Function11()=0;
	virtual void Function12()=0;
	virtual void Function13()=0;
	virtual void Function14()=0;
	virtual void Function15()=0;
	virtual void Function16()=0;
	virtual void Function17()=0;
	virtual void Function18()=0;
	virtual void Function19()=0;
	virtual void Function20()=0;
	virtual void Function21()=0;
	virtual void Function22()=0;
	virtual void Function23()=0;
	virtual void Function24()=0;
	virtual void Function25()=0;
	virtual void Function26()=0;
	virtual void Function27()=0;
	DWORD getThis();
	void FuncDrawTAGSs ( BYTE bDrawn, int Index, float flValue, float flValue2 );

	//CNameTagManager *clone() {return new CDTagManager(*this);}
};


typedef void (CDTagManager::*TypeAPtr)(unsigned char,int,float,float);

/*CNameTagManager *someMethod (
  std::map<int,CNameTagManager *> clonables, int type)
{
return clonables[type]->clone();
}

*/

typedef struct  
{
	int		(__stdcall* iGetNextIndex )( void );
	int		(__stdcall* iGetCurrentIndex )( void );
	void	(__stdcall* Destructor )( void );
	BOOL	(__stdcall* bCheck )( DWORD dwArgument );	
	void	(__stdcall* MiniMapMSG )( DWORD dwArgument, DWORD dwArgument1 );
	void	(__stdcall* FuncDrawTAGS )( BYTE bDrawn, int Index, float flValue, float flValue2 );
	BOOL	(__stdcall* bIsActive )( void );
	void (__stdcall * pFunc6 )( void );
	void (__stdcall * pFunc7 )( void );
	void (__stdcall * pFunc8 )( void );
	void (__stdcall * pFunc9 )( void );
	void (__stdcall * pFunc10 )( void );
	void (__stdcall * pFunc11 )( void );
	void (__stdcall * pFunc12 )( void );
	void (__stdcall * pFunc13 )( void );
	void (__stdcall * pFunc14 )( void );
	void (__stdcall * pFunc15 )( void );
	void (__stdcall * pFunc16 )( void );
	void (__stdcall * pFunc17 )( void );
	void (__stdcall * pFunc18 )( void );
	void (__stdcall * pFunc19 )( void );
	void (__stdcall * pFunc20 )( void );
	void (__stdcall * pFunc21 )( void );
	void (__stdcall * pFunc22 )( void );
	void (__stdcall * pFunc23 )( void );
	void (__stdcall * pFunc24 )( void );
	void (__stdcall * pFunc25 )( void );
	void (__stdcall * pFunc26)( void );
	void (__stdcall * pFunc27 )( void );
	void (__stdcall * pFunc28 )( void );
	void (__stdcall * pFunc29 )( void );
	void (__stdcall * pFunc30 )( void );
	void (__stdcall * pFunc31 )( void );
	void (__stdcall * pFunc32 )( void );
	void (__stdcall * pFunc33 )( void );
	void (__stdcall * pFunc34 )( void );
	void (__stdcall * pFunc35 )( void );
	void (__stdcall * pFunc36)( void );
	void (__stdcall * pFunc37 )( void );


}CTagManager;





class CPlayer
{
public:
	CVTable* VTable; //0000
				char unknown0[84];
	__int32 Kit; //0058
				char unknown1[8];
	char Name[28]; //0064
	CInfo* Info; //0080
	CViewMatrix* ViewMatrix; //0084
				char unknown2[44];
	__int32 Spawned; //00B4
				char unknown3[8];
	float FOV; //00C0
				char unknown4[17];
	BYTE Dead; //00D5
				char unknown5[2];
	__int32 Team; //00D8
				char unknown6[4];
	BYTE ManDown; //00E0
				char unknown7[15];
	DWORD Ping; //00F0
				char unknown8[20];
	BYTE Commander; //0108
				char unknown9[19];
	BYTE InsideControlPoint; //011C
				char unknown10[106];
	BYTE Sprinting; //0187
				char unknown11[180];
	__int32 Ammo; //023C
				char unknown12[24];
	float WeaponHeatPrimary; //0258
	float WeaponHeatSecondary; //025C
				char unknown13[320];
	float Shooting; //03A0
};
class CViewMatrix
{
public:
				char unknown0[184];
	D3DXMATRIX Matrix; //00B8
			/*	char unknown1[44];
	float XPos; //00E8
	float YPos; //00EC
	float ZPos; //00F0
	float Unknown2; //00F4*/
};
class CInfo
{
public:
				char unknown0[4];
	CPlayerInfo* PlayerInfo; //0004
};
class CPlayerInfo
{
public:
	class7* Unknown0; //0000
				char unknown1[16];
	CVehicle* Vehicle; //0014
				char unknown2[4];
	class6* Unknown3; //001C
				char unknown4[28];
	CHealth* Health; //003C

				char unknown84[72];
	D3DXMATRIX Matrix; //0084
	/*			char unknown5[44];
	float XPos; //00B4
	float YPos; //00B8
	float ZPos; //00BC
	float Unknown6; //00C0*/
	//float Unknown7; //00C4
				char unknown8[252];
	BYTE SelectedWeapon; //01C4
				char unknown9[87];
	float Pitch; //021C
				char unknown10[4];
	float Unknown11; //0224
	float StrafeAcceleration; //0228
	float ForwardAccleration; //022C
	__int32 Posture; //0230
				char unknown12[4];
	float YAngle; //0238
				char unknown13[4];
	float XAngle; //0240
				char unknown14[256];
	float Stamina; //0344
	BYTE Unknown15; //0348
	BYTE Unknown16; //0349
	BYTE Sprinting; //034A
	BYTE Unknown17; //034B
};
class CVehicle
{
public:
				char unknown0[400];
	char VehicleName[16]; //0190
};
class CVTable
{
public:
};
class class6
{
public:
};
class class7
{
public:
};
class CHealth
{
public:
				char unknown0[16];
	float Health; //0010
};
void setCommander();
void setCommanderoff();






typedef FARPROC (WINAPI *tGetProcAddress)(IN HMODULE hModule, IN LPCSTR lpProcName );
extern tGetProcAddress pGetProcAddress;

void __cdecl HookinitDLL( CClassManager** pClsMgr );
typedef void (__cdecl *HookinitDLL_t)( CClassManager** pClsMgr );
extern HookinitDLL_t pHookinitDLL;

FARPROC WINAPI hkGetProcAddress(IN HMODULE hModule, IN LPCSTR lpProcName );


/*typedef struct  
{
	int		(__stdcall* iGetNextIndex )( void );
	int		(__stdcall* iGetCurrentIndex )( void );
	void	(__stdcall* Destructor )( void );
	BOOL	(__stdcall* bCheck )( DWORD dwArgument );	
	void	(__stdcall* MiniMapMSG )( DWORD dwArgument, DWORD dwArgument1 );
	void	(__stdcall* FuncDrawTAGS )( BYTE bDrawn, int Index, float flValue, float flValue2 );
	BOOL	(__stdcall* bIsActive )( void );
// lots of place holder to fill the class go here
}CNameTagManager;*/


/*
struct CGameVec
{
	DWORD	m_dwUnknown[33];
	float*	m_pflMatrix; // + 0x84
	DWORD	m_dwUnknown1[11];
	float	m_flXPos; // + 0xB4
	float	m_flYPos; // + 0xB8
	float	m_flZPos; // + 0xBC
};

struct CInfo
{
	DWORD		m_dwUnkown;
	CGameVec*	m_pPosition; //0004
};*/