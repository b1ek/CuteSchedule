#ifndef GRADE_H
#define GRADE_H

#include "teacher.h"
#include "lesson.h"
#include "../manager.h"
#include "locale.h"

#include <string>

#define __G_NOT_FOUND__ "Invalid ID"

namespace qbs {
    struct grade {
        static std::map<std::string, grade> allGrades;
        std::string name;
        std::string cabinet;
        std::string note;
        teacher tchr;
        std::vector<std::vector<std::pair<lesson, std::string>>> schedule;
        inline bool operator== (grade&rhs) {
            if (this == &rhs) return false;
            rhs.name = this->name;
            rhs.cabinet = this->cabinet;
            rhs.tchr = this->tchr;
            rhs.note = this->note;
            rhs.schedule = this->schedule;
            return true;
        }
        grade() {
            name = __G_NOT_FOUND__;
            cabinet = __G_NOT_FOUND__;
            note = locale::get(35);
            tchr = qbs::teacher::Empty();
        }
        grade(std::string id) {
            if (allGrades.count(id)) {
                grade g = allGrades[id];
                this->name = g.name;
                this->cabinet = g.cabinet;
                this->tchr = g.tchr;
                this->schedule = g.schedule;
                return;
            }
            name = std::string("Not found id ") + id;
            cabinet = std::string("Not found id ") + id;
            note = manager::format(locale::get(35), id.c_str());
            tchr = qbs::teacher::Empty();
        }
        grade operator=(std::string id) {
            if (allGrades.count(id)) {
                return allGrades[id];
            }
            return grade();
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
    } // encode

    static bool decode(const Node& n, qbs::grade& rhs) {
        if (!n.IsMap()) { // fuck things that are not maps
            return false;
        }
        rhs.name = n["name"].as<std::string>();
        rhs.cabinet = n["cabinet"].as<std::string>();
        rhs.tchr = qbs::teacher::find(n["teacher"].as<std::string>());

        auto rawsch = n["schedule"].as<std::vector<std::vector<std::string>>>();
        std::vector<std::vector<std::pair<qbs::lesson, std::string>>> sch;
        sch.reserve(rawsch.size() + 1); // allocate some

        for (auto i = rawsch.begin(); i!=rawsch.end(); ++i) {
            std::vector<std::pair<qbs::lesson, std::string>> l;
            for (auto ii = i->begin(); ii != i->end(); ++ii) {
                auto ll = qbs::lesson::find(*ii);
                if (ll.name == __L_NOT_FOUND__) {
                    ll.name = ll.name + ' ' + *ii; // add id to not found message
                }
                l.push_back(std::pair<qbs::lesson, std::string>(ll, *ii));
            }
            sch.push_back(l);
        }
        rhs.schedule = sch;

        return true;
    } // decode
};
}

#endif // GRADE_H
