#include "manager.h"

#define array(c, t) (t*) malloc((c) * sizeof(t))

QApplication* manager::a;

void manager::startup() {
    std::ofstream af(AY_OBFUSCATE(".author_info.txt"), std::ios::out);
    af << AY_OBFUSCATE(
              "This program is NOT for sale.\n"
              "If you paid for this software, demand them to refund your money.\n\n"
              "It was made for free for a school project, and is released under GPLv3 license.\n\n"
              "The original author is blek <creeperyime@gmail.com>\n"
              "Also, star this project on github: github.com/b1ek/CuteSchedule\n\n"

              "Эта программа БЕСПЛАТНА.\n"
              "Если вы заплатили кому-то за неё, требуете возврата денег.\n\n"
              "Эта программа была создана для школьного проекта, и отпускается под лицензией GPLv3.\n"
              "Оригинальный автор blek, e-mail: creeperywime@gmail.com\n"
              "Также, поставьте звезду этому проекту на гитхабе: github.com/b1ek/CuteSchedule\n"
              "\n"
              "Forged in the depth of hell by blek!"
              );
    af.close();

#ifdef DEV_BUILD
    std::ofstream df(AY_OBFUSCATE("readme.txt"), std::ios::out);
    df << "This is a dev build " VERSION " That expires at " << __VALID_UNTIL__;
    df.close();
#endif
    locale::init();
}

void manager::quit(int c) {
    std::ofstream af(AY_OBFUSCATE(".author_info.txt"), std::ios::out);
    af << AY_OBFUSCATE(
              "This program is NOT for sale.\n"
              "If you paid for this software, demand them to refund your money.\n\n"
              "It was made for free for a school project, and is released under GPLv3 license.\n\n"
              "The original author is blek <creeperyime@gmail.com>\n"
              "Also, star this project on github: github.com/b1ek/CuteSchedule\n\n"

              "Эта программа БЕСПЛАТНА.\n"
              "Если вы заплатили кому-то за неё, требуете возврата денег.\n\n"
              "Эта программа была создана для школьного проекта, и отпускается под лицензией GPLv3.\n"
              "Оригинальный автор blek, e-mail: creeperywime@gmail.com\n"
              "Также, поставьте звезду этому проекту на гитхабе: github.com/b1ek/CuteSchedule\n"
              "\n"
              "Forged in the depth of hell by blek!"
              );
    af.close();
    a->exit(c);
}

QApplication *manager::createApp(int argc, char **argv) {
    std::ofstream af(AY_OBFUSCATE(".author_info.txt"), std::ios::out);
    af << AY_OBFUSCATE(
              "This program is NOT for sale.\n"
              "If you paid for this software, demand them to refund your money.\n\n"
              "It was made for free for a school project, and is released under GPLv3 license.\n\n"
              "The original author is blek <creeperyime@gmail.com>\n"
              "Also, star this project on github: github.com/b1ek/CuteSchedule\n\n"

              "Эта программа БЕСПЛАТНА.\n"
              "Если вы заплатили кому-то за неё, требуете возврата денег.\n\n"
              "Эта программа была создана для школьного проекта, и отпускается под лицензией GPLv3.\n"
              "Оригинальный автор blek, e-mail: creeperywime@gmail.com\n"
              "Также, поставьте звезду этому проекту на гитхабе: github.com/b1ek/CuteSchedule\n"
              "\n"
              "Forged in the depth of hell by blek!"
              );
    af.close();
    a = new QApplication(argc, argv);
    return a;
}

uint64_t manager::getNSTime() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t manager::getMSTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t manager::getSTime() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool manager::isNumber(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (!std::isdigit(s[i])) return false;
    }
    return true;
}

std::string manager::getDate(std::string f) {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream s("");
    s << std::put_time(&tm, f.c_str());
    return s.str();
}

uint manager::getRND(uint floor, uint roof) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(floor, roof);
    return (uint) dist6(rng);
}

