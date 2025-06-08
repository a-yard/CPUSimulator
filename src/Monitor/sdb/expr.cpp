#include "../../../Include/expr.hpp"


expr::expr(/* args */)
{
  this->init_regex();
}

expr::~expr()
{
}

void expr::init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      printf("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
      assert(0);
      //panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}



bool expr::make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        //char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //     i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE:
                break;
          case '+':
                tokens[nr_token].type='+';
                strcpy(tokens[nr_token].str,"+");
                nr_token++;
                break;
          case '-':
                tokens[nr_token].type='-';
                strcpy(tokens[nr_token].str,"-");
                nr_token++;
                break;
          case '*':
                tokens[nr_token].type='*';
                strcpy(tokens[nr_token].str,"*");
                nr_token++;
                break;
          case '/':
                tokens[nr_token].type='/';
                strcpy(tokens[nr_token].str,"//");
                //printf("%d \n",nr_token);
                nr_token++;
                break;
          case '(':
                tokens[nr_token].type='(';
                strcpy(tokens[nr_token].str,"(");
                nr_token++;
                break;
          case ')':
                tokens[nr_token].type=')';
                strcpy(tokens[nr_token].str,")");
                nr_token++;
                break;
          case regName:
                {
                  tokens[nr_token].type=NUMBER;
                char obj_reg[10] ;
                strncpy(obj_reg,e+position-substr_len,substr_len);
                obj_reg[substr_len]='\0';
                //printf("%s\n\nsdfsdf\n",obj_reg);
                bool success=1;
                Word_t number=213;
                //number = isa_reg_str2val(obj_reg+1, &success);
                //printf("%x  %s\n",number,obj_reg);
                if(success==0){
                  //panic("no get reg number\n");
                  printf("no get reg number\n");
                  assert(0);
                }
                char number_str [32];
                sprintf(number_str, "%u", number );
                strcpy(tokens[nr_token].str,number_str);
                nr_token++;
                }
                break;
          case hexadecimalNumber:
                {
                  tokens[nr_token].type=NUMBER;
                char hexadecimalNumber_tmp[32];
                char hexadecimalNumber[32];
                strncpy(hexadecimalNumber_tmp,e+position-substr_len+2,substr_len-2);
                hexadecimalNumber_tmp[substr_len-2]='\0';
                sprintf(hexadecimalNumber, "%lu", strtoul(hexadecimalNumber_tmp,NULL,16));
               // printf("hh %s\n\n\n",hexadecimalNumber_tmp);
                strcpy(tokens[nr_token].str,hexadecimalNumber);
               // printf("hexadecimalNumber %s\n",tokens[nr_token].str);
                nr_token++;
                }
                break;
          case NUMBER:
                {
                  tokens[nr_token].type=NUMBER;
                if(substr_len>=32){
                  // panic("error!outblock")
                  printf("error!outblock");
                  assert(0);
                };
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                //printf("%d\n    s = %s  nr_token = %d \n",position-substr_len,tokens[nr_token].str,nr_token);
                nr_token++;
                }
                break;
          case TK_EQ:
                tokens[nr_token].type=TK_EQ;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case NO_TK_EQ:
                tokens[nr_token].type=NO_TK_EQ;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case AND:
                tokens[nr_token].type=AND;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case OR:
                tokens[nr_token].type=OR;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case LESS_THAN:
                tokens[nr_token].type=LESS_THAN;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case GREATER_THAN:
                tokens[nr_token].type=GREATER_THAN;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case Greater_than_or_equal:
                tokens[nr_token].type=Greater_than_or_equal;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case Less_Than_or_equal:
                tokens[nr_token].type=Less_Than_or_equal;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case Shift_left:
                tokens[nr_token].type=Shift_left;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          case Shift_right:
                tokens[nr_token].type=Shift_right;
                strncpy(tokens[nr_token].str,e+position-substr_len,substr_len);
                (tokens[nr_token].str)[substr_len]='\0';
                nr_token++;
                break;
          default: assert(0);//TODO();
        }

        break;
      }
    }
 
    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool expr::check_parentheses(int p,int q){
  int flag=1;
  if(strcmp(tokens[p].str,"(")!= 0 || strcmp(tokens[q].str,")")!=0)return false;
  if(p+1==q)return true;
  for(int i=p+1;i<q;i++){
    if(strcmp(tokens[i].str,"(")==0)flag++;
    if(strcmp(tokens[i].str,")")==0)flag--;
    if(flag==0)return false;
  }
  return true;
}

