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

#include "CTexture3D.h"

CTexture3D::CTexture3D(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
CTexture(p_prefix, p_channel, p_intFormat, p_format, p_type),
m_width(512),
m_height(512),
m_depth(512)
{
	m_target = GL_TEXTURE_3D;
	setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void CTexture3D::setTex(){
	glBindTexture(GL_TEXTURE_3D, m_id);
	glTexImage3D(GL_TEXTURE_3D, 0, m_internalFormat, m_width, m_height, m_depth, 0, m_format, m_type, m_data);
	glBindTexture(GL_TEXTURE_3D, 0);
}

void CTexture3D::setWidth(int p_w){
	m_width = p_w;
	setTex();
}

void CTexture3D::setHeight(int p_h){
	m_height = p_h;
	setTex();
}

void CTexture3D::setDepth(int p_d){
	m_depth = p_d;
	setTex();
}
