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

#ifndef CPROGRAM_H_
#define CPROGRAM_H_

#include "../CGL.h"

#include <QVector>
#include <QLinkedList>
#include <QString>
#include <QFile>
#include <QDebug>

class CProgram {

public:
	CProgram();
	virtual ~CProgram();

	void use() { glUseProgram(m_id); m_used = this; }
	static CProgram* current() { return m_used; }
    static GLuint currentId() { return m_used->m_id; }
	char* loadShader(const QString&);
	int createShader(const QString&, GLenum);
	void initProgram(const QString&);

	void sendUniform1f(const QString&,  GLfloat  v0);
	void sendUniform2f(const QString&,  GLfloat  v0,  GLfloat  v1);
	void sendUniform3f(const QString&,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2);
	void sendUniform4f(const QString&,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2,  GLfloat  v3);
	void sendUniform1i(const QString&,  GLint  v0);
	void sendUniform2i(const QString&,  GLint  v0,  GLint  v1);
	void sendUniform3i(const QString&,  GLint  v0,  GLint  v1,  GLint  v2);
	void sendUniform4i(const QString&,  GLint  v0,  GLint  v1,  GLint  v2,  GLint  v3);

	void sendUniform1fv(const QString&,  GLsizei  count,  const GLfloat * value);
	void sendUniform2fv(const QString&,  GLsizei  count,  const GLfloat * value);
	void sendUniform3fv(const QString&,  GLsizei  count,  const GLfloat * value);
	void sendUniform4fv(const QString&,  GLsizei  count,  const GLfloat * value);
	void sendUniform1iv(const QString&,  GLsizei  count,  const GLint * value);
	void sendUniform2iv(const QString&,  GLsizei  count,  const GLint * value);
	void sendUniform3iv(const QString&,  GLsizei  count,  const GLint * value);
	void sendUniform4iv(const QString&,  GLsizei  count,  const GLint * value);

	void sendUniformMatrix2fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix3fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix4fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix2x3fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix3x2fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix2x4fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix4x2fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix3x4fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	void sendUniformMatrix4x3fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);

private:
	static CProgram* m_used;
	bool m_init;
	GLuint m_id;
};

#endif /* CPROGRAM_H_ */
