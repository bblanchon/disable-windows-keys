add_compile_definitions(UNICODE _UNICODE)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if (MSVC)
    add_compile_options(/W4)
endif()

add_executable(disable-windows-keys WIN32
	app.c
	mainwindow.c
	mainwindow.h
	resource.h
	resource.rc
	shared.h
	stdafx.h
)

add_library(disable-windows-keys-hook SHARED
	hook.c
	hook.def
	shared.h
	stdafx.h
)

add_dependencies(disable-windows-keys disable-windows-keys-hook)
