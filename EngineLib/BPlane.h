#pragma once
#include "Renderer.h"
DllExport class BPlane
{
public:
	BPlane();
	~BPlane();
	 void SetPlane(D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3);
	 float Check(D3DXVECTOR3 p);
private:
	D3DXPLANE* thisPlane;
};