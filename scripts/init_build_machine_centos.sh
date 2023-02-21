dnf install epel-release -y
dnf config-manager --set-enabled powertools -y
dnf localinstall --nogpgcheck https://download1.rpmfusion.org/free/el/rpmfusion-free-release-8.noarch.rpm -y
dnf update -y
dnf install cmake gcc-c++ cairo-devel doxygen libXext-devel ffmpeg-devel protobuf-devel protobuf-compiler gtk3-devel -y
dnf -y install gcc-toolset-9-gcc gcc-toolset-9-gcc-c++
source /opt/rh/gcc-toolset-9/enable
export CI=YES
dnf install doxygen plantuml ImageMagick -y