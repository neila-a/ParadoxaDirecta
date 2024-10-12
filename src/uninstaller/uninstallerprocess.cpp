#include "uninstallerprocess.h"

UninstallerProcess::UninstallerProcess() {
    copyTarget = QDir::toNativeSeparators(QDir::tempPath() + "/" + UninstallerExeName);
    copyDone = QFile::copy(qApp->applicationFilePath(), copyTarget);
}

void UninstallerProcess::uninstall() {
    if (copyDone) {
        setProgram(copyTarget);
        setArguments({qApp->applicationDirPath()});
        startDetached();
        connect(this, &QProcess::errorOccurred, this, &UninstallerProcess::on_error);
        qApp->quit();
    } else {
        emit failed();
    }
}

void UninstallerProcess::on_error() {
    emit failed();
}
