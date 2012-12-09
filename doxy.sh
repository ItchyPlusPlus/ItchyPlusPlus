echo !doxy.sh!
echo !doxy.sh! ( cat Doxyfile ; echo "PROJECT_NUMBER=ItchyPlusPlus-BUILD-ID-${BUILD_ID}" ) | doxygen -
( cat Doxyfile ; echo "PROJECT_NUMBER=ItchyPlusPlus-BUILD-ID-${BUILD_ID}" ) | doxygen -
ESTATUS=$?
echo !doxy.sh! make - finished exiting with error code $ESTATUS
exit $ESTATUS