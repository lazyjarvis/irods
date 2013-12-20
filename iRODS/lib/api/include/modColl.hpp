/*** Copyright (c), The Modents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* modColl.h
 */

#ifndef MOD_COLL_HPP
#define MOD_COLL_HPP

/* This is Object File I/O type API call */

#include "rods.hpp"
#include "rcMisc.hpp"
#include "procApiRequest.hpp"
#include "apiNumber.hpp"
#include "initServer.hpp"
#include "dataObjInpOut.hpp"

#if defined(RODS_SERVER)
#define RS_MOD_COLL rsModColl
/* prototype for the server handler */
int
rsModColl( rsComm_t *rsComm, collInp_t *modCollInp );
int
_rsModColl( rsComm_t *rsComm, collInp_t *modCollInp );
#else
#define RS_MOD_COLL NULL
#endif

extern "C" {

    /* prototype for the client call */
    int
    rcModColl( rcComm_t *conn, collInp_t *modCollInp );

    /* rcModColl - Modify the collType, collInfo1 and collInfo2 of a
     * iRODS collection.
     * Input -
     *   rcComm_t *conn - The client connection handle.
     *   collInp_t *collInp - generic coll input. Relevant items are:
     *      collName - the collection to be registered.
     *      condInput - condition input (optional) - currently not used.
     *
     * OutPut -
     *   int status - status of the operation.
     */

}

#endif	/* MOD_COLL_H */