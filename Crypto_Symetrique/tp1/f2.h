#ifndef F2_H
#define F2_H

#include <stdio.h>
#include <inttypes.h>

typedef uint64_t f2_poly_t;
typedef uint8_t f2_deg_t;
// l'ordre des coefficients polynômiaux est du poids fort au poids faible.

#define F2_VARN "X"

#define PRIME64 {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}

typedef struct {
     f2_poly_t poly;
     f2_deg_t   edeg; //degré de l'extension
     char * varn;
} f2_field_t;

f2_deg_t
f2_poly_degree(const f2_poly_t *);

int
f2_poly_div(f2_poly_t *, f2_poly_t *, const f2_poly_t *, const f2_poly_t *);
// (arg1, arg2) = (quotient, reste) de arg3 par arg4

int
f2_poly_rem(f2_poly_t *, const f2_poly_t *);
// arg1 = reste de arg1 par arg2

int
f2_poly_pgcd(f2_poly_t *, const f2_poly_t *, const f2_poly_t *);

int
f2_poly_x2n(f2_poly_t *, f2_deg_t, const f2_poly_t *)
// arg1 =  X^{2^arg2} modulo arg 3

int
f2_poly_irred(const f2_poly_t *)

int
f2_field_init(f2_field_t *, f2_poly_t, f2_deg_t, const char *);
//crée un élément de corps, en vérifiant que le degré du polynôme 
// est strictement inférieur à celui de l'extension
// que celui de l'extension <= 64

int 
f2_field_init_rand(f2_field_t *, f2_deg_t, const char *);
// choix aléatoire parmi les polynômes de degré < au second argument

void
f2__print_raw(const f2_field_t *, FILE *); 
// format hexadécimal pour le polynôme, entier pour le degré

void
f2_poly_print(const f2_poly_t *, FILE *);
// écriture polynomiale usuelle

int 
f2_poly_cpy(f2_field_t *, const f2_field_t *);
//copie du second argument sur le premier

int 
f2_poly_add(f2_field_t *, const f2_field_t *); 
/* addition sur le premier argument, le degré d'extension du second doit
   être égal à celui du premier. 
   Valeur de retour : 0 si les degrés sont égaux
                      -1 s'ils sont différents
*/

f2_poly_t
f2_poly_sum(const f2_poly_t *, const f2_poly_t *);

/* Pour tous les calculs modulo, le degré de l'extension donc du
polynôme par lequel on quotiente est connu ; il suffit donc de donner
les coefficients suivant du polynôme (qui peut donc être de degré <= 64)
*/

int
f2_xtimes_mod(f2_field_t *, const f2_t *);
/* multiplication sur le premier argument par X, modulo le polynôme
 désigné par le second argument plus X^d (d étant le degré du premier argument).
 erreur si le degré du second argument est supérieur ou égal à d.
  */

f2_field_t
f2_times_mod(f2_field_t *, f2_field_t *, const f2_t *);


#endif /* F2_H */
