#!/bin/sh -xe

echo !doxy.sh!
echo !doxy.sh! building doxygen
( cat Doxyfile ; echo "PROJECT_NUMBER=ItchyPlusPlus-BUILD-ID-${BUILD_ID}"; echo "INPUT=${workspace}"; echo "OUTPUT_DIRECTORY=/doxy/gen/ItchyPlusPlus-BUILD-ID-${BUILD_ID}" ) | doxygen -
ESTATUS=$?
echo !doxy.sh! doxygen - finished exiting with error code $ESTATUS
exit $ESTATUS