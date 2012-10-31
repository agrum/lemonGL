/*
 * CTexture2D.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#include "CTexture2D.h"

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
	CProgram* program = CProgram::current();
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

	program->sendUniformMatrix4fv(m_prefix + "TexMat", 1, GL_TRUE, tex);
	program->sendUniform1i(m_prefix + "TexMap", m_channel);

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
		CLog::log(this, CLog::ERROR, CLog::ERROR_SIZE, "GL_MAX_TEXTURE_SIZE");

	if(p_width != m_width || p_height != m_height){
		m_width = p_width;
		m_height = p_height;
		setTex();
	}
}

