echo !build.sh! cd into src/
cd src/
echo !build.sh! make
make
ESTATUS=$?
echo !build.sh! make - finished exiting with error code $ESTATUS
exit $ESTATUS
