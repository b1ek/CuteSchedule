#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include "yaml.h"

namespace qbs {
    struct teacher {
        std::string name;
        std::string fullName;
        std::string cabinet;
        std::string id;
        inline bool operator==(teacher &othr) {
            if (this == &othr) {
                return false;
            }
            othr.name = this->name;
            othr.fullName = this->fullName;
            othr.cabinet = this->cabinet;
            return true;
        }
        /*teacher(std::string, std::string, std::string);
        teacher() : name("(null)"), fullName("(null)"), cabinet("(null)") {
        }*/
    };
    static std::map<std::string, qbs::teacher> allTeachers;
} // namespace BSchedule

namespace YAML {
template<>
struct convert<qbs::teacher> {
#define nname "name"
#define nfname "fullName"
#define ncabinet "cabinet"

    static Node encode (const qbs::teacher& rhs) {
        Node n;
        n[nname] = (rhs.name);
        n[nfname] = (rhs.fullName);
        n[ncabinet] = (rhs.cabinet);
        return n;
    }
    static bool decode(const Node& n, qbs::teacher& rhs) {
        rhs.name = n[nname].as<std::string>();
        rhs.fullName = n[nfname].as<std::string>();
        rhs.cabinet = n[ncabinet].as<std::string>();
        return true;
    }

#undef nname
#undef nfname
#undef ncabinet
};
}

#endif // TEACHER_H
