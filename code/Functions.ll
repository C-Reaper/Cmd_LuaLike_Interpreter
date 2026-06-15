from math import *
from obj import *

function fib(a)
    if a <= 1
        return a
    end
    return fib(a - 1) + fib(a - 2)
end

function fac(a)
    if a <= 1
        return 1
    end
    return a * fac(a - 1)
end

function gauss(a)
    if a <= 1
        return 1
    end
    return a + gauss(a - 1)
end

function add(a,b)
    return a + b
end

function main()
    --return 1 + 2
    
    --return add(1,add(2,3))
    --return add(add(1,2),3)
    --return add(add(1,2),add(3,4))
    --return add(add(add(1,2),add(3,4)),add(add(5,6),add(7,8)))
    
    --return gauss(3)
    --return gauss(gauss(3))
    --return fac(5)

    --return fib(9)

    --return gauss(gauss(3) + gauss(3)) + gauss(gauss(3) + gauss(3))
    --return math::parseInt(math::getInt(120))
    return math::max(gauss(4),math::min(fib(7),fac(7)))
end
