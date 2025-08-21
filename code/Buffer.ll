/*

if a==b
end
while a==b
end
for i = 0 ; i<10 ; i+=1
end

c = add(10,20) + add(30,40) + add(50,60)
d = a + b + c

if a+1==b
    return a + 1
elif false
    return b + 1
elif false
    return c + 1
end

while a >= 0
    a = a - 1
end

test = input()
print(test + ": Ok it works!\n")
f = object()
f.a = object()
f.a.a = object()
n = object()
n.a = object()
n.a.a = object()
n.a.a.a = object()
m = f.a
m.b = object()

o = Human::new("Bro",18)

l = listmake()
l += "Hello"
l += "World"

ret = listmake()
ret += o
ret += l



Long Jumps
Errors
Line Numbers

ellipsis operator ...

class implementation
/- static methodes
/- dynamic methods & self
- ref parameters
/- calls using . operator

- all operators with str => print method 

*/

function stream()
    self = object()
    self.a = 0
    self.b = 0
    return self
end

function add(e,f)
    return e + f
end

function fib(g)
    if g <= 1
        return g
    end
    return fib(g - 1) + fib(g - 2)
end



include "Script.ll"

from list import listmake
from obj import *

class Human
    function new(name,age)
        m = obj::new("Human")
        m.name = name
        m.age = age
        return m
    end
    
    function hello(self)
        if self.name=="Bro"
            return "Bro " + self.name + " is chillin...."
        end
        return "hello from: " + self.name
    end
end

function listtest(l)
    l[0] = 68
    l["first"] = 67
    return l
end

function main(a,b)
    --h = Human::new("Bro",18)
    --g = h.hello()
    --return g

    l = listmake()
    l += "first"
    l += "second"
    --l *= "first"

    --l -= 0
    return l
end

function fib(a)
    if a <= 1
        return a
    end
    return fib(a - 1) + fib(a - 2)
end

function add(a,b)
    return a + b
end

function main()
    return fib(7)
    b = add(add(add(1,2),add(3,4)),add(add(5,6),add(7,8)))
    return b
    return add(add(add(1,2),add(3,4)),add(add(5,6),add(7,8)))
end