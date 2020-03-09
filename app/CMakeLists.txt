add_compile_definitions(UNICODE _UNICODE)

add_executable(disable-windows-keys WIN32
	app.c
	mainwindow.c
	mainwindow.h
	shared.h
)

add_library(disable-windows-keys-hook SHARED
	hook.c
	shared.h
)

add_dependencies(disable-windows-keys disable-windows-keys-hook)
