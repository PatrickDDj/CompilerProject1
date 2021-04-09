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

int row_count = 1;
// int word_count = 0;

vector<pair<string, int> > lex_result;

map<string, int> word_type_count;


void init_key_words_map(){
    for(int i=0; i<KEY_WORDS.size(); i++){
        KEY_WORDS_MAP[KEY_WORDS[i]] = i+1;
    }
}


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
    return (c >= '0' && c <='9') || (c>='A' && c <='F') || (c>='a' && c <='f');
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
    int n = 1;
    
    //for checking "else if"
    if(code.substr(s, 7) == "else if"){
        n = 7;
    }
    
    else{
        while(is_letter(code[s+n]) || is_digit(code[s+n])){
            n++;
        }
    }
    cur = s + n;
    
    return code.substr(s, n);
}


string check_decimal_number(int s){
    int n = 1;
    
    while(is_digit(code[s+n])){
        n++;
    }
    
    //unqualified identifier like '3aa'
    if(is_letter(code[s+n])){
        printf("[ERROR] unqualified identifier at row [%d]\n", row_count);
        exit(0);
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


void lexical_analysis(string code_path){
    init_key_words_map();
    
    init_code(code_path);
    
    while(cur < code.length()){
        char c = code[cur];
        
        if(is_space(c)){
            cur++;
            if(c=='\n'){
                row_count++;
            }
        }
        
        //handle identifier or key word
        else if(is_letter(c)){
            string id = check_identifier(cur);
            int key_id = KEY_WORDS_MAP[id];
            
            //key_id is not 0, Key Word
            if(key_id!=0){
                // cout_info(id, key_id);
                lex_result.push_back(make_pair(id, key_id));
            }
            
            //key_id is 0, Identifier
            else{
                // print_info(id, KEY_WORDS_MAP["Identifier"]);
                lex_result.push_back(make_pair(id, KEY_WORDS_MAP["Identifier"]));
            }
        }
        
        
        //handle number (beginning with a digit)
        else if(is_digit(c)){
            char next = code[cur+1];
            
            //decimal number : 123, 0
            if(c!='0' || (c == '0' && !(next == 'x' || next == 'X' || is_octal_digit(next)))){
                string decimal_num = check_decimal_number(cur);
                // print_info(decimal_num, KEY_WORDS_MAP["Decimal_Number"]);
                lex_result.push_back(make_pair(decimal_num, KEY_WORDS_MAP["Decimal_Number"]));
            }
            
            else{
                //hexademical number : 0xAF, 0X111F
                if(next == 'x' || next == 'X'){
                    string hexademical_num = check_hexademical_number(cur);
                    // print_info(hexademical_num, KEY_WORDS_MAP["Hexademical_Number"]);
                    lex_result.push_back(make_pair(hexademical_num, KEY_WORDS_MAP["Hexademical_Number"]));
                }
                
                //octal number : 012, 077
                else{
                    string octal_num = check_octal_number(cur);
                    // print_info(octal_num, KEY_WORDS_MAP["Octal_Number"]);
                    lex_result.push_back(make_pair(octal_num, KEY_WORDS_MAP["Octal_Number"]));
                }
            }
        }
        
        
        //handle operator (beginning with <, =, ...)
        else if(is_operator(c)){
            string op = check_operator(cur);
            // print_info(op, KEY_WORDS_MAP[op]);
            lex_result.push_back(make_pair(op, KEY_WORDS_MAP[op]));
        }
        
//        else{
//            cur++;
//        }
    }


    printf("[INFO] results of the lexical analysis : \n");
    for(auto i : lex_result){
        string word = i.first;
        int id = i.second;
        // print_info(word, id);
        printf("< %s  %d >\n", word.c_str(), id);
        
        //get the word_type("Identifier", ...) through KEY_WORDS[id-1]
        word_type_count[KEY_WORDS[id-1]]++;
    }
    printf("-----------------------------------------\n\n");
    

    printf("[INFO] occurrences of different words :  \n");
    for(auto i:word_type_count){
        // cout << i.first << " : " << i.second << endl;
        string word = i.first;
        int count = i.second;
        printf("%s : %d time(s)\n", word.c_str(), count);
    }
    printf("-----------------------------------------\n\n");
    
    

    printf("[INFO] total : %lu word(s) , %d row(s)\n", lex_result.size(), row_count);
    printf("-----------------------------------------\n\n");


}

int main(){
    
    lexical_analysis("p1.txt");

}
