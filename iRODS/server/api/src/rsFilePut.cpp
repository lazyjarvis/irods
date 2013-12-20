/* -*- mode: c++; fill-column: 132; c-basic-offset: 4; indent-tabs-mode: nil -*- */

/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* This is script-generated code (for the most part).  */
/* See filePut.h for a description of this API call.*/

#include "filePut.hpp"
#include "miscServerFunct.hpp"
#include "fileCreate.hpp"
#include "dataObjOpr.hpp"

// =-=-=-=-=-=-=-
// stl includes
#include <iostream>
#include <sstream>

// =-=-=-=-=-=-=-
#include "irods_log.hpp"
#include "irods_file_object.hpp"
#include "irods_stacktrace.hpp"
#include "irods_resource_backport.hpp"


/* rsFilePut - Put the content of a small file from a single buffer
 * in filePutInpBBuf->buf.
 * Return value - int - number of bytes read.
 */

int
rsFilePut( rsComm_t *rsComm, fileOpenInp_t *filePutInp,
           bytesBuf_t *filePutInpBBuf ) {
    rodsServerHost_t *rodsServerHost;
    int remoteFlag;
    int status;
    //remoteFlag = resolveHost (&filePutInp->addr, &rodsServerHost);
    irods::error ret = irods::get_host_for_hier_string( filePutInp->resc_hier_, remoteFlag, rodsServerHost );
    if ( !ret.ok() ) {
        irods::log( PASSMSG( "failed in call to irods::get_host_for_hier_string", ret ) );
        return -1;
    }
    if ( remoteFlag == LOCAL_HOST ) {
        status = _rsFilePut( rsComm, filePutInp, filePutInpBBuf,
                             rodsServerHost );
    }
    else if ( remoteFlag == REMOTE_HOST ) {
        status = remoteFilePut( rsComm, filePutInp, filePutInpBBuf,
                                rodsServerHost );
    }
    else {
        if ( remoteFlag < 0 ) {
            return ( remoteFlag );
        }
        else {
            rodsLog( LOG_NOTICE,
                     "rsFilePut: resolveHost returned unrecognized value %d",
                     remoteFlag );
            return ( SYS_UNRECOGNIZED_REMOTE_FLAG );
        }
    }

    if ( status < 0 ) {
        return ( status );
    }


    return ( status );
}

int
remoteFilePut( rsComm_t *rsComm, fileOpenInp_t *filePutInp,
               bytesBuf_t *filePutInpBBuf, rodsServerHost_t *rodsServerHost ) {
    int status;

    if ( rodsServerHost == NULL ) {
        rodsLog( LOG_NOTICE,
                 "remoteFilePut: Invalid rodsServerHost" );
        return SYS_INVALID_SERVER_HOST;
    }

    if ( ( status = svrToSvrConnect( rsComm, rodsServerHost ) ) < 0 ) {
        rodsLog( LOG_ERROR, "remoteFilePut - svrToSvrConnect failed %d", status );
        return status;
    }


    status = rcFilePut( rodsServerHost->conn, filePutInp, filePutInpBBuf );

    if ( status < 0 && status != DIRECT_ARCHIVE_ACCESS ) {
        rodsLog( LOG_NOTICE,
                 "remoteFilePut: rcFilePut failed for %s",
                 filePutInp->fileName );
    }

    return status;
}

// =-=-=-=-=-=-=-
// local implementation of put
int _rsFilePut(
    rsComm_t*         _comm,
    fileOpenInp_t*    _put_inp,
    bytesBuf_t*       _put_bbuf,
    rodsServerHost_t* _server_host ) {
    int fd = 0;

    // =-=-=-=-=-=-=-
    // NOTE:: this test does not seem to work for i86 solaris
    if ( ( _put_inp->otherFlags & FORCE_FLAG ) != 0 ) {
        // =-=-=-=-=-=-=-
        // create one if it does not exist */
        _put_inp->flags |= O_CREAT;
        fd = _rsFileOpen( _comm, _put_inp );

    }
    else {
        fd = _rsFileCreate( _comm, _put_inp, _server_host );

    } // else

    // =-=-=-=-=-=-=-
    // log, error if any
    if ( fd < 0 ) {
        if ( getErrno( fd ) == EEXIST ) {
            rodsLog( LOG_DEBUG1,
                     "_rsFilePut: filePut for %s, status = %d",
                     _put_inp->fileName, fd );
        }
        else if ( fd != DIRECT_ARCHIVE_ACCESS ) {
            rodsLog( LOG_NOTICE,
                     "_rsFilePut: filePut for %s, status = %d",
                     _put_inp->fileName, fd );
        }
        return ( fd );
    }

    if ( _put_inp->objPath[0] == '\0' ) {
        std::stringstream msg;
        msg << __FUNCTION__;
        msg << " - Empty logical path.";
        irods::log( LOG_ERROR, msg.str() );
        return SYS_INVALID_INPUT_PARAM;
    }

    // =-=-=-=-=-=-=-
    // call write for resource plugin
    irods::file_object_ptr file_obj(
        new irods::file_object(
            _comm,
            _put_inp->objPath,
            _put_inp->fileName,
            _put_inp->resc_hier_,
            fd, 0, 0 ) );
    file_obj->in_pdmo( _put_inp->in_pdmo );

    irods::error write_err = fileWrite( _comm,
                                        file_obj,
                                        _put_bbuf->buf,
                                        _put_bbuf->len );
    int write_code = write_err.code();
    // =-=-=-=-=-=-=-
    // log errors, if any
    if ( write_code != _put_bbuf->len ) {
        if ( write_code >= 0 ) {
            std::stringstream msg;
            msg << "fileWrite failed for [";
            msg << _put_inp->fileName;
            msg << "] towrite [";
            msg << _put_bbuf->len;
            msg << "] written [";
            msg << write_code << "]";
            irods::error err = PASSMSG( msg.str(), write_err );
            irods::log( err );
            write_code = SYS_COPY_LEN_ERR;
        }
        else {
            std::stringstream msg;
            msg << "fileWrite failed for [";
            msg << _put_inp->fileName;
            msg << "]";
            irods::error err = PASSMSG( msg.str(), write_err );
            irods::log( err );
        }
    }

    // =-=-=-=-=-=-=-
    // close up after ourselves
    irods::error close_err = fileClose( _comm,
                                        file_obj );
    if ( !close_err.ok() ) {
        irods::error err = PASSMSG( "error on close", close_err );
        irods::log( err );
    }

    // =-=-=-=-=-=-=-
    // return 'write_err code' as this includes this implementation
    // assumes we are returning the size of the file 'put' via fileWrite
    return write_code;

} // _rsFilePut



