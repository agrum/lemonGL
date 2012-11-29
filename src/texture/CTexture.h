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

#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "../CGL.h"
#include "../log/CLog.h"
#include "../shader/CProgram.h"

#include <limits>
#include <cmath>
#include <QString>
#include <QMatrix4x4>

class CTexture {

public:
	CTexture(QString, GLuint, GLenum, GLenum, GLenum);
	~CTexture();

	static void init();

	void fix();
	void setData(void*);
	void setParameter(GLenum, GLfloat);
	void setParameter(GLenum, GLint);
	GLuint id() { return m_id; }
	void send() const;

protected:
	virtual void setTex() = 0;

protected:
	static QList<int> m_freeChannelList;

	QString m_prefix;
	GLuint m_channel;
	GLuint m_id;
	GLenum m_internalFormat;
	GLenum m_format;
	GLenum m_type;
	GLenum m_target;
    void* m_data;
    bool m_fixed;
};

#endif /* CTEXTURE_H_ */
