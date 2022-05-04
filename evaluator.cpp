#include "evaluator.h"

evaluator::evaluator()
{
    parsed=false;
    hasInput=false;
    filter1="-+*^/()";
    filter2.append("sin");
    filter2.append("cos");
    filter2.append("tan");
    filter2.append("ctan");
    filter2.append("lg");
    filter2.append("ln");
    filter2.append("log");
}

void evaluator::SetString(QString dataIn){
    this->in=dataIn;
    this->hasInput=true;
}

void evaluator::Parse(){
    if(this->hasInput){
        tokens=in.split(filter1);
        while(!in.isEmpty()){
            out.enqueue(tokens.first());
            in.remove(in.indexOf(tokens.first()),tokens.first().size());
            tokens.removeFirst();

        }
    }
}

QString evaluator::GetString(){
    return this->in;
}
