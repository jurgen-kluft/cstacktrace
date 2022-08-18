package cstacktrace

import (
	cbase "github.com/jurgen-kluft/cbase/package"
	"github.com/jurgen-kluft/ccode/denv"
	centry "github.com/jurgen-kluft/centry/package"
	cunittest "github.com/jurgen-kluft/cunittest/package"
)

// GetPackage returns the package object of 'cstacktrace'
func GetPackage() *denv.Package {
	// Dependencies
	cunittestpkg := cunittest.GetPackage()
	centrypkg := centry.GetPackage()
	cbasepkg := cbase.GetPackage()

	// The main (cstacktrace) package
	mainpkg := denv.NewPackage("cstacktrace")
	mainpkg.AddPackage(cunittestpkg)
	mainpkg.AddPackage(centrypkg)
	mainpkg.AddPackage(cbasepkg)

	// 'cstacktrace' library
	mainlib := denv.SetupDefaultCppLibProject("cstacktrace", "github.com\\jurgen-kluft\\cstacktrace")
	mainlib.Dependencies = append(mainlib.Dependencies, cbasepkg.GetMainLib())

	// 'cstacktrace' unittest project
	maintest := denv.SetupDefaultCppTestProject("cstacktrace_test", "github.com\\jurgen-kluft\\cstacktrace")
	maintest.Dependencies = append(maintest.Dependencies, cunittestpkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, centrypkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, cbasepkg.GetMainLib())
	maintest.Dependencies = append(maintest.Dependencies, mainlib)

	mainpkg.AddMainLib(mainlib)
	mainpkg.AddUnittest(maintest)
	return mainpkg
}
