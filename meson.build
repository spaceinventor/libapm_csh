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

apm_csh_dep = declare_dependency(link_with : apm_csh_lib, dependencies : dependencies).as_link_whole()
