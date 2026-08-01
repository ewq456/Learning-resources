# FFmpeg编译与使用


## Linux下完美编译ffmpeg库

wget -O ./config.sub "http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.sub;hb=HEAD"

wget -O ./config.guess "http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.guess;hb=HEAD"

chmod +x config.guess config.sub

---


## 音视频




## 音频录制原理





## 音频播放原理





## 图像基础

- **像素**：像素是一个图片的基本单位，pix是英语单词picture的简写，加上英语单词“元素element”，就得到了“pixel”，简称px，所以“像素”有“图像元素”之意。
- **分辨率**：是指图像的大小或尺寸。比如1920x1080。
- **位深**：是指在记录数字图像的颜色时，计算机实际上是用每个像素需要的位深来表示的。比如红色分量用8bit。
- **帧率**：在1秒钟时间里传输的图片的帧数，也可以理解为图形处理器每秒钟能够刷新几次。比如25fps表示一秒有25张图片。
- **码率**：视频文件在单位时间内使用的数据流量。比如1Mbps。
- **Stride**：指在内存中每行像素所占的空间。为了实现内存对齐每行像素在内存中所占的空间并不一定是图像的宽度。

### 像素

<h3><font color=red size=4>构成图像的最小单位，每个像素都有自己的颜色</font></h3>

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6569f4644a664fe7b0ced631029279f8.png)


像素，简单来说，就是构成图像的最小单位。想象一下，如果你有一张很大的图片，你把它放大很多倍，直到看到一个个的小方块，每个小方块就是一个像素。这些小方块就像拼图游戏中的单个拼图块，它们组合在一起，就形成了完整的图像。

每个像素都有自己的颜色，当我们在屏幕上看图片时，实际上是在看成千上万个这样的小方块，它们的颜色混合在一起，让我们看到了丰富多彩的图像。就像画家用小点来作画一样，这些小点就是像素，它们组合在一起，就能创造出各种美丽的图案。

在数字图像中，像素的数量决定了图像的清晰度。像素越多，图像越清晰，因为每个像素都能提供更多的细节。这就像你用高倍放大镜看东西，能看到更多的细节一样。所以，当你听到“高分辨率”这个词时，它通常意味着图像中有很多像素，因此图像看起来更清晰。

### 分辨率

<h3><font color=red size=4>屏幕或图像中像素点的数量，决定了图像的清晰度</font></h3>

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/3cf42e602ffb436a908a4c19fc04ce41.png)

分辨率，就像是给图像的清晰度打分的一个标准。想象一下，你有一个放大镜，通过它可以看到更多的细节。分辨率就像是告诉你，你的放大镜能放大到什么程度，让你看到多少细节。

具体来说，分辨率通常是指屏幕上或者图像中能显示的像素点的数量。比如，我们经常听到的“1080p”分辨率，意味着图像的高度上有1080个像素点，宽度上有更多的像素点（比如1920个），所以整个屏幕或图像是由1920×1080个像素点组成的。

用一个简单的比喻：想象一下你有一个由很多小格子组成的网格，每个格子就是一个像素点。分辨率就是告诉你这个网格有多少行（高度上的像素点）和多少列（宽度上的像素点）。分辨率越高，意味着网格越密集，每个格子越小，你能看到的细节就越多，图像也就越清晰。

就像你在看一本书，如果字号（分辨率）很小，每一页可以写很多字，但每个字看起来就会很小，细节多但不够清晰；如果字号（分辨率）很大，每一页写的字就少，但每个字看起来会更大，更容易看清楚。分辨率就是帮你决定在一定空间内，你能展示多少细节的一个参数。

### 位深

<h3><font color=red size=4>每个像素可以表示的颜色信息的位数，影响颜色的丰富程度和过渡的平滑性</font></h3>

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b85f1cc8444e41bbbe073ae557ee2c85.png)

位深，可以想象成是每个像素能够显示的颜色的丰富程度。就像是一个调色板，位深越高，调色板上的颜色就越多，能够调配出的颜色也就越精细。

具体来说，位深是指每个像素可以表示的颜色信息的位数。比如，8位位深意味着每个像素可以用8位二进制数来表示，也就是2的8次方，等于256种不同的颜色。而16位位深则意味着每个像素可以用16位二进制数来表示，也就是2的16次方，等于65536种不同的颜色。

用一个简单的比喻：如果把每个像素想象成一个可以装不同颜色的小桶，位深就像是告诉你这个小桶可以装多少种颜色。8位位深的小桶只能装256种颜色，而16位位深的小桶可以装65536种颜色。显然，16位位深的小桶能装的颜色更多，调配出的颜色也更丰富，所以图像看起来也更细腻、更真实。

位深越高，图像的颜色过渡就越平滑，没有明显的色带或色块，就像渐变色一样自然。而位深较低时，颜色过渡可能会显得生硬，因为可使用的颜色种类有限，无法精确地表现出细微的颜色变化。

### 帧率

<h3><font color=red size=4>视频或动画中每秒钟显示的静态图像数量，影响动态画面的流畅度</font></h3>

帧率，可以想象成是电影或视频播放时，每秒钟能展示多少个画面。就像翻书一样，每一页都是一个画面，你翻得越快，故事的连续性就越好，看起来也越流畅。

具体来说，帧率是指视频或动画中每秒钟能够显示的静态图像（帧）的数量。帧率通常用“帧/秒”（fps，frames per second）来表示。比如，24fps意味着视频每秒钟会展示24个画面，60fps则意味着每秒钟展示60个画面。

用一个简单的比喻：想象一下你在看一本漫画书，每一页都是一个静态的画面。如果你快速翻页，漫画里的人物动作就会显得很流畅，就像在动一样。帧率就像是告诉你，你翻页的速度有多快。翻得越快，动作看起来就越连贯，越接近真实世界的动态。

