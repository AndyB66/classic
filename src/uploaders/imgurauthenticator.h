#ifndef IMGURAUTHENTICATOR_H
#define IMGURAUTHENTICATOR_H

#include <QUrl>

class ImgurAuthenticator
{
	Q_OBJECT

	QOAuth2AuthorizationCodeFlow oauth2;

	static const auto callbackPort = 1235;
	static const auto authUrlBase =
			QString("https://api.imgur.com/oauth2/authorize");



public:
	ImgurAuthenticator();

	QUrl buildAuthorizeUrl();
};

#endif // IMGURAUTHENTICATOR_H
