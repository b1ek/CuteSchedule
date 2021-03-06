#include "cutelogger.h"

QFile *CuteLogger::out;
QDateTime CuteLogger::date;
bool CuteLogger::initalized;

// TODO:
//  do the logger

void CuteLogger::init() {
    if (initalized) return;
    open();

    CuteLogger::initalized = true;
}

void CuteLogger::uninit() {
    if (!initalized) return;
    out->close();

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
    CuteLogger::write(QString("[INFO]  ") +
                      date.toString("[hh:mm:ss.zz] ") +
                      msg + '\n');
}

void CuteLogger::warn(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[WARN]  ") +
                      date.toString("[hh:mm:ss.zz] ") +
                      msg + '\n');
}

void CuteLogger::eror(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[ERROR] ") +
                      date.toString("[hh:mm:ss.zz] ") +
                      msg + '\n');
}

void CuteLogger::crit(QString msg) {
    CuteLogger::date = QDateTime::currentDateTime();
    CuteLogger::write(QString("[CRIT]  ") +
                      date.toString("[hh:mm:ss.zz] ") +
                      msg + '\n');

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
    QTextStream st(out);
    st << msg;
}

void CuteLogger::open() {
    if (initalized) return;
    CuteLogger::date = QDateTime::currentDateTime();
    if (!QDir("logs").exists()) {
        QDir().mkdir("logs");
    }
    QString lp = "logs";
    Config c;
    if (c.get("config/logpath") != "(null)") {
        lp = c.get("config/logpath").c_str();
    }

    auto nm = (lp + "/log_" + manager::getDate("%Y_%m_%d__%H_%M").c_str() + ".log.txt");
    out = new QFile(nm);

    if (out->error()) {
        goto err;
    }

    if (out->open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream a(out);
        a << AY_OBFUSCATE("CuteSchedule ver. " VERSION " " VERCODE " by blek!\n"
        "CuteLogger ver. " CUTELOG_V "\n"
        "\n"
        "This program is free software and released under GNU GPLv3 license.\n"
        "If you bought this program, you have all rights to demand a refund.\n"
        "Official website: cute.blek.codes\n\n");

        return;
    }
    return;
    err:
    QMessageBox::critical(nullptr, "Error", QString("Could not open file ") + nm + ": " + out->errorString());
    manager::quit(CANT_OPEN_LOG_FILE);
    return;
}
