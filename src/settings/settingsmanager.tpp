#ifndef SETTINGSMANAGER_TPP
#define SETTINGSMANAGER_TPP

#include <QButtonGroup>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QDial>
#include <QDoubleSpinBox>
#include <QFontComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSlider>
#include <QSpinBox>
#include <QTextEdit>
#include <QTimeEdit>
#include <QWidget>
#include <QMainWindow>
#include <QDebug>

template<>QVariant SettingsManager::Input<QButtonGroup>::toVariant() const
{
	return object->checkedId();
}

template<>void SettingsManager::Input<QButtonGroup>::fromVariant(QVariant variant)
{
	if (object->button(variant.toInt()))
		object->button(variant.toInt())->setChecked(true);
}

template<>QVariant SettingsManager::Input<QCalendarWidget>::toVariant() const
{
	return object->selectedDate();
}

template<>void SettingsManager::Input<QCalendarWidget>::fromVariant(QVariant variant)
{
	object->setSelectedDate(variant.toDate());
}

template<>QVariant SettingsManager::Input<QCheckBox>::toVariant() const
{
	return object->isChecked();
}

template<>void SettingsManager::Input<QCheckBox>::fromVariant(QVariant variant)
{
	object->setChecked(variant.toBool());
}

template<>QVariant SettingsManager::Input<QComboBox>::toVariant() const
{
	if (object->isEditable())
		return object->currentText();
	else
		return object->currentIndex();
}

template<>void SettingsManager::Input<QComboBox>::fromVariant(QVariant variant)
{
	int i = variant.toInt();
	if (object->isEditable() && object->lineEdit())
		object->lineEdit()->setText(variant.toString());
	else if (0 <= i && i < object->count())
		object->setCurrentIndex(i);
	else
		object->setCurrentIndex(0);
}

template<>QVariant SettingsManager::Input<QDateEdit>::toVariant() const
{
	return object->date();
}

template<>void SettingsManager::Input<QDateEdit>::fromVariant(QVariant variant)
{
	object->setDate(variant.toDate());
}

template<>QVariant SettingsManager::Input<QDateTimeEdit>::toVariant() const
{
	return object->dateTime();
}

template<>void SettingsManager::Input<QDateTimeEdit>::fromVariant(QVariant variant)
{
	object->setDateTime(variant.toDateTime());
}

template<>QVariant SettingsManager::Input<QDial>::toVariant() const
{
	return object->value();
}

template<>void SettingsManager::Input<QDial>::fromVariant(QVariant variant)
{
	object->setValue(variant.toInt());
}

template<>QVariant SettingsManager::Input<QDoubleSpinBox>::toVariant() const
{
	return object->value();
}

template<>void SettingsManager::Input<QDoubleSpinBox>::fromVariant(QVariant variant)
{
	object->setValue(variant.toDouble());
}

template<>QVariant SettingsManager::Input<QFontComboBox>::toVariant() const
{
	return object->currentFont();
}

template<>void SettingsManager::Input<QFontComboBox>::fromVariant(QVariant variant)
{
	object->setCurrentFont(variant.value<QFont>());
}

template<>QVariant SettingsManager::Input<QGroupBox>::toVariant() const
{
	return object->isChecked();
}

template<>void SettingsManager::Input<QGroupBox>::fromVariant(QVariant variant)
{
	object->setChecked(variant.toBool());
}

template<>QVariant SettingsManager::Input<QLineEdit>::toVariant() const
{
	return (object->echoMode() == QLineEdit::Password) ? QVariant(encode(object->text())) : QVariant(object->text());
}

template<>void SettingsManager::Input<QLineEdit>::fromVariant(QVariant variant)
{
	object->setText((object->echoMode() == QLineEdit::Password) ? decode(variant.toByteArray()) : variant.toString());
}

template<>QVariant SettingsManager::Input<QPlainTextEdit>::toVariant() const
{
	return object->toPlainText();
}

template<>void SettingsManager::Input<QPlainTextEdit>::fromVariant(QVariant variant)
{
	object->setPlainText(variant.toString());
}

template<>QVariant SettingsManager::Input<QSlider>::toVariant() const
{
	return object->value();
}

template<>void SettingsManager::Input<QSlider>::fromVariant(QVariant variant)
{
	object->setValue(variant.toInt());
}

template<>QVariant SettingsManager::Input<QSpinBox>::toVariant() const
{
	return object->value();
}

template<>void SettingsManager::Input<QSpinBox>::fromVariant(QVariant variant)
{
	object->setValue(variant.toInt());
}

template<>QVariant SettingsManager::Input<QTextEdit>::toVariant() const
{
	return object->toHtml();
}

template<>void SettingsManager::Input<QTextEdit>::fromVariant(QVariant variant)
{
	object->setHtml(variant.toString());
}

template<>QVariant SettingsManager::Input<QTimeEdit>::toVariant() const
{
	return object->time();
}

template<>void SettingsManager::Input<QTimeEdit>::fromVariant(QVariant variant)
{
	object->setTime(variant.toTime());
}

template<>QVariant SettingsManager::Input<QWidget>::toVariant() const
{
	return object->saveGeometry();
}

template<>void SettingsManager::Input<QWidget>::fromVariant(QVariant variant)
{
	object->restoreGeometry(variant.toByteArray());
}

template<>QVariant SettingsManager::Input<QMainWindow>::toVariant() const
{
	return object->saveState();
}

template<>void SettingsManager::Input<QMainWindow>::fromVariant(QVariant variant)
{
	object->restoreState(variant.toByteArray());
}

#endif // SETTINGSMANAGER_TPP
