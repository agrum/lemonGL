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
