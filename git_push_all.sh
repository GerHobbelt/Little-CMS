#! /bin/bash
#

cat <<EOF

>>> Pushing our work to both remotes...

EOF
for f in GerHobbelt/thirdparty-lcms2 GerHobbelt/Little-CMS ; do
    echo ""
    echo "::REPO: $f"
    git push --all --follow-tags git@github.com:$f.git                                         2>&1
    git push --tags              git@github.com:$f.git                                         2>&1
done

