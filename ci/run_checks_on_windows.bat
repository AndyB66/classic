rem call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" %1

echo -------------------------
echo -------------------------
echo Trying AGAIN
echo -------------------------
echo -------------------------

cd release
rm "*.cpp"
rm "*.obj"
echo -------------------------
dir /n
echo -------------------------
fotorelacjonusz.exe -v
