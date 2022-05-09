#include "evaluator.h"

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

float evalMinus(float arg1){
    return -arg1;
}

evaluator::evaluator()
{
}

void evaluator::SetString(QString dataIn){
    this->in=dataIn;

    this->parsed=false;
    this->tokenized=false;
    this->varNr=0;

    if(dataIn.size()>0) this->hasInput=true;
    else this->hasInput=false;
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
        qDebug()<<in;
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
        throw std::runtime_error("NO INPUT");
    }
}

void evaluator::Parse(){
    this->postFix.clear();
    this->operatorStack.clear();
    this->Tokenize();

    QString lastVar="";

    while(!pTokens.isEmpty()){
        token tok=pTokens.dequeue();
        if(tok.isNumber()){
            postFix.enqueue(tok);
        }else if(tok.isVariable()){
            postFix.enqueue(tok);
            if(tok.GetString()!=lastVar){
                varNr++;
                lastVar=tok.GetString();
            }
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
                postFix.enqueue(tok2);
            }
            operatorStack.push(tok);
        }else if(tok.isLPara()){
            operatorStack.push(tok);
        }else if(tok.isRPara()){
            while(!operatorStack.top().isLPara()){
                if(operatorStack.isEmpty()){
                    throw std::runtime_error("mismatched paranthesis");
                }
                token tok3=operatorStack.pop();
                postFix.enqueue(tok3);
            }
            //check for mismatched paranthesis
            if(operatorStack.top().isLPara()){
                operatorStack.pop();
            }
            //if(operatorStack.top().isFunction()){
            //    postFix.enqueue(operatorStack.pop());
            //}
        }else if(tok.isFunction()){
            operatorStack.push(tok);
        }

    }

    for(token tok:qAsConst(operatorStack)){
        qDebug()<<tok.GetString();
    }

    while(!operatorStack.isEmpty()){
        if(!operatorStack.top().isLPara())
            postFix.enqueue(operatorStack.pop());
        else
            throw std::runtime_error("mismatched paranthesis");
    }//check for mismatched paranthesis

    parsed=true;
}

float evaluator::Evaluate(){
    QStack<token> resultStack;

    if(!parsed){
        this->Parse();
    }

    QQueue<token> cpy=postFix;

    if(varNr==0){
        while(!cpy.isEmpty()){
            token tok = cpy.dequeue();
            if(tok.isNumber()){
                resultStack.push(tok);
            }
            else if(tok.isOperator()){
                if(tok.GetString()=="!"){
                    token o1=resultStack.pop(), res; //operand 1, result
                    res.SetString(QString::number(evalFact(o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="_"){
                    token o1=resultStack.pop(), res; //operand 1, result
                    res.SetString(QString::number(evalMinus(o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="+"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalAdd(o1.GetString().toFloat(), o2.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="-"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalSub(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="/"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalDiv(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="*"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalMul(o1.GetString().toFloat(), o2.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="^"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalPow(o1.GetString().toFloat(), o2.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="%"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalMod(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
            }
            else{
                throw std::runtime_error("Not a valid expression");
            }
        }
    }
    qDebug()<<resultStack.top().GetString().toFloat();
    return resultStack.top().GetString().toFloat();
}

float evaluator::Evaluate(float value){
    QStack<token> resultStack;

    if(!parsed){
        this->Parse();
    }

    QQueue<token> cpy=postFix;

    if(varNr==1){
        while(!cpy.isEmpty()){
            token tok = cpy.dequeue();
            if(tok.isNumber()){
                resultStack.push(tok);
            }
            else if(tok.isVariable()){
                tok.SetString(QString::number(value));
                resultStack.push(tok);
            }
            else if(tok.isOperator()){
                if(tok.GetString()=="!"){
                    token o1=resultStack.pop(), res; //operand 1, result
                    res.SetString(QString::number(evalFact(o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="_"){
                    token o1=resultStack.pop(), res; //operand 1, result
                    res.SetString(QString::number(evalMinus(o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="+"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalAdd(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="-"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalSub(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="/"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalDiv(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="*"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalMul(o1.GetString().toFloat(), o2.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="^"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalPow(o1.GetString().toFloat(), o2.GetString().toFloat())));
                    resultStack.push(res);
                }
                else if(tok.GetString()=="%"){
                    token o1=resultStack.pop(), o2=resultStack.pop(), res;
                    res.SetString(QString::number(evalMod(o2.GetString().toFloat(), o1.GetString().toFloat())));
                    resultStack.push(res);
                }
            }
            else{
                throw std::runtime_error("Not a valid expression");
            }
        }
    }
    qDebug()<<resultStack.top().GetString().toFloat();
    return resultStack.top().GetString().toFloat();
}

//Cand din input vine un operator cu prioritate mai mica, se muta toti
//operatorii din stiva de operatori in postFixput
QString evaluator::GetString(){
    return this->in;
}
