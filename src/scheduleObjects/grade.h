#ifndef GRADE_H
#define GRADE_H

#include "teacher.h"
#include "lesson.h"
#include <string>

namespace qbs {
    struct grade {
        std::string name;
        std::string cabinet;
        teacher tchr;
        std::vector<std::vector<lesson>> schedule;
    };
}

namespace YAML {
template<> struct convert<qbs::grade> {
    static Node encode(const qbs::grade rhs) {
        Node n;
        n["name"] = rhs.name;
        n["cabinet"] = rhs.cabinet;
        n["teacher"] = rhs.tchr;
        return n;
    }
};
}

#endif // GRADE_H
