# <font style="color:rgb(31, 35, 40);">Qt的事件循环</font>

## <font style="color:rgb(31, 35, 40);">什么是事件循环</font>

<font style="color:rgb(31, 35, 40);">假设有3个线程A、B和C：</font>  
<font style="color:rgb(31, 35, 40);">线程A，一个死循环，等待其他线程的事件通知，大部分时间阻塞着；</font>  
<font style="color:rgb(31, 35, 40);">线程B、C，需要执行功能时，只需要把事件通知发给线程A，线程A就会解除阻塞，执行B、C想要执行的功能；</font>  
<font style="color:rgb(31, 35, 40);">这样，不管线程B、C需要执行的功能多么耗时，都可以立即响应，因为它们只要把事件ID发给线程A就结束了；</font>  
<font style="color:rgb(31, 35, 40);">所谓事件循环，就是有一个主线程，保存了一个事件队列（其他线程需要做的事情），循环遍历队列执行对应的功能，在队列为空时候，阻塞等待。</font>

# <font style="color:rgb(24, 24, 24);">Qt没有被正确安装，请运行make install -- 问题的解决办法</font>

:::info
找到 qmake 所在路径执行 ./qmake -query 查看具体信息是否正确

:::

```cpp
QT_SYSROOT:
QT_INSTALL_PREFIX:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
QT_INSTALL_ARCHDATA:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
QT_INSTALL_DATA:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
QT_INSTALL_DOCS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/doc
QT_INSTALL_HEADERS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/include
QT_INSTALL_LIBS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/lib
QT_INSTALL_LIBEXECS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/libexec
QT_INSTALL_BINS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/bin
QT_INSTALL_TESTS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/tests
QT_INSTALL_PLUGINS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/plugins
QT_INSTALL_IMPORTS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/imports
QT_INSTALL_QML:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/qml
QT_INSTALL_TRANSLATIONS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/translations
QT_INSTALL_CONFIGURATION:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
QT_INSTALL_EXAMPLES:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/examples
QT_INSTALL_DEMOS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/examples
QT_HOST_PREFIX:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
QT_HOST_DATA:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
QT_HOST_BINS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/bin
QT_HOST_LIBS:/root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1/lib
QMAKE_SPEC:linux-g++
QMAKE_XSPEC:linux-arm-gnueabi-g++
QMAKE_VERSION:3.0
QT_VERSION:5.7.1

```

:::info
在 qmake 同级目录创建 qt.conf 

:::

```cpp
[Paths]
Prefix = /root/share/qtInstaller/sysroots/armv7ahf-neon-linux-gnueabi/root/qtInstaller/qt-everywhere-opensource-src-5.7.1/qtbase/qt5.7.1
Binaries = bin
Libraries = lib
Headers = include
Plugins = plugins
Imports = imports
Qml2Imports = qml
Data = .
Documentation = doc
Examples = examples
Demos = demos
Translations = translations
Settings = .
Sysroot =
TargetSpec = linux-arm-gnueabi-g++
HostSpec = linux-g++
```

:::info
再重启 qtcreator 添加 qmake 就可以了

:::

# <font style="color:rgb(34, 34, 38);">QEvent的所有事件</font>

QEvent 类是所有事件类的基类，事件对象包含事件参数。



Qt 的主事件循环（QCoreApplication::exec()）从事件队列中获取本地窗口系统事件，将它们转化为 QEvents，然后将转换后的事件发送给 QObjects。



一般来说，事件来自底层窗口系统（spontaneous() 返回 true），但也可以使用 QCoreApplication::sendEvent() 和 QCoreApplication::postEvent()（spontaneous() 返回 false）来手动发送事件。



QObjects 通过调用它们的 QObject::event() 函数接收事件。该函数可以在子类中重新实现，来处理自定义的事件以及添加额外的事件类型，QWidget::event() 就是一个很著名的例子。默认情况下，像 QObject::timerEvent() 和 QWidget::mouseMoveEvent() 这样的事件可以被发送给事件处理函数。QObject::installEventFilter() 允许一个对象拦截发往另一个对象的事件。



基本的 QEvent 只包含了一个事件类型参数。QEvent 的子类包含了额外的描述特定事件的参数。



### 成员类型

