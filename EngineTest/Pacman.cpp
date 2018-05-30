#include "Pacman.h"

bool Pacman::init(Renderer& rkRenderer){



	imp = new ImporterPG2(rkRenderer);
	root = new Node();

	if (!imp->importScene("Assets/elmenemovil.3ds", *root, bspMan))
		return false;


#pragma region oldStuffFromBeforeAssImp
	//meshy.setRenderer(rkRenderer);
	//meshy2.setRenderer(rkRenderer);
	//meshy3.setRenderer(rkRenderer);

	//if (!imp.importMesh("Assets/Teapot.obj", meshy))
	//	return false;

	//if (!imp.importMesh("Assets/Torus.obj", meshy2))
	//	return false;

	//if (!imp.importMesh("Assets/Cube.obj", meshy3))
	//	return false;

	/*root.addChild(&meshy3);
	root.addChild(&node1);
	node1.addChild(&meshy);
	node1.addChild(&meshy2);*/

	//TexVertex meshVertex[] = {hhh
	//	{ -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, },
	//	{ 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, },
	//	{ -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, },
	//	{ 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, },
	//	{ -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, },
	//	{ 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, },
	//	{ -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, },
	//	{ 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, },
	//};

	//ColorVertex vertices[] =
	//{
	//	{ -3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 0, 255), },
	//	{ 3.0f, 3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 0), },
	//	{ -3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0), },
	//	{ 3.0f, -3.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255), },
	//	{ -3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(0, 0, 255), },
	//	{ 3.0f, 3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 0), },
	//	{ -3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(255, 0, 0), },
	//	{ 3.0f, -3.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 255), },
	//};

	//unsigned short indices[] = {
	//	0, 1, 2,    // side 1
	//	2, 1, 3,
	//	4, 0, 6,    // side 2
	//	6, 0, 2,
	//	7, 5, 6,    // side 3
	//	6, 5, 4,
	//	3, 1, 7,    // side 4
	//	7, 1, 5,
	//	4, 5, 0,    // side 5
	//	0, 5, 1,
	//	3, 7, 2,    // side 6
	//	2, 7, 6,
	//};

	//meshy.setMeshData(meshVertex, D3DPT_TRIANGLELIST, sizeof(TexVertex), indices, 36);
	//meshy2->setMeshData(vertices, D3DPT_TRIANGLELIST, sizeof(ColorVertex), indices, 36);

	/*ob1.setScale(1.5, 6);
	ob1.setPos(1.0f, 0.0f);

	ob2.setScale(6, 1.5);
	ob2.setPos(0.0f, -1.0f);

	obstacles.push_back(&ob1);
	obstacles.push_back(&ob2);

	playerChar.setPos(0.0f, 0.0f);

	scalex = 100.0f;
	scaley = 100.0f;

	playerChar.setScale(scalex, scaley);

	playerChar.setTexture(rkRenderer.loadTexture("Assets/megamanani.png",D3DCOLOR_XRGB(255,0,255)));
	idle = new Animation();
	jumping = new Animation();
	walking = new Animation();

	idle->addFrame(0.0f, 0.0f, 26.0f, 30.0f, 182.0f, 30.0f, 1000.0f, 2);

	playerChar.setAnimation(idle);

	jumping->addFrame(52.0f, 0.0f, 26.0f, 30.0f, 182.0f, 30.0f);
	walking->addFrame(78.0f, 0.0f, 26.0f, 30.0f, 182.0f, 30.0f, 400.0f, 3);

	if (!m.import("Assets/mm1map.tmx", rkRenderer))
	return false;*/
#pragma endregion

	camSpeedDivider = 1000.0f;
	gameCamera = new Camera(rkRenderer);
	rkRenderer.setMatrix(D3DTS_VIEW, gameCamera->viewMatrix());

	//gameCamera->setPos(250.0f, 200.0f, -1000.0f);
	//meshy.setScale(10.0f,10.0f,10.0f);
	//meshy.setPos(100.0f, 0.0f, -500.0f);

	//meshy2.setScale(10.0f, 10.0f, 10.0f);
	//meshy2.setPos(400.0f, 0.0f, -500.0f);
	//meshy->setRotation(0.0f, 1.0f, 0.0f);
	//meshy2->setPos(0.0f, 0.0f, 0.0f);

	gameCamera->setPos(0.0f, 0.0f, -20.0f);
	return true;
}

