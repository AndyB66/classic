#pragma once

#include "imguranonuploader.h"
#include <QWidget>

namespace Ui {
class ImgurLoginUploader;
}

class ImgurLoginUploader : public ImgurAnonUploader
{
	Q_OBJECT

public:
	explicit ImgurLoginUploader(QWidget *parent, QSettings &settings);
	~ImgurLoginUploader();

	virtual void load();

	virtual bool init(int imageNumber);
	virtual QString uploadImage(QString filePath, QIODevice *image);

	void requestAuthorization();

protected:
	bool checkToken();
	void authorize();

private slots:
	void pageFinished();

protected:
	virtual void setAuthorization(NetworkTransaction *tr);

	Ui::ImgurLoginUploader *ui;
	static const QString resPage;

	QString accessToken;
	QString refreshToken;
	QDateTime expires;

};

