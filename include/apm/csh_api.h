#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <slash/optparse.h>
#include <apm/environment.h>

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
#define APM_INIT_VERSION 10

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


/**** Referring to CSP hosts by name or address */

/* host information forward declaration */
typedef struct host_s host_t;

/**
 * @brief Set the size that the known_hosts_add will malloc() when creating a new node
 * @param new_size new size in bytes to allocate onwards
 */
void known_host_set_storage_size(uint32_t new_size);

/**
 * @brief Return the current size known_hosts_add will malloc() when creating a new node
 * @return current allocation size in bytes
 */
uint32_t known_host_get_storage_size();

/**
 * @brief Adds a new host information (CSP address and name) to the list of known hosts
 * @param addr CSP address for the host
 * @param new_name corresponding name 
 * @param override_existing set to true if you want to allow updating the name for a host with the given address
 * @return pointer to new/updated host_t entry or NULL if memory allocation failed
 */
host_t * known_hosts_add(int addr, const char * new_name, bool override_existing);

/**
 * @brief Copy the hostname in the name memory area if found
 * @param find_host CSP address to look for
 * @param name a valid memory area where the hostname will be copied
 * @param buflen size in bytes of the "name" parameter
 * @return 0 if no host was found, 1 if the name was found and copied into "name"
 */
int known_hosts_get_name(int find_host, char * name, int buflen);

/**
 * @brief returns the CSP address for the given name if found
 * @param find_name name to find
 * @return CSP address if name was found, -1 otherwise
 */
int known_hosts_get_node(const char * find_name);

/**
 * @brief Get a node's CSP address from a string containing either a name to lookup in the "known hosts" list or a decimal number
 * @param res_ptr pointer to a valid integer that will contain the looked up CSP address
 * @param arg string containing either a decimal number or a name to lookup
 * @return 1 if arg contained a valid name, 2 if valid number. In this case, *res_ptr is a valid CSP address. 0 in case of failure (*res_ptr is untouched then)
 */
int get_host_by_addr_or_name(void *res_ptr, const char *arg);

/**
 * @brief a slash tab-completion function that can complete CSP node names based on the known host list
 * 
 * You can use this function as the "completer" parameter of the slash_cmd_*  macros
 * 
 * @param slash ptr to current slash instance
 * @param token partial string to complete
 */
void host_name_completer(struct slash *slash, char * token);

/**
 * @brief a slash tab-completion function that completes parameter names, based on the parameter list.
 * 
 * Arguments identical to `host_name_completer()`
 */
void param_completer(struct slash *slash, char * token);

/**
 * @brief Add an option to given parser that can handle node parameter as numerical address or hostname
 * @param parser to which the option parser should apply to
 * @param node pointer to a valid variable that will receive the resulting node address as an unsigned int (defaults to `slash_dfl_node`)
 * @return reference to newly created option
 */
optparse_opt_t *csh_add_node_option(optparse_t * parser, unsigned int *node);


/* Python execution related APIs */

/**
 * @brief Execute the given string as Python code within the CSH context
 * @param string Python code to execute
 * @param argc number of arguments (passed through `sys.argv`), 0 if no args
 * @param argv same semantics as C main() function
 * @return 0 in case of success, < 0 in case of failure
 */
extern int csh_python_exec_string(const char *string, int argc, char **argv);
/**
 * @brief Execute the Python code contained in the given filename within the CSH context
 * @param filname name of the file containing Python code to execute
 * @param argc number of arguments (passed through `sys.argv`), 0 if no args
 * @param argv same semantics as C main() function
  * @return 0 in case of success, < 0 in case of failure
*/
extern int csh_python_exec_file(const char *filename, int argc, char **argv);


/** Prototype for a CSH customization prompt function */
typedef int (*csh_custom_apm_prompt_t)(struct slash * slash);

/**
 * @brief APM can customize CSH's prompt by calling this function 
 * @param apm_prompt custom prompt function or NULL to restore CSH default prompt
 * 
 */
extern void csh_set_prompt_for_apm(csh_custom_apm_prompt_t apm_prompt);

#ifdef __cplusplus
}
#endif
