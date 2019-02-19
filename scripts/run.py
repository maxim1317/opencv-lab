#! /home/oberon/anaconda3/bin/python
from termcolor import colored


def find(tip, ext='', location='.'):
    '''
        Finds file using glob
        params:
            tip - approximate filename
            ext - file extention
            location - where to search

        returns abspath if found anything and 0 if nothing
    '''
    from glob import glob
    import os.path

    tip = os.path.join(location, '**', tip + '*' + ext)
    files = glob(tip, recursive=True)

    files = [os.path.relpath(f) for f in files]
    # print("Found ", files)

    return files


def get_args():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        'project',
        nargs='?',
        type=str,
        help='Project name you want to run'
    )
    parser.add_argument(
        '-l',
        '--list',
        action='store_true',
        help='List projects'
    )

    try:
        args = parser.parse_args()
    except Exception as e:
        parser.print_help()
        exit()

    if args.list:
        projects = get_projs()
        for p in projects:
            print(p)
        exit()
    elif not args.project:
        parser.print_help()
        exit()

    return args.project


def get_projs(projects=[]):
    if not len(projects):
        projects = get_projs_dirs()
    projects = [split_dirname(p)[1] for p in projects]

    return projects


def split_dirname(project):
    import os.path
    # print(os.path.split(project))
    return os.path.split(project)


def get_projs_dirs():
    import os.path
    projects = find('CMakeLists.txt')
    projects = [os.path.dirname(p) for p in projects]
    return projects


def scan_projs(cur, offset=4):
    import os

    descriptions = {
        0:
            'Looking for ' + colored('projects', 'yellow') + '...',
        1:
            'Getting ' + colored('projects', 'yellow') + ' ready...'
    }

    out  = offset * ' ' + ' ' + descriptions[0]
    wait = ((50 - len(out)) * " " + "[" + colored("  WAIT  ", 'yellow') + "]\n")
    ok   = ((50 - len(out)) * " " + "[" + colored("   OK   ", 'green') + "]\n")

    print(out, end=wait)
    proj_dirs = get_projs_dirs()
    print(out, end=ok)
    print()

    projects = []
    names    = []

    for p in proj_dirs:
        dir, name = split_dirname(p)
        pr = {
            'dir'      : p,
            'build_dir': os.path.join(p, 'build'),
            'name'     : name,
            'built'    : False,
            'made'     : False
        }
        names.append(name)
        projects.append(pr.copy())

    if cur not in names:
        print(' Project ' + colored(cur, 'red') + ' does not exist!')
        print()
        exit(1)

    # print(projects)
    out  = offset * ' ' + ' ' + descriptions[1]
    wait = ((50 - len(out)) * " " + "[" + colored("  WAIT  ", 'yellow') + "]\n")
    ok   = ((50 - len(out)) * " " + "[" + colored("   OK   ", 'green') + "]\n")

    print(out, end=wait)
    print()

    for p in projects:
        pprint = 2 * offset * ' ' + ' ' + 'Checking ' + colored(p['name'], 'magenta')
        pwait  = ((50 - len(pprint)) * " " + "[" + colored("  WAIT  ", 'yellow') + "]\n")
        pok    = ((50 - len(pprint)) * " " + "[" + colored("   OK   ", 'green') + "]\n")

        print(pprint, end=pwait)

        if not len(find('build', location=p['dir'])):
            print(3 * offset * ' ' + ' ' + 'Restoring ' + colored('structure', 'yellow'))
            os.makedirs(p['build_dir'])
        if not len(find('Makefile', location=p['build_dir'])):
            print(3 * offset * ' ' + ' ' + 'Generating ' + colored('Makefile', 'yellow'))
            success = 0
            if build(p['build_dir']) == success:
                p['built'] = True
        if not len(find(p['name'], ext='.o', location=p['build_dir'])):
            print(3 * offset * ' ' + ' ' + 'Building ' + colored('project', 'yellow'))
            success = 0
            if make(p['build_dir']) == success:
                p['made'] = True

        print(3 * offset * ' ' + ' ' + 'Generating ' + colored('upper Makefile', 'yellow'))
        mk_make(p['dir'])

        print(pprint, end=pok)
        print()

    print(out, end=ok)

    return projects


def mk_structure(name):
    import os

    structure = {
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


def build(build_dir):
    import subprocess

    return subprocess.call(['cmake ..'], shell=True, cwd=build_dir)


def make(build_dir):
    import subprocess

    return subprocess.call(['make'], shell=True, cwd=build_dir)


def mk_make(dir):
    import os.path

    sample = {
        'all':
            'all: build\n'                          +
            '\n',
        'build':
            'build:\n'                                +
            '\t@-make -s -C ' + 'build' + '\n'           +
            '\n',
        'run':
            'run:\n'                                +
            '\t@-make -s -C ' + 'build' + ' run' + '\n'
    }

    try:
        with open(os.path.join(dir, 'Makefile'), 'w+') as file:
            for part in sample.values():
                file.write(part)
    except EnvironmentError:
        return False

    return True


def mk_root_make(cur, projects):

    mf = {
        'all':
            'all: ' + cur + '_run\n' +
            '\n'
    }

    for p in projects:
        build_tg =                                        \
            p['name'] + ':\n'                           + \
            '\t@-make -s -C ' + p['dir'] + '\n'              + \
            '\n'
        run_tg   =                                        \
            p['name'] + '_run' + ':\n'                  + \
            '\t@-make -s -C ' + p['dir'] + ' run' + '\n'
        phony    =                                        \
            '.PHONY: ' + p['name'] + '_run' + '\n'      + \
            '\n'

        mf[p['name']] = build_tg + run_tg + phony

    try:
        with open('Makefile', 'w+') as file:
            for part in mf.values():
                file.write(part)
    except EnvironmentError:
        return False

    return True


def main():
    cur = get_args()

    descriptions = {
        0:
            colored('Scanning projects', 'yellow'),
        1:
            colored('Generating Makefile in root directory', 'yellow')
    }

    out  = ' ' + descriptions[0]
    wait = ((50 - len(out)) * " " + "[" + colored("  WAIT  ", 'yellow') + "]\n")
    ok   = ((50 - len(out)) * " " + "[" + colored("   OK   ", 'green') + "]\n")

    print()
    print(out, end=wait)
    projects = scan_projs(cur)
    print(out, end=ok)

    out  = ' ' + descriptions[1]
    wait = ((50 - len(out)) * " " + "[" + colored("  WAIT  ", 'yellow') + "]\n")
    ok   = ((50 - len(out)) * " " + "[" + colored("   OK   ", 'green') + "]\n")

    print()
    print(out, end=wait)
    mk_root_make(cur, projects)
    print(out, end=ok)
    print()
    return 0


if __name__ == '__main__':
    main()
