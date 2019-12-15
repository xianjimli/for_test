import foo;

def on_changed(value):
    print("value change:" + str(value));
    return value + 100

o = foo.create(on_changed);

for i in range(10000):
    foo.set_value(o, i);
    print(foo.get_value(o));
foo.destroy(o);