在视频和游戏中，高帧率意味着画面更加流畅，没有卡顿感，尤其是在快速运动的场景中，高帧率可以减少模糊和拖影现象，提供更好的视觉体验。而低帧率则可能导致画面卡顿，看起来不够流畅，就像翻页翻得慢，漫画里的动作断断续续的。

### 码率

<h3><font color=red size=4>单位时间内传输的数据量，影响媒体文件的大小和质量</font></h3>

码率，可以想象成是数据流动的“速度”。就像水管里的水流，码率越高，数据流动得越快，信息传递得也越丰富。

具体来说，码率是指单位时间内传输的数据量，通常用“比特每秒”（bps，bits per second）来表示。在视频和音频领域，码率指的是每秒钟传输的比特数，这直接影响了媒体文件的大小和质量。

用一个简单的比喻：如果把数据比作是货物，那么码率就像是运输这些货物的卡车。码率越高，意味着每辆卡车能装载的货物越多，或者需要更多的卡车来运输同样的货物，这样就能更快地把货物（数据）送到目的地。

在视频播放中，高码率意味着视频的质量更高，因为有更多的数据来描述画面的细节和色彩。但同时，这也意味着文件的大小会更大，需要更多的存储空间和更快的网络速度来传输。相反，低码率的视频文件会小一些，但画面质量可能会降低，因为描述画面的数据不够丰富，可能会出现模糊或者压缩的痕迹。

总的来说，码率是一个平衡点，需要根据实际的存储和传输条件来调整，以达到质量和效率的最佳平衡。

### Stride 跨距

<h3><font color=red size=4>指在内存中每行像素所占的空间，为了实现内存对齐每行像素在内存中所占
的空间并不一定是图像的宽度</font></h3>


Stride就像是你在一张纸上画图时，每画完一行后，为了保持整齐或者符合某种规则，不得不跳过一些空白区域，再开始画下一行。这个“跳过”的空白区域，就是Stride。

想象一下，你有一张纸，你打算在上面画很多小格子，每个小格子代表一个像素。如果你画的图像宽度是638个像素，每个像素用3个字节来表示（因为RGB图像每个像素有红、绿、蓝三个颜色通道），那么理论上一行需要638乘以3，也就是1904个字节。

但是，如果你希望每行都能整齐地对齐到16个字节的边界上，就像把书页对齐一样，你会发现1904个字节不能被16整除，这样就做不到完美的对齐。为了让每行都能整齐对齐，你需要在每行的末尾添加一些额外的空白区域，也就是填充一些“虚拟”的像素，使得每行的总字节数能够被16整除。

在这个例子中，你需要在每行的末尾添加6个字节的空白区域，使得每行的总字节数从1904个字节增加到1920个字节，这样就能被16整除，实现了对齐。这个1920个字节，就是这个图像的Stride值。

所以，Stride不仅仅是图像的实际宽度，还包括了为了对齐而添加的额外空间。这就是为什么有时候Stride的值会大于图像的实际宽度。

### RGB

<h3><font color=red size=4>通过调整红、绿、蓝三种颜色光的强度来产生丰富多彩的颜色</font></h3>

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6f399c7dc03248c39ba801a41bd70d38.png)

RGB是一种颜色模型，用来描述颜色的一种方式。想象一下，你有三个不同颜色的魔法水枪，一个喷出红光，一个喷出绿光，一个喷出蓝光。当你单独使用这些水枪时，你只能得到红、绿、蓝三种颜色。但是，如果你同时使用这三个水枪，并且调整它们喷出的光的强度，你就能混合出各种各样的颜色。这就是RGB颜色模型的基本原理：通过调整红、绿、蓝三种颜色光的强度，来产生丰富多彩的颜色。

### YUV

<h3><font color=red size=4>以亮度 (Y：Luminance或Luma) 为基础，通过调整色度信息（U和V）(UV：Chrominance或Chroma) 来描述颜色的色调和饱和度</font></h3>

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/b292fa3a663f468a9d5fafb17888cba0.png)

YUV是另一种颜色模型，它更接近于人眼感知颜色的方式。这里的Y代表亮度，也就是图像的明暗程度；U和V则代表色彩信息，它们描述了颜色的色调和饱和度。你可以把YUV想象成一种调色盘，Y是基础的颜料（亮度），而U和V是调整这个颜料色调和鲜艳度的工具。通过改变Y的值，你可以让图像变亮或变暗；通过调整U和V的值，你可以改变颜色的冷暖和鲜艳度。YUV颜色模型常用于视频压缩，因为它能有效减少数据量，同时保持较好的图像质量

Y和UV分开的好处就是补单可以避免相互干扰，没有UV信息一样可以显示完整的图像，因而解决了<font color=red>彩色电视与黑白电视的兼容问题</font>；还可以<font color=red>降低色度的采样率</font>而不会对图像质量影响太大，降低了视频信号传输时对频宽的要求

YY共用一组UV分量

#### 排列方式

- 打包(packed)格式：将<font color=red>每个像素点的Y、U、V分享交叉排列</font>并以像素点为单元连续的存放在同一数组中，通常几个相邻的像素组成一个宏像素。

  

  

  

- 平面(palaner)格式：<font color=red>使用三个数组分开连续的存放Y、U、V三个分量</font>，即Y、U、V分别存放在各自的数组中。

  
  
  

#### YUV采样表示法

YUV采用A:B:C表示法来描述<font color=red>Y,U,V采样频率比例</font>，下图中黑点表示采样像素点Y分量， <font color=red>空心圆表示采样像素点的UV分量</font>。主要分为 YUV 4:4:4、YUV 4:2:2、YUV 4:2:0 这几种 常用的类型







