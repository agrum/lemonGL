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

#ifndef CVA_H_
#define CVA_H_

#include "../CGL.h"
#include "CFace.h"

#include <stdio.h>
#include <cmath>
#include <QDebug>
#include <QList>
#include <QPair>

class CVA {

public:
	static void create(int);
	static void remove();

	static GLfloat* vertices() { return m_vertices; }
	static GLfloat* textures() { return m_textures; }
	static GLfloat* normals() { return m_normals; }

	static int add(int);
	static void del(int, int);

	static void enable();
	static void disable();

protected:
	CVA() {}

	static QList<QPair<int, int> > m_free;
	static GLfloat* m_vertices;
	static GLfloat* m_textures;
	static GLfloat* m_normals;
};

#endif /* CVA_H_ */
