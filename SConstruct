#!/usr/bin/env python
import os
import sys
from os import path
from methods import print_error
import shutil


libname = "pyGodot"
libuid = "c0bljng070vo4"
entry_symbol = "example_library_init"
compatibility = "4.1"

buildir = "bin"
projectdir = "demo"

localEnv = Environment(tools=["default"], PLATFORM="")

# Build profiles can be used to decrease compile times.
# You can either specify "disabled_classes", OR
# explicitly specify "enabled_classes" which disables all other classes.
# Modify the example file as needed and uncomment the line below or
# manually specify the build_profile parameter when running SCons.

# localEnv["build_profile"] = "build_profile.json"

customs = ["custom.py"]
customs = [os.path.abspath(path) for path in customs]

opts = Variables(customs, ARGUMENTS)
opts.Update(localEnv)

Help(opts.GenerateHelpText(localEnv))

env = localEnv.Clone()

if not (os.path.isdir("godot-cpp") and os.listdir("godot-cpp")):
    print_error("""godot-cpp is not available within this folder, as Git submodules haven't been initialized.
Run the following command to download godot-cpp:

    git submodule update --init --recursive""")
    sys.exit(1)

env = SConscript("godot-cpp/SConstruct", {"env": env, "customs": customs})


# Python include
env.Append(CPPPATH=[path.join("python312", "include")])
env.Append(CPPPATH=[path.join("pybind11", "include")])
env.Append(LIBPATH=[path.join("python312", "libs")])
env.Append(LINKFLAGS=["python3.lib", "python312.lib"])

env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

# .dev doesn't inhibit compatibility, so we don't need to key it.
# .universal just means "compatible with all relevant arches" so we don't need to key it.
suffix = env['suffix'].replace(".dev", "").replace(".universal", "")

lib_filename = "{}{}{}{}".format(env.subst('$SHLIBPREFIX'), libname, suffix, env.subst('$SHLIBSUFFIX'))
lib_platform_path = "{}/{}".format(env['platform'], lib_filename)
lib_path = f"{buildir}/{lib_platform_path}"
library = env.SharedLibrary(
    lib_path,
    source=sources,
)

copy = env.Install("{}/{}/{}/".format(projectdir, buildir, env["platform"]), library)


# Create gdextension file and gdextension.uid file
gdextension_file = path.join(buildir, "{}.gdextension".format(libname))
gdextension_uid_file = path.join(buildir, "{}.gdextension.uid".format(libname))

# Write to the gdextension file
with open(gdextension_file, 'w', encoding='utf-8') as f:
    f.write("[configuration]\n\n")
    f.write(f"entry_symbol = \"{entry_symbol}\"\n")
    f.write(f"compatibility_minimum = \"{compatibility}\"\n\n")
    f.write("[libraries]\n")

    f.write(f"windows.x86_64.single.debug = \"./{lib_platform_path}\"\n")
    f.write(f"windows.x86_64.single.release = \"./{lib_platform_path}\"")

# Write to the gdextension.uid file
with open(gdextension_uid_file, 'w') as f:
    f.write(f"uid://{libuid}\n")  # Replace with a unique identifier or generate one dynamically

shutil.copy(gdextension_file, path.join(projectdir, gdextension_file))
shutil.copy(gdextension_uid_file, path.join(projectdir, gdextension_uid_file))

default_args = [library, copy]
Default(*default_args)
