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

#ifndef COBJECT_H_
#define COBJECT_H_

#include "../shader/CShaderInterface.h"
#include "../mvp/CMVP.h"
#include "../mvp/CLight.h"
#include "../texture/CMaterial.h"
#include "../texture/CMaterialMngr.h"

class CObject {

public:
	CObject();
	CObject(const CObject&);

	void draw(const CMVP* camera, QList<CLight*>* lights = NULL, QVector2D biasVP = QVector2D(0,0));
	virtual void drawSub() = 0;
	virtual void order(const QMatrix4x4&) {}

	void setParent(const CObject*);
	void setMaterial(const CMaterial*);

	void translucent(bool p_b) { m_translucent = p_b; }
	bool isTranslucent() { return m_translucent; }
	void pushMatrix();
	void popMatrix();
	void loadIdentity();
	void translate(GLfloat x, GLfloat y, GLfloat z);
	void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void scale(GLfloat x, GLfloat y, GLfloat z);

private:
	const QMatrix4x4 modelMatrix() const;

protected:
	const CObject* m_parent;
	const CMaterial* m_mat;
	QMatrix4x4 m_modelMatrix;
	QLinkedList<QMatrix4x4> m_matrixStack;
	bool m_translucent;
    void convertMatrix(const QMatrix4x4 p_in, float* p_out);
    void convertMatrix(const QMatrix3x3 p_in, float* p_out);
};

void convertMatrix(const QMatrix4x4, float*);
void convertMatrix(const QMatrix3x3, float*);

#endif /* COBJECT_H_ */
