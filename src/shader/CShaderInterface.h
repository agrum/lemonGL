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
#include "../log/CLog.h"

#include <QVector>
#include <QLinkedList>
#include <QString>
#include <QFile>
#include <QDebug>

class CShaderInterface {

public:
	static GLint add(const QString&);
	static bool del(GLuint);
	static bool use(GLuint);
	inline static GLuint current() { return m_singleton.m_current; }

	static void sendUniform1f(const QString&,  GLfloat  v0);
	static void sendUniform2f(const QString&,  GLfloat  v0,  GLfloat  v1);
	static void sendUniform3f(const QString&,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2);
	static void sendUniform4f(const QString&,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2,  GLfloat  v3);
	static void sendUniform1i(const QString&,  GLint  v0);
	static void sendUniform2i(const QString&,  GLint  v0,  GLint  v1);
	static void sendUniform3i(const QString&,  GLint  v0,  GLint  v1,  GLint  v2);
	static void sendUniform4i(const QString&,  GLint  v0,  GLint  v1,  GLint  v2,  GLint  v3);

	static void sendUniform1fv(const QString&,  GLsizei  count,  const GLfloat * value);
	static void sendUniform2fv(const QString&,  GLsizei  count,  const GLfloat * value);
	static void sendUniform3fv(const QString&,  GLsizei  count,  const GLfloat * value);
	static void sendUniform4fv(const QString&,  GLsizei  count,  const GLfloat * value);
	static void sendUniform1iv(const QString&,  GLsizei  count,  const GLint * value);
	static void sendUniform2iv(const QString&,  GLsizei  count,  const GLint * value);
	static void sendUniform3iv(const QString&,  GLsizei  count,  const GLint * value);
	static void sendUniform4iv(const QString&,  GLsizei  count,  const GLint * value);

	static void sendUniformMatrix2fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix3fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix4fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix2x3fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix3x2fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix2x4fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix4x2fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix3x4fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);
	static void sendUniformMatrix4x3fv(const QString&,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value);

private:
	CShaderInterface();
	~CShaderInterface();

	char* loadShader(const QString&);
	int createShader(GLuint, const QString&, GLenum);
	GLint initProgram(const QString&);

private:
	static CShaderInterface m_singleton;

	GLuint m_current;
	QList<GLuint> m_programList;
};

#endif /* CPROGRAM_H_ */
