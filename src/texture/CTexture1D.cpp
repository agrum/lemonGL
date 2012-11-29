/*
 * CTexture1D.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#include "CTexture1D.h"

CTexture1D::CTexture1D(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
CTexture(p_prefix, p_channel, p_intFormat, p_format, p_type),
m_width(512)
{
	m_target = GL_TEXTURE_1D;
	setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void CTexture1D::setTex(){
	glBindTexture(GL_TEXTURE_1D, m_id);
	glTexImage1D(GL_TEXTURE_1D, 0, m_internalFormat, m_width, 0, m_format, m_type, m_data);
	glBindTexture(GL_TEXTURE_1D, 0);
}

void CTexture1D::setWidth(int p_w){
	m_width = p_w;
	setTex();
}