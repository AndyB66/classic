#ifndef IMGURAUTHENTICATOR_H
#define IMGURAUTHENTICATOR_H


class ImgurAuthenticator
{
	Q_OBJECT

	QOAuth2AuthorizationCodeFlow oauth2;

public:
	ImgurAuthenticator();
};

#endif // IMGURAUTHENTICATOR_H
