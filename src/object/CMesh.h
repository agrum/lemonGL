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

#ifndef CMESH_H_
#define CMESH_H_

#include "CObject.h"
#include "CFace.h"

class CMesh : public CObject {

public:
	CMesh();
	CMesh(const QString&);
	CMesh(const CMesh&);

	void addFace(CFace*);
	void free();
	bool operator==(const QString&);

	virtual void drawSub();

protected:
	QString m_group;
	QList<CFace*> m_faces;
	QList<int> m_order;
};

#endif /* CMESH_H_ */
