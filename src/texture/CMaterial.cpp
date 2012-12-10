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
m_specularMap(NULL),
m_coneMap(NULL)
{
	CLog::sign(this, "CMat" + p_group);
}

CMaterial::CMaterial(const CMaterial& p_mat):
m_group(p_mat.m_group),
m_diffuse(0,0,0),
m_ambient(0,0,0),
m_specular(0,0,0),
m_diffuseMap(NULL),
m_ambientMap(NULL),
m_specularMap(NULL),
m_coneMap(NULL)
{
	CLog::sign(this, "CMat" + m_group);
}

CMaterial::~CMaterial(){
	if(m_diffuseMap != NULL)
		delete m_diffuseMap;
	if(m_ambientMap != NULL)
		delete m_ambientMap;
	if(m_specularMap != NULL)
		delete m_specularMap;
	if(m_coneMap != NULL)
		delete m_coneMap;
}

void CMaterial::sendToProgram() const {
	//Diffuse
	if(m_diffuseMap == NULL){
		CShaderInterface::sendUniform3f("diffuse", m_diffuse.x(), m_diffuse.y(), m_diffuse.z());
		CShaderInterface::sendUniform1i("isDiffuseMap", 0);
	}
	else{
		m_diffuseMap->send();
		CShaderInterface::sendUniform1i("isDiffuseMap", 1);
	}
	//Ambient
	if(m_ambientMap == NULL){
		CShaderInterface::sendUniform3f("ambient", m_ambient.x(), m_ambient.y(), m_ambient.z());
		CShaderInterface::sendUniform1i("isAmbientMap", 0);
	}
	else{
		m_ambientMap->send();
		CShaderInterface::sendUniform1i("isAmbientMap", 1);
	}
	//Specular
	if(m_specularMap == NULL){
		CShaderInterface::sendUniform3f("specular", m_specular.x(), m_specular.y(), m_specular.z());
		CShaderInterface::sendUniform1i("isSpecularMap", 0);
	}
	else{
		m_specularMap->send();
		CShaderInterface::sendUniform1i("isSpecularMap", 1);
	}
	//Relief through cone
	if(m_coneMap == NULL){
		CShaderInterface::sendUniform1i("isConeMap", 0);
	}
	else {
		m_coneMap->send();
		CShaderInterface::sendUniform1i("isConeMap", 1);
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
	m_diffuseMap = new CTexture2D("diffuse", p_filename, 1);
}

void CMaterial::setAmbientMap(const QString& p_filename){
	m_ambientMap = new CTexture2D("ambient", p_filename, 2);
}

void CMaterial::setSpecularMap(const QString& p_filename){
	m_specularMap = new CTexture2D("specular", p_filename, 3);
}

void CMaterial::setReliefMap(const QString& p_filename){
	if(m_coneMap != NULL)
		return;

	//Imported from cone step mapping paper (Dummer 2006)
	const float max_ratio = 1.0;
	const float invRed = 1.0/5.0;
	QImage img;
	uchar* data;
	int width, height;
	int chans = 4;
	int scanWidth;

	//Image init
	QStringList fileNameSplit = p_filename.split('.');
	QString coneMapName;

	fileNameSplit.removeLast();
	coneMapName = QString("%1%2").arg(fileNameSplit.join(".")).arg("Cone.png");
	if( img.load(coneMapName) ){
		setConeMap(coneMapName);
		return;
	}
	if( ! img.load(p_filename) )
		CLog::log(this, CLog::WARNING, CLog::ERROR_NULL, "error loading texture " + p_filename);
	img = img.convertToFormat(QImage::Format_ARGB32);
	data = img.bits();
	width = img.width();
	height = img.height();
	scanWidth = chans*width;

	//Derivatives
	for (int x = 0; x < width; ++x){
		for (int y = 0; y < height; ++y){
			int der;
			// Blue is the slope in x
			if (x == 0)
				der = (data[y*scanWidth + chans*(x+1) + 2] - data[y*scanWidth + chans*(x) + 2]) / 2;
			else if (x == width - 1)
				der = (data[y*scanWidth + chans*(x) + 2] - data[y*scanWidth + chans*(x-1) + 2]) / 2;
			else
				der = data[y*scanWidth + chans*(x+1) + 2] - data[y*scanWidth + chans*(x-1) + 2];
			data[y*scanWidth + chans*x] = 127 + der / 2;
			// Alpha is the slope in y
			if (y == 0)
				der = (data[(y+1)*scanWidth + chans*x + 2] - data[(y)*scanWidth + chans*x + 2]) / 2;
			else if (y == height - 1)
				der = (data[(y)*scanWidth + chans*x + 2] - data[(y-1)*scanWidth + chans*x + 2]) / 2;
			else
				der = (data[(y+1)*scanWidth + chans*x + 2] - data[(y-1)*scanWidth + chans*x + 2]);
			data[y*scanWidth + chans*x + 3] = 127 - der / 2;
		}
	}

	//Cones
	for (int x = 0; x < width; ++x){
		for (int y = 0; y < height; ++y){
			int depth = 255 - data[y*scanWidth + chans*x + 2];
			float expand = 1.0;
			float ratio = max_ratio;

			//Boundaries expanding
			for (int a = 1; a < ratio*invRed*depth; a += expand){
				for (int b = 1; b < ratio*invRed*depth; b += expand){
					//Searching on boundaries
					for (int i = -a; i <= a; ++i){
						for (int j = -b; j < b; ++j){
							if(i == -a || i == a || j == -b || j == b){
								if(x + i > 0
										&& x + i < width - 1
										&& y + j > 0
										&& y + j < height - 1){
									int diff = depth - (255 - data[(y+j)*scanWidth + chans*(x+i) + 2]);
									diff *= invRed;
									if(diff > 0){
										float ratioTmp = sqrt(i*i + j*j)/diff;
										if (ratioTmp < ratio)
											ratio = ratioTmp;
									}
								}
							}
						}
					}
				}
			}
			data[y*scanWidth + chans*x + 1] = ratio*255;
		}
	}

	//Save and use
	img.save(coneMapName);
	setConeMap(coneMapName);
}

void CMaterial::setConeMap(const QString& p_filename){
	m_coneMap = new CTexture2D("cone", p_filename, 4);
}
