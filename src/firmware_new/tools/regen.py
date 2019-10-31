"""
Generate a script that can be used by STM32CubeMX command line interface. And
generate STM32CubeMX code accordingy.
"""
import sys
import os
import subprocess
import argparse
from rules_python.python.runfiles import runfiles


CUBE_SCRIPT = '''\
###############################################################################
# This file is auto-generated. DO NOT MODIFY!
#
# Note: The paths in this files are relative to the where the STM32CubeMX is
#       invoked, rather than relative to where this .script file is.
###############################################################################
# Load the project-specific config file (.ioc)
config load {ioc}

# Generate the peripheral initializations in main.c
project couplefilesbyip 0

# Generate code in the project direcotry
generate code {codegen_dir}

# Exit the program
exit
'''


def generate_cubemx_code(cpu, ioc, codegen_dir, cubemx):
    """Generate STM32CubeMX code
    
    @param cpu: Name of the board
    @param ioc: Path to .ioc file
    @param codegen_dir: Directory in which STM32CubeMX code is to be generated
    @param cubemx: Path to STM32CubeMX binary
    """
    r = runfiles.Create()
    env = {}
    env.update(r.EnvVars())
    p = subprocess.Popen([r.Rlocation("path/to/binary")], env, ...)


if __name__ == '__main__':
    with open("__main__/external/cubemx/test"
    with open("/home/akhil/thunderbots/Software/src/firmware_new/boards/frankie_v1/testfile", "+w") as fle:
        fle.write("TESTING")

    print(sys.argv)
    r = runfiles.Create()
    env = {}
    env.update(r.EnvVars())
    print(env)
    print(r.Rlocation("__main__/external/cubemx/STM32CubeMX"))
    # generate_cubemx_code(args.board, args.ioc, args.output_dir, args.cube_bin)
