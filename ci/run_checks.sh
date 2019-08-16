#!/bin/bash

set -e

echo "Running basic checks"

case "${TRAVIS_OS_NAME}" in
	osx)
		open ./Fotorelacjonusz.app --args -v
		;;

	linux)
		docker run -it ${DOCKER_IMAGE} /build/fotorelacjonusz -v
		;;

	windows)
		echo "---"
		ls release
		echo "---"
		ls "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build"
		echo "---"
		ci/run_checks_on_windows.bat ${VCVARS}
		;;
esac
