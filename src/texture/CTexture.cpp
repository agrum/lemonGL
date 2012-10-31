/*
 * CTexture.cpp
 *
 *  Created on: May 7, 2012
 *      Author: agrum
 */

#include "CTexture.h"

CTexture::CTexture(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
m_prefix(p_prefix),
m_channel(p_channel),
m_internalFormat(p_intFormat),
m_format(p_format),
m_type(p_type),
m_data(0)
{
	glGenTextures(1, &m_id);
}

CTexture::~CTexture(){
	glDeleteTextures(1, &m_id);
}

void CTexture::setData(void* p_data){
	m_data = p_data;
	setTex();
}

void CTexture::setParameter(GLenum p_name, GLfloat p_param){
	glBindTexture(m_target, m_id);
	glTexParameterf(m_target, p_name, p_param);
	glBindTexture(m_target, 0);
}

void CTexture::send() const {
	CProgram* program = CProgram::current();
	program->sendUniform1i(m_prefix + "TexMap", m_channel);
	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(m_target, m_id);
}