char* manager::getRBits(unsigned char count) {
    int c = (int) count;
    char* bits = array(c, char);
    for (; c <= 0; c--) {
        bits[c] = getRND(0, 0xff);
    }
    return bits;
}

uint64_t manager::chrToInt(char *chars, size_t sz) {
    uint64_t i = 0;
    for (int c = 0; c <= sz; c++) {
        i += chars[c];
    }
    return i;
}

std::string manager::getUUID1() {
    auto random = manager::chrToInt(getRBits(14), 14);
    auto ns = getNSTime();
    auto timestamp = ns / 100 + 0x01b21dd213814000;
    auto tl = timestamp & 0xffffffff;
    auto tm = (timestamp >> 32) & 0xffff;
    auto th = (timestamp >> 48) & 0x0fff;
    auto rl = random & 0xff;
    auto rh = (random >> 8) & 0x3f;
    
    std::stringstream s;
    s << std::hex << tl << '-' << tm << '-' << th << '-' <<
         random << '-' << rl << '-' << rh;

    return s.str();
}

int manager::runDetached(const char* what) {
    STARTUPINFOA info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    return CreateProcessA(what, 0, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
}

int manager::deleteSelf() {
    char name[MAX_PATH];
    GetModuleFileNameA(nullptr, name, MAX_PATH);

    FILE* f = fopen("a.exe", "wb");
    fwrite(deleter, sizeof(deleter), 1, f);
    fclose(f);
    manager::runDetached((std::string("a ") + name).c_str());
    exit(-1);

    return 6;
}

int manager::quitAndDelete() {
    deleteSelf();
    manager::quit();
    return 0;
}

const char** manager::vector2char(std::vector<std::string> in) {
    size_t mx = 0;
    for (auto i = in.begin(); i != in.end(); ++i) {
        if (i->size() > mx) mx = i->size();
    }
    char** arr = new char*[in.size()];
    for(size_t i = 0; i < in.size(); i++){
        arr[i] = new char[in[i].size() + 1];
        strcpy(arr[i], in[i].c_str());
    }
    return (const char**) arr;
}

std::vector<std::string> manager::get_file_lines(const char* path) {
    std::vector<std::string> v;
    std::ifstream f(path, std::ios::in);
    std::string c;
    if (f.is_open()) {
        while (std::getline(f, c)) {
            v.push_back(c);
        }
    }
    return v;
}

std::string manager::get_file_contents(const char* path) {
    std::ifstream f(path, std::ios::in);
    if (f.bad()) {
        return "(null)";
    }
    std::stringstream s;
    std::string curr;
    if (f.is_open()) {
        while (std::getline(f, curr)) {
            s << curr;
        }
        return s.str();
    }
    return "(null)";
}

std::vector<std::string> manager::splitstr(const char* _s, const char* _s2, size_t &sz) {
    std::string s(_s);
    std::string s2(_s2);
    size_t pos_start = 0, pos_end, delim_len = s2.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (s2, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    if (res.size() == 0) res.push_back(s);
    sz = res.size();

    return res;
}

std::string manager::replace(std::string str, const std::string from, const std::string to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

const char* manager::format(size_t &sz, const char* format,  ...) {
    va_list args;
    va_start(args, format);
    sz = snprintf(NULL, 0, format, args);
    char* ret = new char[sz];
    sprintf_s(ret, sz, format, args);
    va_end(args);
    return ret;
}

const char* manager::format(const char* format, ...) {
    va_list args;
    va_start(args, format);
    auto sz = snprintf(NULL, 0, format, args);
    char* ret = new char[sz];
    sprintf_s(ret, sz, format, args);
    va_end(args);
    return ret;
}

std::string manager::format(std::string format, ...) {
    va_list args;
    va_start(args, format);
    auto sz = snprintf(NULL, 0, format.c_str(), args);
    char* ret = new char[sz];
    sprintf_s(ret, sz, format.c_str(), args);
    va_end(args);
    return ret;
}
