#include "cutelogger.h"

QFile* CuteLogger::out;
QDateTime CuteLogger::date;
bool CuteLogger::initalized;

void CuteLogger::init() {
    if (initalized) return;
    CuteLogger::out = open();
    CuteLogger::initalized = true;
}

void CuteLogger::uninit() {
    if (!initalized) return;
    CuteLogger::out->close();
    CuteLogger::initalized = false;
}

void CuteLogger::reload() {
    if (CuteLogger::initalized) {
        uninit();
    }
    init();
}

void CuteLogger::info(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[INFO]  ") + date.toString("[hh:mm:ss.zz] ") + msg + '\n');
}

void CuteLogger::warn(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[WARN]  ") + date.toString("[hh:mm:ss.zz] ") + msg + '\n');
}

void CuteLogger::eror(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[ERROR] ") + date.toString("[hh:mm:ss.zz] ") + msg + '\n');
}

void CuteLogger::crit(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[CRIT]  ") + date.toString("[hh:mm:ss.zz] ") + msg + '\n');

}

void CuteLogger::log(QString msg, Code c) {
    switch (c) {
    case Code::Info:
        info(msg);
        break;
    case Code::Warn:
        warn(msg);
        break;
    case Code::Error:
        eror(msg);
        break;
    case Code::Critical:
        crit(msg);
        break;
    }
}

void CuteLogger::write(QString msg) {
    if (!initalized) CuteLogger::init();
    CuteLogger::out->write(msg.toLocal8Bit());
}

QFile *CuteLogger::open() {
    CuteLogger::date = QDateTime::currentDateTime();
    if (!QDir("logs").exists()) {
        QDir().mkdir("logs");
    }
    auto nm = (QString("logs/") + date.toString("yy.MM.dd - hh:mm") + ".log.txt");
    auto f = new QFile(nm);
    if (!f->open(QIODevice::WriteOnly)) {
        f->close();
        return CuteLogger::out;
    }
    if (f->exists()) {
        f->open(f->openMode() | QIODevice::Append);
    }
    return f;
}
