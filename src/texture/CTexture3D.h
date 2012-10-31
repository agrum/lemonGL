/*
 * CTexture3D.h
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#ifndef CTEXTURE3D_H_
#define CTEXTURE3D_H_

#include "CTexture.h"

class CTexture3D : public CTexture {

public:
	CTexture3D(QString, GLuint, GLenum, GLenum, GLenum);

	void setWidth(int);
	void setHeight(int);
	void setDepth(int);

private:
	void setTex();

private:
	GLuint m_width, m_height, m_depth;

};

#endif /* CTEXTURE3D_H_ */
