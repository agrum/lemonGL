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

#include "CTexture2D.h"

CTexture2D::CTexture2D(QString p_prefix, QString p_path, GLuint p_channel):
CTexture(p_prefix, p_channel, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)
{
	m_target = GL_TEXTURE_2D;
	setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	appendImg(p_path);
}

CTexture2D::CTexture2D(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
CTexture(p_prefix, p_channel, p_intFormat, p_format, p_type),
m_width(512),
m_height(512)
{
	m_target = GL_TEXTURE_2D;
	setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void CTexture2D::setTex(){
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_format, m_type, m_data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture2D::setWidth(int p_w){
	m_width = p_w;
	setTex();
}

void CTexture2D::setHeight(int p_h){
	m_height = p_h;
	setTex();
}

void CTexture2D::sendToProgram(const QMatrix4x4& p_mvp) const {
	float tex[16];
	QMatrix4x4 tmp(
			0.5, 0.0, 0.0, 0.5,
			0.0, 0.5, 0.0, 0.5,
			0.0, 0.0, 0.5, 0.5,
			0.0, 0.0, 0.0, 1.0);
	tmp = tmp * p_mvp;
	for(int a = 0; a < 4; a++)
		for(int b = 0; b < 4; b++)
			tex[a*4 + b] = tmp(a, b);

	CShaderInterface::sendUniformMatrix4fv(m_prefix + "TexMat", 1, GL_TRUE, tex);
	CShaderInterface::sendUniform1i(m_prefix + "TexMap", m_channel);

	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void CTexture2D::appendImg(const QString& p_filename){
	QImage img;

	if( ! img.load(p_filename) ) qDebug() << "error loading texture " + p_filename ;

	m_image = QGLWidget::convertToGLFormat(img);
	if( m_image.isNull() ) qDebug() << "error GL_formatted_image" ;

	m_width = m_image.width();
	m_height = m_image.height();
	m_internalFormat = GL_RGBA;
	m_format = GL_RGBA;
	m_type = GL_UNSIGNED_BYTE;
	m_data = m_image.bits();
	setTex();
}

void CTexture2D::setSize(GLuint p_width, GLuint p_height){
	if(p_width > GL_MAX_TEXTURE_SIZE || p_height > GL_MAX_TEXTURE_SIZE)
		pLog::logE(this, pLog::ERROR_NONE, "GL_MAX_TEXTURE_SIZE");

	if(p_width != m_width || p_height != m_height){
		m_width = p_width;
		m_height = p_height;
		setTex();
	}
}

