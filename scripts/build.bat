@echo off

mkdir bin > NUL 2>&1
cl ^
    /Zi ^
    src\*.c ^
    /Fo"bin\\" ^
    /Fe"bin\\main.exe" ^
    /Fd"bin\\main.pdb" ^
    /I"vendor\raylib-5.5_win64_msvc16\include" ^
    /link ^
        /NODEFAULTLIB:LIBCMT ^
        /LIBPATH:"vendor\raylib-5.5_win64_msvc16\lib" ^
            raylib.lib ^
        user32.lib ^
        kernel32.lib ^
        gdi32.lib ^
        ucrt.lib ^
        winmm.lib ^
        shell32.lib
