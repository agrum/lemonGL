/*
 * CTexture2D.h
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
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
