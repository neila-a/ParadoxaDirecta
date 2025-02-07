#ifndef CITIESPROCESS_H
#define CITIESPROCESS_H

#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include "../main/consts.h"
#include "../main/settings.h"

class CitiesProcess : public QProcess {
    Q_OBJECT
public:
    CitiesProcess(QString gameDir);
    void play();

private:
    Settings settings;
    void setupEnvironment();
    QString _gameDir;
private slots:
    void on_finished(int exitCode);
    void on_error(ProcessError error);
};

#endif // CITIESPROCESS_H
