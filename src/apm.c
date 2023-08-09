
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apm_csh.h"

#ifdef APM_HAVE_PARAM
#include <param/param.h>
#include <param/param_list.h>
#include <vmem/vmem.h>
#include <vmem/vmem_ram.h>
#endif

#ifdef APM_HAVE_SLASH
#include <slash/slash.h>
#include <slash/optparse.h>
#include <slash/dflopt.h>
#endif

#include <apm/apm.h>

#if 0
/* __attribute__((constructor)) will run automatically when linking with the loading application, 
    but no arguments can be passed. */
__attribute__((constructor)) void libinit(void) {

}
#endif

/* slash_list_add() is declared 'weak' such that loaders without slash (such as PyCSH) 
    can still load parameter APMs (such as PSU drivers). */
__attribute__((weak)) extern int slash_list_add(struct slash_command * cmd);

/* Library init signature versions:
    1 = void libmain()
    2 = int libmain()
*/
__attribute__((used)) const int apm_init_version = 3;  // NOTE: Must be updated when APM init signature(s) change.

/* libmain() is the init function called by a loading application (CSH)
    when linking with an APM. */
/* 'used' is an attempt to prevent the linker from discarding libmain(),
    when it fails to forsee it being called from the loading application (CSH).
    This does not appear sufficient however,
    so .as_link_whole() in meson.build must also be used. */
__attribute__((used))
int libmain(void) {

    const int verbose = 1;
    int ret = 0;

#ifdef APM_HAVE_SLASH

    /* __attribute__((visibility("hidden"))) prevents the section symbols from linking with 
	the loading application (csh) when compiling an APM.
	In simple terms: When used alone, this means the APM must define at least 1 command,
	(so "__start_slash" will be generated by GCC) before it can use slash as a dependency.
    But when combined with 'weak' the value will be NULL, instead of linking with the sections in CSH. */
    extern struct slash_command __start_slash __attribute__((visibility("hidden"), weak));
    extern struct slash_command __stop_slash __attribute__((visibility("hidden"), weak));

    if (slash_list_add != NULL) {  // If the loading application uses slash.
        for (struct slash_command * cmd = &__start_slash; cmd < &__stop_slash; cmd += 1) {
            int res = slash_list_add(cmd);
            if (res != 0) {
                ret = res;
                if (verbose)
                    fprintf(stderr, "Failed to add slash command \"%s\" while loading APM (return status: %d)\n", cmd->name, ret);
            }
        }
    }
#endif

#ifdef APM_HAVE_PARAM

    extern param_t __start_param __attribute__((visibility("hidden"), weak));
    extern param_t __stop_param __attribute__((visibility("hidden"), weak));

    /* Check if we have parameter section defined */
    if (&__start_param != &__stop_param) {
        for (param_t * param = &__start_param; param < &__stop_param; param += 1) {
            int res = param_list_add(param);
            if (res != 0) {
                ret = res;
                if (verbose)
                    fprintf(stderr, "Failed to add parameter \"%s\" while loading APM (return status: %d)\n", param->name, ret);
            }
        }
    }
#endif

    if (ret)
        return ret;

    if (apm_init != NULL)
        ret = apm_init();

    return ret;
}
