#include "citiesprocess.h"

CitiesProcess::CitiesProcess(QString gameDir) {
    _gameDir = gameDir;

    connect(this, &QProcess::finished, this, &CitiesProcess::on_finished);
    connect(this, &QProcess::errorOccurred, this, &CitiesProcess::on_error);

    settings.setValue("gamepath", QString(gameDir));

    setStandardErrorFile("currentStdError.log");
    setStandardOutputFile("currentStdOutput.log");
}

void CitiesProcess::play() {
    setupEnvironment();
    setWorkingDirectory(_gameDir);

    // QVariant can't process enum
    const autoOrManual autoOrManual = static_cast<enum autoOrManual>(
        settings.value("autoOrManual", 0).toInt());
    switch (autoOrManual) {
    case autoOrManual::auto_:
        setProgram(_gameDir + Settings::CITIES);
        setArguments(settings.getStartArguments());
        start();
        break;
    case autoOrManual::manual:
        startCommand(settings.getStartCommand());
        break;
    }
}

void CitiesProcess::on_error(ProcessError error) {
    settings.writeLauncherpath();

    QStringList errorInfo;
    errorInfo.append(tr("错误代码（QProcess::ProcessError）: %1").arg(error));
    const autoOrManual autoOrManual = static_cast<enum autoOrManual>(
        settings.value("autoOrManual", 0).toInt());
    errorInfo.append(tr("启动模式（autoOrManual）: %1").arg(autoOrManual));
    switch (autoOrManual) {
    case autoOrManual::auto_:
        errorInfo.append(tr("Program: %1").arg(program()));
        errorInfo.append(tr("Arguments: %1").arg(arguments().join(" ")));
        break;
    }

    QMessageBox msgBox(QMessageBox::Critical,
                       tr("城市天际线启动失败"),
                       errorInfo.join("\n"),
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
