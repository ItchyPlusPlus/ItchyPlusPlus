echo !build.sh! make clean
make clean
echo !build.sh! make
make
ESTATUS=$?
echo !build.sh! make - finished exiting with error code $ESTATUS
exit $ESTATUS
