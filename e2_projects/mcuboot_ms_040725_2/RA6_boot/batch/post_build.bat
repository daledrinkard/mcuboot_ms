srec_cat ${BuildArtifactFileBaseName}.srec -crop 0x00000000 0x000D8000 -o ap.srec
srec_cat ${BuildArtifactFileBaseName}.srec -crop 0x60000000 0x607FFFFF -o rs.srec
