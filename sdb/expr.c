/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ,TK_BR,TK_NU,'+','-','*','/'

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\+", '+'},         // plus delete a \
  {"==", TK_EQ},        // equal
  {"\(",TK_BR1},
  {"\)",TK_BR2},
  {"\d",TK_NU},
  {"\-",'-'},
  {"\*",'*'},
  {"\/",'/'},
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
		case TK_NOTYPE:
    // 记录没有特定类型的令牌
    tokens[nr_token++] = (Token){TK_NOTYPE, substr_start, position};
    break;
  case '+':
    // 记录加号令牌
    tokens[nr_token++] = (Token){'+', substr_start, position};
    break;
  case TK_EQ:
    // 记录等号令牌
    tokens[nr_token++] = (Token){TK_EQ, substr_start, position};
    break;
  case TK_BR:
    // 记录括号令牌
    tokens[nr_token++] = (Token){TK_BR, substr_start, position};
    break;
  case TK_NU:
    // 记录数字令牌
    tokens[nr_token++] = (Token){TK_NU, substr_start, position};
    break;
  case '-':
    // 记录减号令牌
    tokens[nr_token++] = (Token){'-', substr_start, position};
    break;
  case '*':
    // 记录乘号令牌
    tokens[nr_token++] = (Token){'*', substr_start, position};
    break;
  case '/':
    // 记录除号令牌
    tokens[nr_token++] = (Token){'/', substr_start, position};
    break;
  default:
    // 对于未知的令牌类型，这里可以记录错误或执行其他操作
    printf("Unknown token type: %d\n", rules[i].token_type);
    break    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool check_parentheses(p,q){
  if tokens[p]=="\(" || tokens[q]=="\)"{
    int i,j=p,0;
    for (i;i<=q;i++){
      a = tokens[i];
      if a=='+'||a=='-'||a=='*'||a=='/'{
        j++;}
    if (j>1){
      return false;}
    else if (j==1){
      return true;}
    else return -1;
    }
  }
  else print('Unknown');
  return 0;
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  eval(0, arrlen(tokens-1)) {
    if (p > q) {
      print('bad expression');
      return -1;/* Bad expression */
    }
    else if (p == q) {
	    return tokens[p]
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    }
    else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
      return eval(p + 1, q - 1);
    }
    else {
      op = the position of 主运算符 in the token expression;
      val1 = eval(p, op - 1);
      val2 = eval(op + 1, q);

      switch (op_type) {
        case '+': return val1 + val2;
        case '-': return val1 - val2;/* ... */
        case '*': return val1 * val2;/* ... */
        case '/': return val1 / val2;/* ... */
        default: assert(0);
    /* We should do more things here. */
      }
    }
  return 0;
}
