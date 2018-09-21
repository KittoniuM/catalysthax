
#include <windows.h>
//#pragma warning(disable:4786)
//#include <string>
//#include <iostream>
#include <string>
#include <mbstring.h>
#include "main.h"
#include "d3d9.h"
#include "Hooks.h"
#include "AddLog.h"
#include "MemHacks.h"
#include "CVAR.h"
using namespace std;

#define M_PI		3.14159265358979323846
#define M_RADPI		57.295779513082f

/*struct mMatrix
{
	D3DXMATRIX world;
	D3DXMATRIX view;
};*/
D3DMATRIX *world;

D3DVECTOR viewprt;


CClassManager **ecxReg;
CClassManager *g_pClsMgr;
CClassManager gClassManager;
CClassManager gHookedClassManager;

CPlayerManager* pPlayerManager;

CNameTagManager *pNameTag;
CNameTagManager *gNameTag;

CDTagManager *hkNameTag;


tGetProcAddress pGetProcAddress;
HookinitDLL_t pHookinitDLL;

extern float ScreenCenterX;
extern float ScreenCenterY;
extern CCVAR *pCVar;

DWORD newmat = 1;
DWORD curmat = 0;
DWORD matc = 0;


PDWORD *ppdwReturnValue;

DWORD **ecxTag; DWORD *ecxHk; DWORD **gEcx;
DWORD gTag;
DWORD gGetMatrix;
//mMatrix *pMatrix;

bool back = false;

bool test1 = false;

CTagManager *pgtag;

float mody = -1.0f;


int matcount = 3;
bool dcoord = true;
bool mworld = true;



inline void MakeVector( const float* qAngle, float* qVector ) 
{ 
	float pitch = 0.0f; 
	float yaw = 0.0f; 
	float tmp = 0.0f;            

	pitch = (float)(qAngle[0] * M_PI/180.0f); 
	yaw = (float)(qAngle[1] * M_PI/180.0f); 
	tmp = (float)cos(pitch);

	qVector[0] = (float) (-tmp * -cos(yaw)); 
	qVector[1] = (float) (sin(yaw)*tmp);
	qVector[2] = (float) -sin(pitch);
}
void VectorSubtract(const float *in, const float *sub, float *res)
{
	for( int i = 0; i < 3; i++ )
		res[i] = in[i] - sub[i];
}
float VectorLength(float *in)
{
	float s = in[0]*in[0]+in[1]*in[1]+in[2]*in[2];
	if( s > 0.0 )
		s = (float)sqrt(s);
	return s;
}
float VectorAngle(float *v1, float *v2)
{
  int k;
  float dotprod = 0.0, angle;
  
  for( k = 0; k < 3; k++ )
  {
    dotprod += v1[k]*v2[k];
  }   
  angle = (float)acos((double)dotprod/(VectorLength(v1)*VectorLength(v2)));
  return angle;
}
void VectorAngles(const float *forward, float *angles)
{
	float tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 90.0;
		else
			pitch = 270.0;
	}
	else
		yaw = (atan2(forward[1], forward[0]) * 180.0 / M_PI);

	if (yaw < 0) yaw += 360.0;
		tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
		
	pitch = (atan2(forward[2], tmp) * 180.0 / M_PI);

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
void MakeDelta(float *src, float *dst, float *vec) 
{ 
    vec[0] = src[0] - dst[0]; 
    vec[1] = src[1] - dst[1]; 
    vec[2] = src[2] - dst[2]; 
} 
float Degree(float radian) 
{ 
    return radian * (180/M_PI); 
} 
void MakeAngle(float *vec, float *angle) 
{ 
    float hyp = sqrt(vec[0]*vec[0] + vec[1]*vec[1]); 
    angle[0] = Degree(atan(vec[2]/hyp)); 
    angle[2] = 0.0f; 
    if(vec[0] >= 0) 
    { 
        if(vec[1] >= 0)        {    angle[1] = Degree(atan(fabs(vec[1]/vec[0]))) + 180;    } 
        else                {    angle[1] = Degree(atan(fabs(vec[0]/vec[1]))) + 90;    } 
    } 
    else 
    { 
        if(vec[1] >= 0)        {    angle[1] = Degree(atan(fabs(vec[0]/vec[1]))) + 270;    } 
        else                {    angle[1] = Degree(atan(fabs(vec[1]/vec[0])));        } 
    } 
} 

