#! /bin/sh

home_app=~/app

if test -d /llj/app ; then
   home_app=/llj/app
fi

home_stab=${home_app}/stab

./configure --prefix=${home_stab}

if test -d ${home_stab}; then
    rm -rf ${home_stab}
fi

make install

make distclean
