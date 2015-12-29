#!/bin/bash

# Set CFLAGS to be strict for supported versions on Travis
# Even if all versions can be compiled strictly now, it is possible that
# someone will break something, and this 

# Bash return statements are not useful. You have to echo the value
# and then capture it by calling the function with $( foo )
function contains() {
    local n=$#
    local value=${!n}
    for ((i=1;i < $#;i++)) {
        if [ "${!i}" == "${value}" ]; then
            echo "1"
            return 0
        fi
    }
    echo "0"
    return 0
}

strictPHPVersions=()
strictPHPVersions+=("5.6")
strictPHPVersions+=("7")

strictGraphicsMagickVersions=()
strictGraphicsMagickVersions+=("dev")
strictGraphicsMagickVersions+=("1.3.23")
strictGraphicsMagickVersions+=("1.3.22")
strictGraphicsMagickVersions+=("1.3.19")
strictGraphicsMagickVersions+=("1.3.17")


echo "TRAVIS_PHP_VERSION is ${TRAVIS_PHP_VERSION}"
echo "GRAPHICSMAGICK_VERSION is ${GRAPHICSMAGICK_VERSION}"

strictGraphicsMagick=$(contains "${strictGraphicsMagickVersions[@]}" "${GraphicsMAGICK_VERSION}" )
strictPHP=$(contains "${strictPHPVersions[@]}" "${TRAVIS_PHP_VERSION}" )

echo "strictGraphicsMagick is ${strictGraphicsMagick}"
echo "strictPHP is ${strictPHP}"

if [[ $strictPHP = '1' ]] && [[ $strictGraphicsMagick = '1' ]]; then 
	CFLAGS="-Wno-deprecated-declarations -Wdeclaration-after-statement -Werror -Wall"; 
else 
	CFLAGS="-Wno-deprecated-declarations";
fi

echo "Setting CFLAGS to ${CFLAGS}"

export CFLAGS=$CFLAGS