void CalcAngle( const float* vSource, const float* vDest, float* vAngles )
{
/*	double delta[3] = { (vSource[0]-vDest[0]), (vSource[1]-vDest[1]), (vSource[2]-vDest[2]) };
	double hyp = sqrt( delta[0]*delta[0] + delta[1]*delta[1] );

	vAngles[0] = (float) (atan(delta[2]/hyp) * M_RADPI);
	vAngles[1] = (float) (atan(delta[1]/delta[0]) * M_RADPI);
	vAngles[2] = 0.0f;

	if( delta[0] >= 0.0f )
		vAngles[1] += 180.0f;*/
	float aim[3];
	float ta[3];//, tb, tc;
	//flat flViewAngles[3];
	D3DXMATRIX view = world[1];

	ta[0] = view._13;
	ta[1] = view._23;
	ta[2] = view._33;

	/*

	if( ta == 0 && tb == 0 && tc == 0){
		newmat = 1; return false;}*/

	VectorSubtract(vDest,vSource,aim);		
	//MakeVector(vSource,view);
	VectorAngle(ta,aim); 

	float fLen = sqrtf(aim[2]*aim[2]);
	

	vAngles[0] = 180 / M_PI * atan2f( aim[1], fLen );
	vAngles[1] = 180 / M_PI * atan2f( aim[0], aim[2] );
	vAngles[2] = 0;


}

bool NewCalcScreen(const float* in, float* out, float flFov, float* mainViewOrigin, 
				  float* mainViewAngles, int displayCenterX, int displayCenterY)
{

	if(GetAsyncKeyState(VK_HOME)&1)
		test1 = !test1;


	float aim[3];
	float newaim[3];
//	float view[3];
//	float tmp[3];
	float num;

	if( flFov == 0.0f )
		return false;

/*if (tmp[0]>180)  tmp[0]-=360;
	if (tmp[1]>180)  tmp[1]-=360;
	if (tmp[0]<-180) tmp[0]+=360;
	if (tmp[1]<-180) tmp[1]+=360;*/
/*tmp = aim - mainViewAngles	*/

	CalcAngle(mainViewOrigin, in, aim);
//	add_log("Enemy Angle xyz: %f %f %f Local xyz: %f %f %f", aim[0], aim[1], aim[2], mainViewAngles[0], mainViewAngles[1], mainViewAngles[2]);

	newaim[0] = aim[0] * M_PI / 180.0f;
	newaim[1] = aim[1] * M_PI / 180.0f;
	newaim[2] = aim[2] * M_PI / 180.0f;

	if (newaim[0]>180)  newaim[0]-=360;
	if (newaim[1]>180)  newaim[1]-=360;
	if (newaim[0]<-180) newaim[0]+=360;
	if (newaim[1]<-180) newaim[1]+=360;	
	if(test1)
	{
	/*	newaim[0] = aim[0];
		newaim[1] = aim[1];
		newaim[2] = aim[2];*/
		newaim[0] = aim[0] - mainViewAngles[0];
		newaim[1] = aim[1] - mainViewAngles[1];
		newaim[2] = aim[2] - mainViewAngles[2];

		if (newaim[0]>180)  newaim[0]-=360;
		if (newaim[1]>180)  newaim[1]-=360;
		if (newaim[0]<-180) newaim[0]+=360;
		if (newaim[1]<-180) newaim[1]+=360;	
	}





/*	newaim[0] = aim[0] - mainViewAngles[0];
	newaim[1] = aim[1] - mainViewAngles[1];
	newaim[2] = aim[2] - mainViewAngles[2];

	if (newaim[0]>180)  newaim[0]-=360;
	if (newaim[1]>180)  newaim[1]-=360;
	if (newaim[0]<-180) newaim[0]+=360;
	if (newaim[1]<-180) newaim[1]+=360;

	if(test1)
	{
		newaim[0] += mainViewAngles[0];
		newaim[1] += mainViewAngles[1];
		newaim[2] += mainViewAngles[2];

		if (newaim[0]>180)  newaim[0]-=360;
		if (newaim[1]>180)  newaim[1]-=360;
		if (newaim[0]<-180) newaim[0]+=360;
		if (newaim[1]<-180) newaim[1]+=360;	
	}*/

	


	//VectorSubtract(in,mainViewOrigin,aim);	
	//MakeVector(mainViewAngles,view);
	//VectorAngle(view,aim);

	/*if (  > ( flFov/ 1.8 ) )
	{
		return false;
	}		

	VectorRotateZ(aim,-mainViewAngles[1],newaim);// yaw
	VectorRotateY(newaim,-mainViewAngles[0],tmp);// pitch
	VectorRotateX(tmp,-mainViewAngles[2],newaim);// roll*/

	//they are behind us!@~!#@!$@!$

	if (newaim[0] <= 0)
	{
		return false;
	}

	//tmp[0] = (displayCenterX / flFov) - 1.0/3.0);
	//tmp[1] = (displayCenterX / flFov) - 1.2/3.2);





	num = (float)((displayCenterX/newaim[0])*(120.0/flFov - 1.0/3.0));

//	add_log("NewView: %f %f %f Offset: %i", newaim[0], newaim[1], newaim[2], num);

	out[0] = displayCenterX - num*newaim[0];
	out[1] = displayCenterY - num*newaim[1];
//	add_log("Screen Vecs: %f %f", out[0], out[1]);

	return true;
}



