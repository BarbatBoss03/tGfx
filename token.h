#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QStringList>

class token
{
private:
    QString tok;
    QString filter="+-/*()%^!";
    QStringList funcFilter={"sin","cos","atan","tan","ln","log"};
    bool op=false, nr=false, func=false;
public:
    token();
    void SetString(QString in);
    QString GetString();
    bool isOperator();
    bool isNumber();
    bool isFunction();
};

#endif // TOKEN_H
