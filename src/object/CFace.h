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

#ifndef CFACE_H_
#define CFACE_H_

#include "CVA.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QVector3D>
#include <QVector2D>

class CFace {

public:
	CFace(const QByteArray&, const QList<QVector3D>&, const QList<QVector2D>&, const QList<QVector3D>&);
	~CFace();

	GLfloat* blehPosition(){ return m_vertices; }
	GLfloat* blehNormal(){ return m_normals; }

	void draw();

private:
	GLfloat* m_vertices;
	GLfloat* m_textures;
	GLfloat* m_normals;

	GLuint* m_indices;
	int* m_count;
	int m_size;
	int m_start;
};

#endif /* CFACE_H_ */
