#ifndef __expr_H__
#define __expr_H__
#include "common.hpp"
#include <regex.h>
// #include "macro.h"
#include "BUS.hpp"
enum {
  TK_NOTYPE = 256, TK_EQ,NUMBER,DEREF,regName,hexadecimalNumber,minussign,
  AND,OR,NO_TK_EQ,LESS_THAN,GREATER_THAN,Greater_than_or_equal,Less_Than_or_equal,
  Shift_left,Shift_right
} ;
static struct rule {
    const char *regex;
    int token_type;
  } rules[] = {
    {" +", TK_NOTYPE},    // spaces
    {"--",TK_NOTYPE},     //"--"->spaces
    {"\\+", '+'},         // plus
    {"\\-",'-'},          //subtract
    {"\\*",'*'},          //nultiply
    {"\\/",'/'},          //except
    {"\\(",'('},          //Opening parentheses
    {"\\)",')'},          //Opening parentheses
    {"[0]x[0-9,a-z]+",hexadecimalNumber},
    {"[0-9]+",NUMBER},
    {"[$][$,r,s,g,t,a,p][0-9,p,c,a]*",regName},
    
    {"==", TK_EQ},        // equal
    {"!=",NO_TK_EQ},      //not equal
    {"&&",AND},           //AND
    {"\\|\\|",OR},            //OR
  
    {"<<",Shift_left},   //Shift_left
    {">>",Shift_right},    //Shift_right
    
  
    {"<=",Greater_than_or_equal},   //Greater_than_or_equal
    {">=",Less_Than_or_equal},  //Less_Than_or_equal
    {"<",LESS_THAN},      //LESS_THAN
    {">",GREATER_THAN},   //GREATER_THAN
    
  };
  
  #define NR_REGEX ARRLEN(rules)

  static regex_t re[NR_REGEX] = {};

  typedef struct token {
    int type;
    char str[32];
  } Token;
  
  static Token tokens[10000] __attribute__((used)) = {};
  static int nr_token __attribute__((used))  = 0;
class expr
{
private:
    BUS * BUSObj;
public:
    expr(/* args */);
    ~expr();
    bool make_token(char *e);
    bool check_parentheses(int p,int q);
    int getmainop(int p ,int q);
    Word_t eval(int p,int q);
    Word_t ComputeExpr(char *e, bool *success);
    void init_regex();
};

#endif