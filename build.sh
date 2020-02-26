#!/bin/bash

set -e

BASEDIR=$(dirname $0)
JOBS=$(grep -c ^processor /proc/cpuinfo)
MAKEFLAGS=" -j${JOBS} -l${JOBS}"
CMAKE_OPTIONS=""
GOOGLE_CPPLINT_PY=$BASEDIR/scripts/cpplint.py

# for printing colored text
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
BOLD='\033[1m'
NONE='\033[0m'

function clean() {
  if [ -d build ]; then
    rm -r build
  fi
  if [ -d output ]; then
    rm -r output
  fi
  echo -e "\n${BLUE}build & output removed.${NONE}"
}

function run_cmake() {
  echo -e "\n${BLUE}Run cmake ...${NONE}"
  if [ ! -d build ]; then
    mkdir -p build
  fi
  cd build && cmake .. ${CMAKE_OPTIONS}
  cd -
}

function run_build() {
  if [ ! -d build ]; then
    run_cmake
  fi
  echo -e "\n${BLUE}Start compiling ...${NONE}"
  cd build && make ${MAKEFLAGS}
  cd -
}

function run_lint() {
  set +e
  echo -e "\n${BLUE}Run google c++ style checking:${NONE}"
  find $BASEDIR/ \( -type d -name ".git" -o -type d -name "build" \) -prune -o -print \
    | grep -e '\.h$' -e '\.hpp$' -e '\.cc$' -e '\.cpp$' -e '\.cxx$' -e '\.cu$' -e '\.cuh$' \
    | xargs python $GOOGLE_CPPLINT_PY

  if [ $? -ne 0 ]; then
    echo -e ""
    echo -e "${RED}*** Please fix the code style errors before compiling!${NONE}"
    exit 1
  fi
  echo -e "\n${GREEN}Your code style looks good!${NONE}"
  set -e
}

function run_unittest() {
  cd build
  make test
  if [ $? -ne 0 ]; then
    cd -
    return 1
  fi
  cd -
}

function print_usage() {
  echo -e "\n${GREEN}Usage${NONE}:
  .${BOLD}/build.sh${NONE} [OPTION]"
  echo -e "\n${GREEN}Options${NONE}:
  ${BLUE}all${NONE}:     clean all and build
  ${BLUE}partial${NONE}: incremental build
  ${BLUE}lint${NONE}:    check code style
  ${BLUE}clean${NONE}:   clean all
  ${BLUE}test${NONE}:    run unit tests
  ${BLUE}help${NONE}:    print usage
  "
}

function main() {
  local option=$1

  case $option in
    all)
      clean
      run_lint
      run_cmake
      run_build
      ;;
    partial)
      run_build
      ;;
    lint)
      run_lint
      ;;
    clean)
      clean
      ;;
    test)
      run_unittest
      ;;
    help)
      print_usage
      ;;
    *)
      print_usage
      ;;
  esac
}

main $@

