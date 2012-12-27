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

#ifndef CMATERIAL_H_
#define CMATERIAL_H_

#include "CTexture1D.h"
#include "CTexture2D.h"
#include "CTexture3D.h"

#include "pomelog.h"
#include <QVector3D>

class CMaterial : public pLogBehavior {

public:
	CMaterial(const QString&);
	CMaterial(const CMaterial&);
	~CMaterial();

	void sendToProgram() const;

	const QString& getGroup();

	void setDiffuse(const QVector3D&);
	void setAmbient(const QVector3D&);
	void setSpecular(const QVector3D&);
	void setDiffuseMap(const QString&);
	void setAmbientMap(const QString&);
	void setSpecularMap(const QString&);
	void setReliefMap(const QString&);
	void setConeMap(const QString&);

private:
	QString m_group;
	QVector3D m_diffuse;
	QVector3D m_ambient;
	QVector3D m_specular;
	CTexture2D* m_diffuseMap;
	CTexture2D* m_ambientMap;
	CTexture2D* m_specularMap;
	CTexture2D* m_coneMap;
};

#endif /* CMATERIAL_H_ */
