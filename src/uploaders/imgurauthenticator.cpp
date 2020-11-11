#include "imgurauthenticator.h"

ImgurAuthenticator::ImgurAuthenticator()
{

}

void ImgurLoginUploader::requestAuthorization()
{
	auto callbackPort = 1235;
	auto callbackHandler = new QOAuthHttpServerReplyHandler(callbackPort, this);

	QUrl authorizeUrl("https://api.imgur.com/oauth2/authorize");
	authorizeUrl.addQueryItem(CLIENT_ID_CSTR, IMGUR_CLIENT_ID);
	authorizeUrl.addQueryItem(REDIRECT_URI_CSTR, resPage);
	authorizeUrl.addQueryItem(RESPONSE_TYPE_CSTR, TOKEN_CSTR);
	authorizeUrl.addQueryItem("state", "0");

	oauth2.setReplyHandler(callbackHandler);
	oauth2.setAuthorizationUrl(authorizeUrl);


}


RedditWrapper::RedditWrapper(QObject *parent) : QObject(parent)
{
	connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](
			QAbstractOAuth::Status status) {
		if (status == QAbstractOAuth::Status::Granted)
			emit authenticated();
	});
	oauth2.setModifyParametersFunction([&](QAbstractOAuth::Stage stage, QVariantMap *parameters) {
		if (stage == QAbstractOAuth::Stage::RequestingAuthorization && isPermanent())
			parameters->insert("duration", "permanent");
	});
	connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
			&QDesktopServices::openUrl);
}


oauth2.setReplyHandler(replyHandler);
oauth2.setAuthorizationUrl(QUrl("https://www.reddit.com/api/v1/authorize"));
oauth2.setAccessTokenUrl(QUrl("https://www.reddit.com/api/v1/access_token"));
oauth2.setScope("identity read");

connect(&oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, [=](
		QAbstractOAuth::Status status) {
	if (status == QAbstractOAuth::Status::Granted)
		emit authenticated();
});
oauth2.setModifyParametersFunction([&](QAbstractOAuth::Stage stage, QVariantMap *parameters) {
	if (stage == QAbstractOAuth::Stage::RequestingAuthorization && isPermanent())
		parameters->insert("duration", "permanent");
});
connect(&oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
		&QDesktopServices::openUrl);
