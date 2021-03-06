/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* fsckUtil.h - Header for fsckUtil.c */

#ifndef FSCK_UTIL_HPP
#define FSCK_UTIL_HPP

#include "rodsClient.hpp"
#include "parseCommandLine.hpp"
#include "rodsPath.hpp"
#include "scanUtil.hpp"

#ifdef __cplusplus
extern "C" {
#endif
int
fsckObj( rcComm_t *conn, rodsArguments_t *myRodsArgs, rodsPathInp_t *rodsPathInp, char hostname[LONG_NAME_LEN] );
int
fsckObjDir( rcComm_t *conn, rodsArguments_t *myRodsArgs, char *inpPath, char *hostname );
int
chkObjConsistency( rcComm_t *conn, rodsArguments_t *myRodsArgs, char *inpPath, char *hostname );

#ifdef __cplusplus
}
#endif
#endif  /* FSCK_UTIL_H */
