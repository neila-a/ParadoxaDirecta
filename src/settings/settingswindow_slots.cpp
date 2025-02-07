#include "./ui_settingswindow.h"
#include "settingswindow.h"

#define STEAM_CITIES "steam://rungameid/255710"

void SettingsWindow::on_autoOrManual_currentChanged(int index) {
    settings.setValue("autoOrManual", index);
    processStartCommand();
}

void SettingsWindow::on_startCommand_textEdited(const QString &arg1) {
    settings.setValue("startCommand", arg1);
}

void SettingsWindow::continueGameCheckBox_checkStateChanged(Qt::CheckState value) {
    if (value == Qt::Checked) {
        settings.setValue("continueGame", true);
    } else {
        settings.setValue("continueGame", false);
    }
    processStartCommand();
}

void SettingsWindow::disableWorkshopCheckBox_checkStateChanged(Qt::CheckState value) {
    if (value == Qt::Checked) {
        settings.setValue("disableWorkshop", true);
    } else {
        settings.setValue("disableWorkshop", false);
    }
    processStartCommand();
}

void SettingsWindow::disableModsCheckBox_checkStateChanged(Qt::CheckState value) {
    if (value == Qt::Checked) {
        settings.setValue("disableMods", true);
    } else {
        settings.setValue("disableMods", false);
    }
    processStartCommand();
}

void SettingsWindow::noLogsCheckBox_checkStateChanged(Qt::CheckState value) {
    if (value == Qt::Checked) {
        settings.setValue("noLogs", true);
    } else {
        settings.setValue("noLogs", false);
    }
    processStartCommand();
}

void SettingsWindow::on_fpsLimit_valueChanged(int arg1) {
    settings.setValue("fpsLimit", arg1);
    processStartCommand();
}

void SettingsWindow::on_renderEngine_currentIndexChanged(int index) {
    settings.setValue("renderEngine", index);
    processStartCommand();
}

void SettingsWindow::on_uninstallButton_clicked() {
    const QMessageBox::StandardButton ret = QMessageBox::warning(this,
                                                                 tr("卸载"),
                                                                 tr("确定卸载启动器吗？"),
                                                                 QMessageBox::Yes
                                                                     | QMessageBox::Cancel,
                                                                 QMessageBox::Cancel);

    switch (ret) {
    case QMessageBox::Yes: {
        uninstallerProcess = new UninstallerProcess;
        connect(uninstallerProcess,
                &UninstallerProcess::failed,
                this,
                &SettingsWindow::uninstaller_failed);
        uninstallerProcess->uninstall();
        break;
    }
    default:
        break;
    }
}

void SettingsWindow::uninstaller_failed() {
    QMessageBox msgBox(QMessageBox::Critical,
                       tr("卸载失败"),
                       tr("启动器卸载失败，请手动删除启动器文件或尝试重启电脑。"),
                       QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void SettingsWindow::on_startButton_clicked() {
    settings.writeLauncherpath();
    QProcess process;
    process.setProgram("steam");
    process.setArguments({STEAM_CITIES});
    process.startDetached();
}

void SettingsWindow::on_fpsLimitGroupBox_toggled(bool arg1) {
    settings.setValue("fpsLimitOpen", arg1);
    processStartCommand();
}

void SettingsWindow::on_selectLauncherPath_clicked() {
    const QFileInfo fileInfo(settings.getLauncherpathLocation());
    const QString launcherpath = QFileDialog::getOpenFileName(this,
                                                              tr("选择launcherpath"),
                                                              fileInfo.absolutePath(),
                                                              "launcherpath (launcherpath)");
    settings.setValue("launcherpathLocation", launcherpath);
    ui->launcherPath->setText(launcherpath);
}

void SettingsWindow::on_addEnvButton_clicked() {
    ui->envTable->setRowCount(ui->envTable->rowCount() + 1);
}

void SettingsWindow::on_envTable_itemChanged(QTableWidgetItem *item) {
    if (!initing) {
        const QTableWidgetItem *value = ui->envTable->item(item->row(), 1);
        const QTableWidgetItem *key = ui->envTable->item(item->row(), 0);
        settings.beginGroup("Env");
        switch (item->column()) {
        // key
        case 0:
            settings.setValue(item->text(), value == nullptr ? "" : value->text());
            break;
        // value
        case 1:
            settings.setValue(key == nullptr ? "" : key->text(), item->text());
            break;
        }
        settings.endGroup();
    }
}

void SettingsWindow::on_envTable_itemSelectionChanged() {
    const QList<QTableWidgetItem *> selectedItems = ui->envTable->selectedItems();
    if (selectedItems.length() > 0) {
        ui->deleteEnvButton->setDisabled(false);
    } else {
        ui->deleteEnvButton->setDisabled(true);
    }
}

void SettingsWindow::on_deleteEnvButton_clicked() {
    const int currentRow = ui->envTable->currentRow();
    const QTableWidgetItem *keyItem = ui->envTable->item(currentRow, 0);
    const QString key = keyItem->text();

    settings.beginGroup("Env");
    settings.remove(key);
    settings.endGroup();

    ui->envTable->removeRow(currentRow);
}

bool SettingsWindow::openLogFile(QString fileName) {
    QString logPath = qApp->applicationDirPath() + "/" + fileName;
    return QDesktopServices::openUrl(QUrl("file://" + QDir::fromNativeSeparators(logPath)));
}

void SettingsWindow::on_stdOutputButton_clicked() {
    openLogFile("currentStdOutput.log");
}

void SettingsWindow::on_stdErrorButton_clicked() {
    openLogFile("currentStdError.log");
}
