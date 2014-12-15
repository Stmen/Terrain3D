//==================================================================================================================|
// Created 2014.12.11 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _t3d_SETTINGS_H
#define _t3d_SETTINGS_H

#include <QtCore/QSettings>
#include <QtCore/QHash>

#include "Main.h"

class SettingsListener;

class Settings : public QObject
{
	Q_OBJECT

public:
	/**
	 * @brief The default constructor is only available for QML. Instantiating
	 * a Settings instance in C++ is pointless.
	 */
	Settings() :
		mSettings(nullptr),
		mVersion("0.0.0")
	{}

	/**
	 * @brief Loads the settings from file and creates a table of default values.
	 * Should be called once at the begining before any QApplications exist.
	 */
	void init();

	enum Key
	{
		//graphics
		GraphicsScreenResolutionWidth,
		GraphicsScreenResolutionHeight,
		GraphicsScreenIsFullscreen,
		GraphicsCameraPositionX,
		GraphicsCameraPositionY,
		GraphicsCameraPositionZ,
		GraphicsCameraFOV,
		GraphicsCameraLOD,
		GraphicsCameraWireframe,

		//world
		WorldGeneratorSize,
		WorldGeneratorTextureMapResolution,
		WorldGeneratorSeed,
		WorldTerrainSpacing,
		WorldTerrainHeightScale,
		WorldTerrainBlockSize,
		WorldTerrainSpanSize


	}; Q_ENUMS(Key)

	/**
	 * @brief Each key/value enqueued with enqueueValue() is applied to the
	 * settings by calls to setValue().
	 */
	void applyQueuedValues();

	/**
	 * @brief Removes all queued settings from the settings queue.
	 */
	void clearQueuedValues() { mSettingsQueue.clear(); }

	/**
	 * Enques the \p key and \p value in a temporary queue which can later be
	 * be applied using applyQueuedValues().
	 */
	Q_INVOKABLE void enqueueValue(Key key, const QVariant &newValue);

	/**
	 * @brief Assigns \p value to be associated with \p key.
	 *
	 * @param key The key to associate with
	 * @param value The value to associate with
	 */
	void setValue(Key key, const QVariant &newValue);

	/**
	 * @returns The value associated with \p key. If the key does not exists, a
	 * default value is returned.
	 *
	 * @param key The key to find a value for
	 */
	Q_INVOKABLE QVariant value(Key key);

	/**
	 * @brief Adds \p listener to a list. All delegate methods are called
	 * as documented.
	 * @param listener The listener to add
	 */
	void addListener(SettingsListener *listener);

	/**
	 * @brief Removes \p listener from the list of listeners.
	 *
	 * @param listener The listener to be removed
	 */
	void removeListener(SettingsListener *listener);

private:
	Q_DISABLE_COPY(Settings)

	QSettings *mSettings;
	const QString mVersion;
	QHash<Key, QVariant> mDefaultValues;
	QList<SettingsListener*> mListeners;
	QList<QPair<Key, QVariant>> mSettingsQueue;

	QString stringNameForKey(Key key);
	void initDefaultValues();
	void checkForMissingDefaultValues();
};

class SettingsListener
{
public:
	/**
	 * @brief Called whenever a Settings value is changed. It is also called
	 * when the setting is loaded for the first time during application statup.
	 *
	 * @param key The key this value represents
	 * @param newValue The current value
	 * @param oldValue The value before before the new value
	 */
	virtual void settingsValueUpdated(Settings::Key key,
									  const QVariant &newValue,
									  const QVariant &oldValue) = 0;
};

#endif