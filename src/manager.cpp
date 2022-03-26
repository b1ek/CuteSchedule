#include "manager.h"

#define array(c, t) (t*) malloc((c) * sizeof(t))

QApplication* manager::a;

void manager::startup() {
    logger::init();
}

void manager::quit(int c) {
    logger::uninit();
}

QApplication *manager::createApp(int argc, char **argv) {
    a = new QApplication(argc, argv);
    return a;
}

uint64_t manager::getNSTime() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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
