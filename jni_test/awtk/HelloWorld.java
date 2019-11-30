 public class HelloWorld {
     public native void print();
     public native long create();
     public native int sum(long obj, int a, int b);
     public native void destroy(long obj);

     public int test() {
      return this.OK;
     }

     static public final int OK = get_ok();
     static public native int get_ok();
 }
 
