grammar G1

program : 
  block ;

block : 
  { operator_list } ;

operator_list : 
  operator tail ;

tail : 
  ; operator tail | 
  ;


operator : 
  id = expr | block;

expr : 
  simple_expr expr#0 ;

simple_expr : 
  sign term simple_expr#1 | 
  term simple_expr#2 ;

term : 
  factor term#1 ;

factor : 
  id | 
  const | 
  ( simple_expr ) | 
  not factor ;

sign : 
  + - ;

rel_op : 
  = <> < <= > >= ;

sum_op : 
  + - or ;

mul_op : 
  * / div mod and ;

simple_expr#0 : 
  sum_op term simple_expr#3 ;

term#0 : 
  mul_op factor term#2 ;

expr#0 : 
  rel_op simple_expr | 
  ;

simple_expr#1 : 
  simple_expr#0 | 
  ;

simple_expr#2 : 
  simple_expr#0 | 
  ;

term#1 : 
  term#0 | 
  ;

simple_expr#3 : 
  simple_expr#0 | 
  ;

term#2 : 
  term#0 | 
  ;

