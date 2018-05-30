#include "BPlane.h"

BPlane::BPlane()
{
	thisPlane = new D3DXPLANE;
}

BPlane::~BPlane()
{
	delete thisPlane;
	thisPlane = NULL;
}
void BPlane::SetPlane(D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3)
{
	D3DXPlaneFromPoints(thisPlane, &point1, &point2, &point3);
}

float BPlane::Check(D3DXVECTOR3 point)
{
	return D3DXPlaneDotCoord(thisPlane, &point);
}