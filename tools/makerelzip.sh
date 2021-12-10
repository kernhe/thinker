#!/bin/sh

ZIP="rel/Thinker-rel-$(date '+%Y%m%d').zip"
if [ -e "patch/thinker.dll" ]; then
  if ! [ -e $ZIP ]; then
    mkdir -p build/tmp
    cd build/tmp
    cp -f ../../patch/{thinker.exe,thinker.dll} .
    cp -f ../../{Readme,Details,Changelog}.md .
    cp -fr ../../docs/* .
    7z a -mx9 -sdel ../../$ZIP .
  fi
fi
