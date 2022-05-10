#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <QDebug>
#include <QString>
#include <QQueue>
#include <QStack>
#include <QtMath>
#include <QMap>

#include "token.h"

class evaluator
{
private:

    QString filter1="-+*^%/!_";
    QStringList funcFilter={"sin","cos","atan","tan","ln","log"};

    QMap<QString, int> priorityDict={{"+", 2},{"-", 2},{"*", 3},{"/", 3},
                                    {"^", 4},{"(", 1},{"_", 3},{"!", 3}};
    QMap<QString, int> assocDict={{"+", 0},{"-", 0},{"*", 0},{"/", 0},
                                  {"^", 1},{"(", 0},{"_", 0},{"!", 0}};

    float result;
    bool tokenized=false, parsed=false, hasInput=false;

    QString in;
    QQueue<token> pTokens;
    QQueue<token> postFix;
    QStack<token> operatorStack;

    int varNr=0;

    void Tokenize();
public:
    evaluator();
    void SetString(QString dataIn);
    void Parse();
    float Evaluate();
    float Evaluate(float value);
    bool isParsed();
    QString GetString();
};

#endif // EVALUATOR_H
