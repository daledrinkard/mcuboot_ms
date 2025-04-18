srec_cat %2.srec -crop 0x00020000 0x00060000 -offset -0x00020200 -o ap.bin -binary
srec_cat %2.srec -crop 0x60000000 0x607FFFFF -offset -0x60000000 -o rs.bin -binary
pause
python %1\ra\fsp\src\rm_mcuboot_port\rm_mcuboot_port_sign.py  sign --header-size 0x200 --align 128 --max-align 128 --slot-size 0x40000 --max-sectors 8  --pad --pad-header ap.bin ap.bin.signed
python %1\ra\fsp\src\rm_mcuboot_port\rm_mcuboot_port_sign.py sign --header-size 0x200 --align 128 --max-align 128 --slot-size 0x100000 --max-sectors 32  --pad --pad-header rs.bin rs.bin.signed
copy /B /Y ap.bin.signed + rs.bin.signed %2.signed.bin

