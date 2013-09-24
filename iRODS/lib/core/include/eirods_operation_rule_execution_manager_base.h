


#ifndef __EIRODS_OPERATION_RULE_EXECUTION_MANAGER_BASE_H__
#define __EIRODS_OPERATION_RULE_EXECUTION_MANAGER_BASE_H__

// =-=-=-=-=-=-=-
// eirods includes
#include "eirods_log.h"

// =-=-=-=-=-=-=-
// boost includes
#include <boost/smart_ptr.hpp>

// =-=-=-=-=-=-=-
// stl includes
#include <string>


namespace eirods {
    /// =-=-=-=-=-=-=-
    /// @brief base class for rule execution which will allow
    ///        the use of a stub for client side network plugins
    class operation_rule_execution_manager_base {
        public:
        // =-=-=-=-=-=-=-
        /// @brief Constructor
        operation_rule_execution_manager_base( 
            const std::string& _inst,   // plugin name 
            const std::string& _op,     // operation name
            keyValPair_t&      _kvp ) : // vars from fco
            instance_( _inst ),
            op_name_( _op ),
            kvp_( _kvp ) {
        }
        
        /// =-=-=-=-=-=-=-
        /// @brief necessary virtual dtor
        virtual ~operation_rule_execution_manager_base() {}

        /// =-=-=-=-=-=-=-
        /// @brief execute rule for pre operation
        virtual error exec_pre_op( 
            std::string& ) = 0; // rule results

        /// =-=-=-=-=-=-=-
        /// @brief execute rule for post operation
        virtual error exec_post_op( 
            std::string& ) = 0; // rule results

        /// =-=-=-=-=-=-=-
        /// @brief execute rule for post operation
        virtual error exec_op( 
            const std::string&, // rule name 
            std::string& ) = 0; // results of call to rule

        protected:
            std::string instance_; // instance name of the plugin
            std::string op_name_;  // operation name
            keyValPair_t& kvp_;    // vars from fco to pass to pep

    }; // class operation_rule_execution_manager_base

    typedef boost::shared_ptr< operation_rule_execution_manager_base > oper_rule_exec_mgr_ptr;

}; // namespace eirods

#endif // __EIRODS_OPERATION_RULE_EXECUTION_MANAGER_BASE_H__



