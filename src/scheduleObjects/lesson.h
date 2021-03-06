#ifndef LESSON_H
#define LESSON_H

#include <string>
#include "teacher.h"

#define __L_NOT_FOUND__ "NF"

namespace qbs {
    struct lesson {
        std::string name;
        std::string cabinet;
        teacher __teacher;
        static std::map<std::string, lesson> allLessons;
        static lesson Empty() {
            return lesson();
        }
        lesson() {
            name = __L_NOT_FOUND__;
            cabinet = __L_NOT_FOUND__;
            __teacher = qbs::teacher::Empty();
        }
        lesson(std::string id) {
            if (allLessons.count(id)) {
                lesson l = allLessons[id];
                name = l.name;
                __teacher = l.__teacher;
                cabinet = l.cabinet;
            }
            name = std::string("Not found lesson with id ") + id;
            cabinet = "N/A";
            __teacher = qbs::teacher::Empty();
        }
        lesson operator= (std::string id) {
            if (allLessons.count(id)) {
                return allLessons[id];
            }
            return lesson::Empty();
        }
        static lesson find(std::string id) {
            if (allLessons.count(id)) {
                return allLessons[id];
            }
            return lesson::Empty();
        }
    };
}

#define l_namekey "name"
#define l_tchrkey "teacher"
#define l_classkey "cabinet"

namespace YAML {
template<>
struct convert<qbs::lesson> {
    static Node encode(const qbs::lesson& rhs)   {
        Node n;
        n[0] = rhs.name;
        n[1] = rhs.__teacher;
        n[2] = rhs.cabinet;
        return n;
    }
    static bool decode(const Node& n, qbs::lesson& rhs) {        
        if (n.IsScalar()) return false;
        if (n.IsMap()) {
            rhs.name = n[l_namekey].as<std::string>();
            rhs.__teacher = qbs::teacher::find(n[l_tchrkey].as<std::string>());
            rhs.cabinet = n[l_classkey].as<std::string>();
        } else {
            rhs.__teacher = qbs::teacher::find(n[0].as<std::string>());
            rhs.name = n[1].as<std::string>();
            rhs.cabinet = n[2].as<std::string>();
        }
        if (rhs.cabinet == ".") {
            rhs.cabinet = "?";
        }
        return true;
    }
};
}

#undef l_namekey
#undef l_tchrkey
#undef l_classkey

#endif // LESSON_H
