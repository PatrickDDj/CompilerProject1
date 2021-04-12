//
//  main.cpp
//  Compiler_Porject1
//
//  Created by PatrickDD on 2021/3/29.
//
#include "Defitions.h"

map<string, int> KEY_WORDS_MAP;

string code;
int cur = 0;
int row = 1;
int col = 1;

vector<pair<vector<string>, int> > lex_result;

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


string row_col(int r, int c){
    return to_string(r) + "." + to_string(c);
}


bool is_letter(char c){
    return (c >='a' && c<='z') || (c >='A' && c<='Z');
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


void check_string_constant(){
    int n=1;
    
    bool is_valid = false;
    
    while(cur+n < code.length()){
        
        if(code[cur+n] == '\n'){
            printf("[ERROR] unqualified string constant '%s' at row [%d] col[%d-%d]\n", code.substr(cur, n).c_str() ,row, col, col+n-1);
           break;
        }
        
        if(code[cur+n] == '"'){
            is_valid = true;
            n++;
            break;
        }
        n++;
    }
    
    string string_constant = code.substr(cur, n);
//    int len_string_constant = string_constant.length();
    
    if(is_valid){
        lex_result.push_back(make_pair(vector<string>{string_constant, row_col(row, col), row_col(row, col+n-1)}, KEY_WORDS_MAP["String_Constant"]));
    }

    col += n;
    cur += n;
    
}

void check_identifier(){
    int n = 1;
    
    //for checking "else if"
    if(code.substr(cur, 7) == "else if"){
        n = 7;
    }
    
    else{
        while(is_letter(code[cur+n]) || is_digit(code[cur+n])){
            n++;
        }
    }
    
    
    string id = code.substr(cur, n);
    int key_id = KEY_WORDS_MAP[id];
//    int len_id = id.length();
    
    
    lex_result.push_back(make_pair(vector<string>{id, row_col(row, col),
        row_col(row, col+n-1)}, (key_id==0 ? KEY_WORDS_MAP["Identifier"]:key_id)));
    
    cur += n;
    col += n;
    
}


void check_decimal_number(){
    int n = 1;
    
    string num;
    
    while(is_digit(code[cur+n])){
        n++;
    }
    
    //unqualified identifier like '3aa'
    if(is_letter(code[cur+n])){
        while(!is_operator(code[cur+n]) && !is_space(code[cur+n])){
            n++;
        }
        printf("[ERROR] unqualified identifier '%s' at row [%d] col[%d-%d]\n", code.substr(cur, n).c_str() ,row, col, col+n-1);
    }
    else{
        num = code.substr(cur, n);
        lex_result.push_back(make_pair(vector<string>{num, row_col(row, col), row_col(row, col+n-1)}, KEY_WORDS_MAP["Decimal_Number"]));
        
    }

    cur += n;
    col += n;

}


void check_hexademical_number(){
    int n=1;
    
    char x = code[cur+n];
    if(x == 'x' || x=='X'){
        n++;
    }
    while(is_hexademical_digit(code[cur+n])){
        n++;
    }

    
    string num = code.substr(cur, n);
    lex_result.push_back(make_pair(vector<string>{num, row_col(row, col), row_col(row, col+n-1)}, KEY_WORDS_MAP["Hexademical_Number"]));
    
    cur += n;
    col += n;
}


void check_octal_number(){
    int n=1;
    while(is_octal_digit(code[cur+n])){
        n++;
    }
    
    string num = code.substr(cur, n);
    lex_result.push_back(make_pair(vector<string>{num, row_col(row, col), row_col(row, col+n-1)}, KEY_WORDS_MAP["Octal_Number"]));
    
    cur += n;
    col += n;
}


void check_operator(){
    int n=1;
    bool flag = false;
    char c = code[cur];
    if(!flag && (c=='(' || c==')' || c=='[' || c== ']' || c=='{' || c=='}' || c=='.' || c=='#'
       || c=='_' || c==',' || c==';' || c=='"' || c=='\'')){
        flag = true;
    }
    if(!flag && (c=='!' || c=='&' || c=='~' || c=='^' || c=='|'
       || c=='+' || c=='-' || c=='*' || c=='/' || c=='%'
       || c=='>' || c=='<' || c=='=')){
        if(code[cur+n]=='='){
            n++;
            flag = true;
        }
    }

    if(!flag && (c=='&' || c=='|' || c=='>' || c=='<' || c=='+' || c=='-' || c=='/')){
        //    n is 1
        if(code[cur+n] == code[cur]){
            n++;
            flag = true;
        }
    }
    if(!flag && c=='-'){
        if(code[cur+n] == '>'){
            n++;
            flag = true;
        }
    }
    
    string op = code.substr(cur, n);
    lex_result.push_back(make_pair(vector<string>{op, row_col(row, col), row_col(row, col+n-1)}, KEY_WORDS_MAP[op]));
    
    col += n;
    cur += n;

}

void check_number(){
    char c = code[cur];
    char next = code[cur+1];

    //decimal number : 123, 0
    if(c!='0' || (c == '0' && !(next == 'x' || next == 'X' || is_octal_digit(next)))){
        check_decimal_number();

    }
    
    else{
        //hexademical number : 0xAF, 0X111F
        if(next == 'x' || next == 'X'){
            check_hexademical_number();
        }
        
        //octal number : 012, 077
        else{
            check_octal_number();
        }
    }
}
    
void check_space(){
    char c = code[cur];
    cur++;
    if(c=='\n'){
        row++;
        col = 1;
    }
    else{
        col++;
    }
}


void lexical_analysis(string code_path){
    init_key_words_map();
    
    init_code(code_path);
    
    while(cur < code.length()){
        char c = code[cur];
        
        if(is_space(c)){
            check_space();
        }
        
        //handle identifier or key word
        else if(is_letter(c)){
            check_identifier();
        }
        
        
        //handle number (beginning with a digit)
        else if(is_digit(c)){
            check_number();
        }
        else if(c == '"'){
            check_string_constant();
        }
        
        //handle operator (beginning with <, =, ...)
        else if(is_operator(c)){
            check_operator();
        }
    }


    printf("[INFO] results of the lexical analysis : \n");
    for(auto i : lex_result){
        vector<string> word_info = i.first;
        int id = i.second;
        // print_info(word, id);
        printf("[%s]-[%s] : < %s  %d >\n", word_info[1].c_str(), word_info[2].c_str(), word_info[0].c_str(), id);
        
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
    
    

    printf("[INFO] total : %d word(s) , %d row(s)\n", lex_result.size(), row);
    printf("-----------------------------------------\n\n");

}

int main(){
    
    lexical_analysis("p1.txt");
 
}
