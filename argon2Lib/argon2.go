package argon2Lib

// #cgo CFLAGS: -I../../../xebia/Argon2/Source/C99/Argon2/ -I../../../xebia/Argon2/Source/C99/Blake2 -I../../../xebia/Argon2/Source/C99/Common
// #cgo LDFLAGS: -L/Users/mgrol/src/go/src/github.com/xebia/Argon2/Build -largon2
// #cgo amd64 386 CFLAGS: -DX86=1
// #include <stdlib.h>
// #include "hash.h"
import "C"
import "unsafe"

func HashPassword(clearTextPassword string) string {

	chash := C.hash_password(C.CString(clearTextPassword))
	defer C.free(unsafe.Pointer(chash))

	return C.GoString(chash)
}

// #cgo LDFLAGS: -L../../xebia/Argon2/Build -largon2
