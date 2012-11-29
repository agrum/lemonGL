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
		ERROR_USED = 112,
		ERROR_NULL = 113
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
