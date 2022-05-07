#ifndef TOKEN_H
#define TOKEN_H

#include <QString>
#include <QStringList>
#include <QDebug>

class token
{
private:
    QString tok;
    QString filter="+-/*%^!";
    QStringList funcFilter={"sin","cos","atan","tan","ln","log"};
    bool op=false, nr=false, func=false, var=false;
public:
    token();
    void SetString(QString in);
    QString GetString();
    bool isOperator();
    bool isNumber();
    bool isFunction();
    bool isVariable();
};

#endif // TOKEN_H