枚举QEvent::Type：



这个枚举类型定义了Qt中有效的事件类型。事件类型和每个类型的专门类如下：

| **<font style="color:rgb(79, 79, 79);">常量</font>**         | **<font style="color:rgb(79, 79, 79);">值</font>**           | **<font style="color:rgb(79, 79, 79);">描述</font>**         |
| :----------------------------------------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| <font style="color:rgb(79, 79, 79);">QEvent::None</font>     | <font style="color:rgb(79, 79, 79);">0</font>                | <font style="color:rgb(79, 79, 79);">不是一个事件</font>     |
| <font style="color:rgb(79, 79, 79);">QEvent::ActionAdded</font> | <font style="color:rgb(79, 79, 79);">114</font>              | <font style="color:rgb(79, 79, 79);">一个新 action 被添加（QActionEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ActionChanged</font> | <font style="color:rgb(79, 79, 79);">113</font>              | <font style="color:rgb(79, 79, 79);">一个 action 被改变（QActionEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ActionRemoved</font> | <font style="color:rgb(79, 79, 79);">115</font>              | <font style="color:rgb(79, 79, 79);">一个 action 被移除（QActionEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ActivationChange</font> | <font style="color:rgb(79, 79, 79);">99</font>               | <font style="color:rgb(79, 79, 79);">Widget 的顶层窗口激活状态发生了变化</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationActivate</font> | <font style="color:rgb(79, 79, 79);">121</font>              | <font style="color:rgb(79, 79, 79);">这个枚举已被弃用，使用 ApplicationStateChange 代替</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationActivated</font> | <font style="color:rgb(79, 79, 79);">ApplicationActivate</font> | <font style="color:rgb(79, 79, 79);">这个枚举已被弃用，使用 ApplicationStateChange 代替</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationDeactivate</font> | <font style="color:rgb(79, 79, 79);">122</font>              | <font style="color:rgb(79, 79, 79);">这个枚举已被弃用，使用 ApplicationStateChange 代替</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationFontChange</font> | <font style="color:rgb(79, 79, 79);">36</font>               | <font style="color:rgb(79, 79, 79);">应用程序的默认字体发生了变化</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationLayoutDirectionChange</font> | <font style="color:rgb(79, 79, 79);">37</font>               | <font style="color:rgb(79, 79, 79);">应用程序的默认布局方向发生了变化</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationPaletteChange</font> | <font style="color:rgb(79, 79, 79);">38</font>               | <font style="color:rgb(79, 79, 79);">应用程序的默认调色板发生了变化</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationStateChange</font> | <font style="color:rgb(79, 79, 79);">214</font>              | <font style="color:rgb(79, 79, 79);">应用程序的状态发生了变化</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ApplicationWindowIconChange</font> | <font style="color:rgb(79, 79, 79);">35</font>               | <font style="color:rgb(79, 79, 79);">应用程序的图标发生了变化</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ChildAdded</font> | <font style="color:rgb(79, 79, 79);">68</font>               | <font style="color:rgb(79, 79, 79);">一个对象获得孩子（QChildEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ChildPolished</font> | <font style="color:rgb(79, 79, 79);">69</font>               | <font style="color:rgb(79, 79, 79);">一个部件的孩子被抛光（QChildEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ChildRemoved</font> | <font style="color:rgb(79, 79, 79);">71</font>               | <font style="color:rgb(79, 79, 79);">一个对象时区孩子（QChildEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Clipboard</font> | <font style="color:rgb(79, 79, 79);">40</font>               | <font style="color:rgb(79, 79, 79);">剪贴板的内容发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Close</font>    | <font style="color:rgb(79, 79, 79);">19</font>               | <font style="color:rgb(79, 79, 79);">Widget 被关闭（QCloseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::CloseSoftwareInputPanel</font> | <font style="color:rgb(79, 79, 79);">200</font>              | <font style="color:rgb(79, 79, 79);">一个部件要关闭软件输入面板（SIP）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ContentsRectChange</font> | <font style="color:rgb(79, 79, 79);">178</font>              | <font style="color:rgb(79, 79, 79);">部件内容区域的外边距发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ContextMenu</font> | <font style="color:rgb(79, 79, 79);">82</font>               | <font style="color:rgb(79, 79, 79);">上下文弹出菜单（QContextMenuEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::CursorChange</font> | <font style="color:rgb(79, 79, 79);">183</font>              | <font style="color:rgb(79, 79, 79);">部件的鼠标发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::DeferredDelete</font> | <font style="color:rgb(79, 79, 79);">52</font>               | <font style="color:rgb(79, 79, 79);">对象被清除后将被删除（QDeferredDeleteEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::DragEnter</font> | <font style="color:rgb(79, 79, 79);">60</font>               | <font style="color:rgb(79, 79, 79);">在拖放操作期间鼠标进入窗口部件（QDragEnterEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::DragLeave</font> | <font style="color:rgb(79, 79, 79);">62</font>               | <font style="color:rgb(79, 79, 79);">在拖放操作期间鼠标离开窗口部件（QDragLeaveEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::DragMove</font> | <font style="color:rgb(79, 79, 79);">61</font>               | <font style="color:rgb(79, 79, 79);">拖放操作正在进行（QDragMoveEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Drop</font>     | <font style="color:rgb(79, 79, 79);">63</font>               | <font style="color:rgb(79, 79, 79);">拖放操作完成（QDropEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::DynamicPropertyChange</font> | <font style="color:rgb(79, 79, 79);">170</font>              | <font style="color:rgb(79, 79, 79);">动态属性已添加、更改或从对象中删除</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::EnabledChange</font> | <font style="color:rgb(79, 79, 79);">98</font>               | <font style="color:rgb(79, 79, 79);">部件的 enabled 状态已更改</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Enter</font>    | <font style="color:rgb(79, 79, 79);">10</font>               | <font style="color:rgb(79, 79, 79);">鼠标进入部件的边界（QEnterEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::EnterEditFocus</font> | <font style="color:rgb(79, 79, 79);">150</font>              | <font style="color:rgb(79, 79, 79);">编辑部件获得焦点进行编辑，必须定义 QT_KEYPAD_NAVIGATION</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::EnterWhatsThisMode</font> | <font style="color:rgb(79, 79, 79);">124</font>              | <font style="color:rgb(79, 79, 79);">当应用程序进入“What’s This?”模式，发送到 toplevel 顶层部件</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Expose</font>   | <font style="color:rgb(79, 79, 79);">206</font>              | <font style="color:rgb(79, 79, 79);">当其屏幕上的内容无效，发送到窗口，并需要从后台存储刷新</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::FileOpen</font> | <font style="color:rgb(79, 79, 79);">116</font>              | <font style="color:rgb(79, 79, 79);">文件打开请求（QFileOpenEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::FocusIn</font>  | <font style="color:rgb(79, 79, 79);">8</font>                | <font style="color:rgb(79, 79, 79);">部件或窗口获得键盘焦点（QFocusEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::FocusOut</font> | <font style="color:rgb(79, 79, 79);">9</font>                | <font style="color:rgb(79, 79, 79);">部件或窗口失去键盘焦点（QFocusEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::FocusAboutToChange</font> | <font style="color:rgb(79, 79, 79);">23</font>               | <font style="color:rgb(79, 79, 79);">部件或窗口焦点即将改变（QFocusEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::FontChange</font> | <font style="color:rgb(79, 79, 79);">97</font>               | <font style="color:rgb(79, 79, 79);">部件的字体发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Gesture</font>  | <font style="color:rgb(79, 79, 79);">198</font>              | <font style="color:rgb(79, 79, 79);">触发了一个手势（QGestureEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GestureOverride</font> | <font style="color:rgb(79, 79, 79);">202</font>              | <font style="color:rgb(79, 79, 79);">触发了手势覆盖（QGestureEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GrabKeyboard</font> | <font style="color:rgb(79, 79, 79);">188</font>              | <font style="color:rgb(79, 79, 79);">Item 获得键盘抓取（仅限 QGraphicsItem）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GrabMouse</font> | <font style="color:rgb(79, 79, 79);">186</font>              | <font style="color:rgb(79, 79, 79);">项目获得鼠标抓取（仅限 QGraphicsItem）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneContextMenu</font> | <font style="color:rgb(79, 79, 79);">159</font>              | <font style="color:rgb(79, 79, 79);">在图形场景上的上下文弹出菜单（QGraphicsScene ContextMenuEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneDragEnter</font> | <font style="color:rgb(79, 79, 79);">164</font>              | <font style="color:rgb(79, 79, 79);">在拖放操作期间，鼠标进入图形场景（QGraphicsSceneDragDropEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneDragLeave</font> | <font style="color:rgb(79, 79, 79);">166</font>              | <font style="color:rgb(79, 79, 79);">在拖放操作期间鼠标离开图形场景（QGraphicsSceneDragDropEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneDragMove</font> | <font style="color:rgb(79, 79, 79);">165</font>              | <font style="color:rgb(79, 79, 79);">在场景上正在进行拖放操作（QGraphicsSceneDragDropEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneDrop</font> | <font style="color:rgb(79, 79, 79);">167</font>              | <font style="color:rgb(79, 79, 79);">在场景上完成拖放操作（QGraphicsSceneDragDropEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneHelp</font> | <font style="color:rgb(79, 79, 79);">163</font>              | <font style="color:rgb(79, 79, 79);">用户请求图形场景的帮助（QHelpEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneHoverEnter</font> | <font style="color:rgb(79, 79, 79);">160</font>              | <font style="color:rgb(79, 79, 79);">鼠标进入图形场景中的悬停项（QGraphicsSceneHoverEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneHoverLeave</font> | <font style="color:rgb(79, 79, 79);">162</font>              | <font style="color:rgb(79, 79, 79);">鼠标离开图形场景中一个悬停项（QGraphicsSceneHoverEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneHoverMove</font> | <font style="color:rgb(79, 79, 79);">161</font>              | <font style="color:rgb(79, 79, 79);">鼠标在图形场景中的悬停项内移动（QGraphicsSceneHoverEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneMouseDoubleClick</font> | <font style="color:rgb(79, 79, 79);">158</font>              | <font style="color:rgb(79, 79, 79);">鼠标在图形场景中再次按下（双击）（QGraphicsSceneMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneMouseMove</font> | <font style="color:rgb(79, 79, 79);">155</font>              | <font style="color:rgb(79, 79, 79);">鼠标在图形场景中移动（QGraphicsSceneMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneMousePress</font> | <font style="color:rgb(79, 79, 79);">156</font>              | <font style="color:rgb(79, 79, 79);">鼠标在图形场景中按下（QGraphicsSceneMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneMouseRelease</font> | <font style="color:rgb(79, 79, 79);">157</font>              | <font style="color:rgb(79, 79, 79);">鼠标在图形场景中释放（QGraphicsSceneMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneMove</font> | <font style="color:rgb(79, 79, 79);">182</font>              | <font style="color:rgb(79, 79, 79);">部件被移动（QGraphicsSceneMoveEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneResize</font> | <font style="color:rgb(79, 79, 79);">181</font>              | <font style="color:rgb(79, 79, 79);">部件已调整大小（QGraphicsSceneResizeEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::GraphicsSceneWheel</font> | <font style="color:rgb(79, 79, 79);">168</font>              | <font style="color:rgb(79, 79, 79);">鼠标滚轮在图形场景中滚动（QGraphicsSceneWheelEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Hide</font>     | <font style="color:rgb(79, 79, 79);">18</font>               | <font style="color:rgb(79, 79, 79);">部件被隐藏（QHideEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::HideToParent</font> | <font style="color:rgb(79, 79, 79);">27</font>               | <font style="color:rgb(79, 79, 79);">子部件被隐藏（QHideEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::HoverEnter</font> | <font style="color:rgb(79, 79, 79);">127</font>              | <font style="color:rgb(79, 79, 79);">鼠标进入悬停部件（QHoverEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::HoverLeave</font> | <font style="color:rgb(79, 79, 79);">128</font>              | <font style="color:rgb(79, 79, 79);">鼠标留离开悬停部件（QHoverEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::HoverMove</font> | <font style="color:rgb(79, 79, 79);">129</font>              | <font style="color:rgb(79, 79, 79);">鼠标在悬停部件内移动（QHoverEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::IconDrag</font> | <font style="color:rgb(79, 79, 79);">96</font>               | <font style="color:rgb(79, 79, 79);">窗口的主图标被拖走（QIconDragEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::IconTextChange</font> | <font style="color:rgb(79, 79, 79);">101</font>              | <font style="color:rgb(79, 79, 79);">部件的图标文本发生改变（已弃用）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::InputMethod</font> | <font style="color:rgb(79, 79, 79);">83</font>               | <font style="color:rgb(79, 79, 79);">正在使用输入法（QInputMethodEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::InputMethodQuery</font> | <font style="color:rgb(79, 79, 79);">207</font>              | <font style="color:rgb(79, 79, 79);">输入法查询事件（QInputMethodQueryEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::KeyboardLayoutChange</font> | <font style="color:rgb(79, 79, 79);">169</font>              | <font style="color:rgb(79, 79, 79);">键盘布局已更改</font>   |
| <font style="color:rgb(79, 79, 79);">QEvent::KeyPress</font> | <font style="color:rgb(79, 79, 79);">6</font>                | <font style="color:rgb(79, 79, 79);">键盘按下（QKeyEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::KeyRelease</font> | <font style="color:rgb(79, 79, 79);">7</font>                | <font style="color:rgb(79, 79, 79);">键盘释放（QKeyEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::LanguageChange</font> | <font style="color:rgb(79, 79, 79);">89</font>               | <font style="color:rgb(79, 79, 79);">应用程序翻译发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::LayoutDirectionChange</font> | <font style="color:rgb(79, 79, 79);">90</font>               | <font style="color:rgb(79, 79, 79);">布局的方向发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::LayoutRequest</font> | <font style="color:rgb(79, 79, 79);">76</font>               | <font style="color:rgb(79, 79, 79);">部件的布局需要重做</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Leave</font>    | <font style="color:rgb(79, 79, 79);">11</font>               | <font style="color:rgb(79, 79, 79);">鼠标离开部件的边界</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::LeaveEditFocus</font> | <font style="color:rgb(79, 79, 79);">151</font>              | <font style="color:rgb(79, 79, 79);">编辑部件失去编辑的焦点，必须定义 QT_KEYPAD_NAVIGATION</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::LeaveWhatsThisMode</font> | <font style="color:rgb(79, 79, 79);">125</font>              | <font style="color:rgb(79, 79, 79);">当应用程序离开“What’s This?”模式，发送到顶层部件</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::LocaleChange</font> | <font style="color:rgb(79, 79, 79);">88</font>               | <font style="color:rgb(79, 79, 79);">系统区域设置发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::NonClientAreaMouseButtonDblClick</font> | <font style="color:rgb(79, 79, 79);">176</font>              | <font style="color:rgb(79, 79, 79);">鼠标双击发生在客户端区域外</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::NonClientAreaMouseButtonPress</font> | <font style="color:rgb(79, 79, 79);">174</font>              | <font style="color:rgb(79, 79, 79);">鼠标按钮按下发生在客户端区域外</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::NonClientAreaMouseButtonRelease</font> | <font style="color:rgb(79, 79, 79);">175</font>              | <font style="color:rgb(79, 79, 79);">鼠标按钮释放发生在客户端区域外</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::NonClientAreaMouseMove</font> | <font style="color:rgb(79, 79, 79);">173</font>              | <font style="color:rgb(79, 79, 79);">鼠标移动发生在客户区域外</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MacSizeChange</font> | <font style="color:rgb(79, 79, 79);">177</font>              | <font style="color:rgb(79, 79, 79);">用户更改了部件的大小（仅限 OS X）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MetaCall</font> | <font style="color:rgb(79, 79, 79);">43</font>               | <font style="color:rgb(79, 79, 79);">通过 QMetaObject::invokeMethod() 调用异步方法</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ModifiedChange</font> | <font style="color:rgb(79, 79, 79);">102</font>              | <font style="color:rgb(79, 79, 79);">部件修改状态发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MouseButtonDblClick</font> | <font style="color:rgb(79, 79, 79);">4</font>                | <font style="color:rgb(79, 79, 79);">鼠标再次按下（QMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MouseButtonPress</font> | <font style="color:rgb(79, 79, 79);">2</font>                | <font style="color:rgb(79, 79, 79);">鼠标按下（QMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MouseButtonRelease</font> | <font style="color:rgb(79, 79, 79);">3</font>                | <font style="color:rgb(79, 79, 79);">鼠标释放（QMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MouseMove</font> | <font style="color:rgb(79, 79, 79);">5</font>                | <font style="color:rgb(79, 79, 79);">鼠标移动（QMouseEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::MouseTrackingChange</font> | <font style="color:rgb(79, 79, 79);">109</font>              | <font style="color:rgb(79, 79, 79);">鼠标跟踪状态发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Move</font>     | <font style="color:rgb(79, 79, 79);">13</font>               | <font style="color:rgb(79, 79, 79);">部件的位置发生改变（QMoveEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::NativeGesture</font> | <font style="color:rgb(79, 79, 79);">197</font>              | <font style="color:rgb(79, 79, 79);">系统检测到手势（QNativeGestureEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::OrientationChange</font> | <font style="color:rgb(79, 79, 79);">208</font>              | <font style="color:rgb(79, 79, 79);">屏幕方向发生改变（QScreenOrientationChangeEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Paint</font>    | <font style="color:rgb(79, 79, 79);">12</font>               | <font style="color:rgb(79, 79, 79);">需要屏幕更新（QPaintEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::PaletteChange</font> | <font style="color:rgb(79, 79, 79);">39</font>               | <font style="color:rgb(79, 79, 79);">部件的调色板发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ParentAboutToChange</font> | <font style="color:rgb(79, 79, 79);">131</font>              | <font style="color:rgb(79, 79, 79);">部件的 parent 将要更改</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ParentChange</font> | <font style="color:rgb(79, 79, 79);">21</font>               | <font style="color:rgb(79, 79, 79);">部件的 parent 发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::PlatformPanel</font> | <font style="color:rgb(79, 79, 79);">212</font>              | <font style="color:rgb(79, 79, 79);">请求一个特定于平台的面板</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::PlatformSurface</font> | <font style="color:rgb(79, 79, 79);">217</font>              | <font style="color:rgb(79, 79, 79);">原生平台表面已创建或即将被销毁（QPlatformSurfaceEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Polish</font>   | <font style="color:rgb(79, 79, 79);">75</font>               | <font style="color:rgb(79, 79, 79);">部件被抛光</font>       |
| <font style="color:rgb(79, 79, 79);">QEvent::PolishRequest</font> | <font style="color:rgb(79, 79, 79);">74</font>               | <font style="color:rgb(79, 79, 79);">部件应该被抛光</font>   |
| <font style="color:rgb(79, 79, 79);">QEvent::QueryWhatsThis</font> | <font style="color:rgb(79, 79, 79);">123</font>              | <font style="color:rgb(79, 79, 79);">如果部件有“What’s This?”帮助，应该接受事件</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ReadOnlyChange</font> | <font style="color:rgb(79, 79, 79);">106</font>              | <font style="color:rgb(79, 79, 79);">部件的 read-only 状态发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::RequestSoftwareInputPanel</font> | <font style="color:rgb(79, 79, 79);">199</font>              | <font style="color:rgb(79, 79, 79);">部件想要打开软件输入面板（SIP）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Resize</font>   | <font style="color:rgb(79, 79, 79);">14</font>               | <font style="color:rgb(79, 79, 79);">部件的大小发生改变（QResizeEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ScrollPrepare</font> | <font style="color:rgb(79, 79, 79);">204</font>              | <font style="color:rgb(79, 79, 79);">对象需要填充它的几何信息（QScrollPrepareEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Scroll</font>   | <font style="color:rgb(79, 79, 79);">205</font>              | <font style="color:rgb(79, 79, 79);">对象需要滚动到提供的位置（QScrollEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Shortcut</font> | <font style="color:rgb(79, 79, 79);">117</font>              | <font style="color:rgb(79, 79, 79);">快捷键处理（QShortcutEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ShortcutOverride</font> | <font style="color:rgb(79, 79, 79);">51</font>               | <font style="color:rgb(79, 79, 79);">按下按键，用于覆盖快捷键（QKeyEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Show</font>     | <font style="color:rgb(79, 79, 79);">17</font>               | <font style="color:rgb(79, 79, 79);">部件显示在屏幕上（QShowEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ShowToParent</font> | <font style="color:rgb(79, 79, 79);">26</font>               | <font style="color:rgb(79, 79, 79);">子部件被显示</font>     |
| <font style="color:rgb(79, 79, 79);">QEvent::SockAct</font>  | <font style="color:rgb(79, 79, 79);">50</font>               | <font style="color:rgb(79, 79, 79);">Socket 激活，用于实现 QSocketNotifier</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::StateMachineSignal</font> | <font style="color:rgb(79, 79, 79);">192</font>              | <font style="color:rgb(79, 79, 79);">信号被传递到状态机（QStateMachine::SignalEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::StateMachineWrapped</font> | <font style="color:rgb(79, 79, 79);">193</font>              | <font style="color:rgb(79, 79, 79);">事件是一个包装器，用于包含另一个事件（QStateMachine::WrappedEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::StatusTip</font> | <font style="color:rgb(79, 79, 79);">112</font>              | <font style="color:rgb(79, 79, 79);">状态提示请求（QStatusTipEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::StyleChange</font> | <font style="color:rgb(79, 79, 79);">100</font>              | <font style="color:rgb(79, 79, 79);">部件的样式发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TabletMove</font> | <font style="color:rgb(79, 79, 79);">87</font>               | <font style="color:rgb(79, 79, 79);">Wacom 写字板移动（QTabletEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TabletPress</font> | <font style="color:rgb(79, 79, 79);">92</font>               | <font style="color:rgb(79, 79, 79);">Wacom 写字板按下（QTabletEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TabletRelease</font> | <font style="color:rgb(79, 79, 79);">93</font>               | <font style="color:rgb(79, 79, 79);">Wacom 写字板释放（QTabletEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::OkRequest</font> | <font style="color:rgb(79, 79, 79);">94</font>               | <font style="color:rgb(79, 79, 79);">Ok 按钮在装饰前被按下，仅支持 Windows CE</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TabletEnterProximity</font> | <font style="color:rgb(79, 79, 79);">171</font>              | <font style="color:rgb(79, 79, 79);">Wacom 写字板进入接近事件（QTabletEvent），发送到 QApplication</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TabletLeaveProximity</font> | <font style="color:rgb(79, 79, 79);">172</font>              | <font style="color:rgb(79, 79, 79);">Wacom 写字板离开接近事件（QTabletEvent），发送到 QApplication</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ThreadChange</font> | <font style="color:rgb(79, 79, 79);">22</font>               | <font style="color:rgb(79, 79, 79);">对象被移动到另一个线程。这是发送到此对象的最后一个事件在上一个线程中，参见：QObject::moveToThread()</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Timer</font>    | <font style="color:rgb(79, 79, 79);">1</font>                | <font style="color:rgb(79, 79, 79);">定时器事件（QTimerEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ToolBarChange</font> | <font style="color:rgb(79, 79, 79);">120</font>              | <font style="color:rgb(79, 79, 79);">工具栏按钮在 OS X 上进行切换</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ToolTip</font>  | <font style="color:rgb(79, 79, 79);">110</font>              | <font style="color:rgb(79, 79, 79);">一个 tooltip 请求（QHelpEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ToolTipChange</font> | <font style="color:rgb(79, 79, 79);">184</font>              | <font style="color:rgb(79, 79, 79);">部件的 tooltip 发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TouchBegin</font> | <font style="color:rgb(79, 79, 79);">194</font>              | <font style="color:rgb(79, 79, 79);">触摸屏或轨迹板事件序列的开始（QTouchEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TouchCancel</font> | <font style="color:rgb(79, 79, 79);">209</font>              | <font style="color:rgb(79, 79, 79);">取消触摸事件序列（QTouchEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TouchEnd</font> | <font style="color:rgb(79, 79, 79);">196</font>              | <font style="color:rgb(79, 79, 79);">触摸事件序列结束（QTouchEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::TouchUpdate</font> | <font style="color:rgb(79, 79, 79);">195</font>              | <font style="color:rgb(79, 79, 79);">触摸屏事件（QTouchEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::UngrabKeyboard</font> | <font style="color:rgb(79, 79, 79);">189</font>              | <font style="color:rgb(79, 79, 79);">Item 失去键盘抓取（QGraphicsItem）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::UngrabMouse</font> | <font style="color:rgb(79, 79, 79);">187</font>              | <font style="color:rgb(79, 79, 79);">Item 失去鼠标抓取（QGraphicsItem、QQuickItem）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::UpdateLater</font> | <font style="color:rgb(79, 79, 79);">78</font>               | <font style="color:rgb(79, 79, 79);">部件应该排队在以后重新绘制</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::UpdateRequest</font> | <font style="color:rgb(79, 79, 79);">77</font>               | <font style="color:rgb(79, 79, 79);">部件应该被重绘</font>   |
| <font style="color:rgb(79, 79, 79);">QEvent::WhatsThis</font> | <font style="color:rgb(79, 79, 79);">111</font>              | <font style="color:rgb(79, 79, 79);">部件应该显示“What’s This”帮助（QHelpEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WhatsThisClicked</font> | <font style="color:rgb(79, 79, 79);">118</font>              | <font style="color:rgb(79, 79, 79);">部件的“What’s This”帮助链接被点击</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::Wheel</font>    | <font style="color:rgb(79, 79, 79);">31</font>               | <font style="color:rgb(79, 79, 79);">鼠标滚轮滚动（QWheelEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WinEventAct</font> | <font style="color:rgb(79, 79, 79);">132</font>              | <font style="color:rgb(79, 79, 79);">发生了 Windows 特定的激活事件</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowActivate</font> | <font style="color:rgb(79, 79, 79);">24</font>               | <font style="color:rgb(79, 79, 79);">窗口已激活</font>       |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowBlocked</font> | <font style="color:rgb(79, 79, 79);">103</font>              | <font style="color:rgb(79, 79, 79);">窗口被模态对话框阻塞</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowDeactivate</font> | <font style="color:rgb(79, 79, 79);">25</font>               | <font style="color:rgb(79, 79, 79);">窗户被停用</font>       |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowIconChange</font> | <font style="color:rgb(79, 79, 79);">34</font>               | <font style="color:rgb(79, 79, 79);">窗口的图标发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowStateChange</font> | <font style="color:rgb(79, 79, 79);">105</font>              | <font style="color:rgb(79, 79, 79);">窗口的状态（最小化、最大化或全屏）发生改变（QWindowStateChangeEvent）</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowTitleChange</font> | <font style="color:rgb(79, 79, 79);">33</font>               | <font style="color:rgb(79, 79, 79);">窗口的标题发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WindowUnblocked</font> | <font style="color:rgb(79, 79, 79);">104</font>              | <font style="color:rgb(79, 79, 79);">一个模态对话框退出后，窗口将不被阻塞</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::WinIdChange</font> | <font style="color:rgb(79, 79, 79);">203</font>              | <font style="color:rgb(79, 79, 79);">本地窗口的系统标识符发生改变</font> |
| <font style="color:rgb(79, 79, 79);">QEvent::ZOrderChange</font> | <font style="color:rgb(79, 79, 79);">126</font>              | <font style="color:rgb(79, 79, 79);">部件的 z 值发生了改变，该事件不会发送给顶层窗口</font> |


<font style="color:rgb(77, 77, 77);">用户事件的值应该介于 User 和 MaxUser 之间。</font>

| **<font style="color:rgb(79, 79, 79);">常量</font>**        | **<font style="color:rgb(79, 79, 79);">值</font>** | **<font style="color:rgb(79, 79, 79);">描述</font>**         |
| :---------------------------------------------------------- | :------------------------------------------------- | :----------------------------------------------------------- |
| <font style="color:rgb(79, 79, 79);">QEvent::User</font>    | <font style="color:rgb(79, 79, 79);">1000</font>   | <font style="color:rgb(79, 79, 79);">用户定义的事件</font>   |
| <font style="color:rgb(79, 79, 79);">QEvent::MaxUser</font> | <font style="color:rgb(79, 79, 79);">65535</font>  | <font style="color:rgb(79, 79, 79);">最后的用户事件 ID</font> |


<font style="color:rgb(77, 77, 77);">为方便起见，可以使用 registerEventType() 函数来注册和存储一个自定义事件类型，这样做会避免意外地重用一个自定义事件类型。</font>














































































































































































---
