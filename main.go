package main

import (
	"flag"
	"fmt"

	"github.com/xebia/argon2-go/argon2Lib"
)

func main() {
	password := flag.String("password", "secret", "Cleartext password")
	flag.Parse()

	hashedPassword := argon2Lib.HashPassword(*password)

	fmt.Printf("%s", hashedPassword)
}
