all: clean
	gcc -g -shared -I/work/tools/jdk-13.0.1/include -I /work/tools/jdk-13.0.1/include/linux awtk-jni.cpp -lstdc++ -o libawtk-jni.so
	/work/tools/jdk-13.0.1/bin/javac awtk/*.java *.java -d objs
	jar cvfm awtk.jar MANIFEST.MF -C objs .

run:
	/work/tools/jdk-13.0.1/bin/java -Djava.library.path=.  -classpath . -jar awtk.jar

clean:
	rm -rf *.so *.class *.jar objs/*
