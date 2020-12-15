# Disable Windows Keys
# https://bblanchon.github.io/disable-windows-keys
# Copyright (C) 2020  Benoit Blanchon

set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")
set(SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/disable-windows-keys.iss")

option(SIGN "Sign the executable with the certificate" OFF)
if (SIGN)
	set(CERTIFICATE_THUMBPRINT "77019b7fece9cc99f06103897b9e9c0545bdc4b9")
	set(DESCRIPTION "Disable Windows Key")
	set(SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/disable-windows-keys.iss")
	set(SIGNTOOL "signtool.exe sign /sha1 ${CERTIFICATE_THUMBPRINT} /tr http://timestamp.digicert.com /td sha256 /fd sha256 /d $q${DESCRIPTION}$q $f")

	add_custom_target(setup
		COMMAND iscc "/DBuildDir=$<TARGET_FILE_DIR:disable-windows-keys>" "/DSignTool=custom" "/Scustom=${SIGNTOOL}" "/O${OUTPUT_DIR}" ${SCRIPT}
		DEPENDS disable-windows-keys
		BYPRODUCTS Output/disable-windows-keys.exe
	)
else()
	add_custom_target(setup
		COMMAND iscc "/DBuildDir=$<TARGET_FILE_DIR:disable-windows-keys>" "/O${OUTPUT_DIR}" ${SCRIPT}
		DEPENDS disable-windows-keys
		BYPRODUCTS Output/disable-windows-keys.exe
	)
endif()