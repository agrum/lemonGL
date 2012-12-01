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

#include "CMaterial.h"

CMaterial::CMaterial(const QString& p_group):
m_group(p_group),
m_diffuse(0,0,0),
m_ambient(0,0,0),
m_specular(0,0,0),
m_diffuseMap(NULL),
m_ambientMap(NULL),
m_specularMap(NULL)
{

}

CMaterial::CMaterial(const CMaterial& p_mat):
m_group(p_mat.m_group),
m_diffuse(0,0,0),
m_ambient(0,0,0),
m_specular(0,0,0),
m_diffuseMap(NULL),
m_ambientMap(NULL),
m_specularMap(NULL)
{

}

CMaterial::~CMaterial(){
	if(m_diffuseMap != NULL)
		delete m_diffuseMap;
	if(m_ambientMap != NULL)
		delete m_ambientMap;
	if(m_specularMap != NULL)
		delete m_specularMap;
}

void CMaterial::sendToProgram() const {
	if(m_diffuseMap == NULL){
		CShaderInterface::sendUniform3f("diffuse", m_diffuse.x(), m_diffuse.y(), m_diffuse.z());
		CShaderInterface::sendUniform1i("isDiffuseMap", 0);
	}
	else{
		m_diffuseMap->send();
		CShaderInterface::sendUniform1i("isDiffuseMap", 1);
	}
	if(m_ambientMap == NULL){
		CShaderInterface::sendUniform3f("ambient", m_ambient.x(), m_ambient.y(), m_ambient.z());
		CShaderInterface::sendUniform1i("isAmbientMap", 0);
	}
	else{
		m_ambientMap->send();
		CShaderInterface::sendUniform1i("isAmbientMap", 1);
	}
	if(m_specularMap == NULL){
		CShaderInterface::sendUniform3f("specular", m_specular.x(), m_specular.y(), m_specular.z());
		CShaderInterface::sendUniform1i("isSpecularMap", 0);
	}
	else{
		m_specularMap->send();
		CShaderInterface::sendUniform1i("isSpecularMap", 1);
	}
}

const QString& CMaterial::getGroup(){
	return m_group;
}

void CMaterial::setDiffuse(const QVector3D& p_v){
	m_diffuse = p_v;
}

void CMaterial::setAmbient(const QVector3D& p_v){
	m_ambient = p_v;
}

void CMaterial::setSpecular(const QVector3D& p_v){
	m_specular = p_v;
}

void CMaterial::setDiffuseMap(const QString& p_filename){
	m_diffuseMap = new CTexture2D("diffuse", 1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, m_diffuseMap->id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_diffuseMap->appendImg(p_filename);
}

void CMaterial::setAmbientMap(const QString& p_filename){
	m_ambientMap = new CTexture2D("ambient", 2, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, m_ambientMap->id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_ambientMap->appendImg(p_filename);
}

void CMaterial::setSpecularMap(const QString& p_filename){
	m_specularMap = new CTexture2D("specular", 3, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	glBindTexture(GL_TEXTURE_2D, m_specularMap->id());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_specularMap->appendImg(p_filename);
}
