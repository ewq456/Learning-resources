#bin/bash

FALG1=0
FALG2=0

CURRENT_USER=$(whoami)

VRVHOT="vrvscreenhot"

LIBSCREENSO="libvcemsscreen.so"

VRVSCREENHOTPATH="/home/$CURRENT_USER/$VRVHOT"

LIBVCMESSCREENPATH="/home/$CURRENT_USER/$LIBSCREENSO"

ESA="/opt/apps/cn.com.vrv.cems/files/cems/esa"

/home/$CURRENT_USER/sectool 0

echo "########################################"

if [ -e $VRVSCREENHOT ]; then
    sudo cp "$VRVSCREENHOTPATH" "$ESA"
    echo "sudo cp $VRVSCREENHOTPATH $ESA"

    if [ -e $LIBVCMESSCREENPATH ]; then
        sudo cp "$LIBVCMESSCREENPATH" "$ESA"
        echo "sudo cp $LIBVCMESSCREENPATH $ESA"

        FLAG2=2
    else   
        echo "$LIBVCMESSCREENPATH does not exist"
    fi

    sudo patchelf --remove-rpath "$ESA/$VRVHOT"
    echo "sudo patchelf --remove-rpath $ESA/$VRVHOT"

    sudo cp "$ESA/$VRVHOT" "$ESA/$VRVHOT.kylin990"
    echo "sudo cp $ESA/$VRVHOT $ESA/$VRVHOT.kylin990"

    FLAG1=1
else
    echo "$VRVSCREENHOTPATH does not exist"
fi

if [ $FLAG1 -eq 1 ]; then
    MD5=$(md5sum $ESA/$VRVHOT)
    echo "$MD5"
fi

if [ $FLAG2 -eq 2 ]; then
    MD5=$(md5sum $ESA/$LIBSCREENSO)
    echo "$MD5"
fi
echo "########################################"

ps -ax -o pid,comm | grep vpengine

VPENGINE=$(pgrep vpengine)

sudo kill -9 $VPENGINE

echo " kill -9 $VPENGINE"

sleep 1

ps -ax -o pid,comm | grep vpengine

echo "########################################"