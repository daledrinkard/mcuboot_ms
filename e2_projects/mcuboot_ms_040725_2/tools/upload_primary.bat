copy /Y ..\RA6_primary_L\Bootable\RA6_primary_L.signed.bin bins\primary.bin
rem copy /Y ..\RA6_primary_L\Bootable\RA6_primary_L.bin.signed bins\primary.bin
pause
jlink upload_primary
pause