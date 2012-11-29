/*
 * CGLString.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: agrum
 */

#include "CGLString.h"

CGLString::CGLString(GLenum p_enum){
	switch (p_enum) {
	case GL_NO_ERROR:
		append( "GL_NO_ERROR");
		break;
	case GL_INVALID_ENUM:
		append( "GL_INVALID_ENUM");
		break;
	case GL_INVALID_VALUE :
		append( "GL_INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION :
		append( "GL_INVALID_OPERATION");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION :
		append( "GL_INVALID_FRAMEBUFFER_OPERATION");
		break;
	case GL_OUT_OF_MEMORY :
		append( "GL_OUT_OF_MEMORY");
		break;
	case GL_STACK_UNDERFLOW :
		append( "GL_STACK_UNDERFLOW");
		break;
	case GL_STACK_OVERFLOW :
		append( "GL_STACK_OVERFLOW");
		break;
	default :
		append( "GL_NO_NAME");
		;
	}
}
