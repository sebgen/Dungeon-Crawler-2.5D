from __future__ import print_function
import glob, os

f = open('emcc_build.bat', 'w')
f.write('mkdir -p webbuild\n')
f.write('rm -r webbuild/*\n')
f.write('emcc ')
f.write('-O3 ')

# Ugly! fix later:
os.chdir("src")
for file in glob.glob("*.cpp"):
    f.write('src/' + file + " ")
for file in glob.glob("**/*.cpp"):
    f.write('src/' + file + " ")
for file in glob.glob("**/**/*.cpp"):
    f.write('src/' + file + " ")
for file in glob.glob("**/**/**/*.cpp"):
    f.write('src/' + file + " ")
for file in glob.glob("**/**/**/**/*.cpp"):
    f.write('src/' + file + " ")

# ALLOW_MEMORY_GROWTH=0 seems to cause a crash with SDL & TTF
f.write('-I include -I src -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s ALLOW_MEMORY_GROWTH=0 -s TOTAL_MEMORY=167772160 --use-preload-plugins --preload-file resources -o webbuild/main.html --std=c++14 -DCHAISCRIPT_NO_THREADS -DCHAISCRIPT_NO_THREADS_WARNING')

f.close() 
