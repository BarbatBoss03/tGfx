#include "token.h"

token::token()
{

}

void token::SetString(QString in){
    this->op=false; this->nr=false; this->func=false; this->var=false;
    this->lParanthesis=false; this->rParanthesis=false;
    bool ok;
    in.toFloat(&ok);
    if(this->filter.contains(in)){
        this->op=true;
        this->tok=in;
    }
    else if(in=="("){
        this->lParanthesis=true;
        this->tok=in;
    }
    else if(in==")"){
        this->rParanthesis=true;
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
        throw std::runtime_error("INVALID INPUT");
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

bool token::isLPara(){
    return this->lParanthesis;
}

bool token::isRPara(){
    return this->rParanthesis;
}
