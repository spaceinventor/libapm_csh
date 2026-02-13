
#pragma once

/**
 * @brief User-definable init hook.
 * 
 * May be defined by the author(s) of the APM,
 * whereafter it will then be (indirectly) called by the loading application.
 * 
 * @return truthy value indicates an error to the loading application,
 *  which should then unlink or close.
 */
__attribute__((weak, visibility("hidden"))) int apm_init(void);

int libmain(void);