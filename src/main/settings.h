#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QObject>
#include <QSettings>
#include <QStringList>
#include <QtGlobal>

class Settings : public QSettings {
    Q_OBJECT
public:
    explicit Settings(QSettings *parent = nullptr);
    const QStringList getStartArguments();

    const QString getLauncherpathLocation();
    bool writeLauncherpath();

    const QString getGamepath();
    const QString getStartCommand();

    static const QString CITIES;
    static const QString basePath;

signals:
};

#endif // SETTINGS_H
