#! /bin/bash


ROOT_DIR="/opt/gardener"
FILES_DIR=$"${ROOT_DIR}/files"
BIN_DIR="${ROOT_DIR}/bin"


echo "Installing gardeners monitor..."
if [ ! -d "$ROOT_DIR" ]; then
echo $"Creating var/lib folder"
  mkdir "$ROOT_DIR"
else
  echo $"Directory already exists. If you want a clean install try to first use the uninstaller"
  echo -n "Aborting installation..."
  echo "Done"
  exit 0
fi


echo -n $"Creating base folder: ${FILES_DIR}..."
mkdir "$FILES_DIR"
echo "Done"
echo -n $"Creating binary folder: ${BIN_DIR}..."
mkdir "$BIN_DIR"
echo "Done"
echo -n "Copying db to dest directory..."
cp gardener_db.sqlite "$FILES_DIR"
echo "Done"

echo -n "Copying required binaries..."
cp cmake-build-release/gardener $BIN_DIR
echo "Done"





echo "Installation done"




