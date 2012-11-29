/*
 * CGLString.h
 *
 *  Created on: Nov 7, 2012
 *      Author: agrum
 */

#ifndef CGLSTRING_H_
#define CGLSTRING_H_

#include "../CGL.h"
#include <QString>

class CGLString : public QString {

public:
	CGLString(GLenum);
};

#endif /* CGLSTRING_H_ */
