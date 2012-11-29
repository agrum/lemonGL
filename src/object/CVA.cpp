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

#include "CVA.h"

QList<QPair<int, int> > CVA::m_free;
GLfloat* CVA::m_vertices = NULL;
GLfloat* CVA::m_textures = NULL;
GLfloat* CVA::m_normals = NULL;

void CVA::create(int p_size){
	m_vertices = new GLfloat [p_size*3];
	m_textures = new GLfloat [p_size*2];
	m_normals = new GLfloat [p_size*3];

	QPair<int, int> initPair(0, p_size);
	m_free.push_back(initPair);

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, m_textures );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, m_normals );
}

void CVA::remove(){
	delete [] m_vertices;
	delete [] m_textures;
	delete [] m_normals;
}

void CVA::enable(){
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );

}

void CVA::disable(){
	glDisableVertexAttribArray( 2 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 0 );
}

int CVA::add(int p_size){
	for(int a = 0; a < m_free.size(); a++)
		if(m_free[a].second >= p_size){
			int rtn = m_free[a].first;
			m_free[a].first += p_size;
			m_free[a].second -= p_size;
			if(m_free[a].second == 0)
				m_free.removeAt(a);
			return rtn;
		}

	qDebug() << "Can't add new face, VertexArray full";
	return -1;
}

void CVA::del(int p_start, int p_size){
	QPair<int, int> newPair(p_start, p_size);
	bool merged = false;

	for(int a = 0; a < m_free.size(); a++){
		if(m_free[a].first == p_start + p_size + 1){
			m_free[a].first = p_start;
			m_free[a].second += p_size;
			a = -1;
		}
		else if(m_free[a].first + m_free[a].second + 1 == p_start){
			m_free[a].second += p_size;
			a = -1;
		}
	}

	if(!merged)
		m_free.push_back(newPair);
}