bool bWorldtoScreenx( IDirect3DDevice9* pDevice, CPlayer* pPlayer, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch)
{
	/*if(GetAsyncKeyState(VK_F10)&1)
		mody += 0.1f;

	if(GetAsyncKeyState(VK_F9)&1)
		mody -= 0.1f;*/

	/*if(GetAsyncKeyState(VK_F8)&1)
	{
		matcount++;
		if(matcount == 8)
			matcount = 0;
	}*/
	if(pLocalPlayer->FOV == 0)
		return false;

	if(world == 0 || pDevice == 0) return false;

	//float flLocalPos[3], flRemotePos[3];flScreen[3],
//	float  flViewAngles[3];
	D3DXMATRIX View = world[1];
	D3DXMATRIX Proj = world[matcount];
	D3DXMATRIX World = world[0];
	/*if(mworld)
		World;
	else
	{
		World = pPlayer->ViewMatrix->Matrix;
		//add_log("PLAYERS MATRIX XYZ!!: %f %f %f", World._41, World._42, World._43);
	}*/


	D3DVIEWPORT9 Viewport;
	if(View._41 == 0 && View._42 == 0 && View._43 == 0){
		newmat = 1; return false;}

if( SUCCEEDED( pDevice->GetViewport( &Viewport ) ) == false )
		return false;

D3DXVECTOR3 PlayerW;
	
	PlayerW.x = pPlayer->Info->PlayerInfo->Matrix._41;

	if(pPlayer->Info->PlayerInfo->Health == 0)
		return false;

	if(pPlayer->Info->PlayerInfo->Health->Health > 0.0f && ch)
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42 + mody;
	else
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42;

	PlayerW.z = pPlayer->Info->PlayerInfo->Matrix._43;
	/*}if(dcoord)
	{
	else
	{
		PlayerW.x = 0;
	PlayerW.y = 0;
	PlayerW.z = 0;
	}*/
	

	if(!D3DXVec3Project( pScreen, &PlayerW, &Viewport, &Proj, &View, &World))
		return false;

	if(pScreen->z > 1.0f)
		return false;
//D3DXMATRIX View = world[1];
/*D3DVECTOR Angles;

float hyp = sqrtf(/*View._13 * View._13 + View._23 * View._23 + /View._33 * View._33 );

Angles.x = atan2f( View._13, View._33 ) * 180 / M_PI;
Angles.y = atan2f( View._23, hyp) * 180 / M_PI;
Angles.z = 0.0f;

viewprt.x = Angles.x;
	viewprt.y = Angles.y;
	viewprt.z = Angles.z;


	//add_log("Screen XYZ: %f %f %f", pScreen->x, pScreen->y, pScreen->z);

	

	/*flRemotePos[0] = pPlayer->Info->PlayerInfo->XPos;
	flRemotePos[1] = pPlayer->Info->PlayerInfo->YPos;
	flRemotePos[2] = pPlayer->Info->PlayerInfo->ZPos;

	flLocalPos[0] = pLocalPlayer->Info->PlayerInfo->XPos;
	flLocalPos[1] = pLocalPlayer->Info->PlayerInfo->YPos;
	flLocalPos[2] = pLocalPlayer->Info->PlayerInfo->ZPos;
*/
/*	float ta, tb, tc, vec[3];

	_asm{
		push eax;
		push ebx;
		mov eax, world;
		add eax, 0x48;
		mov ebx, [eax];	
		mov ta, ebx;	
		add eax, 0x10;
		mov ebx, [eax];
		mov tb, ebx;
		add eax, 0x10;
		mov ebx, [eax];
		mov tc, ebx;
		pop ebx;
		pop eax;
	}
	vec[0] = ta;
	vec[1] = tb;
	vec[2] = tc;
	MakeAngle(vec, flViewAngles);
/*
	float fLen = sqrtf(tc*tc);

	flViewAngles[0] = 180 / M_PI * atan2f( tb, fLen );
	flViewAngles[1] = 180 / M_PI * atan2f( ta, tc );
	flViewAngles[2] = 0;

	if( ta == 0 && tb == 0 && tc == 0){
		newmat = 1; return false;}

	viewprt.x = flViewAngles[0];
	viewprt.y = flViewAngles[1];
	viewprt.z = flViewAngles[2];*/


	//add_log("xyz: %f %f %f", ta, tb, tc);




	


	/*View._41 = 0;
	View._42 = 0;
	View._43 = 0;
	look.x = View._13;
	look.y = View._23;
	look.z = View._33;

	D3DVECTOR look;

	look.x = View._13;
	look.y = View._23;
	look.z = View._33;/
	float fLen = sqrtf(tc*tc);

	flViewAngles[0] = 180 / M_PI * atan2f( tb, fLen );
	flViewAngles[1] = 180 / M_PI * atan2f( ta, tc );
	flViewAngles[2] = 0;

	


/*	D3DXMatrixInverse(&View, NULL, &View);
	double RotateX, RotateY, RotateZ;

	RotateY = asin(-View._13);

	if (cos(RotateY) != 0)
	{
		RotateX = atan2(View._23, View._33);
		RotateZ = atan2(View._12, View._11);
	}
	else
	{
		RotateX = atan2(View._21, View._22);
		RotateZ = 0.0;
	}


	flViewAngles[0] = D3DXToDegree(RotateX);
	flViewAngles[1] = D3DXToDegree(RotateY);
	flViewAngles[2] = D3DXToDegree(RotateZ);/

	viewprt.x = flViewAngles[0];
	viewprt.y = flViewAngles[1];
	viewprt.z = flViewAngles[2];

	bool bReturn = NewCalcScreen( flRemotePos, flScreen, pLocalPlayer->FOV, 
		flLocalPos, flViewAngles, ScreenCenterX, ScreenCenterY);

	pScreen->x = flScreen[0];
	pScreen->y = flScreen[1];*/

	return true;
}
bool bWorldtoScreenx1( IDirect3DDevice9* pDevice, CPlayer* pPlayer, D3DXVECTOR3 *PlayerW, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch)
{
	if(pLocalPlayer->FOV == 0.0f || pLocalPlayer->FOV == 0)
		return false;

//	if(world == 0) return false;

	D3DXMATRIX View = world[1];
	D3DXMATRIX Proj = world[matcount];
	D3DXMATRIX World = world[0];	
	if(View._41 == 0 && View._42 == 0 && View._43 == 0){
		newmat = 1; return false;}

D3DVIEWPORT9 Viewport;
if( SUCCEEDED( pDevice->GetViewport( &Viewport ) ) == false )
		return false;

//ScreenCenterX = Viewport.Width / 2;
//	ScreenCenterY = Viewport.Height / 2;
//if((Viewport.Width / 2) > ScreenCenterX) ScreenCenterX = ( float )Viewport.Width / 2;
//if((Viewport.Height / 2) > ScreenCenterY) ScreenCenterY = ( float )Viewport.Height / 2; 
//D3DXVECTOR3 PlayerW = PlayerV;

	/*
	PlayerW.x = pPlayer->Info->PlayerInfo->Matrix._41;

	if(pPlayer->Info->PlayerInfo->Health == 0)
		return false;

	if(pPlayer->Info->PlayerInfo->Health->Health > 0.0f && ch)
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42 + mody;
	else
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42;

	PlayerW.z = pPlayer->Info->PlayerInfo->Matrix._43;
	*/
	

	if(!D3DXVec3Project( pScreen, PlayerW, &Viewport, &Proj, &View, &World))
		return false;

	if(pScreen->z > 1.0f)
		return false;

	return true;
}
bool bWorldtoScreenxall( IDirect3DDevice9* pDevice, CPlayer* pPlayer, D3DXVECTOR3 *PlayerW, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch)
{

	if(world == 0) return false;


	D3DXMATRIX View = world[1];
	D3DXMATRIX Proj = world[matcount];
	D3DXMATRIX World = world[0];


	D3DVIEWPORT9 Viewport;
	if(View._41 == 0 && View._42 == 0 && View._43 == 0){
		newmat = 1; return false;}

if( SUCCEEDED( pDevice->GetViewport( &Viewport ) ) == false )
		return false;
//D3DXVECTOR3 PlayerW = PlayerV;

	/*
	PlayerW.x = pPlayer->Info->PlayerInfo->Matrix._41;

	if(pPlayer->Info->PlayerInfo->Health == 0)
		return false;

	if(pPlayer->Info->PlayerInfo->Health->Health > 0.0f && ch)
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42 + mody;
	else
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42;

	PlayerW.z = pPlayer->Info->PlayerInfo->Matrix._43;

	*/
	

//	ScreenCenterX = Viewport.Width / 2;
//	ScreenCenterY = Viewport.Height / 2;

	if(!D3DXVec3Project( pScreen, PlayerW, &Viewport, &Proj, &View, &World))
		return false;

	if(pScreen->z > 1.0f)
		return false;

	return true;
}
//char g_szClassList[7][20] = { "SpecialOp", "Sniper", "Assault", "Support", "Engineer", "Medic", "AntiTank" };




	

















