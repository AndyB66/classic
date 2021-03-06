#pragma once

#include <QString>
#include <QMap>

class NetworkTransaction;

// TODO: Make it <QString, QVariant> to avoid unnecessary data conversions.
typedef QMap<QString, QString> ParamMap;

class ImgurResponse : public ParamMap
{
public:
	ImgurResponse(const NetworkTransaction &tr);
	void debug() const;

	ParamMap data;
	bool success;
	int status;
	QString error;
	QString mergedError;

private:
	void parseResponse(const NetworkTransaction &tr);
};
