#include<bits/stdc++.h>
using namespace std;
typedef string::const_iterator State;

double expression(State &begin);
double number(State &begin);
void error();

void error(){
    cout<<"error"<<endl;
    exit(0);
}

double expression(State &begin){
    bool minus=false;
    if((*begin)=='-'){
        minus=true;
        begin++;
    }
    double ret=number(begin);
    if(minus)ret*=-1;
    while(1){
        if((*begin)=='+'){
            begin++;
            ret+=number(begin);
        }
        else if((*begin)=='-'){
            begin++;
            ret-=number(begin);
        }
        else break;
    }
    return ret;
}

double number(State &begin){
    auto isNumber=[](State begin){return (0<=(*begin)-'0')&&((*begin)-'0'<=9);};
    if(!isNumber(begin))error();
    double ret=0;
    while(isNumber(begin)){
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