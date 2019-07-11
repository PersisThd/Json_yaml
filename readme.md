# json-data-structure

## 简介

####1、设计JSON数据结构，方便读取成员值

JSON是一种树形数据结构。具体JSON格式可参考：http://www.w3school.com.cn/json/json_syntax.asp

一个JSON，包含一个JSON值类型。

JSON值是一种可变类型，可以是：BOOL值，数值，字符串，数组，对象。

数组的成员类型是JSON值，也就是说一个数组，可能包含0到n个成员，每个成员都是JSON值。

对象由1到n个键值对组成，键值对由键（字符串）和值（即JSON值类型）组成。


```C
JSON ::= Value 
Value ::= BOOLValue | Num | Str | Array | Object 
Array ::= Value* 
Object ::= KeyValue+ 
KeyValue ::= Key Value
```

####2、把JSON值格式化为YAML格式的字符串





