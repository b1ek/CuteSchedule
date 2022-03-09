#include "config.h"
#include "errors.h"
#include "noGui/console.h"

#include <sstream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <sys/stat.h>
#include <QFile>

#define print(something) std::cout << something << std::endl

inline std::string fred(std::string path) {
    std::ifstream f(path);
    return std::string((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
}

inline bool fexist (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

std::vector<std::string> split (std::string s, std::string delimiter) {
   size_t pos_start = 0, pos_end, delim_len = delimiter.length();
   std::string token;
   std::vector<std::string> res;

   while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
       token = s.substr (pos_start, pos_end - pos_start);
       pos_start = pos_end + delim_len;
       res.push_back (token);
   }

   res.push_back (s.substr (pos_start));
   return res;
}

Config::Config() {
    this->file = YAML::LoadFile("config.yml");
}

void Config::reload() {
    file = YAML::LoadFile("config.yml");
    qbs::allTeachers = loadTeachers();
}

YAML::Node Config::getNode(std::string ofWhat, bool& exists) {
    if (ofWhat == "%root%" || ofWhat == "") {
        exists = true;
        return file;
    }
    auto path = split(ofWhat, "/");
    if (path.size() == 1) {
        #define P file[path[0]]
        if (P.IsDefined()) {
            if (P["external"].IsDefined() && !P["external"].IsMap()) {
                if (P["external"].as<std::string>() == "config.yml") {
                    P["external_error"] = "Cannot import the same file!";
                }
                else if (P["external"].IsSequence()) {
                    std::vector<std::string> pth = P["external"].as<std::vector<std::string>>();
                    std::string f;
                    std::stringstream nex;
                    for (auto p = pth.begin(); p != pth.end(); ++p) {
                        if (fexist(*p)) {
                            f += fred(*p);
                            f += "\n";
                        }
                        nex << *p << ", ";
                    }
                    if (nex.str().size()) {
                        std::stringstream msg("Некоторые файлы указанные в external не существуют: ");
                        msg << nex.str();
                        P["external_error"] = msg.str();
                    }
                    exists = true;
                    return YAML::Load(f);
                }
                if (!fexist(P["external"].as<std::string>())) {
                    std::stringstream msg("Файл ");
                    msg << P["external"].as<std::string>() << " не существует.";
                    P["external_error"] = msg.str();
                    exists = false;
                    return P;
                }
                exists = true;
                return YAML::LoadFile(P["external"].as<std::string>());
            }
            exists = true;
            return P;
        }
        exists = false;
        return YAML::Node();
    } //if size 1
    YAML::Node fst = file[path[0]];

    for (auto i = path.begin() + 1; i != path.end(); ++i) {

        if (fst.IsMap()) {
            if (fst[i->c_str()].IsMap()) {
                if (i->size() >= 1) {
                    fst = fst[i->c_str()];
                }
            } else {
                exists = true;
                return fst[i->c_str()];
            }
        } // if map

    } // for loop
    exists = false;
    return YAML::Node(0);
} // config::getnode

std::string Config::get(std::string what) {
    bool exists;
    auto node = this->getNode(what, exists);
    if (exists && !node.IsMap()) {
        std::stringstream strs;
        strs << node;
        return strs.str();
    }
    return "(null)";
}

bool Config::exists(std::string what) {
    bool exists;
    this->getNode(what, exists);
    return exists;
}

std::map<std::string, qbs::teacher> Config::loadTeachers() {
    bool exists;
    auto tyml = this->getNode("teachers", exists);
    if (exists) {
        return tyml.as<std::map<std::string, qbs::teacher>>();
    }
    exit(NO_TEACHER_SPECIFIED);
}
