/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* getXmsgTicket.h
 *
 */

#ifndef GET_XMSG_TICKET_HPP
#define GET_XMSG_TICKET_HPP

/* This is Object File I/O type API call */

#include "rods.hpp"
#include "rcMisc.hpp"
#include "procApiRequest.hpp"
#include "apiNumber.hpp"
#include "dataObjInpOut.hpp"
#include "msParam.hpp"

#if defined(RODS_SERVER)
#define RS_GET_XMSG_TICKET rsGetXmsgTicket
/* prototype for the server handler */
int
rsGetXmsgTicket( rsComm_t *rsComm, getXmsgTicketInp_t *getXmsgTicketInp,
                 xmsgTicketInfo_t **outXmsgTicketInfo );
#else
#define RS_GET_XMSG_TICKET NULL
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* prototype for the client call */
int
rcGetXmsgTicket( rcComm_t *conn, getXmsgTicketInp_t *getXmsgTicketInp,
                 xmsgTicketInfo_t **outXmsgTicketInfo );

#ifdef __cplusplus
}
#endif
#endif	/* GET_XMSG_TICKET_H */
