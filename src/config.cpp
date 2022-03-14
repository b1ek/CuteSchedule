#include "config.h"
#include "logger.h"

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

std::map<std::string, qbs::grade> qbs::grade::allGrades;
std::map<std::string, qbs::teacher> qbs::teacher::allTeachers;
std::map<std::string, qbs::lesson> qbs::lesson::allLessons;
Config::Config() {
    if (fexist("config.yml")) {
        logger::log("No config file found, created a default one");
    }

    this->file = YAML::LoadFile("config.yml");
    bool exists;
    qbs::teacher::allTeachers = this->getNode("teachers", exists)
            .as<std::map<std::string, qbs::teacher>>();
    qbs::lesson::allLessons = this->getNode("lessons", exists)
            .as<std::map<std::string, qbs::lesson>>();
    qbs::grade::allGrades = this->getNode("grades", exists)
            .as<std::map<std::string, qbs::grade>>();

    logger::log("Loaded config");
}

void Config::reload() {
    file = YAML::LoadFile("config.yml");

    bool exists;
    qbs::teacher::allTeachers = this->getNode("teachers", exists)
            .as<std::map<std::string, qbs::teacher>>();
    qbs::lesson::allLessons = this->getNode("lessons", exists)
            .as<std::map<std::string, qbs::lesson>>();
    qbs::grade::allGrades = this->getNode("grades", exists)
            .as<std::map<std::string, qbs::grade>>();

    logger::log("Reloaded config");
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
