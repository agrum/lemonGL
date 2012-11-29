/*
 * CLemonGL.h
 *
 *  Created on: Nov 29, 2012
 *      Author: agrum
 */

#ifndef CLEMONGL_H_
#define CLEMONGL_H_

#include "../src/log/CLog.h"
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
	}

private:
	lemonGL();
};

#endif /* CLEMONGL_H_ */
