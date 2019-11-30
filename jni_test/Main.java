import awtk.*;

class Main {
 public static void main(String[] args) {
     HelloWorld h = new HelloWorld();
     long obj = h.create();
     System.out.println(obj);
     int a = h.sum(obj, 123, 213);
     h.destroy(obj);

     new Widget().print();
 }

 static {
     System.loadLibrary("awtk-jni");
 }
 
}
