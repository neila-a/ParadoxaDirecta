#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QTableWidgetItem>
#include "../main/consts.h"
#include "../main/settings.h"
#include "../uninstaller/uninstallerprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SettingsWindow;
}
QT_END_NAMESPACE

class SettingsWindow : public QMainWindow {
    Q_OBJECT

public:
    SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void on_autoOrManual_currentChanged(int index);
    void on_startCommand_textEdited(const QString &arg1);
    void continueGameCheckBox_checkStateChanged(int value);
    void disableWorkshopCheckBox_checkStateChanged(int value);
    void disableModsCheckBox_checkStateChanged(int value);
    void noLogsCheckBox_checkStateChanged(int value);
    void on_fpsLimit_valueChanged(int arg1);
    void on_renderEngine_currentIndexChanged(int index);
    void on_uninstallButton_clicked();
    void on_startButton_clicked();
    void on_fpsLimitGroupBox_toggled(bool arg1);
    void on_selectLauncherPath_clicked();
    void on_addEnvButton_clicked();
    void on_envTable_itemChanged(QTableWidgetItem *item);
    void on_envTable_itemSelectionChanged();
    void on_deleteEnvButton_clicked();

    void uninstaller_failed();

    void on_stdOutputButton_clicked();

    void on_stdErrorButton_clicked();

private:
    Ui::SettingsWindow *ui;
    Settings settings;

    bool initing = false;
    UninstallerProcess *uninstallerProcess = nullptr;
    bool openLogFile(QString fileName);
    void processStartCommand();
    void processDefaultValues();
    // Because unknown reasons, the qt.core.qmetaobject.connectslotsbyname method is broken here (QCheckBox class)
    void processConnects();
};
#endif // SETTINGSWINDOW_H
