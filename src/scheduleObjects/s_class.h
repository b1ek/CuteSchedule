#ifndef GRADE_H
#define GRADE_H

#include <string>
#include "teacher.h"

namespace qbs {
    struct s_class {
        std::string name;
        teacher _teacher;
    };
}

#endif // GRADE_H
