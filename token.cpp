#include "token.h"

token::token()
{

}

void token::SetString(QString in){
    bool ok;
    in.toFloat(&ok);
    if(in.contains(this->filter)){
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
    else{
        throw "INVALID INPUT";
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
