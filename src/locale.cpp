#include "locale.h"

QList<QString> locale::trs;

void locale::init() {
    auto tmp = manager::get_file_contents("locale/current.txt");
    auto list = manager::splitstr(tmp, "\n");

    free(tmp);
    free(list);
}
