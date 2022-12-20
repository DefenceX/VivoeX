#!/usr/bin/bash -e
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

apt install protobuf-compiler qtpositioning5-dev libqt5svg5-dev qttools5-dev unzip -y
wget -nc https://osmdata.openstreetmap.de/download/coastlines-split-4326.zip

# Unzip if directory dows not already exist
if [ ! -d "coastlines-split-4326" ]; then
  unzip ./coastlines-split-4326
  cp ./coastlines-split-4326/lines.shp ./coastlines.shp
fi


apt autoremove

mkdir -p ./downloads
cd ./downloads

# England
if [ ! -f "england-latest.osm.pbf" ]; then
  wget -nc https://download.geofabrik.de/europe/great-britain/england-latest.osm.pbf
fi
if [ ! -f "england.poly" ]; then
  wget -nc https://download.geofabrik.de/europe/great-britain/england.poly
fi
echo "England OK..."

# Germany
if [ ! -f "germany-latest.osm.pbf" ]; then
  wget -nc https://download.geofabrik.de/europe/germany-latest.osm.pbf
fi
if [ ! -f "germany.poly" ]; then
  wget -nc https://download.geofabrik.de/europe/germany.poly
fi
echo "Germany OK..."

# Australia
if [ ! -f "australia-latest.osm.pbf" ]; then
  wget -nc https://download.geofabrik.de/australia-oceania/australia-latest.osm.pbf
fi
if [ ! -f "australia.poly" ]; then
  wget -nc https://download.geofabrik.de/australia-oceania/australia.poly
fi
echo "Australia OK..."

echo "Map files ready.."
cd -

if [ ! -f "world/water.idx" ]; then
  mkdir -p world 
  ../../build/external/install/usr/local/bin/BasemapImport --destinationDirectory world --coastlines ./coastlines.shp
fi

cd ./downloads
mkdir -p archives
OSM_BASE=../../../build/external/libosmscout


if [ ! -d "england-latest" ]; then
mkdir -p england-latest 
cp ../world ./england-latest/. -rf
cp ../coastlines.shp ./england-latest/.
$OSM_BASE/build/Import/Import  \
    --typefile $OSM_BASE/src/stylesheets/map.ost \
    --destinationDirectory england-latest \
    --bounding-polygon england.poly\
    england-latest.osm.pbf 
tar -zcvf england-latest.tar.gz england-latest
mv england-latest.tar.gz ./archives
fi 

if [ ! -d "germany-latest" ]; then
mkdir -p germany-latest
cp ../world ./germany-latest/. -rf
cp ../coastlines.shp ./germany-latest/.
$OSM_BASE/build/Import/Import  \
    --typefile $OSM_BASE/src/stylesheets/map.ost \
    --destinationDirectory germany-latest \
    --bounding-polygon germany.poly\
    germany-latest.osm.pbf 
tar -zcvf germany-latest.tar.gz germany-latest
mv germany-latest.tar.gz ./archives
rm -rf germany-latest
fi

if [ ! -d "australia-latest" ]; then
mkdir -p australia-latest
cp ../world ./australia-latest/. -rf
cp ../coastlines.shp ./australia-latest/.
$OSM_BASE/build/Import/Import  \
    --typefile $OSM_BASE/src/stylesheets/map.ost \
    --destinationDirectory australia-latest \
    --bounding-polygon australia.poly\
    australia-latest.osm.pbf 
tar -zcvf australia-latest.tar.gz australia-latest
mv australia-latest.tar.gz ./archives
rm -rf australia-latest
fi

echo "All done OK..."
