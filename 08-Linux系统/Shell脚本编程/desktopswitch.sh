#!/bin/bash

# 检查参数数量
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 --wallpaper /path/to/your/wallpaper"
    exit 1
fi

# 检查参数键是否为--wallpaper
if [ "$1" != "--wallpaper" ]; then
    echo "The first argument must be --wallpaper"
    exit 1
fi

# 检查文件是否存在
if [ ! -f "$2" ]; then
    echo "The wallpaper file does not exist: $2"
    exit 1
fi

# 检查 DBus 是否正在运行
if ! pidof -x dbus-daemon >/dev/null; then
    echo "DBus does not seem to be running. Please start DBus and retry."
    exit 1
fi

# 获取输出设备名的列表
output_names=$(dbus-send --dest=com.deepin.daemon.Display /com/deepin/daemon/Display --print-reply com.deepin.daemon.Display.ListOutputNames | grep string | awk '{print $2}' | tr -d '"')

# 如果没有找到输出设备，退出脚本
if [ -z "$output_names" ]; then
    echo "No output devices found."
    exit 1
fi

# 设置壁纸
for element in $output_names; do
    dbus-send --dest=com.deepin.daemon.Appearance /com/deepin/daemon/Appearance \
    --print-reply com.deepin.daemon.Appearance.SetMonitorBackground \
    string:"$element" string:"file://${2}" 2>/dev/null
    
    if [ $? -ne 0 ]; then
        echo "Failed to set wallpaper for monitor $element"
    else
        echo "Wallpaper set for monitor $element"
    fi
done

echo "All done."
