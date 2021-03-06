#pragma once

#include <QString>
#include <QCoreApplication>

class QWidget;

class Exception
{
	Q_DECLARE_TR_FUNCTIONS(Exception)

public:
	Exception(const char *file, int line, const char *func, QString what);
	void showMessage(QWidget *parent) const;
	QString message() const;

private:
	const QString file, func, what;
	const int line;
};

static inline bool throw_func(const char *file, int line, const char *func, QString what)
{
	throw Exception(file, line, func, what);
}


#define THROW(x)  throw Exception(__FILE__, __LINE__, Q_FUNC_INFO, x);
#define OR_THROW(x)	or throw_func(__FILE__, __LINE__, Q_FUNC_INFO, x);

#define SEEK_ERROR(x) (QString("Wrong offset: %1").arg(x))
