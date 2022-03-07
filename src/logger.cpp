#include "logger.h"

void md(const char* filename) {
    if (!QDir(filename).exists()) {
        QDir().mkdir(filename);
    }
}
bool af(const char* fn) {
    if( access( fn, F_OK ) == 0 ) {
        QFile f(fn);
        if (f.open(QIODevice::ReadWrite | QIODevice::Append)) {
            return true;
        }
        return false;
    } else {
        return true;
    }
}

logger::logger() {

}

void logger::init() {
}

void logger::regConfig(Config c) {
}
