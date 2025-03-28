#pragma once
#ifdef __cplusplus
extern "C" {
#endif

struct slash;

extern unsigned int slash_dfl_node;
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
