#pragma once
#ifdef __cplusplus
extern "C" {
#endif


/*

CSH API version 

************
* IMPORTANT: Must be updated when ABI breaks or the API is extended!
************

ABI in this context covers:
    - types defined in this file
    - libparam ABI
    - slash ABI
    - csp ABI
in summary: all the libraries used by *both* CSH and the APMs

"API is extended" means: non breaking ABI changes aka new functions, new types etc
*/
#define APM_INIT_VERSION 9

struct slash;

/* Represent the current desired default CSP node CSH operates on */
extern unsigned int slash_dfl_node;
/* Represent the current desired default timeout for CSP communication */
extern unsigned int slash_dfl_timeout;

extern unsigned int rdp_dfl_window;
extern unsigned int rdp_dfl_conn_timeout;
extern unsigned int rdp_dfl_packet_timeout;
extern unsigned int rdp_dfl_delayed_acks;
extern unsigned int rdp_dfl_ack_timeout;
extern unsigned int rdp_dfl_ack_count;


/**
 * @brief a slash tab-completion function that can complete CSP node names based on the known host list
 * 
 * You can use this function as the "completer" parameter of the slash_cmd_*  macros
 * 
 * @param slash ptr to current slash instance
 * @param token partial string to complete
 */
void host_name_completer(struct slash *slash, char * token);

#ifdef __cplusplus
}
#endif