void Pacman::frame(Renderer& pkRenderer, DirectInput& rkInput, Timer& rkTimer){
	showMe = accumulate(begin(*nameVector), end(*nameVector), showMe);
	/*ob1.draw(pkRenderer);
	ob2.draw(pkRenderer);*/

	//m.draw(pkRenderer, 800, 600);

	//meshy->RotateY(0.1f);

	gameCamera->updateFrustum();

	if (!nameVector->empty())
		nameVector->clear();

	root->updateBV();
	root->draw(pkRenderer, gameCamera->getFrustum().aabbInFrustum(root->getAABB()),gameCamera->getFrustum(), *nameVector,gameCamera->getPos(),bspMan);

	if (rkInput.keyDown(Input::KEY_F)){
		gameCamera->strafe(-fSpeed);;
	}

	if (rkInput.keyDown(Input::KEY_G)){
		gameCamera->walk(-fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_T)){
		gameCamera->walk(fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_H)){
		gameCamera->strafe(fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_LCONTROL)){
		gameCamera->fly(-fSpeed);
	}

	if (rkInput.keyDown(Input::KEY_SPACE)){
		gameCamera->fly(fSpeed);
	}

	//if (rkInput.keyDown(Input::KEY_K)){
	//	root->getChildNode("Root")->ScaleAll(-0.05f,-0.05f,-0.05f);
	//}

	if (rkInput.keyDown(Input::KEY_L)){
		root->getChildNode("Root")->ScaleAll(0.05f, 0.05f, 0.05f);
	}

	if (rkInput.keyDown(Input::KEY_Z)){
		root->ScaleAll(-0.05f, -0.05f, -0.05f);
	}

	if (rkInput.keyDown(Input::KEY_X)){
		root->ScaleAll(0.05f, 0.05f, 0.05f);
	}



	if (!isColliding){

		pkRenderer.drawText(showMe);
		showMe = "";
		//if (rkInput.keyDown(Input::KEY_DOWN)){

		//	root->getChildNode("Group002")->getChildMesh("Teapot001")->ScaleY(-1.00f);

		//}

		if (rkInput.keyDown(Input::KEY_UP)){


			root->getChildMesh("Control")->ScaleY(1.00f);


		}

		if (rkInput.keyDown(Input::KEY_RIGHT)) {


			root->getChildNode("Root")->getChildNode("group6")->getChildMesh("Control")->MoveX(1.00f);

		}
		if (rkInput.keyDown(Input::KEY_LEFT)){



			root->getChildNode("Root")->getChildNode("group6")->getChildMesh("Control")->MoveX(-1.00f);


		}

		//if (rkInput.keyDown(Input::KEY_W)){
		//	root->getChildNode("Group001")->MoveY(1.00f);
		//}

		//if (rkInput.keyDown(Input::KEY_S)){
		//	root->getChildNode("Group001")->MoveY(-1.00f);
		//}

		//if (rkInput.keyDown(Input::KEY_D)){
		//	root->getChildNode("Group001")->MoveX(1.00f);
		//}

		//if (rkInput.keyDown(Input::KEY_A)){
		//	root->getChildNode("Group001")->MoveX(-1.00f);
		//}

		if (rkInput.keyDown(Input::KEY_Q)){
			gameCamera->roll(0.1f);
		}

		if (rkInput.keyDown(Input::KEY_E)){
			gameCamera->roll(-0.1f);
		}

		gameCamera->pitch(rkInput.mouseRelPosY() / camSpeedDivider);

		gameCamera->yaw(rkInput.mouseRelPosX() / camSpeedDivider);
	}

}

void Pacman::deinit(){

}
