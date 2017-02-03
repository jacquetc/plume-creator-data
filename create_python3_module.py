#!/usr/bin/python3
from shutil import copyfile, copytree, ignore_patterns, rmtree
import os
import time
from subprocess import call


DESTDIR = "../lib/"

# list all *.h

#file_list = []
#for root, dirs, files in os.walk("./src"):
#    for file in files:
#        if file.endswith(".h"):
#            file_list.append(os.path.join(root, file))

#config_list = []




# pre clean up
try:
    rmtree(DESTDIR)
except FileNotFoundError:
    pass

#copy :

try:
    copytree(src="./src", dst=DESTDIR, symlinks=False)
except FileExistsError:
    pass




config_list = []
for file in os.listdir("./python"):
    if file.endswith(".py") or file.endswith(".sip"):
        config_list.append(file)
				

for file in config_list:
	copyfile(os.path.join("./python",file), os.path.join(DESTDIR,file))


# build the library
os.chdir(DESTDIR)

call(["qmake"])
call(["make", "-j"])

# build SIP :

os.chdir(DESTDIR)

for file in config_list:
    if file.endswith(".sip"):
        basename = file.split('.')[0]
        call(['python3', os.path.join(DESTDIR, "configure.py"), basename])
        call(["make", "-j"])

# clean up

os.chdir(DESTDIR)
import glob


# get list of files that match
cleanupFiles = glob.glob("./*")
to_be_ignored = glob.glob("./*.so")
to_be_ignored += glob.glob("./*plume-creator-data*")
print(to_be_ignored)
for file in to_be_ignored:
    try:
        cleanupFiles.remove(file)
    except ValueError as error:
        pass
for cleanupFile in cleanupFiles:
    if os.path.isdir(cleanupFile):
        rmtree(cleanupFile, ignore_errors=True)
        continue
    os.remove(cleanupFile)




# move build files :
python_modules = glob.glob("*.so")
libs = glob.glob("*plume-creator-data*")


#for file in python_modules:
#    print(home)
#    os.makedirs(os.path.join( home,"/.local/lib/"), exist_ok=True)
#    copyfile(file, os.path.join("~/.local/lib/", file),  follow_symlinks=False)

