package cstacktrace

import (
	cbase "github.com/jurgen-kluft/cbase/package"
	denv "github.com/jurgen-kluft/ccode/denv"
	cunittest "github.com/jurgen-kluft/cunittest/package"
)

// GetPackage returns the package object of 'cstacktrace'
func GetPackage() *denv.Package {
	// Dependencies
	cunittestpkg := cunittest.GetPackage()
	cbasepkg := cbase.GetPackage()

	// The main (cstacktrace) package
	mainpkg := denv.NewPackage("cstacktrace")
	mainpkg.AddPackage(cunittestpkg)
	mainpkg.AddPackage(cbasepkg)

	// 'cstacktrace' library
	mainlib := denv.SetupDefaultCppLibProject("cstacktrace", "github.com\\jurgen-kluft\\cstacktrace")
	mainlib.Dependencies = append(mainlib.Dependencies, cbasepkg.GetMainLib())

	// 'cstacktrace' unittest project
	maintest := denv.SetupDefaultCppTestProject("cstacktrace"+"_test", "github.com\\jurgen-kluft\\cstacktrace")
	maintest.Dependencies = append(maintest.Dependencies, cunittestpkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, cbasepkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, mainlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddUnittest(maintest)
	return mainpkg
}
