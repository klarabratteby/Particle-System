#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/klarabratteby/particlesystem/build
  make -f /Users/klarabratteby/particlesystem/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/klarabratteby/particlesystem/build
  make -f /Users/klarabratteby/particlesystem/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/klarabratteby/particlesystem/build
  make -f /Users/klarabratteby/particlesystem/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/klarabratteby/particlesystem/build
  make -f /Users/klarabratteby/particlesystem/build/CMakeScripts/ReRunCMake.make
fi

