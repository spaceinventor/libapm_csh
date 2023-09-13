project('apm_csh', 'c')

apm_csh_inc = include_directories('.', 'include')

dependencies = []
dependencies += dependency('csp', fallback: ['csp', 'csp_dep'], required: false).partial_dependency(links: false, includes: true)
param_dep = dependency('param', fallback: ['param', 'param_dep'], required: false).partial_dependency(links: false, includes: true)
slash_dep = dependency('slash', fallback: ['slash', 'slash_dep'], required: false).partial_dependency(links: false, includes: true)
dependencies += param_dep
dependencies += slash_dep

conf = configuration_data()
if slash_dep.found()
	conf.set('APM_HAVE_SLASH', 1)
endif
if param_dep.found()
	conf.set('APM_HAVE_PARAM', 1)
endif
apm_csh_h = configure_file(output: 'apm_csh.h', configuration: conf)

apm_csh_sources = [
	'src/apm.c',
]

apm_csh_lib = static_library('apm_csh_lib',
                         apm_csh_sources,
                         include_directories: apm_csh_inc,
                         dependencies : dependencies,
                         link_args : ['-Wl,-Map=cshmodtest.map', '-lm'],
                         install : false)

# .as_link_whole() prevents the linker from discarding functions/symbols that appear unused.
# Specifically; functions/symbols that are unused during static linking,
# but that may be called after dynamic linking with the loading application (csh).
apm_csh_dep = declare_dependency(link_with : apm_csh_lib, dependencies : dependencies, include_directories: apm_csh_inc).as_link_whole()
