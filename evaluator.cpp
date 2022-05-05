#include "evaluator.h"

evaluator::evaluator()
{
}

void evaluator::SetString(QString dataIn){
    this->in=dataIn;
    this->hasInput=true;
}

void evaluator::Tokenize(){
    token t;
    QStringList tokens;
    if(this->hasInput){
        for(int i=0; i<this->in.size(); i++){
            if(filter1.contains(this->in[i])){
                in.insert(i, ' ');
                i++;
                in.insert(i+1, ' ');
                i++;
            }
        }
        tokens=in.split(' ');
        for(const auto& tok:qAsConst(tokens)){
            t.SetString(tok);
            pTokens.enqueue(t);
        }
        hasInput=false;
        tokenized=true;
    }
    else
    {
        throw "NO INPUT";
    }
}

void evaluator::Parse(){
    this->Tokenize();
}

//Cand din input vine un operator cu prioritate mai mica, se muta toti
//operatorii din stiva de operatori in output
QString evaluator::GetString(){
    return this->in;
}
