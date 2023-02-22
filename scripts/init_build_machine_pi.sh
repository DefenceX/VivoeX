sudo apt install bzip2 bison flex gperf automake texinfo libtool libtool-bin help2man libncurses5-dev

mkdir -p  ~/src/RaspberryPi/toolchain
cd ~/src/RaspberryPi/toolchain
wget -nc http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.25.0.tar.bz2
tar xjf crosstool-ng-1.25.0.tar.bz2
cd crosstool-ng-1.25.0

# We chose to configure the tool to be installed in a local directory inside our home directory.
mkdir -p ~/local/crosstool-ng
./configure --prefix=${HOME}/local/crosstool-ng
make 
make install