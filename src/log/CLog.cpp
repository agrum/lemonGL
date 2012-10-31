/*
 * CLog.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#include "CLog.h"

CLog* CLog::m_log = NULL;
int CLog::m_logLvl = 0;
QMap<void*, QString> CLog::m_signatory;
QQueue<QString> CLog::m_pendingLog;
QMutex CLog::m_mutex;

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

int CLog::sign(void* p_key, const QString& p_value){
	if(p_key == NULL || p_value.isNull())
		return log(m_log, CLog::ERROR, CLog::ERROR_SIGNATURE, "Signature empty");

	QString value = p_value;
	if(value.length() < CLOG_SIGN_LENGTH)
		value = value.fill('-', CLOG_SIGN_LENGTH - value.length());
	else if(value.length() > CLOG_SIGN_LENGTH)
		value = value.left(CLOG_SIGN_LENGTH);

	m_signatory.insert(p_key, value);

	return 0;
}

int CLog::log(void* p_signKey, Code p_code, Msg p_msg, const QString& p_ext){
	if(p_code == ALL)
		return log(m_log, CLog::ERROR, CLog::ERROR_CODE, "Asked for ALL code");
	else if((p_code & m_logLvl) == 0)
		return 0;

	QString sign = m_signatory.value(p_signKey);
	QString code = m_log->getCodeString(p_code);
	QString msg = m_log->getMsgString(p_msg);
	QString logMsg = QString("(%1) %2 | %3::%4 | %5")
							.arg(code)
							.arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
							.arg(sign)
							.arg(msg)
							.arg(p_ext);

	if(code.isNull())
		return log(m_log, CLog::ERROR, CLog::ERROR_CODE, sign);
	if(msg.isNull())
		return log(m_log, CLog::ERROR, CLog::ERROR_MESSAGE, sign);

	qDebug() << logMsg;
	m_mutex.lock();
	m_pendingLog.enqueue(logMsg);
	m_mutex.unlock();

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
	case ERROR_SIZE :
		return CLOG_MSG_ERROR_SIZE;
		break;
	default :
		;
	}
	return "";
}
