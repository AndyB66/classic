call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" %1

echo -------------
echo -------------
echo Building Zlib
echo -------------
echo -------------
pushd third-party\zlib-1.2.11 || goto :fail
if "%VCVARS%"=="x64" ( nmake -f win32/Makefile.msc AS=ml64 LOC="-DASMV -DASMINF -I." OBJA="inffasx64.obj gvmat64.obj inffas8664.obj" )
if "%VCVARS%"=="x86" ( nmake -f win32/Makefile.msc LOC="-DASMV -DASMINF" OBJA="inffas32.obj match686.obj" )
popd

echo --------------
echo --------------
echo Building QtFtp
echo --------------
echo --------------
pushd third-party\qtftp\src || goto :fail
qmake CONFIG+=staticlib CONFIG+=c++11 CONFIG+=release || goto :fail
nmake || goto :fail
popd

echo ---------------
echo ---------------
echo Building QuaZIP
echo ---------------
echo ---------------
pushd third-party\quazip\quazip || goto :fail
qmake CONFIG+=staticlib CONFIG+=c++11 CONFIG+=release INCLUDEPATH+=$$PWD\..\..\zlib-1.2.11 || goto :fail
nmake || goto :fail
popd

echo ------------------------
echo ------------------------
echo Building Fotorelacjonusz
echo ------------------------
echo ------------------------
lrelease fotorelacjonusz.pro || goto :fail
qmake DEFINES+=QUAZIP_STATIC CONFIG+=release CONFIG+=c++11 INCLUDEPATH+=$$PWD\third-party\zlib-1.2.11 LIBS+="$$PWD\third-party\zlib-1.2.11\zlib.lib" LIBS+="$$PWD\third-party\qtftp\lib\Qt5Ftp.lib" LIBS+="$$PWD\third-party\quazip\quazip\release\quazip.lib" || goto :fail
nmake || goto :fail

echo -------------------------
echo -------------------------
echo Deploying Fotorelacjonusz
echo -------------------------
echo -------------------------
windeployqt --compiler-runtime --verbose 2 release\fotorelacjonusz.exe

goto :eof

:fail
echo Something went wrong.
exit /b 1
