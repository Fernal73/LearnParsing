#ifndef MFCALC_H
#define MFCALC_H
/* Function type. */
typedef double (func_t) (double);

/* Data type for links in the chain of symbols. */
struct symrec
{
  /* name of symbol */
  char *name;  
  /* type of symbol: either VAR or FUN */
  int type;    
  union
  {
    /* value of a VAR */
    double var;    
    /* value of a FUN */
    func_t *fun;   
  } value;
  /* link field */
  struct symrec *next;  
};

typedef struct symrec symrec;

/* The symbol table: a chain of 'struct symrec'. */
extern symrec *sym_table;

symrec *putsym (char const *name, int sym_type);
symrec *getsym (char const *name);

#endif /* end of include guard MFCALC_H */
