#include"Camera.h"

Camera::Camera(Renderer& rkRenderer):r(rkRenderer){
	m_view = new D3DXMATRIX();
	UpdateCam();

	m_maxPitch = D3DXToRadian(60.0f);
	m_invertY = false;
	m_enableYMovement = true;

	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_maxVelocity = 1.0f;

	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera(){
	delete m_view;
}

void Camera::UpdateCam(){
	float lookLengthOnXZ = sqrtf(m_look.z * m_look.z + m_look.x * m_look.x);
	m_pitch = atan2f(m_look.y, lookLengthOnXZ);
	m_yaw = atan2f(m_look.x, m_look.z);

	if (D3DXVec3Length(&m_velocity) > m_maxVelocity){
		m_velocity = *(D3DXVec3Normalize(&m_velocity, &m_velocity)) * m_maxVelocity;
	}

	m_position += m_velocity;
	m_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lookAt = m_position + m_look;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(m_view, &m_position, &m_lookAt, &up);

	m_right.x = m_view->_11;
	m_right.y = m_view->_21;
	m_right.z = m_view->_31;
	m_up.x = m_view->_12;
	m_up.y = m_view->_22;
	m_up.z = m_view->_32;
	m_look.x = m_view->_13;
	m_look.y = m_view->_23;
	m_look.z = m_view->_33;
	
	

	r.setMatrix(D3DTS_VIEW, m_view);
}

void Camera::walk(float dist){

	m_velocity += m_look * dist;

//	UpdateCam();
}

void Camera::strafe(float dist){

	m_velocity += m_right * dist;

//	UpdateCam();
}

void Camera::fly(float dist){

	if (m_enableYMovement){
		m_velocity.y += dist;
	}

//	UpdateCam();
}

void Camera::roll(float angle){
	if (angle == 0.0f){
		return;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_look, angle);
	D3DXVec3TransformNormal(&m_right, &m_right, &rotation);
	D3DXVec3TransformNormal(&m_up, &m_up, &rotation);

	//UpdateCam();
}

void Camera::pitch(float angle){
	if (angle == 0.0f){
		return;
	}

    angle = (m_invertY) ? -angle : angle;
	m_pitch -= angle;
	if (m_pitch > m_maxPitch){
		return;
	}
	else if (m_pitch < -m_maxPitch){
		return;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_right, angle);
	D3DXVec3TransformNormal(&m_up, &m_up, &rotation);
	D3DXVec3TransformNormal(&m_look, &m_look, &rotation);

//	UpdateCam();
}

void Camera::yaw(float angle){
	if (angle == 0.0f)
	{
		return;
	}
	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &m_up, angle);
	D3DXVec3TransformNormal(&m_right, &m_right, &rotation);
	D3DXVec3TransformNormal(&m_look, &m_look, &rotation);

//	UpdateCam();
}

void Camera::setPos(float fPosX, float fPosY, float fPosZ){
	m_position.x = fPosX;
	m_position.y = fPosY;
	m_position.z = fPosZ;

//	UpdateCam();
}

D3DXVECTOR3 Camera::getPos() {
	return m_position;
}

void Camera::setForward(float fX, float fY, float fZ){
	m_lookAt.x = fX;
	m_lookAt.y = fY;
	m_lookAt.z = fZ;
	D3DXVec3Normalize(&m_look, &(m_lookAt - m_position));

}

const Matrix& Camera::viewMatrix() const{
	return m_view;
}

const Frustum& Camera::getFrustum() const{
	return camFrustum;
}

void Camera::updateFrustum(){
	UpdateCam();
	D3DXMATRIX viewProjection;
	D3DXMatrixMultiply(&viewProjection, m_view, r.getProjectionMatrix());
	camFrustum.updateFrustum(viewProjection);
}