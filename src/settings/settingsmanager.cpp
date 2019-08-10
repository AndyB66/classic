#include "settingsmanager.h"
#include "secrets.h"
#include "application.h"

#include <QSettings>

#include "settingsmanager.tpp"

uint qHash(const QPointer<QObject> &pointer)
{
	return qHash(pointer.data());
}

SettingsManager::AbstractInput::AbstractInput(QString name, QVariant defaultVal): //QObject *receiver, const char *member,
	key(name), defaultVal(defaultVal), //receiver(receiver), member(member),
	wasChanged(false),
	pasKey(QByteArray::fromHex(PASSWORD_RAW_KEY))
{
}

SettingsManager::AbstractInput::~AbstractInput()
{
}

void SettingsManager::AbstractInput::connect(QObject *receiver, const char *member)
{
	QString string(member);
	string.remove(QRegExp("^[0-9]+"));
	string.remove(QRegExp("\\(\\)$"));

	listeners.insert(qMakePair(QPointer<QObject>(receiver), string.toAscii()));
}

void SettingsManager::AbstractInput::changedRemotely() const
{
	foreach (Listener listener, listeners)
		QMetaObject::invokeMethod(listener.first, listener.second);
}

QByteArray SettingsManager::AbstractInput::encode(QString pass) const
{
	return qCompress(pass.toAscii()) ^ pasKey;
}

QString SettingsManager::AbstractInput::decode(QByteArray pass) const
{
	return pass.isEmpty() ? "" : qUncompress(pass ^ pasKey);
}

SettingsManager::SettingsManager(QSettings &settings):
	settings(settings)
{
}

SettingsManager::~SettingsManager()
{
	qDeleteAll(inputs);
}

void SettingsManager::connectMany(QObject *receiver, const char *member, AbstractField *f0, AbstractField *f1,
								  AbstractField *f2, AbstractField *f3, AbstractField *f4, AbstractField *f5,
								  AbstractField *f6, AbstractField *f7, AbstractField *f8, AbstractField *f9)
{
	if (f0)	f0->connect(receiver, member);
	if (f1)	f1->connect(receiver, member);
	if (f2)	f2->connect(receiver, member);
	if (f3)	f3->connect(receiver, member);
	if (f4)	f4->connect(receiver, member);
	if (f5)	f5->connect(receiver, member);
	if (f6)	f6->connect(receiver, member);
	if (f7)	f7->connect(receiver, member);
	if (f8)	f8->connect(receiver, member);
	if (f9)	f9->connect(receiver, member);
}

void SettingsManager::load(AbstractInput *singleInput)
{
	foreach (AbstractInput *input, singleInput ? QList<AbstractInput *>() << singleInput : inputs)
		input->fromVariant(settings.value(input->key, input->defaultVal));
}

void SettingsManager::save(AbstractInput *singleInput)
{
	Application::busy();

	QSet<Listener> listeners; // call each listener only once when multiple options changed
	foreach (AbstractInput *input, singleInput ? QList<AbstractInput *>() << singleInput : inputs)
	{
		if (input->toVariant() == settings.value(input->key, input->defaultVal))
		{
			input->wasChanged = false;
			continue;
		}

		input->wasChanged = true;
		listeners.unite(input->listeners);
		settings.setValue(input->key, input->toVariant());

		QStringList listenerNames;
		foreach (Listener listener, input->listeners)
		{
			const QString name = listener.first->objectName().isEmpty() ? listener.first->metaObject()->className() : listener.first->objectName();
			listenerNames << QString("%2@%1").arg(name).arg(QString(listener.second));
		}
		qDebug() << input->key << "triggers:" << listenerNames.join(", ");
	}

	foreach (Listener listener, listeners)
		if (listener.first)
			QMetaObject::invokeMethod(listener.first, listener.second.constData());

	Application::idle();
}

QByteArray operator^(const QByteArray &a1, const QByteArray &a2)
{
	QByteArray res = a1;
	for (int i = 0, j = 0; i < res.size(); ++i, ++j %= a2.size())
		res.data()[i] ^= a2.data()[j];
	return res;
}
