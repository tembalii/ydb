GO_LIBRARY()
IF (OS_DARWIN AND ARCH_ARM64 OR OS_DARWIN AND ARCH_X86_64 OR OS_LINUX AND ARCH_AARCH64 OR OS_LINUX AND ARCH_X86_64 OR OS_WINDOWS AND ARCH_X86_64)
    SRCS(
		attr.go
		doc.go
		handler.go
		json_handler.go
		level.go
		logger.go
		record.go
		text_handler.go
		value.go
    )
ENDIF()
END()


RECURSE(
	internal
)
