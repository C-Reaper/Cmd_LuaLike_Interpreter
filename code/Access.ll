from io import *
from list import *
from obj import *

/*
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
*/

function main()
    --h = Human::new("Bro",18)
    --g = h.hello()
    --return g

    l = list::new()
    l += "first"
    l += "second"

    if l.contains("first")
        io::print("Is contained!")
    else
        io::print("Is not contained!")
    end

    --l.append("third")
    --l.append("fourth")
    --l.append("third")
    --l.append("fourth")

    --io::print(l.tostr())
    --io::print(l.tostr())

    return l
end