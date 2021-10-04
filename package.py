name = "lcms"

version = "2.12.0"

description = \
    """
    Little CMS intends to be an OPEN SOURCE small-footprint color management engine.
    """

with scope("config") as c:
    # Determine location to release: internal (int) vs external (ext)

    # NOTE: Modify this variable to reflect the current package situation
    release_as = "ext"

    # The `c` variable here is actually rezconfig.py
    # `release_packages_path` is a variable defined inside rezconfig.py

    import os
    if release_as == "int":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_INT"]
    elif release_as == "ext":
        c.release_packages_path = os.environ["SSE_REZ_REPO_RELEASE_EXT"]

    #c.build_thread_count = "physical_cores"

requires = [
    "libtiff",
    "libjpeg",
]

private_build_requires = [
]

variants = [
    ["platform-linux", "arch-x86_64", "os-centos-7"],
]

uuid = "repository.Little-CMS"

def pre_build_commands():
    command("source /opt/rh/devtoolset-6/enable")

def commands():
    env.LCMS_ROOT = "{root}"
    env.LCMS_LOCATION = "{root}"


    env.PATH.prepend("{root}/bin")