DWORD team1pts = 0;
DWORD team2pts = 0;



DWORD gGetPts=0;

__declspec( naked ) VOID hkGetPts(DWORD team)
{
	_asm{
		push ebp;
		mov ebp, esp;
		push team;
		call gGetPts;
		push ebx;
		mov ebx, [eax];
		cmp ebx, 1;
		je team1;
		cmp ebx, 2;
		je team2;
		jmp none;
team1:
		mov ebx, [eax+0x84];
		mov team1pts, ebx;
		jmp none;
team2:
		mov ebx, [eax+0x84];
		mov team2pts, ebx;
none:
		pop ebx;
		pop ebp;
		ret 4;
	}
}

__declspec( naked ) VOID hkGetMatrix()
{
	_asm call gGetMatrix;
	_asm{
		cmp newmat, 0;
		je cdon;
		push ecx;
		mov ecx, matc;
		cmp eax, world;
		je equ;
		mov world, eax;
		xor ecx, ecx;
equ:
		inc ecx;
		cmp ecx, 30;
		jl don;
		mov newmat, 0;
		xor ecx, ecx;
don:
		mov matc, ecx;
		pop ecx;
cdon:
		ret;
	}
}
DWORD minivert = 0;
__declspec( naked ) void FuncDrawTAGS ( BYTE bDrawn, int Index, float flValue, float flValue2 )
{

	_asm pushad;

//	while(GetAsyncKeyState(VK_F7) == 0)
//	{
//	}
		acOn();
		tfOn();
		Mine();
		TagDist();
		TagsOn();
		dTags();
		radar();
		Health();
		kits();	
	_asm popad;

	_asm call minivert;

	_asm pushad;
		TagDistOff();
		TagsOff();
		MineOff();
		doff();
		radoff();
		Healthoff();
		kitsoff();	
		tfOff();
		acOff();
	_asm popad;

	_asm ret;
}
__declspec( naked ) void CDTagManager::FuncDrawTAGSs ( BYTE bDrawn, int Index, float flValue, float flValue2 )
{

	_asm pushad;
		acOn();
		tfOn();
		Mine();
		TagDist();
		TagsOn();
		dTags();
		radar();
		Health();
		kits();	
	_asm popad;

	_asm call gTag;

	_asm pushad;
		TagDistOff();
		MineOff();
		TagsOff();
		doff();
		radoff();
		Healthoff();
		kitsoff();	
		tfOff();
		acOff();
	_asm popad;

	_asm ret;
}



