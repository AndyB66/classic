#ifndef DISPLAYSLIDER_TPP
#define DISPLAYSLIDER_TPP

template<>QVariant SettingsManager::Input<DisplaySlider>::toVariant() const
{
	return object->value();
}

template<>void SettingsManager::Input<DisplaySlider>::fromVariant(QVariant variant)
{
	object->setValue(variant.toInt());
}

#endif // DISPLAYSLIDER_TPP
