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

#include "CLog.h"

CLog* CLog::m_log = NULL;

CLog::CLog(const QString& p_logPath, int p_logLvl) :
		m_logFile(p_logPath)
{
	m_log = this;
	m_logLvl = p_logLvl;
	sign(this, "CLog");

	if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Text)){
		log(m_log, CLog::ERROR, CLog::ERROR_LOG_FILE, "Can't open file");
		return;
	}

	start();
}

CLog::~CLog(){
	m_logFile.close();
}

void CLog::init(const QString& p_logPath, int p_logLvl){
	if(m_log == NULL)
		new CLog(p_logPath, p_logLvl);
}

void CLog::close(){
	if(m_log != NULL)
		delete m_log;
}

int CLog::sign(const void* p_key, const QString& p_value){
	if(m_log == NULL)
		return -1;

	if(p_key == NULL || p_value.isNull())
		return log(m_log, CLog::ERROR, CLog::ERROR_SIGNATURE, "Signature empty");

	QString value = p_value;
	while(value.length() < CLOG_SIGN_LENGTH)
		value += '-';
	if(value.length() > CLOG_SIGN_LENGTH)
		value = value.left(CLOG_SIGN_LENGTH);

	m_log->m_signatory.insert(p_key, value);

	return 1;
}

int CLog::log(const void* p_signKey, Code p_code, Msg p_msg, const QString& p_ext){
	if(m_log == NULL)
		return -1;
	else if(p_code == ALL)
		return log(m_log, CLog::ERROR, CLog::ERROR_CODE, "Asked for ALL code");
	else if((p_code & m_log->m_logLvl) == 0)
		return 0;

	QString addr = QString("%1").arg((int) p_signKey, 16, 16);
	QString sign = m_log->m_signatory.value(p_signKey);
	QString code = m_log->getCodeString(p_code);
	QString msg = m_log->getMsgString(p_msg);
	QString logMsg = QString("(%1) %2 | %3::%4 | %5 | %6")
							.arg(code)
							.arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
							.arg(sign)
							.arg(msg)
							.arg(addr)
							.arg(p_ext);

	if(code.isNull())
		return log(m_log, CLog::ERROR, CLog::ERROR_CODE, sign);
	if(msg.isNull())
		return log(m_log, CLog::ERROR, CLog::ERROR_MESSAGE, sign);

	qDebug() << logMsg;
	m_log->m_mutex.lock();
	m_log->m_pendingLog.enqueue(logMsg);
	m_log->m_mutex.unlock();

	return 0;
}

void CLog::run(){
	while(true){
		m_mutex.lock();
		while(!m_pendingLog.empty())
			if(m_logFile.write(m_pendingLog.dequeue().toAscii()) == -1)
				exit(log(m_log, CLog::ERROR, CLog::ERROR_LOG_FILE, "Writing error"));
		m_mutex.unlock();

		msleep(1000);
	}
}

const QString CLog::getCodeString(Code p_code){
	switch (p_code) {
	case INFO:
		return CLOG_CODE_INFO;
		break;
	case DEBUG:
		return CLOG_CODE_DEBUG;
		break;
	case WARNING :
		return CLOG_CODE_WARNING;
		break;
	case ERROR :
		return CLOG_CODE_ERROR;
		break;
	default :
		;
	}
	return "";
}

const QString CLog::getMsgString(Msg p_msg){
	switch (p_msg) {
	case ERROR_LOG_FILE:
		return CLOG_MSG_ERROR_LOG_FILE;
		break;
	case ERROR_SIGNATURE:
		return CLOG_MSG_ERROR_SIGNATURE;
		break;
	case ERROR_CODE :
		return CLOG_MSG_ERROR_CODE;
		break;
	case ERROR_MESSAGE :
		return CLOG_MSG_ERROR_MESSAGE;
		break;
	case ERROR_GL :
		return CLOG_MSG_ERROR_GL;
		break;
	case ERROR_SIZE :
		return CLOG_MSG_ERROR_SIZE;
		break;
	case ERROR_USED :
		return CLOG_MSG_ERROR_USED;
		break;
	case ERROR_NULL :
		return CLOG_MSG_ERROR_NULL;
		break;
	default :
		;
	}
	return "";
}
