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

#include "CTexture.h"

QList<int> CTexture::m_freeChannelList;

void CTexture::init(){
	for(int i = 0; i < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS; i++)
		m_freeChannelList.push_back(i);
}

CTexture::CTexture(QString p_prefix, GLuint p_channel, GLenum p_intFormat, GLenum p_format, GLenum p_type):
m_prefix(p_prefix),
m_channel(p_channel),
m_internalFormat(p_intFormat),
m_format(p_format),
m_type(p_type),
m_data(0),
m_fixed(false)
{
	CLog::sign(this, "CTexture");

	if(!m_freeChannelList.contains(m_channel)){
		CLog::log(this, CLog::WARNING, CLog::ERROR_USED, "channel fixed by another texture");
		return;
	}

	glGetError();
	glGenTextures(1, &m_id);
	if(int e = glGetError() != 0)
		CLog::log(this, CLog::ERROR, CLog::ERROR_GL, "glGenTextures() " + CGLString(e));
}

CTexture::~CTexture(){
	glGetError();
	glDeleteTextures(1, &m_id);
	if(int e = glGetError() != 0)
		CLog::log(this, CLog::ERROR, CLog::ERROR_GL, "glDeleteTextures() " + CGLString(e));
	if(m_fixed)
		m_freeChannelList.push_back(m_channel);
}

void CTexture::fix(){
	if(!m_freeChannelList.contains(m_channel)){
		CLog::log(this, CLog::ERROR, CLog::ERROR_USED, "channel already fixed, can't fix");
		return;
	}

	glActiveTexture(GL_TEXTURE0 + m_channel);
	glBindTexture(m_target, m_id);
	m_fixed = true;
	m_freeChannelList.removeOne(m_channel);
}

void CTexture::setData(void* p_data){
	m_data = p_data;

	glGetError();
	setTex();
	if(int e = glGetError() != 0)
		CLog::log(this, CLog::ERROR, CLog::ERROR_GL, "setData() " + CGLString(e));
}

void CTexture::setParameter(GLenum p_name, GLfloat p_param){
	glGetError();
	glBindTexture(m_target, m_id);
	glTexParameterf(m_target, p_name, p_param);
	glBindTexture(m_target, 0);
	if(int e = glGetError() != 0)
		CLog::log(this, CLog::ERROR, CLog::ERROR_GL, "setParameter() " + CGLString(e));
}

void CTexture::setParameter(GLenum p_name, GLint p_param){
	glGetError();
	glBindTexture(m_target, m_id);
	glTexParameteri(m_target, p_name, p_param);
	glBindTexture(m_target, 0);
	if(int e = glGetError() != 0)
		CLog::log(this, CLog::ERROR, CLog::ERROR_GL, "setParameter() " + CGLString(e));
}

void CTexture::send() const {
	glGetError();
	CProgram* program = CProgram::current();
	program->sendUniform1i(m_prefix + "TexMap", m_channel);
	if(!m_fixed){
		glActiveTexture(GL_TEXTURE0 + m_channel);
		glBindTexture(m_target, m_id);
	}
	if(int e = glGetError() != 0)
		CLog::log(this, CLog::ERROR, CLog::ERROR_GL, "send() " + CGLString(e));
}
