#include "locale.h"

std::vector<std::string> locale::trs;

void locale::init() {
    //auto tmp = manager::get_file_lines("locale/current.txt");
    trs = manager::get_file_lines("locale/current.txt");
}

void locale::uninit() {}

const char* locale::get(size_t id) {
    id -= 1;
    if (id > trs.size()) {
        return "(null)";
    }
    return trs[id].c_str();
}
