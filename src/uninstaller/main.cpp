#include <QFile>
#include <QMessageBox>
#include "../main/settings.h"
#include "../main/translatedapplication.h"

int main(int argc, char *argv[]) {
    TranslatedApplication a(argc, argv);

    QDir::setCurrent(argv[1]);

    Settings settings;
    QStringList files = {"bootstrapper-v2",
                         "uninstaller",
                         "settings",
                         "config.ini",
                         settings.getLauncherpathLocation()};
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