- 4:4:4 表示色度频道没有下采样，即一个Y分量对应着一个U分量和一个V分量
- 4:2:2 表示 2:1 的水平下采样，没有垂直下采样，即每两个Y分量共用一个U分量和一个V分量
- 4:2:0 表示 2:1 的水平下采样，2:1 的垂直下采样，即每四个Y分量共用一个U分量和一个V分量

#### YUV数据存储

##### 4:4:4格式-YUV444P

<font color=red>I444(YUV444P)</font>格式

- 对应Ffmpeg像素表示AV_PIX_FMT_<font color=red>YUV444P</font>, ///< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples）

  



##### 4:2:2格式-YUV422P

<font color=red>I422(YUV422P)</font>格式

- 对应Ffmpeg像素表示AV_PIX_FMT_YUV422P, ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)

- 该类型为planar格式

  



##### 4:2:0格式-YUV420P

<font color=red>I420(YUV420P)</font>格式

- 对应Ffmpeg像素表示AV_PIX_FMT_YUV420P, ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)

- 该类型为planar格式

- (4+1+1)/4 = 1.5字节

  



##### 4:2:0格式-NV12

<font color=red>NV12</font>格式

- 对应Ffmpeg像素表示AV_PIX_FMT_NV12, ///< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V）

  



##### 4:2:0格式-参考





## 视频的概念

### 视频码率：kb/s

> 是指视频文件在单位时间内使用的数据流量，也叫码流率。码率越大，说明单位时间内取样率越大，数据流精度就越高。

### 视频帧率：fps

> 通常说一个视频的25帧，指的就是这个视频帧率，即1秒中会显示25帧。帧率越高，给人的视觉就越流畅。

### 视频分辨率

> 分辨率就是我们常说的640x480分辨率、1920x1080分辨率，分辨率影响视频图像的大小。

## 音频基础

### 音频编码基本原理

音频编码的基本原理是将模拟音频信号转换成数字信号，然后通过压缩技术减少数据量，以便于存储和传输。这个过程可以分为以下几个步骤：

- 模拟到数字的转换（模数转换，ADC）：

  - 音频信号最初是以模拟形式存在的，比如麦克风捕捉到的声音波形。模数转换器（ADC）将这些连续变化的模拟信号转换成离散的数字信号。这个过程就是采样，即按照一定的采样频率（如44.1kHz）在每个样本点上测量信号的振幅。
- 量化：
  - 量化是确定样本点振幅级别的过程。采样精度（采样深度）决定了量化级别的数量。例如，16位的采样深度可以提供65536个可能的振幅级别，这比8位的256个级别要精细得多。
- 编码：
  - 将量化后的样本点转换成二进制数据。这些数据可以是原始的PCM（脉冲编码调制）数据，也可以是经过压缩的格式，如MP3、AAC等。
- 压缩：
  - 压缩是减少音频数据量的过程，可以分为有损压缩和无损压缩两种。有损压缩通过移除人耳不易察觉的音频信息来减少文件大小，而无损压缩则保留所有数据，但文件大小通常比有损压缩大。
- 封装：
  - 将压缩后的音频数据封装到容器格式中，如MP3、WAV、FLAC等。这些容器格式定义了如何组织音频数据，以及可能包含的元数据（如艺术家、专辑信息等）。
- 解码：
  - 当需要播放或处理音频时，解码器将压缩的音频数据还原成原始的数字音频信号。
    数字到模拟的转换（数模转换，DAC）：

最后，数字信号通过数模转换器（DAC）转换成模拟信号，这样扬声器或耳机就可以播放出声音了。

### 音频编解码器选型

```bash
OPUS
MP3
AAC
AC3和EAC3 杜比公司的方案 
```

请参考：《详解音频编解码的原理、演进和应用选型等 - 知乎 (zhihu.com) 》
https://zhuanlan.zhihu.com/p/55218899



### 音频常见名词

#### 采样频率

每秒钟采样的点的个数。常用的采样频率有：

```bash
22000（22kHz）： 无线广播。

44100（44.1kHz）：CD音质。

48000（48kHz）： 数字电视，DVD。

96000（96kHz）： 蓝光，高清DVD。

192000(192kHz): 蓝光，高清DVD。
```

> - 想象一下，你有一个秒表，用来记录声音的波动。采样频率就是这个秒表每秒钟“滴答”的次数，也就是记录声音波动的点的个数。
> - 比如22kHz（22000次/秒）就是说，这个秒表每秒钟会“滴答”22000次，记录22000个声音的点。数字越大，记录的声音细节就越多，音质也就越好。

#### 采样精度（采样深度）

每个“样本点”的大小，

```bash
# 常用的大小为8bit， 16bit，24bit
```

> - 这就像是用不同粗细的笔来记录声音的波动。8bit、16bit、24bit就像是不同粗细的笔，bit数越高，笔越粗，能记录的声音细节就越多，音质也就越丰富。
> - 比如8bit可以记录256级音量变化，16bit可以记录65536级，24bit可以记录16777216级。显然，24bit的笔能记录更多的声音细节。

#### 通道数

```bash
# 单声道，双声道，四声道，5.1声道
```

> - 这就像是不同数量的麦克风同时录制声音。单声道就像是一个麦克风，双声道就像两个麦克风，四声道就像四个麦克风，5.1声道则是五个主要麦克风加上一个低音效果麦克风。
> - 通道数越多，能录制的声音方向和空间感就越丰富，听起来也就越立体。

总结一下：

