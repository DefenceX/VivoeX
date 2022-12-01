#!/bin/bash
index=0
while read line ; do
    lines[$index]="$line"
    index=$(($index+1))
done < ../version
before="${lines[0]}\\.${lines[1]}\\.${lines[2]}"
major=${lines[0]}
minor=${lines[1]}
patch=$((${lines[2]}+1))
after="${lines[0]}\\.${lines[1]}\\.${patch}"
echo "Updated to ${major}.${minor}.${patch}"
sed -i "s/${before}/${after}/g" ../README.md

# Update Sonarcloud
sed -i "s/sonar.projectVersion=\([0-9.]\+\)/sonar.projectVersion=${major}.${minor}.${patch}/g" ../sonar-project.properties

# Update code
sed -i "s/static const uint32_t kSemVerMajor= \([0-9]\+\)/static const uint32_t kSemVerMajor = ${major}/g" ../hmi-display/src/gva.h
sed -i "s/static const uint32_t kSemVerMinor = \([0-9]\+\)/static const uint32_t kSemVerMinor = ${minor}/g" ../hmi-display/src/gva.h
sed -i "s/static const uint32_t kSemVerPatch = \([0-9]\+\)/static const uint32_t kSemVerPatch = ${patch}/g" ../hmi-display/src/gva.h

echo "${lines[0]}" > ../version
echo "${lines[1]}" >> ../version
echo "${patch}" >> ../version
echo "${tweak}" >> ../version