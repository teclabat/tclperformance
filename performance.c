#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdlib.h>
#include "tcl.h"
#include "performance.h"

extern int Tclperformance_Init(Tcl_Interp *interp) {
  // initialize stubs
  if (Tcl_InitStubs(interp, "8.6", 0) == NULL) {
    return TCL_ERROR;
  }

  // provide package information
  if (Tcl_PkgProvide(interp, "tclperformance", "0.1") != TCL_OK) {
    return TCL_ERROR;
  }

  // Install "xor" command.
  Tcl_CreateObjCommand(interp, "xor", Tcl_xor_cmd, (ClientData)NULL, (Tcl_CmdDeleteProc*)NULL);

  // fini
  return TCL_OK;
}

int Tcl_xor_cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]) {
    // reset result
    Tcl_ResetResult(interp);

    // check argc
    if (objc != 3) {
        Tcl_AppendResult(interp, "Invalid command count, use: xor <string> <salt>", 0);
        return(TCL_ERROR);
    }

    // get the string to xor
    int textLen;
    const unsigned char* text = Tcl_GetByteArrayFromObj(objv[1], &textLen);
    // get salt to xor with
    int saltLen;
    const unsigned char* salt = Tcl_GetByteArrayFromObj(objv[2], &saltLen);
    // init result string
    unsigned char* result = malloc(textLen);

    // xor the string
    int si = 0;
    int ti = 0;
    for (ti = 0; ti < textLen; ti++) {
        result[ti] = text[ti] ^ salt[si++];
        if (si >= saltLen) si = 0;
    }

    // fini
    Tcl_SetObjResult(interp, Tcl_NewByteArrayObj(result, textLen));
    free(result);
    return TCL_OK;
}