- **采样频率**：每秒钟记录声音的点的个数，数字越大，记录的声音细节越多。
- **采样精度（采样深度）**：每个样本点的大小，bit数越高，能记录的声音细节越丰富。
- **通道数**：同时录制声音的麦克风数量，通道数越多，声音的空间感和立体感越强。



## 封装格式 + 音视频同步

### 封装格式(也叫容器）

<h3><font color=red size=4>将已经编码压缩好的视频流、音频流及字幕按照一定的方案放到一个文件中，便于播放软件播放。
一般来说，视频文件的后缀名就是它的封装格式</font></h3>

封装的格式不一样，后缀名也就不一样。

比如：同样的陷可以做成饺子也可以做成包子。对于视频也是一个道理，同样的音视频流可以用不同容器来承载。

<h3><font color=red size=4>视频Video：使用了H264/AVC压缩算法</font></h3>

<h3><font color=red size=4>音频Audio：使用了AAC压缩算法</font></h3>

<h3><font color=red size=4>封装则使用MP4封装格式</font></h3>

### 常见的视频封装格式

```bash
AVI、MKV、MPE、MPG、MPEG
MP4、WMV、MOV、3GP
M2V、M1V、M4V、OGM
RM、RMS、RMM、RMVB、IFO
SWF、FLV、F4V、
ASF、PMF、XMB、DIVX、PART
DAT、VOB、M2TS、TS、PS
```

<h3><font color=red>H264+AAC封装为FLV或MP4是最为流行的模式</font></h3>

### 音视频同步基础

#### 音视频同步概念

- DTS（Decoding Time Stamp）
  - 即解码时间戳，这个时间戳的意义在于告诉播放器该在什么时候解码这一帧的数据
- <font color=red>PTS（Presentation Time Stamp）</font>
  - 即显示时间戳，<font color=red>这个时间戳用来告诉播放器该在什么时候显示这一帧的数据</font>

#### 音视频同步方式

- <font color=red>Audio Master：</font>同步视频到音频
- <font color=red>Video Master：</font>同步音频到视频
- <font color=red>External Clock Master：</font>同步音频和视频到外部时钟。

> 一般情况下 Audio Master > External Clock Master > Video Master 



# FFempg命令处理实战



## ffmpeg音视频处理流程

```bash
ffmpeg -i test_1920x1080.mp4 -acodec copy -vcodec libx264 -s 1280x720 test_1280x720.flv

ffmpeg：这是调用 ffmpeg 程序的命令。

-i test_1920x1080.mp4：-i 参数后面跟着的是输入文件的路径，这里指定了输入文件名为 test_1920x1080.mp4。

-acodec copy：-acodec 参数后面跟着的是音频编解码器，copy 表示不对音频进行重新编码，直接复制原始音频流。

-vcodec libx264：-vcodec 参数后面跟着的是视频编解码器，libx264 是一个开源的 H.264 视频编解码器，用于对视频进行编码。

-s 1280x720：-s 参数后面跟着的是输出视频的分辨率，这里设置为 1280x720，即宽1280像素，高720像素。

test_1280x720.flv：这是输出文件的名称，.flv 是输出文件的格式。
```





## ffmpeg命令分类查询





### ffmpeg -version





### ffmpeg -buildconf





### ffmpeg -formats

```bash
D. 表示 Demuxing supported，即支持解复用（demuxing）。解复用是指从一个复合格式（如视频文件）中提取出单独的媒体流（如视频流、音频流）的过程。如果一个容器格式后面有 D. 标记，意味着 ffmpeg 支持将该格式的文件作为输入，从中提取媒体流。

.E 表示 Muxing supported，即支持复用（muxing）。复用是指将多个媒体流（如视频流、音频流）合并成一个复合格式（如视频文件）的过程。如果一个容器格式后面有 .E 标记，意味着 ffmpeg 支持将媒体流合并成该格式的文件作为输出。
```





### ffmpeg -muxers





### ffmpeg -demuxers





### ffmpeg -devices





### 查看具体分类所支持的参数

```bash
ffmepg -h type=name
```

```bash
ffmpeg -h muxer=flv
ffmpeg -h filter=atempo (atempo调整音频播放速率)
ffmpeg -h encoder=libx264
```

## ffplay 播放控制





## ffplay 播放命令选项

### 主要选项

- **-x width** 强制显示宽带。

- **-y height** 强制显示高度。

- **-video_size size** 帧尺寸 设置显示帧存储(WxH格式)，仅适用于类似原始YUV等没有包含帧大小(WxH)的视频。

  比如: 

  ```bash
  ffplay -pixel_format yuv420p -video_size 320x240 -framerate 5 yuv420p_320x240.yuv
  ```

- **-pixel_format forma**t 格式设置像素格式。

- **-fs** 以全屏模式启动。

- **-an** 禁用音频（不播放声音）

- **-vn** 禁用视频（不播放视频）

- **-sn** 禁用字幕（不显示字幕）

- **-ss pos** 根据设置的秒进行定位拖动，注意时间单位：

  比如:

  ```bash
  '55' 55 seconds,'12:03:45' ,12 hours, 03 minutes and 45 seconds, '23.189' 23.189 second
  ```

- **-t duration** 设置播放视频/音频长度，时间单位如 **-ss** 选项

- **-bytes** 按字节进行定位拖动（0=off 1=on -1=auto）。

- **-seek_interval interval** 自定义左/右键定位拖动间隔（以秒为单位），默认值为10秒（代码没有看到实现）

- **-nodisp** 关闭图形化显示窗口，视频将不显示

- **-noborder** 无边框窗口

- **-volume vol** 设置起始音量。音量范围**[0 ~100]**
  **-f fmt** 强制使用设置的格式进行解析。比如**-f s16le**

