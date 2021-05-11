grammar Grammar;

program : block;

block : '{' operator_list '}';

operator_list : operator tail;

tail : ';' operator tail | ; 

operator : id '=' expr | block;

expr : simple_expr | simple_expr rel_op simple_expr;

simple_expr : term | sign term | simple_expr sum_op term;

term : factor | term mul_op factor;

factor : id | const | '(' simple_expr ')' | 'not' factor;

sign :'+' | '-';

rel_op : '==' | '<>' | '<' | '<=' | '>' | '>=';

sum_op : '+' | '-' | 'or';

mul_op : '*' | '/' | 'div' | 'mod' | 'and';

id : 'a' .. 'z' +;

const : '0' .. '9' +;

