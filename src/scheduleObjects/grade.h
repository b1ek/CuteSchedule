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
        std::vector<std::vector<std::pair<lesson, std::string>>> schedule;
        inline bool operator== (grade&rhs) {
            if (this == &rhs) return false;
            rhs.name = this->name;
            rhs.cabinet = this->cabinet;
            rhs.tchr = this->tchr;
            rhs.schedule = this->schedule;
        }
    };
}

namespace YAML {
template<>
struct convert<qbs::grade> {
    static Node encode(const qbs::grade rhs) {
        Node n;
        n["name"] = rhs.name;
        n["cabinet"] = rhs.cabinet;
        n["teacher"] = rhs.tchr;
        std::vector<std::vector<std::string>> ids;
        for (auto i = rhs.schedule.begin(); i != rhs.schedule.end(); ++i) {
            std::vector<std::string> l;
             for (auto ii = (*i).begin(); ii != (*i).end(); ++ii) {
                 l.push_back((*ii).second);
             }
             ids.push_back(l);
        }
        n["schedule"] = ids;
        return n;
    }
    static bool decode(const Node& n, qbs::grade& rhs) {
        if (!n.IsMap()) {
            return false;
        }
        rhs.name = n["name"].as<std::string>();
        rhs.cabinet = n["cabinet"].as<std::string>();
        std::string tid = n["teacher"].as<std::string>();

        if (qbs::allTeachers.count(tid)) {
            rhs.tchr = qbs::allTeachers[tid];
        }

        return true;
    }
};
}

#endif // GRADE_H
