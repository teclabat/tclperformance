#include "../config.h"
#include <stdlib.h>
#include "tcl.h"
#include "performance.h"
#define NS_PREFIX PACKAGE_NAME"::"

extern int Performance_Init(Tcl_Interp *interp) {
    // initialize stubs
    if (Tcl_InitStubs(interp, "8.6-", 0) == NULL)
        return TCL_ERROR;

    // create namespace
    if (Tcl_CreateNamespace(interp, NS_PREFIX, NULL, NULL) == NULL)
        return TCL_ERROR;

    // Install "xor" command in the performance namespace.
    Tcl_CreateObjCommand(interp, NS_PREFIX "xor", Tcl_xor_cmd, (ClientData)NULL, (Tcl_CmdDeleteProc*)NULL);

    // provide package information
    if (Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION) != TCL_OK)
        return TCL_ERROR;

    // fini
    return TCL_OK;
}

/* Tcl 9 lowercase alias for load command compatibility */
extern int performance_Init(Tcl_Interp *interp) {
    return Performance_Init(interp);
}

int Tcl_xor_cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
    // reset result
    Tcl_ResetResult(interp);

    // check argc
    if (objc != 3) {
        Tcl_AppendResult(interp, "Invalid command count, use: xor <string> <salt>", (char *)NULL);
        return(TCL_ERROR);
    }

    // get the string to xor
    Tcl_Size textLen;
    const unsigned char* text = Tcl_GetByteArrayFromObj(objv[1], &textLen);
    // get salt to xor with
    Tcl_Size saltLen;
    const unsigned char* salt = Tcl_GetByteArrayFromObj(objv[2], &saltLen);
    // init result string
    unsigned char* result = malloc(textLen);

    // xor the string
    Tcl_Size si = 0;
    Tcl_Size ti = 0;
    for (ti = 0; ti < textLen; ti++) {
        result[ti] = text[ti] ^ salt[si++];
        if (si >= saltLen) si = 0;
    }

    // fini
    Tcl_SetObjResult(interp, Tcl_NewByteArrayObj(result, textLen));
    free(result);
    return TCL_OK;
}


