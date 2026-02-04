#include "tcl.h"

/* Tcl 8 compatibility shim */
#ifndef TCL_SIZE_MAX
#include <limits.h>
#ifndef Tcl_Size
typedef int Tcl_Size;
#endif
#define TCL_SIZE_MAX INT_MAX
#define TCL_SIZE_MODIFIER ""
#define Tcl_GetSizeIntFromObj Tcl_GetIntFromObj
#endif

extern int Performance_Init(Tcl_Interp *interp);
extern int performance_Init(Tcl_Interp *interp);
extern int Tcl_xor_cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);

