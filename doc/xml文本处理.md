#xml文本处理
##xml文本解析器比较
![](https://i.imgur.com/NZ34dlI.png)

###Xerces XML解析器
Xerces前身是IBM的XML4C，XML4C也是一种功能强大的XML解析器，之后交给Apache基金会管理，遂改名为Xerces，Xerces-C++让你的程序提供读写XML数据更加容易，提供的共享库通过DOM、SAX、SAX2 API等方式对XML文档进行解析、生成、操作和验证。
Xerces-C++忠实于XML 1.0建议和相关标准。
Xerces-C++解析器高性能、模块化并且可扩展。相关开发资料也比较完善。
除了C++版本，Xerces同时还提供Xerces Java，Xerces Perl等版本。

###TinyXML解析器
TinyXML相比Xerces要功能简单些，正如其名Tiny，使用方法也比较简单，TinyXML也是一个开源的解析XML解析库，用于C++，支持Windows和Linux。TinyXML通过DOM模型遍历和分析XML。

###XMLBooster解析器
XMLBooster开发关注点比较有特色，更加关注解析性能，针对特殊需求使用更加方便的数据结构以提高性能。

###LibXML解析器
LibXML本来是为Gnome项目开发（C开发），之后被广泛使用，功能非常强大，几乎适合于常见的所有操作系统下编译和开发使用。libxml++（地址：http://libxmlplusplus.sourceforge.net/） 是对libxml XML解析器的C++封装版本。此外还有各种语言封装包，参加官方链接。
