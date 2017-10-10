#! /bin/sh

node=`uname -n`
home_app=~/app/${node}

home_stab=${home_app}/stab

./configure --prefix=${home_stab}

if test -d ${home_stab}; then
    rm -rf ${home_stab}
fi

make install

make distclean
