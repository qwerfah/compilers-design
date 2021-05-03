grammar Grammar;

program : block;

block : '{' operator_list '}';

operator_list : operator tail;

tail : ';' operator tail | ; 

operator : id '=' expr;

expr : simple_expr expr#0;

expr#0 : rel_op simple_expr | ;

simple_expr : term simpe_expr';

simple_expr' : sum_op term | sum_op term simple_expr';

term : factor | factor term';

term' : mul_op factor | mul_op factor term';

factor : id | const | '(' simple_expr ')' | 'not' factor;

sign :'+' | '-';

rel_op : '=' | '<>' | '<' | '<=' | '>' | '>=';

sum_op : '+' | '-' | 'or';

mul_op : '*' | '/' | 'div' | 'mod' | 'and';

id : 'a' .. 'z' +;

const : '0' .. '9' +;

