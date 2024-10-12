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
    static const QString CITIES;

signals:
};

#endif // SETTINGS_H