- **-window_title title** 设置窗口标题（默认为输入文件名）

- **-loop number** 设置播放循环次数

- **-showmode mode** 设置显示模式，可用的模式值：0 显示视频，1 显示音频波形，2 显示音频频谱。缺省为0，如果视频不存在则自动选择2

- **-vf filtergraph** 设置视频滤镜

- **-af filtergraph** 设置音频滤镜

### 高级选项

- **-stats** 打印多个回放统计信息，包括显示流持续时间，编解码器参数，流中的当前位置，以及音频/视频同步差值。默认情况下处于启用状态，要显式禁用它则需要指定**-nostats**。
- **-fast** 非标准化规范的多媒体兼容优化。
- **-genpts** 生成**pts**。
- **-sync type** 同步类型 将主时钟设置为 **audio（type=audio）**，**video（type=video）**或 **external（type=ext）**，默认是 **audio** 为主时钟。
- **-ast audio_stream_specifier** 指定音频流索引，比如 **-ast 3**，播放流索引为 **3** 的音频流
- **-vst video_stream_specifier** 指定视频流索引，比如 **-vst 4**，播放流索引为 **4** 的视频流
- **-sst subtitle_stream_specifier** 指定字幕流索引，比如 **-sst 5**，播放流索引为 **5** 的字幕流
- **-autoexit** 视频播放完毕后退出。
- **-exitonkeydown** 键盘按下任何键退出播放
- **-exitonmousedown** 鼠标按下任何键退出播放
- **-codec:media_specifier codec_name** 强制使用设置的多媒体解码器，
- **media_specifier** 可用值为 **a**（音频）， **v**（视频）和 **s** 字幕。比如 **codec:v h264_qsv** 强制视频采用 **h264_qsv** 解码
- **-acodec codec_name** 强制使用设置的音频解码器进行音频解码
- **-vcodec codec_name** 强制使用设置的视频解码器进行视频解码
- **-scodec codec_name** 强制使用设置的字幕解码器进行字幕解码
- **-autorotate** 根据文件元数据自动旋转视频。值为0或1 ，默认为1。
- **-framedrop** 如果视频不同步则丢弃视频帧。当主时钟非视频时钟时默认开启。若需禁用则使用 **-noframedrop**
- **-infbuf** 不限制输入缓冲区大小。尽可能快地从输入中读取尽可能多的数据。播放实时流时默认启用，如果未及时读取数据，则可能会丢弃数据。此选项将不限制缓冲区的大小。若需禁用则使用 **-noinfbuf**

### ffplay 更多选项

http://www.ffmpeg.org/ffplay.html



## ffplay 命令播放

- **播放本地文件**

  - ```bash
    ffplay -window_title "test time" -ss 2 -t 10 -autoexit test.mp4
    ```

  - ```bash
    ffplay buweishui.mp3
    ```

- **播放网络流**

  - ```bash
    ffplay -window_title "rtmp stream" 
    ```

  - ```bash
    rtmp://202.69.69.180:443/webcast/bshdlive-pc
    ```

- **强制解码器**

  - **mpeg4解码器**：

    ```bash
    ffplay -vcodec mpeg4 test.mp4
    ```

  - **h264解码器**：

    ```bash
    ffplay -vcodec h264 test.mp4
    ```

- **禁用音频或视频**

  - **禁用音频**：

    ```bash
    ffplay test.mp4 -an
    ```

  - **禁用视频**：

    ```bash
    ffplay test.mp4 -vn
    ```

- **播放YUV数据**

  - ```bash
    ffplay -pixel_format yuv420p -video_size 320x240 -framerate 5 
    ```

  - ```bash
    yuv420p_320x240.yuv
    ```

- **播放RGB数据**

  - ```bash
    ffplay -pixel_format rgb24 -video_size 320x240 -i rgb24_320x240.rgb
    ```

  - ```bash
    ffplay -pixel_format rgb24 -video_size 320x240 -framerate 5 -i rgb24_320x240.rgb
    ```

- **播放PCM数据**

  - ```bash
    ffplay -ar 48000 -ac 2 -f f32le 48000_2_f32le.pcm
    ```

  - ```bash
    -ar set audio sampling rate (in Hz) (from 0 to INT_MAX) (default 0)
    ```

  - ```bash
    -ac set number of audio channels (from 0 to INT_MAX) (default 0)
    ```

## ffplay 简单过滤器

- 视频旋转

  - ```bash
    ffplay -i test.mp4 -vf transpose=1
    ```

- 视频反转

  - ```bash
    ffplay test.mp4 -vf hflip
    ```

  - ```bash
    ffplay test.mp4 -vf vflip
    ```

- 视频旋转和反转

  - ```bash
    ffplay test.mp4 -vf hflip,transpose=1
    ```

- 音频变速播放

  - ```bash
    ffplay -i test.mp4 -af atempo=2
    ```

- 视频变速播放

  - ```bash
    ffplay -i test.mp4 -vf setpts=PTS/2
    ```

- 音视频同时变速

  - ```bash
    ffplay -i test.mp4 -vf setpts=PTS/2 -af atempo=2
    ```

更多参考
http://www.ffmpeg.org/ffmpeg-filters.html

## ffmpeg 命令参数说明

主要参数

- **-i** 设定输出流
- **-f** 设定输出格式
- **-ss** 开始时间
- **-t** 时间长度

音频参数

- **-aframes** 设置要输出的音频帧数
- **-b:a** 音频码率
- **-ar** 设定采样率
- **-ac** 设定声音的Channel（渠道）数
- **-acodec** 设定声音编解码器，如果用copy表示原始编解码数据必须被拷贝
- **-an** 不处理音频
- **-af** 音频过滤器