PDWORD* __stdcall pdwImportClassbyName( DWORD* pszClassName )
{
	_asm mov ecx, ecxReg;
	ppdwReturnValue = gClassManager.pImportClassbyName( pszClassName );
/*	add_log("IMPORT 1 HIT");
*/

	//_asm int 3;
	
	
	
	_asm pushad;
	//add_log("IMPORT 2 HIT!!");

	BYTE* pString1 = (BYTE*)pszClassName + 4;
/*	char aa = pString1[0];
	int b, c;

	b = _mbsncmp( (const unsigned char *)pString1, (const unsigned char *)"a", 1);
	c = _mbsncmp( (const unsigned char *)pString1, (const unsigned char *)"Z", 1);
	if((strcmp( (const char *)pString1, "hWndBf2TempSlt") == 0) || (strcmp( (const char *)pString1, "rodSpecial") == 0))
	{
		b = -1;
		c = -1;
	}
	//add_log("aa: %s b: %i c: %i", pString1, b, c);
	
	if((b  == -1) && (c == -1))
		add_log("%s 0x%x", pString1 , ppdwReturnValue);
	else
	{
		string *pString = reinterpret_cast<string*>( pszClassName );
		add_log("%s 0x%x", pString->c_str() , ppdwReturnValue);
	}*/
///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
///*
///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
	if ( strcmp( (const char *)pString1, "NametagManager" ) == 0)
	{

		
		
		if(!back)
		{
			//add_log("len: %i plen: %i pplen: %i", strlen((const char *)ppdwReturnValue), strlen((const char *)*ppdwReturnValue), strlen((const char *)**ppdwReturnValue));
	
		intMemHacks();

		/*acOn();
		TagsOn();
		TagsOff();
		acOff();////////////////*/

			//hkNameTag = new CNameTagManager;
			back = true;
		ecxTag = ppdwReturnValue;


		pNameTag = (CNameTagManager*)ppdwReturnValue;
		hkNameTag = (CDTagManager *)ppdwReturnValue;
		
		//hkNameTag->FuncDrawTAGS(1, 2, 3.0f, 5.0f);
		


		//DWORD tgpt = hkNameTag->getThis();

		DWORD hkdr = (DWORD)&hkGetPts;
		DWORD addr;//, tagAdr;
DWORD rettr;
//
	/*	typedef void (CDTagManager::*memPtr)(unsigned char,int,float,float);
			memPtr ffAdd = &CDTagManager::FuncDrawTAGSs;


		_asm{
			push eax;
			mov eax, ffAdd;
			mov addr, eax;
			pop eax;
		}


		



		//rettr = (DWORD)*ppdwReturnValue+0x14;

		_asm{
			mov eax, ppdwReturnValue;
			mov eax, [eax];
			add eax, 0x18;
			mov rettr, eax;
		}*/

		BYTE *src=(BYTE *)addr; BYTE *des=(BYTE *)rettr; DWORD dwback;
/*
		if(VirtualProtect(des, 4, PAGE_READWRITE, &dwback) )
		{

			_asm{
				push ebx;
				mov eax, rettr;
				mov ebx, [eax];
				mov gTag, ebx;
				mov ebx, addr;
				mov [eax], ebx;
				pop ebx;
			}
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
		//	AddLog("gNameTags: 0x%x", gTag);
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////

			//memcpy(des, src, 4);

			add_log("addr 0x%x  gTag 0x%x  ppdwReturnValue 0x%x", addr, gTag, ppdwReturnValue);

			VirtualProtect(des, 4, dwback, &dwback);

		}
		else
			add_log("Failed to hook tags!");

  */

		DWORD dwRendDX9Base = (DWORD)GetModuleHandle("RendDX9.dll");

		//dwRendDX9Base += 0x2123A4;
		dwRendDX9Base += 0x21A3B4;

		des = (BYTE*)dwRendDX9Base;

		addr = (DWORD)&hkGetMatrix;

		if(VirtualProtect(des, 4, PAGE_READWRITE, &dwback) )
		{
			_asm{
				push ebx;
				mov eax, dwRendDX9Base;
				mov ebx, [eax];
				mov gGetMatrix, ebx;
				mov ebx, addr;
				mov [eax], ebx;
				pop ebx;
			}
			VirtualProtect(des, 4, dwback, &dwback);
		}
		else
			add_log("Failed to get Matrix!");
		add_log("My Matrix info Prt: 0x%x Hooked function: 0x%x", gGetMatrix, addr);

		_asm{
			push eax;
			push ebx;
			MOV     eax, [0x991e18];
			MOV     eax, [eax];
			MOV     ebx, [eax];
			add		ebx, 0x10;
			mov		addr, ebx;
			pop ebx;
			pop eax;
		}
	add_log("Get Score info Prt: 0x%x Hooked function: 0x%x", addr, hkdr);
			des = (BYTE*)addr;
		if(VirtualProtect(des, 4, PAGE_READWRITE, &dwback) )
		{
			_asm{
				push eax;
				push ebx;
				mov eax, addr;
				mov ebx, [eax];
				mov gGetPts, ebx;
				mov ebx, hkdr;
				mov [eax], ebx;
				pop ebx;
				pop eax;
			}
			//add_log("PTR TO Get Score info: 0x%x", gGetPts);
			VirtualProtect(des, 4, dwback, &dwback);
		}







			


		}
		//memcpy(&gNameTag, (LPVOID)pNameTag, sizeof(CNameTagManager));, strlen((const char *)*ppdwReturnValue)
		//memcpy(&hkNameTag, (LPVOID)pNameTag, sizeof(CNameTagManager));

		//add_log("hk: 0x%x g: 0x%x", &hkNameTag , &gNameTag);

		//memcpy((void*)(&hkNameTag + 0x14), (LPVOID)&pdwFuncDrawTAGS, sizeof(&pdwFuncDrawTAGS));

		//hkNameTag.FuncDrawTAGS = pdwFuncDrawTAGS;

		//
	}
///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
//*/
///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////

	if ( strcmp( (const char *)pString1, "PlayerManager" ) == 0)
	{
		pPlayerManager = (CPlayerManager*)ppdwReturnValue;
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
	//		add_log("Player Manager: 0x%x", pPlayerManager);
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
		
	}

	



	_asm popad;

	return  ppdwReturnValue;
}

