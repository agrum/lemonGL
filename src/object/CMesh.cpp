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

#include "CMesh.h"

CMesh::CMesh()
{

}

CMesh::CMesh(const QString& p_group):
m_group(p_group)
{

}

CMesh::CMesh(const CMesh& p_mesh):
CObject(p_mesh),
m_group(p_mesh.m_group),
m_faces(p_mesh.m_faces)
{

}

void CMesh::addFace(CFace* p_face){
	m_faces.push_back(p_face);
	m_order.push_back(m_order.size());
}

void CMesh::free(){
	for(int a = 0; a < m_faces.size(); a++)
		delete m_faces[a];
}

bool CMesh::operator==(const QString& p_group){
	return (m_group == p_group);
}

void CMesh::drawSub(){
	for(int a = 0; a < m_faces.size(); a++)
		m_faces[a]->draw();
}
