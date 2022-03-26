#include "logger.h"

static std::string defFolder = "log";

std::ofstream logger::out;
bool logger::initalized;

void logger::md(std::string path) {
    std::replace (path.begin(), path.end(), '\\', '/');
    if (QDir(path.c_str()).exists()) return;
    QDir().mkdir(path.c_str());
}

//         getCD
//           ↓
std::string gcd() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string s = converter.to_bytes(std::wstring(buffer).substr(0, pos));
    std::replace (s.begin(), s.end(), '\\', '/');
    return s;
}

std::string logger::getDate(std::string f) {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream s("");
    s << std::put_time(&tm, f.c_str());
    return s.str();
}

void logger::init() {
    if (initalized) return;
    auto dir = gcd() + '/' + defFolder + '/' + getDate(L_DIR_DATE_F);
    md(dir.c_str());
    out = std::ofstream(gcd() + '/' + dir + '/' + getDate(L_FILE_DATE_F) + ".txt.log");

    initalized = true;
}

void logger::write(std::string msg) {
    if (initalized) out << msg;
}

void logger::log(std::string msg, int level) {
    if (!initalized) return;
    switch (level) {
        case L_INF:
            logger::write(getDate(L_LOG_DATE_F) + "-[INFO]: " + msg);
            break;
        case L_WRN:
            logger::write(getDate(L_LOG_DATE_F) + "-[WARN]: " + msg);
            break;
        case L_ERR:
            logger::write(getDate(L_LOG_DATE_F) + "-[EROR]: " + msg);
            break;
        case L_CRT:
            logger::write(getDate(L_LOG_DATE_F) + "-[CERR]: " + msg);
            break;
    }
}

void logger::uninit() {
    if (initalized) return;
    out.close();
    initalized = false;
}