```bash
ffmpeg -i test.mp4 -b:a 192k -ar 48000 -ac 2 -acodec libmp3lame -aframes 200 out2.mp3
```

视频参数

- -vframes 设置要输出的视频帧数
- -b 设定视频码率
- -b:v 视频码率
- -r 设定帧速率
- -s 设定画面的宽与高
- -vn 不处理视频
- -aspect aspect 设置纵横比 4:3 16:9或1.3333 1.7777
- -vcodec 设定视频编解码器，如果用copy表示原始编解码数据必须被拷贝
- -vf 视频过滤器

```bash
ffmpeg -i test.mp4 -vframes 300 -b:v 300k -r 30 -s 640x480 -aspect 16:9 -vcodec libx265 out.h265
```

## ffmpeg 命令提取音视频数据

保留封装格式

```bash
ffmpeg -i test.mp4 -acodec copy -vn audio.mp4
```

```bash
ffmpeg -i test.mp4 -vcodec copy -an video.mp4
```

提取视频

```bash
# 保留编码格式
ffmpeg -i test.mp4 -vcodec copy -an test_copy.h264
```

```bash
# 强制格式
ffmpeg -i test.mp4 -vcodec libx264 -an test.h264
```

提取音频

```bash
# 保留编码格式
ffmpeg -i test.mp4 -acodec copy -vn test.aac
```

```bash
# 强制格式
ffmpeg -i test.mp4 -acodec libmp3lame -vn test.mp3
```

<font size=5 color=red>-acodec == codec:a</font>

<font size=5 color=red>-vcodec == codec:v</font>



## ffmpeg 命令提取像素格式

- 提取YUV

  - 提取3秒数据，分辨率和源视频一致

  - ```bash
    ffmpeg -i test_1280x720.mp4 -t 3 -pix_fmt yuv420p yuv420p_orig.yuv
    ```

- 提取3秒数据，分辨率转为320x240

  - ```bash
    ffmpeg -i test_1280x720.mp4 -t 3 -pix_fmt yuv420p -s 320x240 yuv420p_320x240.yuv
    ```

- 提取RGB

  - 提取3秒数据，分辨率转为320x240

  - ```bash
    ffmpeg -i test.mp4 -t 3 -pix_fmt rgb24 -s 320x240 rgb24_320x240.rgb
    ```

- RGB和YUV之间的转换

  - ```bash
    ffmpeg -s 320x240 -pix_fmt yuv420p -i yuv420p_320x240.yuv -pix_fmt rgb24 rgb24_320x240_2.rgb
    ```

- 提取PCM

  ```bash
  ffmpeg -i buweishui.mp3 -ar 48000 -ac 2 -f s16le 48000_2_s16le.pcm 
  ffmpeg -i buweishui.mp3 -ar 48000 -ac 2 -sample_fmt s16 out_s16.wav 
  ffmpeg -i buweishui.mp3 -ar 48000 -ac 2 -codec:a pcm_s16le out2_s16le.wav 
  ffmpeg -i buweishui.mp3 -ar 48000 -ac 2 -f f32le 48000_2_f32le.pcm
  ffmpeg -i test.mp4 -t 10 -vn -ar 48000 -ac 2 -f f32le 48000_2_f32le_2.pcm
  ```



# FFmpeg 编程入门



## 播放器框架



## 常用音视频术语

- <font color=red>**容器／文件（Conainer/File）：**</font>即特定格式的多媒体文件，比如mp4、flv、mkv等。
- <font color=red>**媒体流（Stream）：**</font>表示时间轴上的一段连续数据，如一段声音数据、一段视频数据或一段字幕数据，可以是压缩的，也可以是非压缩的，压缩的数据需要关联特定的编解码器（有些码流音频他是纯PCM）。
- <font color=red>**数据帧／数据包（Frame/Packet）：**</font>通常，一个媒体流是由大量的数据帧组成的，对于压缩数据，帧对应着编解码器的最小处理单元，分属于不同媒体流的数据帧交错存储于容器之中。
- <font color=red>**编解码器：**</font>编解码器是以帧为单位实现压缩数据和原始数据之间的相互转换的。



## 常用概念-复用器





## 常用概念-编解码器





# FFmpeg基础



## FFmpeg库简介

FFmpeg整体结构



FFMPEG有8个常用库：

|                   库名                   |                             解释                             |
| :--------------------------------------: | :----------------------------------------------------------: |
|    <font color=blue>**AVUtil**</font>    | 核心工具库，下面的许多其他模块都会依赖该库做一些基本的音视频处理操作。 |
|   **<font color=blue>AVFormat</font>**   | 文件格式和协议库，该模块是最重要的模块之一，封装了Protocol层和Demuxer、 Muxer层，使得协议和格式对于开发者来说是透明的。 |
|   **<font color=blue>AVCodec</font>**    | 编解码库，封装了Codec层，但是有一些Codec是具备自己的License的， FFmpeg是不会默认添加像libx264、 FDK-AAC等库的，但是FFmpeg就像一个平台一样，可以将其他的第三方的Codec以插件的方式添加进来，然后为开发者提供统一的接口。 |
|   <font color=blue>**AVFilter**</font>   | 音视频滤镜库，该模块提供了包括音频特效和视频特效的处理，在使用FFmpeg的API进行编解码的过程中，直接使用该模块为音视频数据做特效处理是非常方便同时也非常高效的一种方式。 |
|   **<font color=blue>AVDevice</font>**   | 输入输出设备库，比如，需要编译出播放声音或者视频的工具ffplay，就需要确保该模块是打开的，同时也需要SDL的预先编译，因为该设备模块播放声音与播放视频使用的都是SDL库。 |
| **<font color=blue>SwrRessample</font>** | 该模块可用于音频重采样，可以对数字音**频进行声道数、数据格式、采样率**等多种基本信息的转换。 |
|   **<font color=blue>SWScale</font>**    | 该模块是将图像进行格式转换的模块，比如，可以将YUV的数据转换为RGB的数据，缩放尺寸由1280*720变为800*480。 |
|   **<font color=blue>PostProc</font>**   | 该模块可用于进行后期处理，当我们使用AVFilter的时候需要打开该模块的开关，因为Filter中会使用到该模块的一些基础函数。 |



