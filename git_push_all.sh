#! /bin/bash
#

cat <<EOF

>>> Pushing our work to both remotes...

EOF
for f in GerHobbelt/thirdpart-lcms2 GerHobbelt/Little-CMS ; do 
	echo $f 
	git push --all git@github.com:$f.git
done

# fetch all remote work as an afterthought
cat <<EOF


>>> Fetching all remote work...

EOF
git fetch --all 
