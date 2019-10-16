attrib -S -H *.suo
del /S /Q *.suo

del /S /Q *.ncb

del /S /Q *.aps

del /s /Q *cache.dat
del /s /Q *.ilk
del /s /Q *.pdb
del /s /Q BuildLog.htm
del /s /Q *.obj
del /s /Q mt.dep
del /s /Q *.manifest
del /s /Q *.res
del /s /Q *.pch
del /s /Q *.idb

RD /S /Q debug
RD /S /Q release

RD /S /Q Autotext
RD /S /Q Dict
RD /S /Q Misc
