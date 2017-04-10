#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Token{
    string name;
    int id;
};

vector <Token> token;
vector <string> word;
void init(){
    token.push_back((Token){"if",1});
    token.push_back((Token){"then",2});
    token.push_back((Token){"else",3});
    token.push_back((Token){"while",4});
    token.push_back((Token){"do",5});
    token.push_back((Token){"+",6});
    token.push_back((Token){"-",7});
    token.push_back((Token){"*",8});
    token.push_back((Token){"/",9});
    token.push_back((Token){">",10});
    token.push_back((Token){"<",11});
    token.push_back((Token){"=",12});
    token.push_back((Token){"(",13});
    token.push_back((Token){")",14});
    token.push_back((Token){";",15});
    token.push_back((Token){"‘",16});
    token.push_back((Token){"==",17});
    token.push_back((Token){">=",18});
    token.push_back((Token){"<=",19});
    token.push_back((Token){"!=",20});
}

int is_symbol(char s){
    if(s=='+'||s=='-'||s=='*'||s=='/'||s=='('||s==')'||s==';'||s=='‘') return 1;
    else if(s=='='||s=='>'||s=='<'||s=='!') return 2;
    else return -1;

}

bool is_number(char c){
    if(c>='0'&&c<='9') return true;
    else return false;

}
void scanner(char *s){
    int len=strlen(s);
    int pos=0;
    while(pos<len){
        while(s[pos]==' '||s[pos]=='\n') pos++;
        char c=s[pos];
        if(isalpha(c)){
            int start=pos;
            while(isalnum(s[pos])) pos++;
            string id;
            char tmp[1000];
            int i;
            for(i=start;i<pos;i++){
                tmp[i-start]=s[i];
            }
            tmp[i-start]='\0';
            id=tmp;
            word.push_back(id);
            continue;
        }else if(is_number(c)){
            int start=pos;
            while(is_number(s[pos])) pos++;
            string num;
            char tmp[1000];
            int i;
            for(i=start;i<pos;i++){
                tmp[i-start]=s[i];
            }
            tmp[i-start]='\0';
            num=tmp;
            word.push_back(num);
            continue;
        }else{
            if(is_symbol(c)==2){
                int next=pos+1;
                char tmp[10];
                string symbol;
                if(next<len&&s[next]=='='){
                    tmp[0]=c;
                    tmp[1]='=';
                    tmp[2]='\0';
                    symbol=tmp;
                    word.push_back(symbol);
                    pos+=2;
                    bool flag=false;
                    while(is_symbol(s[pos])>0){
                        pos++;
                        flag=true;
                    }
                    if(flag) printf("Error:external symbol after %c\n",c);
                }else if(next<len&&is_symbol(s[next])>0){
                    pos++;
                    while(is_symbol(s[pos])>0){
                        pos++;
                    }
                    printf("Error:external symbol after %c\n",c);
                }else{
                    tmp[0]=c;
                    tmp[1]='\0';
                    symbol=tmp;
                    word.push_back(symbol);
                    pos++;
                }
                continue;
            }else if(is_symbol(c)==1){
                string symbol;
                char tmp[10];
                tmp[0]=c;tmp[1]='\0';
                symbol=tmp;
                word.push_back(symbol);
                bool flag=true;
                pos++;
                while(is_symbol(s[pos])>0){
                    flag=false;
                    pos++;
                }
                if(!flag) printf("Error:external symbol after %c\n",c);
                continue;
            }
        }
        pos++;
    }
}

void show(){
    for(int i=0;i<word.size();i++){
        cout<<word[i]<<endl;
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    scanner("if aaa1012+10123+++++12 then");
    show();
    return a.exec();
}

