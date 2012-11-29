/*
 * CLog.h
 *
 *  Created on: Oct 31, 2012
 *      Author: agrum
 */

#ifndef CLOG_H_
#define CLOG_H_

#include "CLogString.h"
#include "CGLString.h"

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
		ERROR_GL = 110,
		ERROR_SIZE = 111,
		ERROR_USED = 112
	};

	static void init(const QString&, int);
	static void close();

	const QString getCodeString(Code);
	const QString getMsgString(Msg);

	static int sign(const void*, const QString&);
	static int log(const void*, Code, Msg, const QString& p_ext = "");
	void run();

private:
	CLog(const QString&, int);
	~CLog();

private:
	static CLog* m_log;

	QFile m_logFile;
	int m_logLvl;
	QMap<const void*, QString> m_signatory;
	QQueue<QString> m_pendingLog;
	QMutex m_mutex;
};

#endif /* CLOG_H_ */
