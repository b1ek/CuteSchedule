#include "userutil.h"

UserUtil::UserUtil()
{

}

void UserUtil::showError(QString message)
{
    QMessageBox box;
    box.critical(0, "Error", message);
    // box.setFixedSize(500,200);
    box.show();
}
