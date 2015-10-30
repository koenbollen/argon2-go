package argon2Lib

// #cgo CFLAGS: -I./Argon2/ -I./Blake2 -I./Common -std=c99 -pthread -O3 -Wall -msse4.1
// #include <stdlib.h>
// #include "hash.h"
import "C"
import "unsafe"

func HashPassword(clearTextPassword string) string {

	chash := C.hash_password(C.CString(clearTextPassword))
	defer C.free(unsafe.Pointer(chash))

	return C.GoString(chash)
}

//// #cgo amd64 386 CFLAGS: -DX86=1
