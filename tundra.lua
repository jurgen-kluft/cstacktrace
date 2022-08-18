local GlobExtension = require("tundra.syntax.glob")
Build {
	ReplaceEnv = {
		OBJECTROOT = "target",
	},
	Env = {
		CPPDEFS = {
			{ "TARGET_PC_DEV_DEBUG", "TARGET_PC", "PLATFORM_64BIT"; Config = "win64-*-debug-dev" },
			{ "TARGET_PC_DEV_RELEASE", "TARGET_PC", "PLATFORM_64BIT"; Config = "win64-*-release-dev" },
			{ "TARGET_PC_TEST_DEBUG", "TARGET_PC", "PLATFORM_64BIT"; Config = "win64-*-debug-test" },
			{ "TARGET_PC_TEST_RELEASE", "TARGET_PC", "PLATFORM_64BIT"; Config = "win64-*-release-test" },
			{ "TARGET_MAC_DEV_DEBUG", "TARGET_MAC", "PLATFORM_64BIT"; Config = "macosx-*-debug-dev" },
			{ "TARGET_MAC_DEV_RELEASE", "TARGET_MAC", "PLATFORM_64BIT"; Config = "macosx-*-release-dev" },
			{ "TARGET_MAC_TEST_DEBUG", "TARGET_MAC", "PLATFORM_64BIT"; Config = "macosx-*-debug-test" },
			{ "TARGET_MAC_TEST_RELEASE", "TARGET_MAC", "PLATFORM_64BIT"; Config = "macosx-*-release-test" },
		},
	},
	Units = function ()
		-- Recursively globs for source files relevant to current build-id
		local function SourceGlob(dir)
			return FGlob {
				Dir = dir,
				Extensions = { ".c", ".cpp", ".s", ".asm" },
				Filters = {
					{ Pattern = "_win32"; Config = "win64-*-*" },
					{ Pattern = "_mac"; Config = "macosx-*-*" },
					{ Pattern = "_test"; Config = "*-*-*-test" },
				}
			}
		end
		local xunittest_library = StaticLibrary {
			Name = "cunittest",
			Config = "*-*-*-test",
			Sources = { SourceGlob("../cunittest/source/main/cpp") },
			Includes = { "..//cunittest/source/main/include" },
		}
		local xentry_library = StaticLibrary {
			Name = "centry",
			Config = "*-*-*-*",
			Sources = { SourceGlob("../centry/source/main/cpp") },
			Includes = { "..//centry/source/main/include" },
		}
		local xbase_library = StaticLibrary {
			Name = "cbase",
			Config = "*-*-*-*",
			Sources = { SourceGlob("../cbase/source/main/cpp") },
			Includes = { "..//cbase/source/main/include","..//cunittest/source/main/include" },
		}
		local xhash_library = StaticLibrary {
			Name = "xhash",
			Config = "*-*-*-*",
			Sources = { SourceGlob("source/main/cpp") },
			Includes = { "..//xhash/source/main/include","..//cbase/source/main/include" },
		}
		local unittest = Program {
			Name = "xhash_test",
			Config = "*-*-*-test",
			Sources = { SourceGlob("source/test/cpp") },
			Includes = { "source/main/include","source/test/include","..//cunittest/source/main/include","..//centry/source/main/include","..//cbase/source/main/include","..//xhash/source/main/include" },
			Depends = { xunittest_library,xentry_library,xbase_library,xhash_library },
		}
		Default(unittest)
	end,
	Configs = {
		Config {
			Name = "macosx-clang",
			Env = {
			PROGOPTS = { "-lc++" },
			CXXOPTS = {
				"-std=c++11",
				"-arch x86_64",
				"-Wno-new-returns-null",
				"-Wno-missing-braces",
				"-Wno-unused-function",
				"-Wno-unused-variable",
				"-Wno-unused-result",
				"-Wno-write-strings",
				"-Wno-c++11-compat-deprecated-writable-strings",
				"-Wno-null-dereference",
				"-Wno-format",
				"-fno-strict-aliasing",
				"-fno-omit-frame-pointer",
			},
		},
		DefaultOnHost = "macosx",
		Tools = { "clang" },
		},
		Config {
			ReplaceEnv = {
				OBJECTROOT = "target",
			},
			Name = "linux-gcc",
			DefaultOnHost = "linux",
			Tools = { "gcc" },
		},
		Config {
			ReplaceEnv = {
				OBJECTROOT = "target",
			},
			Name = "win64-msvc",
			Env = {
				PROGOPTS = { "/SUBSYSTEM:CONSOLE" },
				CXXOPTS = { },
			},
			DefaultOnHost = "windows",
			Tools = { "msvc-vs2017" },
		},
	},
	SubVariants = { "dev", "test" },
}
