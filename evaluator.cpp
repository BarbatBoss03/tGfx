#include "evaluator.h"

evaluator::evaluator()
{
}

void evaluator::SetString(QString dataIn){
    this->in=dataIn;
    this->hasInput=true;
}

void evaluator::Tokenize(){
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
            if(tok!=""){
                token t;
                t.SetString(tok);
                pTokens.enqueue(t);
            }
        }
        hasInput=false;
        tokenized=true;
    }
    else
    {
        //throw "NO INPUT";
    }
}

void evaluator::Parse(){
    this->Tokenize();
    while(!pTokens.isEmpty()){
        token tok=pTokens.dequeue();
        if(tok.isNumber()){
            out.enqueue(tok);
        }else if(tok.isVariable()){
            out.enqueue(tok);
        }else if(tok.isOperator()){
            while((!operatorStack.isEmpty()
                   &&
                   operatorStack.top().GetString()!="(")
                  &&
                  ( (priorityDict[tok.GetString()]<
                    priorityDict[operatorStack.top().GetString()])
                    ||
                    (priorityDict[tok.GetString()]==
                     priorityDict[operatorStack.top().GetString()]
                     &&
                     assocDict[tok.GetString()]==0
                    )
                    )
                  )
            {
                token tok2=operatorStack.pop();
                out.enqueue(tok2);
            }
            this->operatorStack.push(tok);
        }else if(tok.GetString()=="("){

        }else if(tok.GetString()==")"){

        }else if(tok.isFunction()){
            qDebug()<<"FUNCTIONS NOT IMPLEMENTED";
        }
    }
}

//Cand din input vine un operator cu prioritate mai mica, se muta toti
//operatorii din stiva de operatori in output
QString evaluator::GetString(){
    return this->in;
}
