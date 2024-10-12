#include "citiesprocess.h"

CitiesProcess::CitiesProcess(QString gameDir) {
    connect(this, &QProcess::finished, this, &CitiesProcess::on_finished);
    connect(this, &QProcess::errorOccurred, this, &CitiesProcess::on_error);

    if (!settings.contains("startCommand")) {
        settings.setValue("startCommand", QString(gameDir) + Settings::CITIES);
    }

    setStandardErrorFile("currentStdError.log");
    setStandardOutputFile("currentStdOutput.log");
}

void CitiesProcess::play() {
    setupEnvironment();
    setWorkingDirectory(gameDir);

    // QVariant can't process enum
    const autoOrManual autoOrManual = static_cast<enum autoOrManual>(
        settings.value("autoOrManual", 0).toInt());
    switch (autoOrManual) {
    case autoOrManual::auto_:
        setProgram(gameDir + Settings::CITIES);
        setArguments(settings.getStartArguments());
        start();
        break;
    case autoOrManual::manual:
        const QString command = settings.value("startCommand").toString();
        startCommand(command);
        break;
    }
}

void CitiesProcess::on_error(ProcessError error) {
    settings.writeLauncherpath();
    QMessageBox msgBox(QMessageBox::Critical,
                       tr("城市天际线启动失败"),
                       tr("错误代码（QProcess::ProcessError）：%1").arg(error),
                       QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();
    qApp->exit(error);
}

void CitiesProcess::on_finished(int exitCode) {
    settings.writeLauncherpath();
    qApp->exit(exitCode);
}

void CitiesProcess::setupEnvironment() {
    settings.beginGroup("Env");
    const QStringList envs = settings.allKeys();
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QListIterator<QString> envIter(envs);
    while (envIter.hasNext()) {
        const QString key = envIter.next();
        env.insert(key, settings.value(key).toString());
    }
    settings.endGroup();
    setProcessEnvironment(env);
}
