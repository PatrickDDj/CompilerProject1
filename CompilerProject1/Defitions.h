//
//  Defitions.h
//  Compiler_Porject1
//
//  Created by PatrickDD on 2021/3/29.
//

#ifndef Defitions_h
#define Defitions_h

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


//#define MAIN 0
//
//
//#define INT 1   //int
//#define BOOL 2  //bool
//#define CHAR 3  //char
//
////operator
//#define NOT 11   // !
//#define BYTE_AND 12 //&
//#define COMPLEMENT 13 // ~
//#define BYTE_XOR  14 // ^
//#define MUL 15 // *
//#define DIV 16// /
//#define MOD 17 // %
//#define ADD 18 // +
//#define SUB 19 // -
//#define LES_THAN 20 // <
//#define GRT_THAN 21 // >
//#define ASG 22 // =
//#define ARROW 23 // ->
//#define SELF_ADD 24 // ++
//#define SELF_SUB 25 // --
//#define LEFT_MOVE 26 // <<
//#define RIGHT_MOVE 27 // >>
//#define LES_EQUAL 28 // <=
//#define GRT_EQUAL 29 // >=
//#define EQUAL 30 // ==
//#define NOT_EQUAL 31 // !=
//#define AND 32 // &&
//#define OR 33 // ||
//#define COMPLETE_ADD 34 // +=
//#define COMPLETE_SUB 35 // -=
//#define COMPLETE_MUL 36 // *=
//#define COMPLETE_DIV 37 // /=
//#define COMPLETE_BYTE_XOR 38 // ^=
//#define COMPLETE_BYTE_AND 39 // &=
//#define COMPLETE_COMPLEMENT 40 // ~=
//#define COMPLETE_MOD 41 //%=
//#define BYTE_OR 42 // |
//
//
//#define LEFT_BRA 50 // (
//#define RIGHT_BRA 51 // )
//#define LEFT_INDEX 52 // [
//#define RIGHT_INDEX 53 // ]
//#define L_BOUNDER 54 //  {
//#define R_BOUNDER 55 // }
//#define POINTER 56 // .
//#define JING 57 // #
//#define UNDER_LINE 58 // _
//#define COMMA 59 // ,
//#define SEMI 60 // ;
//#define SIN_QUE 61 // '
//#define DOU_QUE 62 // "


const vector<string> KEY_WORDS = {
    "main", "include", "void", "return",
    "int", "bool", "float", "double","char",
    
    "(", ")", "[", "]", "{", "}", ".", "#", "_", ",", ";", "'", "\"",
    
    "!", "&", "~", "^","|",
    "+", "-", "*", "/", "%",
    ">", "<", "=",
    "->", "++", "--",
    "<<", ">>",
    "<=", ">=", "==", "!=",
    "&&", "||",
    "+=", "-=", "/=","*=", "^=", "&=", "|=", "%=", "~=",
    
    "Identifier",
    "Decimal_Number", //十进制
    "Hexademical_Number", //十六进制
    "Octal_Number", //八进制
    
    "if", "else", "while", "for", "else if",
    "get", "put"
    
};

#endif /* Defitions_h */
