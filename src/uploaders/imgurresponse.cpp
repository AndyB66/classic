#include "imgurresponse.h"
#include "networktransaction.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QDebug>

ImgurResponse::ImgurResponse(const NetworkTransaction &tr):
	success(false),
	status(0)
{
	parseResponse(tr);
}

void ImgurResponse::debug() const
{
	QDebug debug(QtDebugMsg);
	debug.nospace() << "{\n";
	debug << "  success:     " << success << "\n";
	debug << "  status:      " << status << "\n";
	debug << "  error:       " << error << "\n";
	debug << "  mergedError: " << mergedError << "\n";
	debug << "  data:\n";
	debug << "  {\n";
	for (ParamMap::ConstIterator i = data.begin(); i != data.end(); ++i)
		debug << "    " << i.key() << ":\t" << i.value() << "\n";
	debug << "  }\n";
	for (ParamMap::ConstIterator i = begin(); i != end(); ++i)
		debug << "  " << i.key() << ":\t" << i.value() << "\n";
	debug << "}\n";
	debug.space();
}

/**
 * @brief Parses network transaction which contains a JSON response from Imgur.
 */
void ImgurResponse::parseResponse(const NetworkTransaction &tr)
{
	QJsonDocument jsonDoc = QJsonDocument::fromJson(tr.data.toUtf8());
	QJsonObject jsonRoot = jsonDoc.object();

	if (jsonRoot.contains("error")) {
		error = jsonRoot["error"].toString();
	}

	if (jsonRoot.contains("success")) {
		success = jsonRoot["success"].toBool();
	}

	if (jsonRoot.contains("status")) {
		status = jsonRoot["status"].toInt();
	}

	if (jsonRoot.contains("data")) {
		QJsonObject jsonData = jsonRoot["data"].toObject();
		QJsonObject::const_iterator it;

		for(it = jsonData.constBegin(); it != jsonData.constEnd(); it++) {
			data.insert(it.key(), it.value().toVariant().toString());
		}
	}

	if (data.contains("error") && error.isEmpty())
		error = data.take("error");

	QStringList errors;
	if (!tr.error.isEmpty())
		errors << tr.error;
	if (!error.isEmpty())
		errors << error;
	if (contains("message"))
		errors << value("message");
	if (data.contains("message"))
		errors << data["message"];

	mergedError = errors.join("\n");
}
