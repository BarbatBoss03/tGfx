#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <QDebug>
#include <QString>
#include <QQueue>
#include <QStack>
#include <QtMath>

float evalAdd(float arg1, float arg2){
    return arg1+arg2;
}

float evalSub(float arg1, float arg2){
    return arg1-arg2;
}

float evalMul(float arg1, float arg2){
    return arg1*arg2;
}

float evalDiv(float arg1, float arg2){
    if(arg2==0){
        throw "DIVIDE BY ZERO";
    }
    return arg1/arg2;
}

int evalMod(int arg1, int arg2){
    if(arg2==0){
        throw "DIVIDE BY ZERO";
    }
    return arg1%arg2;
}

float evalPow(float arg1, float arg2){
    return qPow(arg1, arg2);
}

int evalFact(int arg1){
    if (arg1<=0){
        throw "UNSUPPORTED OPERATION";
    }
    int result=1;
    for(int i=1; i<=arg1; i++){
        result=result*i;
    }
    return result;
}

int evalMinus(int arg1){
    return -arg1;
}

class evaluator
{
private:
    QString in;
    QString filter1;
    QStringList tokens, filter2;
    float result;
    bool parsed=false, hasInput=false;
    QQueue<QString> out;
    QStack<QString> operators;
public:
    evaluator();
    void SetString(QString dataIn);
    void Parse();
    bool isParsed();
    QString GetString();
};

#endif // EVALUATOR_H
