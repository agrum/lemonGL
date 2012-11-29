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

#ifndef CTEXTURE2D_H_
#define CTEXTURE2D_H_

#include "CTexture.h"

class CTexture2D : public CTexture {

public:
	CTexture2D(QString, QString, GLuint);
	CTexture2D(QString, GLuint, GLenum, GLenum, GLenum);

	void setWidth(int);
	void setHeight(int);
	void sendToProgram(const QMatrix4x4&) const ;

	void appendImg(const QString&);
	void setSize(GLuint, GLuint);

private:
	void setTex();

private:
	GLuint m_width, m_height;
	QImage m_image;

};

#endif /* CTEXTURE2D_H_ */