//void __cdecl HookinitDLL( CClassManager** pClsMgr )
 void __cdecl HookinitDLL( CClassManager** pClsMgr )
{

	//static bool fst = false;
	//if(!fst)
	//{
	
	
		_asm pushad;

		if(!minivert)
		{
			minivert=(DWORD)VirtualAlloc(NULL, 0x100, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

			DWORD dwRendDX9Base = (DWORD)GetModuleHandle("RendDX9.dll");

			dwRendDX9Base += 0x12F550;

			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
		//	AddLog("MiniVert: 0x%x Tags Detour: 0x%x Base Function: 0x%x", minivert, &FuncDrawTAGS, dwRendDX9Base);
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////
			///////////////////////////@@@@@@@@@@@@@@@@@@@@@@////////////////////////////

			memcpy((void*)minivert, (const void*)dwRendDX9Base, 6);

			BYTE jmp[5];
			DWORD a=0;

			jmp[0] = 0xe9;
			a = (dwRendDX9Base + 6)  - (minivert + 6) - 5;

			memcpy((void*)&jmp[1], (const void*)&a, 4);
			memcpy((void*)(minivert + 6), (const void*)&jmp[0], 5);

			DWORD b = (DWORD)&FuncDrawTAGS;
			a = b - dwRendDX9Base - 5;

			memcpy((void*)&jmp[1], (const void*)&a, 4);

			jmp[5] = 0x90;

			WriteProcessMemory(GetCurrentProcess(), (void*)dwRendDX9Base, &jmp[0], 6, 0);

		}
//	ReadProcessMemory(GetCurrentProcess(), (void*)0x24e0024, &g_pClsMgr, 4, NULL); 
		g_pClsMgr = *pClsMgr;
		ecxReg = pClsMgr;

	//	add_log("HIT! Recieved Classmgr: 0x%x  Pointer: 0x%x RendDX Base: 0x%x ", pClsMgr, *pClsMgr, GetModuleHandle("RendDX9.dll"));

		//while(GetAsyncKeyState(VK_HOME) == 0)
		//{
		//	Sleep(5);
		//}
		memcpy( &gClassManager, (LPVOID)g_pClsMgr, sizeof( CClassManager ) );
		memcpy( &gHookedClassManager, (LPVOID)g_pClsMgr, sizeof( CClassManager ) );

		gHookedClassManager.pImportClassbyName = pdwImportClassbyName;
		
	//	CClassManager *pHk = &gHookedClassManager;

	//	WriteProcessMemory(GetCurrentProcess(), (void*)0x24e0024, &pHk, 4, NULL);

	//	add_log("HIT! Recieved Classmgr: 0x%x  Pointer: 0x%x gClassmgr: 0x%x Hooked: 0x%x", ecxReg, *g_pClsMgr, &gClassManager, &gHookedClassManager);

		

		*pClsMgr = &gHookedClassManager;
/*gge:

		if(!back)
			goto gge;*/

		_asm popad;
	//	_asm pop ebp;

	//	fst = true;
	//}
	//	while(GetAsyncKeyState(VK_END) == 0)
	//	{
	//		Sleep(5);
	//	}


//pHookinitDLL( pClsMgr );
//_asm ret 4;
}

FARPROC WINAPI hkGetProcAddress(IN HMODULE hModule, IN LPCSTR lpProcName )
{
	add_log("%s 0x%x",lpProcName, hModule/*fpReturn*/);

	FARPROC fpReturn = pGetProcAddress( hModule, lpProcName );
	

	if ( lpProcName )
	{
		if ( strcmp( lpProcName, "initDll" ) == 0 && GetModuleHandle( "Renddx9.dll" ) == hModule )
		{
			RetourFunc( (BYTE*) GetProcAddress, (BYTE*)pGetProcAddress, 5 );
			pHookinitDLL = ( HookinitDLL_t ) fpReturn;
			return ( FARPROC )HookinitDLL;
		}
	}
	
	return fpReturn;
}
BYTE pokb = 0x00;
BYTE pok[4] = {0x01, 0x00, 0x00, 0x00};
BYTE pok1[4] = {0x00, 0x00, 0x00, 0x00};
void setCommander()
{
	if(pCVar->Settings.comArtRdy == 0)
	{
		DWORD adr = 0x9DBBF8;
		_asm{
			mov eax, adr;
			mov eax, [eax];
			add eax, 0x15C;
			mov eax, [eax];
			//add eax, 0x44;
			mov adr, eax;
		}
		if(adr)
		{
			pCVar->Settings.comArtRdy = adr;
			DWORD locp = (DWORD)pPlayerManager->pGetLocalePlayer();
			locp += 0x110;
			MyWrite(locp,(DWORD) &pok, 4);
			MyWrite(pCVar->Settings.comArtRdy + 0x44,(DWORD) &pokb, 1);
			MyWrite(pCVar->Settings.comArtRdy + 0x5C,(DWORD) &pokb, 1);
			MyWrite(pCVar->Settings.comArtRdy + 0x64,(DWORD) &pokb, 1);
		}
	} else
	{
		DWORD locp = (DWORD)pPlayerManager->pGetLocalePlayer();
		locp += 0x110;
		MyWrite(locp,(DWORD) &pok, 4);
		MyWrite(pCVar->Settings.comArtRdy + 0x44,(DWORD) &pokb, 1);
		MyWrite(pCVar->Settings.comArtRdy + 0x5C,(DWORD) &pokb, 1);
		MyWrite(pCVar->Settings.comArtRdy + 0x64,(DWORD) &pokb, 1);
	}
}
void setCommanderoff()
{
	DWORD locp = (DWORD)pPlayerManager->pGetLocalePlayer();
	locp += 0x110;
	MyWrite(locp,(DWORD) &pok1, 4);
}
bool bWorldtoScreenx12( IDirect3DDevice9* pDevice, CPlayer* pPlayer, 
					 CPlayer* pLocalPlayer, D3DXVECTOR3* pScreen , bool ch)
{


	if(world == 0) return false;


	D3DXMATRIX View = world[1];
	D3DXMATRIX Proj = world[matcount];
	D3DXMATRIX World = world[0];
	/*if(mworld)
		World;
	else
	{
		World = pPlayer->ViewMatrix->Matrix;
		//add_log("PLAYERS MATRIX XYZ!!: %f %f %f", World._41, World._42, World._43);
	}*/


	D3DVIEWPORT9 Viewport;
	if(View._41 == 0 && View._42 == 0 && View._43 == 0){
		newmat = 1; return false;}

if( SUCCEEDED( pDevice->GetViewport( &Viewport ) ) == false )
		return false;
D3DXVECTOR3 PlayerW;
	if(pPlayer->Info != 0 && pPlayer->Info->PlayerInfo != 0)
	{
		PlayerW.x = pPlayer->Info->PlayerInfo->Matrix._41;
		PlayerW.y = pPlayer->Info->PlayerInfo->Matrix._42;
		PlayerW.z = pPlayer->Info->PlayerInfo->Matrix._43;
	} else if(pPlayer->ViewMatrix != 0 && pPlayer->ViewMatrix->Matrix != 0)
	{
		PlayerW.x = pPlayer->ViewMatrix->Matrix._41;
		PlayerW.y = pPlayer->ViewMatrix->Matrix._42;
		PlayerW.z = pPlayer->ViewMatrix->Matrix._43;
	} else return false;

	

	if(!D3DXVec3Project( pScreen, &PlayerW, &Viewport, &Proj, &View, &World))
		return false;

	if(pScreen->z > 1.0f)
		return false;

	return true;
}



