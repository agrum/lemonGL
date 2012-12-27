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

#ifndef CLEMONGL_H_
#define CLEMONGL_H_

#include "../src/object/CObject.h"
#include "../src/object/CMeshMngr.h"

class lemonGL {

public:
	static void init(){
		glewExperimental = GL_TRUE;

		GLenum error = glewInit();
		if(error != GLEW_OK){
			qDebug() << QString("Echec de l'initialization de GLEW: %1")
					.arg(reinterpret_cast<const char *>(glewGetErrorString(error)));
			exit(-1);
		}

		CTexture::init();
		m_opaqueProgram = CShaderInterface::add("shaders/opaque");
		m_illuminationProgram = CShaderInterface::add("shaders/illumination");
	}

private:
	lemonGL() {}

public:
	static GLint m_opaqueProgram;
	static GLint m_illuminationProgram;
};

#endif /* CLEMONGL_H_ */
