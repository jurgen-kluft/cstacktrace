package main

import (
	pkg "github.com/jurgen-kluft/xstacktrace/package"
)

func main() {
	xcode.Init()
	xcode.Generate(pkg.GetPackage())
}
