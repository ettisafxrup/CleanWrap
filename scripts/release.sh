readonly VERSION_HEADER="../include/Version.hpp"
readonly VERSION="v$(sed -n 's/^#define CLEANWRAP_VERSION "\(.*\)"/\1/p' "$VERSION_HEADER")"

if [ $# -eq 1 ]; then
    ./compile.sh 1
else
    ./compile.sh 
fi



# IF NOT PUSHED YET, PUSH THE FILE TO THE GITHUB REPO
git add .
git commit -m "release: prepare release $VERSION"
git push origin main

git tag "$VERSION"
git push origin "$VERSION" 