#ifndef USERUTIL_H
#define USERUTIL_H

#include <QObject>
#include <QString>

#include <QMessageBox>

class UserUtil : public QObject
{
    Q_OBJECT
public:
    UserUtil();

    static void showError(QString message);
};

#endif // USERUTIL_H