## FFmpeg函数简介



|                  av_register_all()                   |              注册所有组件,4.0已经弃用               |
| :--------------------------------------------------: | :-------------------------------------------------: |
| **<font color=blue>avdevice_register_all()</font>**  |            对设备进行注册，比如V4L2等。             |
| **<font color=blue>avformat_network_init();</font>** | 初始化网络库以及网络加密协议相关的库（比如openssl） |



## FFmpeg函数简介-封装格式相关



### 封装格式API

|          封装格式函数           |                           函数简介                           |
| :-----------------------------: | :----------------------------------------------------------: |
|  **avformat_alloc_context()**   |    负责申请一个AVFormatContext结构的内存,并进行简单初始化    |
|   **avformat_free_context()**   |             释放该结构里的所有东西以及该结构本身             |
|   **avformat_close_input()**    | 关闭解复用器。关闭后就不再需要使用avformat_free_context 进行释放。 |
|    **avformat_open_input()**    |                      打开输入音视频文件                      |
| **avformat_find_stream_info()** |                      获取音视频文件信息                      |
|       **av_read_frame()**       |                         读取音视频包                         |
|    **avformat_seek_file()**     |                  定位文件（可通过时间定位）                  |
|       **av_seek_frame()**       |                定位文件（可通过文件大小定位）                |

### 函数调用流程

<img src="https://i-blog.csdnimg.cn/blog_migrate/636f17a6d29f4d376156bf05e8ed496a.png" alt="img" style="zoom: 67%;" />



## FFmpeg解码函数简介-解码器相关



### 解码函数API

|              解码函数              |                函数简介                 |
| :--------------------------------: | :-------------------------------------: |
|    **avcodec_alloc_context3()**    |            分配解码器上下文             |
|     **avcodec_find_decoder()**     |            根据ID查找解码器             |
| **avcodec_find_decoder_by_name()** |             根据解码器名字              |
|        **avcodec_open2()**         |              打开编解码器               |
|    **avcodec_decode_video2()**     |     解码一帧视频数据（不建议使用）      |
|    **avcodec_decode_audio4()**     |     解码一帧音频数据（不建议使用）      |
|     **avcodec_send_packet()**      |             发送编码数据包              |
|    **avcodec_receive_frame()**     |             接收解码后数据              |
|     **avcodec_free_context()**     | 释放解码器上下文，包含了avcodec_close() |
|        **avcodec_close()**         |               关闭解码器                |

### 解码函数调用流程

<img src="https://i-blog.csdnimg.cn/blog_migrate/76eb20f1790a625c5876b9aae73d6565.png" alt="img" style="zoom:67%;" />



## FFmpeg数据结构简介



|                          结构体类型                          |                             用法                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
|         **<font color=blue>AVFormatContext</font>**          | 封装格式上下文结构体，也是**统领全局的结构体**，保存了视频文件封装格式相关信息。 |
| **<font color=blue>AVInputFormat demuxer</font>**<br />**<font color=blue>AVOutputFormat muxer</font>** |   每种封装格式（例如FLV, MKV, MP4, AVI）对应一个该结构体。   |
|             **<font color=blue>AVStream</font>**             |        视频文件中每个视频（音频）流对应一个该结构体。        |
|          **<font color=blue>AVCodecContext</font>**          |   编解码器上下文结构体，保存了视频（音频）编解码相关信息。   |
|             **<font color=blue>AVCodec</font>**              | 每种视频（音频）编解码器(例如H.264解码器)对应一个该结构体。  |
|             **<font color=blue>AVPacket</font>**             |                    存储一帧压缩编码数据。                    |
|             **<font color=blue>AVFrame</font>**              |               存储一帧解码后像素（采样）数据。               |



## FFmpeg数据结构之间的关系



#### AVFormatContext，AVStream 和 AVCodecContext之间的关系

