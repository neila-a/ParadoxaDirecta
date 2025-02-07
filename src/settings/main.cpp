#include "../main/translatedapplication.h"
#include "../settings/settingswindow.h"

int main(int argc, char *argv[]) {
    TranslatedApplication a(argc, argv);

    SettingsWindow w;
    w.show();
    return a.exec();
}
