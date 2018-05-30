#pragma once
#include "Renderer.h"
#include "BPlane.h"


 class BSPManager
{
public:
	DllExport	BSPManager();
	DllExport	~BSPManager();
	DllExport	void AddPlane(D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3);
	DllExport	 bool CheckTree(D3DXVECTOR3 camPos, D3DXVECTOR3 objMin, D3DXVECTOR3 objMax);
private:
	 vector<BPlane*> planes;

};




