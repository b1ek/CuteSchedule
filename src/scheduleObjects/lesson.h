#ifndef LESSON_H
#define LESSON_H

#include <string>
#include "teacher.h"

namespace qbs {
    struct lesson {
        std::string name;
        teacher __teacher;
    };
    const char* l_namekey = "name";
    const char* l_tchrkey = "teacher";
}

namespace YAML {
template<>
struct convert<qbs::lesson> {
    static Node encode(const qbs::lesson& rhs)   {
        Node n;
        n[0] = rhs.name;
        n[1] = rhs.__teacher;
        return n;
    }
    static bool decode(const Node& n, qbs::lesson& rhs) {
        if (n.IsMap()) {
            rhs.name = n[qbs::l_namekey].as<std::string>();
            rhs.__teacher = n[qbs::l_tchrkey].as<qbs::teacher>();
        }
        return false;
    }
};
}

#endif // LESSON_H
