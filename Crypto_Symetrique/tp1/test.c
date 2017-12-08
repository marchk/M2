#include "f2_poly.h"

/*
f2_poly_t polAES = 0x11b;     //X^8+X^4+X^3+X+1, irréductible non primitif
f2_poly_t polA51a = 0xe4001;  //X^19+X^18+X^17+X^14+1, irréductible primitif
f2_poly_t polA51b = 0x600001; //X^22+X^21+1, irréductible primitif
f2_poly_t polA51c = 0xe00101; //X^23+X^22+X^21+X^8+1, irréductible primitif
*/

f2_poly_t p = 0x4f;
int pri = f2_poly_primitive(p);
printf("polAES primitif ? %d\n\n", pri);
