GO_LIBRARY()
IF (OS_DARWIN AND ARCH_ARM64 OR OS_DARWIN AND ARCH_X86_64 OR OS_LINUX AND ARCH_AARCH64 OR OS_LINUX AND ARCH_X86_64 OR OS_WINDOWS AND ARCH_X86_64)
    SRCS(
		atob.go
		atoc.go
		atof.go
		atoi.go
		bytealg.go
		ctoa.go
		decimal.go
		doc.go
		eisel_lemire.go
		ftoa.go
		ftoaryu.go
		isprint.go
		itoa.go
		quote.go
    )
ENDIF()
END()
