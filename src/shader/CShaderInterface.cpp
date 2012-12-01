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

#include "CShaderInterface.h"

CShaderInterface CShaderInterface::m_singleton;

CShaderInterface::CShaderInterface(){
	CLog::sign(this, "CShaderInterface");
}

CShaderInterface::~CShaderInterface(){
	while(!m_programList.empty())
		glDeleteProgram(m_programList.takeFirst());
}

GLint CShaderInterface::add(const QString& p_name){
	return m_singleton.initProgram(p_name);
}

bool CShaderInterface::del(GLuint p_id){
	if(m_singleton.m_programList.contains(p_id)){
		m_singleton.m_programList.removeOne(p_id);
		glDeleteProgram(p_id);
		return true;
	}
	return false;
}

bool CShaderInterface::use(GLuint p_id){
	if(m_singleton.m_programList.contains(p_id)){
		m_singleton.m_current = p_id;
		glUseProgram(p_id);
		return true;
	}
	return false;
}

//----

char* CShaderInterface::loadShader( const QString& p_filename ){
	FILE* fp;
	char* content = NULL;
	long length;
	QByteArray ba = p_filename.toAscii();

	fp = fopen( ba.data(), "rb" );
	if (fp)	{
		fseek( fp, 0, SEEK_END );
		length = ftell( fp );
		fseek( fp, 0, SEEK_SET );
		content = new char [length+1];
		if(!fread( content, sizeof( char ), length, fp ))
			qDebug() << "meeeh";
		fclose( fp );
		content[length] = '\0';
	}

	return content;
}

int CShaderInterface::createShader(GLuint p_id, const QString& p_filename, GLenum p_shaderType){
	const GLchar* content = loadShader(p_filename);

	if (content == NULL){
		CLog::log(this, CLog::INFO, CLog::ERROR_NULL, "Can't load shader " + p_filename);
		return -1;
	}

	GLint status, logSize;
	QByteArray log;
	GLuint shader = glCreateShader(p_shaderType);

	glShaderSource(shader, 1, &content, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE){
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		log.resize(logSize - 1);
		glGetShaderInfoLog(shader, logSize, &logSize, log.data());
		CLog::log(this, CLog::ERROR, CLog::ERROR_NULL, "Fail compile shader " + p_filename);
		qDebug() << QString("Fail compile shader %:\n\n%2").arg(p_filename).arg(QString(log));
		return -2;
	}
	glAttachShader(p_id, shader);
	delete [] content;

	return 0;
}

GLint CShaderInterface::initProgram( const QString& p_shaderPrefix ){
	GLuint id = glCreateProgram();
	createShader(id, p_shaderPrefix + ".vs", GL_VERTEX_SHADER);
	createShader(id, p_shaderPrefix + ".gs", GL_GEOMETRY_SHADER);
	createShader(id, p_shaderPrefix + ".fs", GL_FRAGMENT_SHADER);

	GLint status, logSize;
	QByteArray log;
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if(status != GL_TRUE){
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logSize);
		log.resize(logSize - 1);
		glGetProgramInfoLog(id, logSize, &logSize, log.data());
		CLog::log(this, CLog::ERROR, CLog::ERROR_NULL, "Fail link program");
		qDebug() << QString("Fail link program \n\n%1").arg(QString(log));
		glDeleteProgram(id);
		return -1;
	}
	m_programList.push_back(id);
	return id;
}

//----------

void CShaderInterface::sendUniform1f(const QString& p_name,  GLfloat  v0){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1f( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0 );
}

void CShaderInterface::sendUniform2f(const QString& p_name,  GLfloat  v0,  GLfloat  v1){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2f( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0, v1 );
}
void CShaderInterface::sendUniform3f(const QString& p_name,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3f( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0, v1, v2 );
}

void CShaderInterface::sendUniform4f(const QString& p_name,  GLfloat  v0,  GLfloat  v1,  GLfloat  v2,  GLfloat  v3){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4f( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0, v1, v2, v3 );
}

void CShaderInterface::sendUniform1i(const QString& p_name,  GLint  v0){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1i( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0 );
}

void CShaderInterface::sendUniform2i(const QString& p_name,  GLint  v0,  GLint  v1){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2i( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0, v1 );
}

void CShaderInterface::sendUniform3i(const QString& p_name,  GLint  v0,  GLint  v1,  GLint  v2){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3i( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0, v1, v2 );
}

void CShaderInterface::sendUniform4i(const QString& p_name,  GLint  v0,  GLint  v1,  GLint  v2,  GLint  v3){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4i( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), v0, v1, v2, v3 );
}


void CShaderInterface::sendUniform1fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform2fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform3fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform4fv(const QString& p_name,  GLsizei  count,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform1iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform1iv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform2iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform2iv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform3iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform3iv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}

void CShaderInterface::sendUniform4iv(const QString& p_name,  GLsizei  count,  const GLint * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniform4iv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, value );
}


void CShaderInterface::sendUniformMatrix2fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix2fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix3fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix3fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix4fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix4fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix2x3fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix2x3fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix3x2fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix3x2fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix2x4fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix2x4fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix4x2fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix4x2fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix3x4fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix3x4fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}

void CShaderInterface::sendUniformMatrix4x3fv(const QString& p_name,  GLsizei  count,  GLboolean  transpose,  const GLfloat * value){
	QByteArray ba = p_name.toLocal8Bit();
	glUniformMatrix4x3fv( glGetUniformLocation( m_singleton.m_current, (const char*) ba.data() ), count, transpose, value );
}


