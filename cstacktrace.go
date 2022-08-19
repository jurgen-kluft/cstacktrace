package main

import (
	ccode "github.com/jurgen-kluft/ccode"
	cpkg "github.com/jurgen-kluft/cstacktrace/package"
)

func main() {
	ccode.Generate(cpkg.GetPackage())
}
