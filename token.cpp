#include "token.h"

token::token()
{

}

void token::SetString(QString in){
    bool ok;
    in.toFloat(&ok);
    if(this->filter.contains(in)){
        this->op=true;
        this->tok=in;
    }
    else if(this->funcFilter.contains(in)){
        this->func=true;
        this->tok=in;
    }
    else if(ok){
        this->nr=true;
        this->tok=in;
    }
    else if(in.size()==1&&in[0].isLetter()){
        this->var=true;
        this->tok=in;
    }
    else{
        //qDebug()<<"INVALID INPUT";
    }
}

QString token::GetString(){
    return this->tok;
}

bool token::isOperator(){
    return this->op;
}

bool token::isNumber(){
    return this->nr;
}

bool token::isFunction(){
    return this->func;
}

bool token::isVariable(){
    return this->var;
}
