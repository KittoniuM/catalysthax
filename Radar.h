
#include "d3d9.h"


class Radar  
{
public:
	bool DrawRadar();
private:
	bool WorldToMap(/*D3DXVECTOR3 World, D3DXVECTOR3 &Screen*/);
//	bool DrawPlayer(D3DXVECTOR3 Screen, bool alli);

	D3DXVECTOR3 worldCV;
	D3DXVECTOR3 screenCV;
	D3DXVECTOR3 curw;
	D3DXVECTOR3 curs;
	float menx, meny, menw, menh, modr;

};


