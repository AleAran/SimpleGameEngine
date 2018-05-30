#include "BSPManager.h"
#include "BPlane.h"
BSPManager::BSPManager()
{

}

BSPManager::~BSPManager()
{
	for (unsigned int i = 0; i < planes.size(); i++) {
		delete planes[i];
		planes[i] = NULL;
	}

	if (!planes.empty())
		planes.clear();
}

void BSPManager::AddPlane(D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3)
{
	BPlane* bspPlane = new BPlane();
	bspPlane->SetPlane(point1, point2, point3);
	planes.push_back(bspPlane);
}

bool BSPManager::CheckTree(D3DXVECTOR3 camPos, D3DXVECTOR3 objMin, D3DXVECTOR3 objMax)
{
	float camCheck = 0;
	float minCheck = 0;
	float maxCheck = 0;
	bool canDraw = true;

	for (int i = planes.size() - 1; i >= 0; i--) {
		if (canDraw) {
			camCheck = planes[i]->Check(camPos);
			minCheck = planes[i]->Check(objMin);
			maxCheck = planes[i]->Check(objMax);

			if (((minCheck > 0 || maxCheck > 0) && camCheck > 0) || ((minCheck < 0 || maxCheck < 0) && camCheck < 0) || (camCheck == 0) || (minCheck == 0 || maxCheck == 0))
				canDraw = true;
			else {
				canDraw = false;
				break;
			}
		}
	}

	return canDraw;
}
