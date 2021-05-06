#ifndef QMDDcircuit_H
#define QMDDcircuit_H

#include <stdio.h>

#include "QMDDpackage.h"
#include "QMDDcomplex.h"
#include "qcost.h"
#include "textFileUtilities.h"
#include <string.h>
#include <iostream>
#include <vector>

/*****************************************************************

    Routines            
*****************************************************************/

int getlabel(char*,QMDDrevlibDescription,int*);

QMDDedge QMDDreadGateFromString(char*, QMDDrevlibDescription*);
QMDDedge QMDDreadGate(FILE*,QMDDrevlibDescription*);
QMDDrevlibDescription QMDDrevlibHeader(FILE*);
QMDDrevlibDescription QMDDcircuitRevlib(char *fname,QMDDrevlibDescription firstCirc,int match, std::vector<QMDDedge>* edges = nullptr);
// reads a circuit in Revlib format: http://www.revlib.org/documentation.php 


/*******************************************************************************/
#endif
