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

#ifndef CLIGHT_H_
#define CLIGHT_H_

#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1

#include "../shader/CProgram.h"
#include "../texture/CTexture2D.h"
#include "CMVP.h"

#include <QVector3D>
#include <QString>
#include <QMatrix4x4>

class CLight : public CMVP {

public:
	CLight();
	~CLight();

	void sendToProgram(const CMVP*, const QMatrix4x4&) const;

	void setType(const QString&);
	void setIntensity(float);
	void setAmbient(float, float, float);
	void setDiffuse(float, float, float);
	void setSpecular(float, float, float);
	void setEnabled(bool);
	void setEnableShadow(bool);
	void setShadowMapSize(GLuint, GLuint);

	bool enabled() { return m_enabled; }

	static void bindFB();
	static void unbindFB();
	void attachTexToFB();

private:
	int m_type;
	float m_intensity;
	QVector3D m_ambient;
	QVector3D m_diffuse;
	QVector3D m_specular;
	bool m_enabled;
	bool m_shadow;

	CTexture2D m_shadowMap;
	static GLuint m_fboId;
	static GLuint m_lightCount;
};

#endif /* CLIGHT_H_ */
