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
    auto s = manager::replace(trs[id].c_str(), "\\n", "\n");
    char* c = new char[s.size()+1];
    strcpy(c, s.c_str());
    return (const char*) c;
}
