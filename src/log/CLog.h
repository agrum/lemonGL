/*
 * CLog.h
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#ifndef CLOG_H_
#define CLOG_H_

#include "CLogString.h"

#include <QThread>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include <QTime>
#include <QFile>
#include <QDebug>

#define CLOG_SIGN_LENGTH 10
#define CLOG_EXT_LENGTH 30

class CLog : public QThread {

public:
	enum Code{
		INFO = 1,
		DEBUG = 2,
		WARNING = 4,
		ERROR = 8,
		ALL = 15
	};

	enum Msg{
		ERROR_LOG_FILE = 100,
		ERROR_SIGNATURE = 101,
		ERROR_CODE = 102,
		ERROR_MESSAGE = 103,
		ERROR_SIZE = 110
	};

	CLog(const QString&, int);
	~CLog();

	const QString getCodeString(Code);
	const QString getMsgString(Msg);

	static int sign(void*, const QString&);
	static int log(void*, Code, Msg, const QString& p_ext = "");
	void run();

private:
	QFile m_logFile;
	static CLog* m_log;
	static int m_logLvl;
	static QMap<void*, QString> m_signatory;
	static QQueue<QString> m_pendingLog;
	static QMutex m_mutex;
};

#endif /* CLOG_H_ */
