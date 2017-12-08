#ifndef F2_POLY_H
#define F2_POLY_H

#include <stdio.h>
#include <inttypes.h>
#include "arithm.h"
typedef uint64_t f2_poly_t;
typedef uint8_t f2_deg_t;
// l'ordre des coefficients polynômiaux est du poids fort au poids faible.

#define F2_VARN 'X'
#define LEN (sizeof(f2_poly_t) << 3)
// Pour pouvoir tirer un polynôme au hasard
#define RANDOMFILE "/dev/urandom"
// Masque pour un polynôme de degré < d, calcule aussi 2^d - 1
#define MASK(d) (  ~((f2_poly_t)0xffffffffffffffff << d) )


#define POLMAX 0xFFFFFFFFFFFFFFFF

/* Les polynômes sur F2 de degré < 64 sont représentés 
 par des entiers de 64 bits, les coefficients sont ordonnés du poids
 fort vers le poids faible. Ex. 0x82 : X^7+X.
*/

/* Calcul sur F_2[X], pour des polynômes de degré au plus 63 */
f2_deg_t
f2_poly_deg(f2_poly_t);

int
f2_poly_print(f2_poly_t, char, FILE *);
// écriture polynomiale usuelle, avec pour variable le second argument

int
f2_poly_div(f2_poly_t *,f2_poly_t *, f2_poly_t, f2_poly_t);
// (arg1, arg2) = (quotient, reste) de arg3 par arg4

f2_poly_t
f2_poly_rem(f2_poly_t, f2_poly_t);
// reste de arg1 par arg2

f2_poly_t
f2_poly_gcd(f2_poly_t, f2_poly_t);
// pgcd(arg1, arg2)


/* Pour tous les calculs modulo. On peut  quotienter par un
polynôme de degré jusqu'à 63. */

f2_poly_t
f2_poly_xtimes(f2_poly_t, f2_poly_t);
// retourne X*arg1 mod (arg2)


f2_poly_t
f2_poly_times(f2_poly_t, f2_poly_t, f2_poly_t);
// retourne arg1 * arg2 modulo  arg3

f2_poly_t
f2_poly_x2n(f2_deg_t, f2_poly_t);
// retourne X^{2^arg1} modulo arg 2

f2_poly_t
f2_poly_parity(f2_poly_t);
//retourne le reste de la division par X+1 (xor des bits)

f2_poly_t
f2_poly_recip(f2_poly_t);
// retourne le polynôme réciproque considéré comme de degré le second argument

int
f2_poly_irred(f2_poly_t);
// vérifie si le polynôme arg1 est irréductible

f2_poly_t
f2_poly_xn(uint8_t, f2_poly_t);
// retourne X^{arg1} modulo arg 2

int
f2_poly_primitive(f2_poly_t);
// vérifie si le polynôme arg1 est primitif

uint8_t
f2_poly_irred_order(f2_poly_t polP);
// renvoie 0 si le polynôme polP n'est pas irréductible, 
// l'ordre multiplicatif d'une racine, soit de  X modulo P sinon
// Si cet ordre égale 1 << f2_poly-deg(P), le polynôme est primitif.

f2_poly_t
f2_poly_random_inf(f2_deg_t);
// retourne un polynôme tiré au hasard parmi les polynômes de degré < arg

f2_poly_t
f2_poly_random(f2_deg_t);
// retourne un polynôme tiré au hasard parmi les polynômes de degré = arg

f2_poly_t
f2_poly_irred_random(f2_deg_t);
// retourne un polynôme tiré au hasard parmi les polynômes irréductibles
// de degré = arg2

f2_poly_t
f2_poly_primitive_random(f2_deg_t);
// retourne un polynôme tiré au hasard parmi les polynômes primitifs
// de degré = arg2

int 
f2_poly_irred_count(f2_deg_t n);

int 
f2_poly_primitive_count(f2_deg_t n);
// compte le nombre de polynômes irréductibles ou primitifs de degré n
// en les engendrant tous. Ces deux fonctions n'ont d'intérêt que pour
// tester vos algorithmes :
//  -- d'une part vous pouvez vérifier les résultats avec
//     les formules données en feuille d'exercice utilisant la fonction
//     de Möbius et la fonction d'Euler,

//  -- d'autre part, si vous respectez les consignes, les algorithmes
//      doivent permettre d'énumérer (et compter) les polynômes
//      irréductibles de degré 20 au maximum en quelques secondes, et
//      ceux primitifs en un temps plus long mais de quelques secondes
//      également.

#endif /* F2_POLY_H */
