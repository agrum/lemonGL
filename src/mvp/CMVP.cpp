/*
	Copyright 2012 Thomas Le Guerroué-Drévillon
	This file is part of lemonGL.

	lemonGL is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	lemonGL is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with lemonGL.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CMVP.h"

CMVP::CMVP():
m_width(512),
m_height(512),
m_position(-1,0,0),
m_direction(1,0,0),
m_vertical(0,0,1),
m_horizontal(QVector3D::crossProduct(m_vertical, m_direction))
{
	m_viewMatrix.setToIdentity();
}

void CMVP::setPerspective(GLfloat p_fovY, GLfloat p_ratio, GLfloat p_zNear, GLfloat p_zFar){
	m_projMatrix.setToIdentity();
	m_projMatrix.perspective(p_fovY, p_ratio, p_zNear, p_zFar);
}


void CMVP::setOrtho(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f){
	m_projMatrix.setToIdentity();
	m_projMatrix.ortho(l, r, b, t, n, f);
}

void CMVP::setViewPortSize(GLuint p_x, GLuint p_y){
	m_width = p_x;
	m_height = p_y;
}

void CMVP::setViewPort(QVector2D p_bias) const {
	glViewport(p_bias.x(), p_bias.y(), m_width, m_height);
}

void CMVP::translate(float p_forward, float p_translate, float p_up){
	m_position += m_direction*p_forward + m_horizontal*p_translate + m_vertical*p_up;
	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(m_position, m_position + m_direction, m_vertical);
}

void CMVP::lookUp(float p_angle){
	QQuaternion quaternion(p_angle, m_horizontal);
	m_direction = quaternion.rotatedVector(m_direction);
	m_vertical = quaternion.rotatedVector(m_vertical);
	m_direction = quaternion.rotatedVector(m_direction);
	m_vertical = quaternion.rotatedVector(m_vertical);
	m_vertical.normalize();
	m_direction.normalize();
	m_horizontal.normalize();
	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(m_position, m_position + m_direction, m_vertical);
}

void CMVP::lookLeft(float p_angle){
	QQuaternion quaternion(p_angle, m_vertical);
	m_direction = quaternion.rotatedVector(m_direction);
	m_horizontal = quaternion.rotatedVector(m_horizontal);
	m_direction = quaternion.rotatedVector(m_direction);
	m_horizontal = quaternion.rotatedVector(m_horizontal);
	m_vertical.normalize();
	m_direction.normalize();
	m_horizontal.normalize();
	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(m_position, m_position + m_direction, m_vertical);
}

void CMVP::lookForward(float p_angle){
	QQuaternion quaternion(p_angle, m_direction);
	m_horizontal = quaternion.rotatedVector(m_horizontal);
	m_vertical = quaternion.rotatedVector(m_vertical);
	m_horizontal = quaternion.rotatedVector(m_horizontal);
	m_vertical = quaternion.rotatedVector(m_vertical);
	m_vertical.normalize();
	m_direction.normalize();
	m_horizontal.normalize();
	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(m_position, m_position + m_direction, m_vertical);
}

void CMVP::lookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
		GLfloat targetX, GLfloat targetY, GLfloat targetZ){
	QVector3D eye(eyeX, eyeY, eyeZ);
	QVector3D target(targetX, targetY, targetZ);
	QVector3D tmp = target - eye;
	tmp.normalize();
	if(tmp.z() != 0){
		tmp.setZ(-(tmp.x()*tmp.x() + tmp.y()*tmp.y())/tmp.z());
		tmp.normalize();
		if(tmp.z() < 0)
			tmp *= -1;
	}
	else
		tmp = QVector3D(0,0,1);

	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(eye, target, tmp);
	m_position = eye;
	m_direction = tmp;
}

void CMVP::lookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
		GLfloat targetX, GLfloat targetY, GLfloat targetZ,
		GLfloat baseX, GLfloat baseY, GLfloat baseZ){
	QVector3D eye(eyeX, eyeY, eyeZ);
	QVector3D target(targetX, targetY, targetZ);
	QVector3D tmp(baseX, baseY, baseZ);
	tmp.normalize();

	m_viewMatrix.setToIdentity();
	m_viewMatrix.lookAt(eye, target, tmp);
	m_position = eye;
	m_direction = tmp;
}
