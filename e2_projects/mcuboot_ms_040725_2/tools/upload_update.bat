copy /Y ..\RA6_update_L\Bootable\RA6_update_L.signed.bin bins\update.bin
rem copy /Y ..\RA6_primary_L\Bootable\RA6_primary_L.bin.signed bins\primary.bin
pause
jlink upload_update
pause