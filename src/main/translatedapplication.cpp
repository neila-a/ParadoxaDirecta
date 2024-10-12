#include "translatedapplication.h"
#include <QLocale>
#include <QTranslator>

TranslatedApplication::TranslatedApplication(int argc, char *argv[])
    : QApplication(argc, argv) {
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ParadoxaDirecta_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            installTranslator(&translator);
            break;
        }
    }
}
