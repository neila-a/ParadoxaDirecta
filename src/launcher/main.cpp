#include "../launcher/citiesprocess.h"
#include "../main/translatedapplication.h"

int main(int argc, char *argv[]) {
    TranslatedApplication a(argc, argv);

    // Read the correct config file.
    QDir::setCurrent(a.applicationDirPath());

    CitiesProcess process(argv[4]);
    process.play();
    return a.exec();
}
