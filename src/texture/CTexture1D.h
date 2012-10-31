/*
 * CTexture1D.h
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#ifndef CTEXTURE1D_H_
#define CTEXTURE1D_H_

#include "CTexture.h"

class CTexture1D : public CTexture {

public:
	CTexture1D(QString, GLuint, GLenum, GLenum, GLenum);

	void setWidth(int);

private:
	void setTex();

private:
	GLuint m_width;
};

#endif /* CTEXTURE1D_H_ */
