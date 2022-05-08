#include<bits/stdc++.h>
using namespace std;
typedef string::const_iterator State;

double expression(State&);
double term(State&);
double factor(State&);
double number(State&);
void error();
void consume(State&,char);

void error(){
    cout<<"error"<<endl;
    exit(0);
}

void consume(State &begin,char expected){
    if(*begin==expected)begin++;
    else error();
}

double expression(State &begin){
    bool minus=false;
    if((*begin)=='-'){
        minus=true;
        begin++;
    }
    double ret=term(begin);
    if(minus)ret*=-1;
    while(1){
        if((*begin)=='+'){
            begin++;
            ret+=term(begin);
        }
        else if((*begin)=='-'){
            begin++;
            ret-=term(begin);
        }
        else break;
    }
    return ret;
}

double term(State &begin){
    double ret=factor(begin);
    while(1){
        if((*begin)=='*'){
            begin++;
            ret*=factor(begin);
        }
        else if((*begin)=='/'){
            begin++;
            double temp=factor(begin);
            if(temp==0)error();
            else{
                ret/=temp;
            }
        }
        else break;
    }
    return ret;
}

double factor(State &begin){
    double ret;
    if((*begin)=='('){
        begin++;
        ret=expression(begin);
        consume(begin,')');
    }
    else ret=number(begin);
    return ret;
}

double number(State &begin){
    if(!isdigit(*begin))error();
    double ret=0;
    while(isdigit(*begin)){
        ret*=10;
        ret+=(*begin)-'0';
        begin++;
    }
    return ret;
}

int main(){
    string formula;
    getline(cin,formula);
    formula.erase(remove(formula.begin(),formula.end(),' '),formula.end());
    State begin=formula.begin();
    double ret=expression(begin);
    if(begin!=formula.end())error();
    cout<<ret<<endl;
}