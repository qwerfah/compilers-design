grammar G1program : 
  block ;

block : 
  { operator_list } ;

operator_list : 
  operator tail ;

tail : 
  ; operator tail | 
  ;

operator : 
  id = expr | 
  { operator_list } ;

expr : 
  simple_expr | 
  simple_expr rel_op simple_expr ;

simple_expr : 
  term | 
  sign term | 
  term simple_expr#0 | 
  sign term simple_expr#0 ;

term : 
  factor | 
  factor term#0 ;

factor : 
  id | 
  const | 
  ( simple_expr ) | 
  not factor ;

sign : 
  + - ;

rel_op : 
  == <> < <= > >= ;

sum_op : 
  + - or ;

mul_op : 
  * / div mod and ;

simple_expr#0 : 
  sum_op term | 
  sum_op term simple_expr#0 ;

term#0 : 
  mul_op factor | 
  mul_op factor term#0 ;