int expr::getmainop(int p ,int q){
  int flag=0;
  int flag_cc=0;
  int flag_jj=0;
  int flag_jy=0;
  int flag_EQ=0;
  int flag_lj=0;
  int flag_shift =0;
  int flag_Notequalforsize=0;
  for(int i=p;i<=q;i++){
    if(strspn(tokens[i].str, "0123456789")==strlen(tokens[i].str))continue;
    else if (strcmp(tokens[i].str,"(")==0)flag++;
    else if(strcmp(tokens[i].str,")")==0)flag--;
    else if(flag!=0)continue;
    else {
      if(tokens[i].type == OR || tokens[i].type == AND){
        flag_lj=i;
      }else if(tokens[i].type == TK_EQ || tokens[i].type == NO_TK_EQ ){
        flag_EQ=i;
      }else if(tokens[i].type == LESS_THAN || tokens[i].type == GREATER_THAN || tokens[i].type == Greater_than_or_equal || tokens[i].type == Less_Than_or_equal){
              flag_Notequalforsize=i;
      }else if(tokens[i].type == Shift_left || tokens[i].type == Shift_right){
              flag_shift=i;
      }else if(flag==0 && (strcmp(tokens[i].str,"-")==0 || strcmp(tokens[i].str,"+")==0)){
        flag_jj = i;
      }else if(tokens[i].type == '*'  || tokens[i].type == '/'){
              flag_cc=i;
      }else{
        if(tokens[i].type == DEREF || tokens[i].type == minussign){
          flag_jy = i;
        }
      }
    }
  }
  if(flag_lj!=0) return flag_lj;
  else if(flag_EQ!=0) return flag_EQ;
  else if(flag_Notequalforsize!=0)return flag_Notequalforsize;
  else if(flag_shift!=0)return flag_shift;
  else if(flag_jj!=0)return flag_jj;
  else if(flag_cc !=0)return flag_cc;
  return flag_jy;
}
Word_t expr::eval(int p,int q){
  
    if(p>q){
      printf("%d   %d\n",p,q);
      //panic("error! bed expression p>q\n");
      assert(0);
    }
    else if(p==q){
      if(strspn(tokens[q].str, "0123456789")==strlen(tokens[q].str) ){
       // printf("s == %s p==q  %x\n",tokens[p].str,(word_t)(strtoull(tokens[p].str,NULL,10)>>4));
        return (strtoul(tokens[q].str,NULL,10));
      }
      else {
        printf("%s     q== %d  p== %d\n\n",tokens[q].str,q,p);
        //panic("error! it not number\n");
        printf("error! it not number\n");
        assert(0);
      }
    }
    else if(check_parentheses(p,q)){
      return eval(p+1,q-1);
    }
    else{
     
      int op_n = getmainop(p,q);
      int op_type =tokens[op_n].type;
     
      if(op_type==DEREF){
        
        return BUSObj->BUSRead(eval(p+1,q),4); 
      }else if(op_type==minussign){
        return (0u-eval(p+1,q));
      }
      Word_t val1 = eval(p,op_n-1);
      Word_t val2 = eval(op_n+1,q);
    

      switch(op_type) {
        case '+':
            return val1+val2;
        case '-':
            return val1-val2;
        case '*':
            return val1*val2;
        case '/':
           
            return val1/val2;
        case TK_EQ:
            return val1 == val2;
        case NO_TK_EQ:
            return val1 != val2;
        case AND:
            return val1 && val2;
        case OR:
            return val1 || val2;
        case Shift_left:
            return val1<<val2;
        case Shift_right:
            return val1>>val2;
        case LESS_THAN:
            return val1<val2;
        case GREATER_THAN:
            return val1>val2;
        case Greater_than_or_equal:
            return val1<=val2;
        case Less_Than_or_equal:
            return val1>=val2;
        default:
              //printf("gl");
              assert(0);  
      }
    }

}

Word_t expr::ComputeExpr(char *e, bool *success) {  
  if (!make_token(e)) {
    *success = false;
    return 0;
  }else *success = true;
  /* TODO: Insert codes to evaluate the expression. */
  //TODO();

  for(int i=0;i<nr_token;i++){
  	if(tokens[i].type == '*' && (i==0 || tokens[i-1].type == '(' || tokens[i-1].type == '*' || tokens[i-1].type == '-' || tokens[i-1].type ==  '+' || tokens[i-1].type == '/' )){
		tokens[i].type = DEREF;
	}
  }
  for(int i=0;i<nr_token;i++ ){
    if(tokens[i].type == '-' && (i==0 || tokens[i-1].type == '(' || tokens[i-1].type == '*' || tokens[i-1].type == '-' || tokens[i-1].type ==  '+' || tokens[i-1].type == '/' )){
      tokens[i].type = minussign;
    }
  }

  Word_t result = eval(0,nr_token-1);
  
 
  return result;
}
