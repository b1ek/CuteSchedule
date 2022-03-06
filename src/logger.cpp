#include "logger.h"

void md(const char* filename) {
    if (!QDir(filename).exists()) {
        QDir().mkdir(filename);
    }
}
QFile of(const char* fn) {
    if( access( fn, F_OK ) == 0 ) {
        QFile f(fn);
        if (f.open(QIODevice::WriteOnly | QIODevice::Append)) {
            return f;
        }
        return null;
    } else {
        // file doesn't exist
    }
}

logger::logger() {

}

void logger::init() {
    md("log");

}
