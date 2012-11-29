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

#ifndef CMVP_H_
#define CMVP_H_

#include "../shader/CProgram.h"
#include "../texture/CTexture.h"
#include "../object/CVA.h"

#include <qquaternion.h>

class CMVP {

public:
	CMVP();

	const QMatrix4x4& viewMatrix() const { return m_viewMatrix; }
	const QMatrix4x4& projMatrix() const { return m_projMatrix; }

	void setPerspective(float fovY, float ratio, float zNear, float zFar);
	void setOrtho(float l, float r, float b, float t, float n, float f);
	void setViewPortSize(GLuint, GLuint);
	void setViewPort(QVector2D p_bias = QVector2D(0,0)) const;
	void translate(float, float, float);
	void lookUp(float);
	void lookLeft(float);
	void lookForward(float);
	void lookAt(float eyeX, float eyeY, float eyeZ,
			float targetX, float targetY, float targetZ);
	void lookAt(float eyeX, float eyeY, float eyeZ,
			float targetX, float targetY, float targetZ,
			float baseX, float baseY, float baseZ);

protected:
	GLuint m_width, m_height;

	QMatrix4x4 m_projMatrix;
	QMatrix4x4 m_viewMatrix;

	QVector3D m_position;
	QVector3D m_direction;
	QVector3D m_vertical;
	QVector3D m_horizontal;
};

#endif /* CMVP_H_ */
