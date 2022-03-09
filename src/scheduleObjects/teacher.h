#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include "yaml.h"

#define T_EMPTY   0b10000000
#define T_CONSTR  0b01000000
#define T_NODECNV 0b00100000
#define T_SEARCHD 0b00010000

namespace qbs {
    struct teacher {
    private:
        int meta;
    public:
        std::string name;
        std::string fullName;
        std::string cabinet;
        inline bool operator==(teacher &othr) {
            if (this == &othr) {
                return false;
            }
            othr.name = this->name;
            othr.fullName = this->fullName;
            othr.cabinet = this->cabinet;
            return true;
        }
        teacher() {
            meta = T_CONSTR;
        }
        static std::map<std::string, qbs::teacher> allTeachers;
        static teacher Empty() {
            teacher t;
            t.name = "(EMPTY_TEACHER)";
            t.fullName = "(EMPTY_TEACHER)";
            t.cabinet = "69(EMPTY_TEACHER)";
            t.meta = T_EMPTY;
            return t;
        }

        teacher operator= (std::string id) {
            if (allTeachers.count(id)) {
                teacher t = allTeachers[id];
                t.meta |= T_SEARCHD;
                return t;
            }
            return teacher::Empty();
        }
    };

} // namesp. qbs

namespace YAML {
template<>
struct convert<qbs::teacher> {
#define nname "name"
#define nfname "fullName"
#define ncabinet "cabinet"

    static Node encode (const qbs::teacher& rhs) {
        Node n;
        n[0] = rhs.name;
        n[1] = rhs.fullName;
        n[2] = rhs.cabinet;
        return n;
    }
    static bool decode(const Node& n, qbs::teacher& rhs) {
        if (n.IsMap()) {
            rhs.name = n[nname].as<std::string>();
            rhs.fullName = n[nfname].as<std::string>();
            rhs.cabinet = n[ncabinet].as<std::string>();
            return true;
        } else if (n.IsSequence() && n.size() >= 3) {
            rhs.name = n[0].as<std::string>();
            rhs.fullName = n[1].as<std::string>();
            rhs.cabinet = n[2].as<std::string>();
            return true;
        }
        return false;
    }

#undef nname
#undef nfname
#undef ncabinet
};
}

#endif // TEACHER_H
