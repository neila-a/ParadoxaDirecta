#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SettingsWindow) {
    ui->setupUi(this);

    processStartCommand();
    processDefaultValues();
    processConnects();

    QString background = settings.getGamepath() + "/LauncherAssets/app-background.png";
    QPixmap pixmap = QPixmap(QDir::toNativeSeparators(background)).scaled(size());
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    setPalette(palette);
}

void SettingsWindow::processConnects() {
    connect(ui->continueGameCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &SettingsWindow::continueGameCheckBox_checkStateChanged);
    connect(ui->disableWorkshopCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &SettingsWindow::disableWorkshopCheckBox_checkStateChanged);
    connect(ui->disableModsCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &SettingsWindow::disableModsCheckBox_checkStateChanged);
    connect(ui->noLogsCheckBox,
            &QCheckBox::checkStateChanged,
            this,
            &SettingsWindow::noLogsCheckBox_checkStateChanged);
}

void SettingsWindow::processDefaultValues() {
    initing = true;

    const autoOrManual autoOrManual = static_cast<enum autoOrManual>(
        settings.value("autoOrManual", 0).toInt());
    ui->autoOrManual->setCurrentIndex(autoOrManual);

    ui->continueGameCheckBox->setChecked(settings.value("continueGame", false).toBool());
    ui->disableWorkshopCheckBox->setChecked(settings.value("disableWorkshop", false).toBool());
    ui->disableModsCheckBox->setChecked(settings.value("disableMods", false).toBool());
    ui->noLogsCheckBox->setChecked(settings.value("noLogs", false).toBool());
    ui->fpsLimitGroupBox->setChecked(settings.value("fpsLimitOpen", false).toBool());

    ui->fpsLimit->setValue(settings.value("fpsLimit", 60).toInt());
    ui->renderEngine->setCurrentIndex(settings.value("renderEngine", 0).toInt());
    ui->launcherPath->setText(settings.getLauncherpathLocation());
    ui->toolBox->setCurrentIndex(0);

    settings.beginGroup("Env");
    ui->envTable->setRowCount(0);
    const QStringList envKeys = settings.allKeys();
    for (int i = 0; i < envKeys.size(); i++) {
        const QString key = envKeys.at(i);
        on_addEnvButton_clicked();
        ui->envTable->setItem(i, 0, new QTableWidgetItem(key));
        ui->envTable->setItem(i, 1, new QTableWidgetItem(settings.value(key).toString()));
    }
    settings.endGroup();

    initing = false;
}

void SettingsWindow::processStartCommand() {
    const autoOrManual autoOrManual = static_cast<enum autoOrManual>(
        ui->autoOrManual->currentIndex());
    if (autoOrManual == autoOrManual::auto_) {
        // Disable edit on auto mode
        ui->startCommand->setDisabled(true);
        ui->startCommand->setText(tr("游戏路径") + Settings::CITIES + " "
                                  + settings.getStartArguments().join(" "));
    } else {
        ui->startCommand->setDisabled(false);
        ui->startCommand->setText(settings.getStartCommand());
    }
}

SettingsWindow::~SettingsWindow() {
    delete ui;
    delete uninstallerProcess;
}
