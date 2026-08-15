readonly VERSION="v1.0.1"

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