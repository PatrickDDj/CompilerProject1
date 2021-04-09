//
//  main.cpp
//  Compiler_Porject1
//
//  Created by PatrickDD on 2021/3/29.
//
#include "Defitions.h"

//#include <unistd.h>

map<string, int> KEY_WORDS_MAP;

string code;
int cur = 0;


void init_key_words_map(){
    for(int i=0; i<KEY_WORDS.size(); i++){
        KEY_WORDS_MAP[KEY_WORDS[i]] = i+1;
    }
}

//int check(string key){
//    return KEY_WORDS_MAP[key];
//}

void init_code(string code_path){
    ifstream infile;
    infile.open(code_path);

    stringstream buffer;
    buffer << infile.rdbuf();

    code = buffer.str();
}


bool is_letter(char c){
    return (c >='a' && c<='z');
}

bool is_digit(char c){
    return (c >='0' && c<='9');
}

bool is_hexademical_digit(char c){
    return (c >= '0' && c <='9') || (c>='A' && c <='F');
}

bool is_octal_digit(char c){
    return (c >= '0' && c <= '7');
}


bool is_space(char c){
    return (c=='\n' || c==' ' || c=='\t');
}

bool is_operator(char c){
    return c=='(' || c==')' || c=='[' || c== ']' || c=='{' || c=='}' || c=='.' || c=='#'
    || c=='_' || c==',' || c==';' || c=='"' || c=='\''
    || c=='!' || c=='&' || c=='~' || c=='^' || c=='|'
    || c=='+' || c=='-' || c=='*' || c=='/' || c=='%'
    || c=='>' || c=='<' || c=='=';

}

string check_identifier(int s){
//    int s = cur_r;
    int n = 1;
    while(is_letter(code[s+n]) || is_digit(code[s+n])){
        n++;
    }
    
    cur = s + n;
    return code.substr(s, n);
}

string check_decimal_number(int s){
    int n = 1;
    
    while(is_digit(code[s+n])){
        n++;
    }

    cur = s + n;
    return code.substr(s, n);
}

string check_hexademical_number(int s){
    int n=1;
    
    char x = code[s+n];
    if(x == 'x' || x=='X'){
        n++;
    }
    while(is_hexademical_digit(code[s+n])){
        n++;
    }

    cur = s + n;
    return code.substr(s, n);
}

string check_octal_number(int s){
    int n=1;
    while(is_octal_digit(code[s+n])){
        n++;
    }
    cur = s + n;
    return code.substr(s, n);
}

string check_operator(int s){
    int n=1;
    bool flag = false;
    char c = code[s];
    if(!flag && (c=='(' || c==')' || c=='[' || c== ']' || c=='{' || c=='}' || c=='.' || c=='#'
       || c=='_' || c==',' || c==';' || c=='"' || c=='\'')){
        flag = true;
    }
    if(!flag && (c=='!' || c=='&' || c=='~' || c=='^' || c=='|'
       || c=='+' || c=='-' || c=='*' || c=='/' || c=='%'
       || c=='>' || c=='<' || c=='=')){
        if(code[s+n]=='='){
            n++;
            flag = true;
        }
    }
    if(!flag && (c=='&' || c=='|' || c=='>' || c=='<' || c=='+' || c=='-')){
        if(code[s+n] == code[s]){
            n++;
            flag = true;
        }
    }
    if(!flag && c=='-'){
        if(code[s+n] == '>'){
            n++;
            flag = true;
        }
    }
    cur = s + n;
    return code.substr(s, n);
}

void cout_info(string word, int id){
    cout << "< " << word<<"  "<<id <<" >" << endl;
}


void handle(){
    init_key_words_map();
    
    init_code("p1.txt");
    
    while(cur < code.length()){
        char c = code[cur];
        
        if(is_space(c)){
            cur++;
        }
        
        
        //handle identifier or key word
        else if(is_letter(c)){
            string id = check_identifier(cur);
            int key_id = KEY_WORDS_MAP[id];
            
            //key_id is not 0, Key Word
            if(key_id!=0){
                cout_info(id, key_id);
            }
            
            //key_id is 0, Identifier
            else{
                cout_info(id, KEY_WORDS_MAP["Identifier"]);
            }
        }
        
        
        //handle number (beginning with a digit)
        else if(is_digit(c)){
            char next = code[cur+1];
            
            //decimal number : 123, 0
            if(c!='0' || (c == '0' && !(next == 'x' || next == 'X' || is_octal_digit(next)))){
                string decimal_num = check_decimal_number(cur);
                cout_info(decimal_num, KEY_WORDS_MAP["Decimal_Number"]);
            }
            else{
                //hexademical number : 0xAF, 0X111F
                if(next == 'x' || next == 'X'){
                    string hexademical_num = check_hexademical_number(cur);
                    cout_info(hexademical_num, KEY_WORDS_MAP["Hexademical_Number"]);
                }
                
                //octal number : 012, 077
                else{
                    string octal_num = check_octal_number(cur);
                    cout_info(octal_num, KEY_WORDS_MAP["Octal_Number"]);
                }
            }
        }
        
        
        //handle operator (beginning with <, =, ...)
        else if(is_operator(c)){
            string op = check_operator(cur);
            cout_info(op, KEY_WORDS_MAP[op]);
        }
        
        else{
            cur++;
        }
    }
}

int main(){
    
    handle();

}
