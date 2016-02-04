
home_3rd=~/3rd

if test -d /llj/3rd ; then
   home_3rd=/llj/3rd
fi

home_boost=$home_3rd/boost
home_rem=$home_3rd/rem_api_1.0.1.21

export LD_LIBRARY_PATH=$home_boost/lib:$home_rem/lib/trade/C++/linux64_debug



