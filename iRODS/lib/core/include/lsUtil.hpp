/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* getUtil.h - Header for for getUtil.c */

#ifndef LS_UTIL_HPP
#define LS_UTIL_HPP

#include "rodsClient.hpp"
#include "parseCommandLine.hpp"
#include "rodsPath.hpp"

extern "C" {

    int
    lsUtil( rcComm_t *conn, rodsEnv *myRodsEnv, rodsArguments_t *myRodsArgs,
            rodsPathInp_t *rodsPathInp );
    int
    lsDataObjUtil( rcComm_t *conn, rodsPath_t *srcPath,
                   rodsEnv *myRodsEnv, rodsArguments_t *rodsArgs,
                   genQueryInp_t *genQueryInp );
    int
    printLsStrShort( char *srcPath );
    int
    lsDataObjUtilLong( rcComm_t *conn, char *srcPath, rodsEnv *myRodsEnv,
                       rodsArguments_t *rodsArgs, genQueryInp_t *genQueryInp );
    int
    printLsLong( rcComm_t *conn, rodsArguments_t *rodsArgs,
                 genQueryOut_t *genQueryOut );
    int
    printLsShort( rcComm_t *conn, rodsArguments_t *rodsArgs,
                  genQueryOut_t *genQueryOut );
    int
    initCondForLs( rodsEnv *myRodsEnv, rodsArguments_t *rodsArgs,
                   genQueryInp_t *genQueryInp );
    int
    lsCollUtil( rcComm_t *conn, rodsPath_t *srcPath, rodsEnv *myRodsEnv,
                rodsArguments_t *rodsArgs );
    int
    printDataAcl( rcComm_t *conn, char *dataId );
    int
    printCollAcl( rcComm_t *conn, char *collId );
    int
    printCollInheritance( rcComm_t *conn, char *collName );
    int
    lsSpecDataObjUtilLong( rcComm_t *conn, rodsPath_t *srcPath,
                           rodsEnv *myRodsEnv, rodsArguments_t *rodsArgs );
    int
    printSpecLsLong( char *objPath, char *ownerName, char *objSize,
                     char *modifyTime, specColl_t *specColl, rodsArguments_t *rodsArgs );
    void
    printCollOrDir( char *myName, objType_t myType, rodsArguments_t *rodsArgs,
                    specColl_t *specColl );
    int
    printDataCollEnt( collEnt_t *collEnt, int flags );
    int
    printDataCollEntLong( collEnt_t *collEnt, int flags );
    int
    printCollCollEnt( collEnt_t *collEnt, int flags );
    int
    lsSubfilesInBundle( rcComm_t *conn, char *srcPath, rodsEnv *myRodsEnv,
                        rodsArguments_t *rodsArgs );
    int
    setSessionTicket( rcComm_t *myConn, char *ticket );
}

#endif	/* LS_UTIL_H */