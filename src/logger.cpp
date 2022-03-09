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

void create_file_if_not_exist(std::string path) {
    std::ofstream outfile;
    outfile.open(path.c_str(), std::ios_base::app);
    outfile.close();
}

std::string blek__getCD() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");

    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string s = converter.to_bytes(std::wstring(buffer).substr(0, pos));
    std::replace (s.begin(), s.end(), '\\', '/');
    return s;
}

#define OPEN_FILE_IN_DEFAULT_APP(path) ShellExecuteA (0, "open", path, 0, 0, SW_SHOW);

Config logger::conf;
bool logger::confRegistered = false;
unsigned char logger::config = L_SINGLESTREAM;
std::ofstream logger::out;
bool logger::stream_opened;

logger::logger() {
    confRegistered = false;
}

void logger::init() {
    // cool stuff: reddit.com/r/cpp/comments/jvdwxp/what_was_the_most_evil_c_code_you_have_seen_in_a/
    if (!confRegistered) {
        md("log");
        #define name ". logger_error.log.txt"
        std::ofstream f;
        f.open("log/" name);
        f << "LOGGER STRUCK AN ERROR! | ОШИБКА ЛОГГЕРА! \n"
             "No config class was registered!\n"
             "Please revert any last updates to the program.\n"
             "If the problem persists, contact the developer.\n"
             "\n"
             "Класс конфигурации не зарегистрирован!\n"
             "Ппожалуйста, откатите предыдущие обновления программы\n"
             "Если проблема все ещё остаётся, свяжитесь с разработчиком.\n"
             "\n"
             "|========Contact developer========|\n"
             "| Email: creeperywime@gmail.com   |\n"
             "| Telegram: @bleki1               |\n"
             "| Discord: blek!#3009             |\n"
             "| Website: blekov.site            |\n"
             "|=================================|\n"
             "\n"
             "For devs:\n"
             "If you were editing my code, please revert your last changes to main.cpp or logger.cpp\\h to make it work."
             "You need to register the config FIRST, and only THEN initialize the logger."
             ;
        f.close();
        Sleep(500);
        OPEN_FILE_IN_DEFAULT_APP((blek__getCD() + "\\log\\" name).c_str());
#undef name
        exit(NO_CONFIG_REGISTERED);
    }
    md(conf.get("config/logpath").c_str());
}


std::string getDate(std::string format) {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream s;
    s.clear();
    s.str("");
    s << std::put_time(&tm, format.c_str());
    return s.str();
}

std::string getFolderDate() {
    return getDate("%d %b %Y");
}

std::string getFileDate() {
    return getDate("[%d.%b.%Y %I-00 %p]");
}

std::string getLogDate() {
    return getDate("[%H:%M.%S]");
}

std::ofstream logger::open_stream() {
#ifndef LOGGER_DISABLED
    md((std::string("log/") + getFolderDate()).c_str());

    std::string p = blek__getCD() + "/log/" + getFolderDate() + "/" + getFileDate() + "-ScheduleLog.txt";
    create_file_if_not_exist(p);

    std::ofstream f;
    f.open(p);
    return f;
#else
    return std::ofstream()
#endif
}

void logger::write(std::string message) {
#ifndef LOGGER_DISABLED
    if ((logger::config & L_SINGLESTREAM) == L_SINGLESTREAM) {
        if (!logger::stream_opened) {
            logger::out = logger::open_stream();
        }
        logger::out << message;
        return;
    }
    auto f = logger::open_stream();
    f << message;
    f.close();
#endif
}

void logger::regConfig(Config c) {
    conf = c;
    confRegistered = true;
}

void logger::log(std::string message, char code) {
#ifndef LOGGER_DISABLED
    if (code == L_INF) {
        logger::write(std::string("[INFO] ") + getLogDate() + ": " + message + "\n");
        return;
    }
    if (code == L_WRN) {
        logger::write(std::string("[WARN] ") + getLogDate() + ": " + message + "\n");
        return;
    }
    if (code == L_ERR) {
        logger::write(std::string("[EROR] ") + getLogDate() + ": " + message + "\n");
        return;
    }
    if (code == L_CRT) {
        logger::write(std::string("[CERR] ") + getLogDate() + ": " + message + "\nThe program will shut down after the critical error.\n");
        return;
    }
    logger::write(std::string("[INFO] ") + getLogDate() + ": " + message + "\n");
    return;
#endif
}

void logger::configure(unsigned char _config, bool overrideExistant) {
    Sleep(5); // to make it look like the function is HUGE
    if (!overrideExistant) {
        logger::config |= _config;
        return;
    }
    logger::config = _config;
}
