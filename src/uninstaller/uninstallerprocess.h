#ifndef UNINSTALLERPROCESS_H
#define UNINSTALLERPROCESS_H

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QProcess>
#define UninstallerExeName "ParadoxaDirecta_uninstaller"

class UninstallerProcess : public QProcess {
    Q_OBJECT
public:
    UninstallerProcess();
    void uninstall();
signals:
    void failed();

private:
    bool copyDone = false;
    QString copyTarget;
private slots:
    void on_error();
};

#endif // UNINSTALLERPROCESS_H
