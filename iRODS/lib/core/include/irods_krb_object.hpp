/* -*- mode: c++; fill-column: 132; c-basic-offset: 4; indent-tabs-mode: nil -*- */

#ifndef _krb_auth_object_H_
#define _krb_auth_object_H_

#include "irods_error.hpp"
#include "irods_auth_object.hpp"

#include <gssapi.h>

namespace irods {

// constant key for krb auth object
    const std::string KRB_AUTH_PLUGIN( "KRB" );
    const std::string AUTH_KRB_SCHEME( "krb" );

    /**
     * @brief Auth object for KRB authentication
     */
    class krb_auth_object : public auth_object {
    public:
        /// @brief Constructor
        krb_auth_object( rError_t* _r_error );
        virtual ~krb_auth_object();

        // Accessors

        /// @brief Returns the KRB credentials
        virtual gss_cred_id_t creds( void ) const {
            return creds_;
        }

        /// @brief Returns the socket number
        virtual int sock( void ) const { return sock_; }

        /// @brief Returns the serverDN
        virtual const std::string& server_dn( void ) const { return server_dn_; }

        /// @brief Returns the digest
        virtual const std::string& digest( void ) const { return digest_; }

        /// =-=-=-=-=-=-=-
        /// @brief serialize object to key-value pairs
        virtual error get_re_vars( keyValPair_t& );

        // Mutators

        /// @brief Sets the KRB credentials
        virtual void creds( gss_cred_id_t _creds ) {
            creds_ = _creds;
        }

        /// @brief Sets the socket number
        virtual void sock( int s ) { sock_ = s; }

        /// @brief Sets the serverDN
        virtual void server_dn( const std::string& s ) { server_dn_ = s; }

        /// @brief Sets the digest
        virtual void digest( const std::string& d ) { digest_ = d; }

        // Methods

        /// @brief undocumented
        error resolve( const std::string& _name, plugin_ptr& _plugin ); // resolve plugin

        /// @brief Comparison operator
        bool operator==( const krb_auth_object& _rhs ) const;


    private:
        gss_cred_id_t creds_;
        int sock_;
        std::string server_dn_;
        std::string digest_;
    };

    typedef boost::shared_ptr<krb_auth_object> krb_auth_object_ptr;

}; // namespace irods

#endif // _krb_auth_object_H_
