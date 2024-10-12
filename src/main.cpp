#include <QFile>
#include <QMessageBox>
#include "launcher/citiesprocess.h"
#include "main/translatedapplication.h"
#include "settings/settingswindow.h"

int main(int argc, char *argv[]) {
    TranslatedApplication a(argc, argv);

    switch (argc) {
    case 5: {
        qDebug() << "launcher mode";

        // Read the correct config file.
        QDir::setCurrent(a.applicationDirPath());

        CitiesProcess process(argv[4]);
        process.play();
        return a.exec();
    }
    case 2: {
        qDebug() << "uninstaller mode";

        QDir::setCurrent(argv[1]);

        Settings settings;
        QStringList files = {"bootstrapper-v2", "config.ini", settings.getLauncherpathLocation()};
        QListIterator<QString> fileIter(files);
        while (fileIter.hasNext()) {
            const QString filePath = fileIter.next();
            QFile::remove(filePath);
        }

        QMessageBox msgBox(QMessageBox::Information,
                           a.tr("卸载完毕"),
                           a.tr("启动器已卸载完毕。"),
                           QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.exec();
        return a.exec();
    }
    case 1: {
        qDebug() << "settings mode";

        SettingsWindow w;
        w.show();
        return a.exec();
    }
    }
}
