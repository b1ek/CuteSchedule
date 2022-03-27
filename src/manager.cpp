#include "manager.h"

#define array(c, t) (t*) malloc((c) * sizeof(t))

QApplication* manager::a;

void manager::startup() {
    logger::init();
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
}

void manager::quit(int c) {
    logger::uninit();
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
