#ifndef QMDDcomplex_H
#define QMDDcomplex_H


/***************************************

    Basic type definition

***************************************/

typedef struct 
{
   long double r,i;
} complex;


#include "QMDDpackage.h"

#include <ostream>
#include <math.h>

#ifndef DEFINE_COMPLEX_H_VARIABLES
#define EXTERN_C	extern 
#else
#define EXTERN_C	
#endif

/***************************************

	Complex Value Lookup Table
	
	The table holds the unique values needed
	in the QQDD.  It stores one value for each
	conjugate pair (the positive iinary).

***************************************/

EXTERN_C int Ctentries;					 // number of complex table entries
EXTERN_C complex Ctable[COMPLEXTSIZE];    // value
EXTERN_C long double Cmag[COMPLEXTSIZE];  // magnitude to avoid repeated computation
EXTERN_C long double Cangle[COMPLEXTSIZE];// angle to avoid repeated computation
EXTERN_C int CTa[MAXRADIX];				 // complex table positions for roots of unity

/*********************************************

Complex computation tables.  These tables save
result of computations over complex values to
avoid recomputation later.

  Cta - addition
  Cts - subtraction
  Ctm - multiplication
  Ctd - division

*********************************************/

EXTERN_C int cta[COMPLEXTSIZE][COMPLEXTSIZE],cts[COMPLEXTSIZE][COMPLEXTSIZE],ctm[COMPLEXTSIZE][COMPLEXTSIZE],ctd[COMPLEXTSIZE][COMPLEXTSIZE];


/**********************************************

Compute trig functions for angle factor*Pi/div
Note use of cosl and sinl for long double computation

**********************************************/

#define QMDDcos(fac,div) cosl((long double)(fac)*Pi/(long double)(div))
#define QMDDsin(fac,div) sinl((long double)(fac)*Pi/(long double)(div))

/***********************************************

Tolerance for testing equality of complex values

***********************************************/

static long double Ctol = 1.0e-10;

#define Cvalue(x) Ctable[x]
#define Dzero 0.0

#define Ceq(x,y) ((fabs((x.r)-(y.r))<Ctol)&&(fabs((x.i)-(y.i))<Ctol))


/**************************************

    Routines
    
**************************************/

void Cprint(complex, std::ostream&);
void Cprint(complex); // print a complex value to STD_OUT

long double angle(int); // computes angle for polar coordinate representation

int Cgt(int,int); // greater than
//TODO int Cgt_new(int a, int b)
int Clt(int, int); // analogous to Cgt

complex Cmake(long double,long double); // make a complex value
complex CmakeOne(void);  // make +1
complex CmakeZero(void); // make  0
complex CmakeMOne(void); // make -1

long double Qmake(int,int,int);
// returns the complex number equal to (a+b*sqrt(2))/c
// required to be compatible with quadratic irrational-based 
// complex number package

void QMDDinitCtable(void); // initialize the complex value table and complex operation tables to empty
void QMDDcomplexInit(void); // initialization


void QMDDcvalue_table_list(void); // print the complex value table entries
int Clookup(complex); // lookup a complex value in the complex value table; if not found add it

complex Conj(complex); /// return complex conjugate


// basic operations on complex values
// meanings are self-evident from the names
// NOTE arguments are the indices to the values 
// in the complex value table not the values themselves

int Cnegative(int);
int Cadd(int,int);
int Csub(int,int);
int Cmul(int,int);
int CintMul(int,int); // multiply by an integer
int Cdiv(int,int);
void QMDDmakeRootsOfUnity(void);
int CAbs(int); /// by PN: returns the absolut value of a complex number
int CUnit(int a); ///by PN: returns whether a complex number has norm 1

#endif
