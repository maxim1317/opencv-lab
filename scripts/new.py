#! /home/oberon/anaconda3/bin/python
from termcolor import colored


def get_args():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'project',
        nargs='+',
        type=str,
        help='Project name you want to create'
    )

    args = parser.parse_args()
    return args.project


def mk_structure(name):
    import os

    structure = {
        'root' : name,
        'build': os.path.join(name, 'build')
    }

    for directory in structure.values():
        if not os.path.exists(directory):
            try:
                os.makedirs(directory)
            except OSError as e:
                print(e)
                return False

    return True


def mk_sample(name):
    import os.path

    sample_path = os.path.join(name, name + '.cpp')

    sample = {
        'copyright':
            '// Copyright 2019 SnesarevMS\n'                +
            '\n',

        'includes' :
            '#include "opencv2/opencv.hpp"\n'               +
            '#include "opencv2/highgui/highgui.hpp"\n'      +
            '\n',

        'namespace':
            'using namespace cv;\n'                         +
            '\n',

        'main':
            'int main(int argc, char** argv) {\n'           +
            '    // create a gui window:\n'                 +
            '    namedWindow("Output", 1);\n'               +
            '\n'                                            +
            '    // wait for the user to press any key:\n'  +
            '    waitKey(0);\n'                             +
            '\n'                                            +
            '    return 0;\n'                               +
            '}'                                             +
            '\n'
    }

    try:
        with open(sample_path, 'w+') as file:
            for part in sample.values():
                file.write(part)
    except EnvironmentError:
        return False

    return True


def mk_cmake(name):
    import os.path

    cmake_path = os.path.join(name, 'CMakeLists.txt')

    cmake = {
        'version':
            'cmake_minimum_required(VERSION 3.13)\n'                        +
            '\n',

        'project':
            'project(' + name + ')\n'                                       +
            '\n',

        'opencv':
            'find_package(OpenCV REQUIRED)\n'                               +
            '\n'
            'message("opencv version: " ${OpenCV_VERSION})\n'               +
            '\n'
            'include_directories(${OpenCV_INCLUDE_DIRS})\n'                 +
            '\n',

        'executable': 'add_executable(' + name + '.o ' + name + '.cpp)\n'   +
            '\n',

        'links':
            'target_link_libraries(' + name + '.o ${OpenCV_LIBS})\n'        +
            '\n',

        'run':
            'add_custom_target(run\n'                                       +
            '    COMMAND ' + name + '.o\n'                                  +
            '    DEPENDS ' + name + '.o\n'                                  +
            '    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}\n'                  +
            ')'                                                             +
            '\n',
    }

    try:
        with open(cmake_path, 'w+') as file:
            for part in cmake.values():
                file.write(part)
    except EnvironmentError:
        return False

    return True


def call_run(project):
    import subprocess

    return subprocess.call(['./run ' + project], shell=True)


def main():
    steps = {
        0: {
            'Function'   : mk_structure,
            'Description': ' Preparing project ' + colored('structure', color='yellow') + '...'
        },
        1: {
            'Function'   : mk_sample,
            'Description': ' Generating ' + colored('template', color='yellow') + '...'
        },
        2: {
            'Function'   : mk_cmake,
            'Description': ' Generating ' + colored('CMakeLists.txt', color='yellow') + ' file' + '...'
        }
    }

    projects = get_args()

    for project in projects:
        print()
        print(' Setting up ' + colored(project, color='yellow') + '...')
        print()

        for step in steps.values():
            out  = step['Description']
            wait = ((50 - len(out)) * " " + "[" + colored("  WAIT  ", 'yellow') + "]\n")
            ok   = ((50 - len(out)) * " " + "[" + colored("   OK   ", 'green') + "]\n")
            fail = ((50 - len(out)) * " " + "[" + colored(" FAILED ", 'red') + "]\n")

            print(out, end=wait)
            if step['Function'](project):
                print(out, end=ok)
                print()
            else:
                print(out, end=fail)
                print()
                break

        call_run(projects[len(projects) - 1])

    return


if __name__ == '__main__':
    main()
