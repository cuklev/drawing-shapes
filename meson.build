project('drawing-shapes', 'cpp')

source_files = [
	'./src/draw.cpp',
	'./src/shapes.cpp'
]
pngpp = dependency('libpng')
pthread = dependency('threads')
deps = [ pngpp, pthread ]

executable('draw', source_files, dependencies : deps)
