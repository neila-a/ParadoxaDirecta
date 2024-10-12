#ifndef TRANSLATEDAPPLICATION_H
#define TRANSLATEDAPPLICATION_H

#include <QApplication>

class TranslatedApplication : public QApplication {
public:
    TranslatedApplication(int argc, char *argv[]);
};

#endif // TRANSLATEDAPPLICATION_H
