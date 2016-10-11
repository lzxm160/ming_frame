#!/bin/sh

CLASSPATH=/usr/share/java/netty3/netty-3.10.6.Final.jar:/usr/share/java/slf4j/slf4j-api.jar:/usr/share/java/slf4j//slf4j-simple.jar:/usr/share/java:./bin
export CLASSPATH
mkdir -p bin
javac -d bin ./src/com/chenshuo/muduo/example/multiplexer/*.java ./src/com/chenshuo/muduo/example/multiplexer/testcase/*.java
java -ea -Djava.net.preferIPv4Stack=true com.chenshuo.muduo.example.multiplexer.MultiplexerTest localhost
