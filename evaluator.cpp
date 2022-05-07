#include "evaluator.h"

evaluator::evaluator()
{
}

void evaluator::SetString(QString dataIn){
    this->in=dataIn;
    this->hasInput=true;
}

void evaluator::Tokenize(){
    this->pTokens.clear();
    QStringList tokens;
    if(this->hasInput){
        for(int i=0; i<this->in.size(); i++){
            if(filter1.contains(this->in[i]) || this->in[i]=='(' || this->in[i]==')'){
                in.insert(i, ' ');
                i++;
                in.insert(i+1, ' ');
                i++;
            }
        }
        for(const auto& tok:qAsConst(funcFilter)){
            int index=-1, j=0;
            index=in.indexOf(tok);
            while(index!=-1){
                j=index+tok.size()+2;
                in.insert(index, ' ');
                in.insert(index+tok.size(), ' ');
                index=in.indexOf(tok, j);
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
    this->out.clear();
    this->operatorStack.clear();
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
                   !operatorStack.top().isLPara())
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
            operatorStack.push(tok);
        }else if(tok.isLPara()){
            operatorStack.push(tok);
        }else if(tok.isRPara()){
            while(operatorStack.top().isLPara()){
                if(operatorStack.isEmpty()){
                    throw "mismatched paranthesis";
                }
                token tok3=operatorStack.pop();
                out.enqueue(tok3);
            }
            //check for mismatched paranthesis
            if(operatorStack.top().isLPara()){
                operatorStack.pop();
            }
            if(operatorStack.top().isFunction()){
                out.enqueue(operatorStack.pop());
            }
        }else if(tok.isFunction()){
            operatorStack.push(tok);
        }
    }
    while(!operatorStack.isEmpty()){
        if(operatorStack.top().isLPara())
            out.enqueue(operatorStack.pop());
        else
            throw "mismatched paranthesis";
    }//check for mismatched paranthesis
    for(token tok:qAsConst(out)){
        qDebug()<<tok.GetString();
    }
}

//Cand din input vine un operator cu prioritate mai mica, se muta toti
//operatorii din stiva de operatori in output
QString evaluator::GetString(){
    return this->in;
}
