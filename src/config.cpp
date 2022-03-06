#include "config.h"
#include "errors.h"
#include "noGui/console.h"

#include <sstream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <sys/stat.h>
#include <QFile>

#define p std::cout
#define n std::endl
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
    YAML::Node fst = file[path[0]];

    for (auto i = path.begin() + 1; i != path.end(); ++i) {

        if (fst.IsMap()) {
            if (fst["external"].IsDefined()) {
                std::string ext = "(null)";
                std::vector<std::string> extv;
                if (fst["external"].IsMap()) {
                    fst.remove("external");
                }
                try {extv = fst["external"].as<std::vector<std::string>>();}
                catch (std::exception) {
                    ext = fst["external"].as<std::string>();
                }

                if (ext == "(null)") {
                    std::string node_txt;
                    for (auto i = extv.begin(); i!= extv.end(); ++i) {
                        if (fexist(*i)) {
                            node_txt.append(fred(*i));
                            node_txt.append("\n");
                        }
                    }
                    fst = YAML::Load(node_txt);
                } else {
                    fst = YAML::LoadFile(ext);
                }
            }
            if (fst[i->c_str()].IsMap()) {
                if (i->size() >= 1) {
                    fst = fst[i->c_str()];
                }
            } else {
                exists = true;
                return fst[i->c_str()];
            }
        }

    }// for
    exists = false;
    return YAML::Node(0);
}


YAML::Node Config::getNode(std::string ofWhat) {
    bool discard;
    return this->getNode(ofWhat, discard);
}

std::string Config::get(std::string what) {
    bool exists;
    auto node = this->getNode(what, exists);
    if (exists) {
        std::stringstream strs;
        strs << node;
        return strs.str();
    } // else {
    return "(null)";
}

bool Config::exists(std::string what) {
    return get(what) != "(null)";
}

std::map<std::string, qbs::teacher> Config::loadTeachers() {
    auto teachersYML = file["teachers"];
    std::map<std::string, qbs::teacher> mp;
    #define external teachersYML["external"]

    if (external.IsDefined() && !external.IsNull() && !external.IsMap()) {
        print("Loading external teachers from " << external.as<std::string>());
    }

    for (auto t = teachersYML.begin(); t != teachersYML.end(); ++t) {
        try {mp.insert({t->first.as<std::string>(), t->second.as<qbs::teacher>()});}
        catch (std::exception) {}
    }
    return mp;
}