![img](https://i-blog.csdnimg.cn/blog_migrate/524c4d6fc907f9bec5eee79d82e631fc.png)

#### 区分不同的码流（AVPacket里面也有一个index的字段）

AVMEDIA_TYPE_CIDEO 视频流

```c
video_index = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1 NULL, 0);
```

AVMEDIA_TYPE_AUDIO 音频流

```c
audio_index = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1 NULL, 0);
```

#### AVPacket和AVFrame之间的关系

<img src="https://i-blog.csdnimg.cn/blog_migrate/64a89734039b1962fa838a5086235e79.png" alt="img" style="zoom: 50%;" />

<img src="https://i-blog.csdnimg.cn/blog_migrate/f20b3ca166825737f96dd74c307031b4.png" alt="img" style="zoom: 67%;" />

<img src="https://i-blog.csdnimg.cn/blog_migrate/e53782ff8a8069d671ef138f0c351c05.png" alt="img" style="zoom: 67%;" />



## FFmpeg数据结构分析



### AVFormatContext

|  iformat   | 输入媒体的AVInputFormat，比如指向AVInputFormatff_flv_demuxer |
| :--------: | :----------------------------------------------------------: |
| nb_streams |                   输入媒体的 AVStream 个数                   |
|  streams   |                  输入媒体的AVStream [] 数组                  |
|  duration  | 输入媒体的时长（以微妙为单位），计算方式可以参考av_dump_format() 函数 |
|  bit_rate  |                        输入媒体的码率                        |

### AVInputFormat

|            name            |   封装格式名称    |
| :------------------------: | :---------------: |
|         extensions         | 封装格式的扩展名  |
|             id             |    封装格式ID     |
| 一些封装格式处理的接口函数 | 比如read_packet() |

### AVStream

|     index      |              标识该视频/音频流               |
| :------------: | :------------------------------------------: |
|   time_base    | 该流的时间基，PTS*time_base=真正的时间（秒） |
| avg_frame_rate |                  该流的帧率                  |
|    duration    |               该视频音频流长度               |
|    codecpar    |               编解码器参数属性               |

### AVCodecParameters

| codec_type | 媒体类型，比如AVMEDIA_TYPE_VIDEO AV_MEDIS_TYPE_AUDIO |
| :--------: | :--------------------------------------------------: |
|  codec_id  |  编解码器类型，比如AV_CODEC_ID_H264 AV_CODEC_ID_AAC  |

### AVCodecContext

|     codec     | 编解码器的AVCodec，比如指向AVCodecff_aac_latm_decoder |
| :-----------: | :---------------------------------------------------: |
| width, height |               图像的宽高（只针对视频）                |
|    pix_fmt    |                像素格式（只针对视频）                 |
|  sampl_rate   |                 采样率（只针对音频）                  |
|   channels    |                 声道数（只针对音频）                  |
|  sample_fmt   |                采样格式（只针对音频）                 |

### AVCodec

|         name         |     编解码名称     |
| :------------------: | :----------------: |
|         type         |    编解码器类型    |
|          id          |     编解码器ID     |
| 一些编解码的接口函数 | 比如int(*decode)() |

### **AVPacket**

|     **pts**      |    显示时间戳    |
| :--------------: | :--------------: |
|     **dts**      |    解码时间戳    |
|     **data**     |   压缩编码数据   |
|     **size**     | 压缩编码数据大小 |
|     **pos**      |  数据的偏移地址  |
| **stream_index** |  所属的AVStream  |

#### AVPacket 常用API

|              AVPacket *av_packet_alloc(void);              |    分配AVPacket这个时候和buffer没有关系    |
| :--------------------------------------------------------: | :----------------------------------------: |
|           **void av_packet_free(AVPacket pkt);**           |          释放AVPacket和_alloc对应          |
|             **av_init_packet(AVPacket *pkt);**             |    初始化AVPacket只是单纯初始化pkt字段     |
|      **int av_new_packet(AVPacket *pkt, int size);**       | 给AVPacket的buf分配内存，引用计数初始化为1 |
| **int av_packet_ref(AVPacket *dst, const AVPacket *src);** |                增加引用计数                |
|          **void av_packet_unref(AVPacket *pkt);**          |                减少引用计数                |
| **void av_packet_move_ref(AVPacket *dst, AVPacket *src);** |                转移引用计数                |
|    **AVPacket *av_packet_clone(const AVPacket *src);**     |   等于 av_packet_alloc()+av_packet_ref()   |

**定义：**

```bash
# Avpacket 用于存储 压缩编码 的数据。可以是音频、视频或字幕数据
```

**用途：**

```bash
# 它通常在解复用操作后存储压缩数据，然后作为输入传给解码器，或者由编码器输出然后传递给复用器
```

**特点：**

```bash
# 包含压缩的数据和相关的元数据，比如时间戳（PTS/DTS）。
# 一个AVPacket通常包含一个压缩帧，但对于音频数据包，可能包含多个压缩帧。
# 数据包可以包含一个或多个编码帧的数据，也可能是一个编码帧的多个不同片段
```

### AVFrame

|   **data**    |             解码后的图像像素数据（音频采样数据）             |
| :-----------: | :----------------------------------------------------------: |
| **linesize**  | 对视频来说是图像中一行像素的大小；对音频来说是整个音频帧的大小 |
| width, height |                   图像的宽高（只针对视频）                   |
|   key_frame   |                  是否为关键帧（只针对视频）                  |
|   pict_type   |             帧类型（只针对视频） 。例如I， P， B             |
|  sample_rate  |                   音频采样率（只针对音频）                   |
|  nb_samples   |                音频每通道采样数（只针对音频）                |
|    **pts**    |                          显示时间戳                          |

#### AVframe 常用API

|           AVFrame *av_frame_alloc(void);            |             分配AVFrame              |
| :-------------------------------------------------: | :----------------------------------: |
|        void av_frame_free(AVFrame **frame);         |             释放AVFrame              |
| int av_frame_ref(AVFrame *dst, const AVFrame *src); |             增加引用计数             |
|        void av_frame_unref(AVFrame *frame);         |             减少引用计数             |
| void av_frame_move_ref(AVFrame *dst, AVFrame *src); |             转移引用计数             |
| int av_frame_get_buffer(AVFrame *frame, int align); |         根据AVFrame分配内存          |
|    AVFrame *av_frame_clone(const AVFrame *src);     | 等于 av_frame_alloc()+av_frame_ref() |

**定义：**

```bash
# AVframe 用于存储 解码后 的音频或视频数据
```

**用途：**

```bash
# 它必须通过av_frame_alloc进行分配，并通过av_frame_free释放，AVframe是解码后的数据，可直接用于渲染或进一步处理
```

**特点：**

```bash
# 包含解码后的原始数据，可以是音频采样数据或视频像素数据。
# 通过解码器从AVPacket中解码得到。
```



## FFmpeg解封装解码





# FLV格式分析



---
