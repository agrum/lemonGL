/*
 * CTexture.h
 *
 *  Created on: May 7, 2012
 *      Author: agrum
 */

#ifndef CTEXTURE_H_
#define CTEXTURE_H_

#include "../CGL.h"
#include "../shader/CProgram.h"

#include <limits>
#include <cmath>
#include <QString>
#include <QMatrix4x4>

class CTexture {

public:
	CTexture(QString, GLuint, GLenum, GLenum, GLenum);
	~CTexture();

	void setData(void*);
	void setParameter(GLenum, GLfloat);
	GLuint id() { return m_id; }
	void send() const;

protected:
	virtual void setTex() = 0;

protected:
	QString m_prefix;
	GLuint m_channel;
	GLuint m_id;
	GLenum m_internalFormat;
	GLenum m_format;
	GLenum m_type;
	GLenum m_target;
    void* m_data;
};

#endif /* CTEXTURE_H_ */
