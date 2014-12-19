//==================================================================================================================|
// Created 2013.11.16 by Daniel L. Watkins
//
// Copyright (C) 2013-2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#include <QtGui/QGuiApplication>
#include <QtCore/QSettings>
#include <QQmlContext>

#include "Main.h"
#include "Terrain3D.h"
#include "Settings.h"

#include <QuickItems/CameraItem.h>

Settings mainSettings;


/**
 * Launches a Terrain3D window instance. Blocks until the instance finishes. The
 * instance may request to be restarted which will cause further blocking until
 * the new instance finishes and does not restart again.
 */
void loadAndRun(QGuiApplication &app)
{
	bool restart = true;

	while (restart)
	{
		{
			t3d::Terrain3D mainWindow(&mainSettings);

			mainWindow.rootContext()->setContextProperty("appSettings", &mainSettings);
			mainWindow.rootContext()->setContextProperty("terrain3D", &mainWindow);
			mainWindow.init();

			app.exec();
			restart = mainWindow.needsRestart();
		}

		qDebug() << "Ending all render threads";	//xyzm
		//t3d::OpenGLQuickItem::endAllRenderThreads();
	}
}


int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	mainSettings.init();


	//set all the QuickItem types
	{
		using namespace t3d::QuickItems;

		qmlRegisterType<CameraItem>("Terrain3D", 1, 0, "Camera");
		qmlRegisterType<Settings>("Terrain3D", 1, 0, "Settings");
	}

	loadAndRun(app);

	return 0;
}
