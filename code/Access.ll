from io import *
from list import *
from obj import *
from math import *

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

    --l.len()

    --if l.contains("first")
    --    io::print("Is contained!\n")
    --else
    --    io::print("Is not contained!\n")
    --end

    io::print("Len is: " + math::getInt(l.len()) + "\n")
    io::print("List: " + l.tostr() + "\n")

    return l
end