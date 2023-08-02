project('apm_csh', 'c')

dependencies = []
dependencies += dependency('csp', fallback: ['csp', 'csp_dep'], required: true).partial_dependency(links: false, includes: true)
dependencies += dependency('param', fallback: ['param', 'param_dep'], required: true).partial_dependency(links: false, includes: true)
dependencies += dependency('slash', fallback: ['slash', 'slash_dep'], required: true).partial_dependency(links: false, includes: true)

addin_param_sources = [
	'src/apm.c',
]

apm_csh_lib = static_library('csh_example_param',
                         addin_param_sources,
                         dependencies : dependencies,
                         link_args : ['-Wl,-Map=cshmodtest.map', '-lm'],
                         install : true)

# .as_link_whole() prevents the linker from discarding functions/symbols that appear unused.
# Specifically; functions/symbols that are unused during static linking,
# but that may be called after dynamic linking by the loading application (csh).
apm_csh_dep = declare_dependency(link_with : apm_csh_lib, dependencies : dependencies).as_link_whole()
