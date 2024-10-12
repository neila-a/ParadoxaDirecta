#include "settings.h"
#include <QCoreApplication>

Settings::Settings(QSettings *parent)
    : QSettings("config.ini", QSettings::IniFormat) {}

#ifdef Q_OS_WINDOWS
const QString Settings::CITIES = "\Cities.exe";
#else
const QString Settings::CITIES = "/Cities.x64";
#endif

const QString Settings::getLauncherpathLocation() {
#ifdef Q_OS_WINDOWS
    const QString basePath = "/AppData/Local/";
#else
    const QString basePath = "/.local/share/";
#endif
    const QString defaultLocation = QDir::homePath() + basePath
                                    + "Paradox Interactive/launcherpath";
    return value("launcherpathLocation", QDir::toNativeSeparators(defaultLocation)).toString();
}

bool Settings::writeLauncherpath() {
    QFile launcherpath(getLauncherpathLocation());
    const bool ok = launcherpath.open(QIODevice::WriteOnly | QIODevice::Text);
    if (ok) {
        launcherpath.write(qApp->applicationDirPath().toUtf8());
    }
    launcherpath.close();
    return ok;
}

const QStringList Settings::getStartArguments() {
    QStringList startArguments = {};
    if (value("continueGame", false).toBool()) {
        startArguments.append("--continuelastsave");
    }
    if (value("disableWorkshop", false).toBool()) {
        startArguments.append("--noWorkshop");
    }
    if (value("disableMods", false).toBool()) {
        startArguments.append("--disableMods");
    }
    if (value("noLogs", false).toBool()) {
        startArguments.append("-nolog");
    }
    if (value("fpsLimitOpen", false).toBool()) {
        startArguments.append("-limitfps " + value("fpsLimit", 60).toString());
    }
    switch (value("renderEngine", 0).toInt()) {
    case 1:
        startArguments.append("-force-opengl");
        break;
    case 2:
        startArguments.append("-force-d3d9");
        break;
    }
    return startArguments;
}
