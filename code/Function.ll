from io import *
from sys import *
--from window import *

function main()
    --w = window::new("Hello World",1000,1000)
    --w.init()
    --while true
    --    w.update()
    --    w.render()
    --    sys::msleep(2000)
    --end

    a = 0
    b = 1

    if a == b
        io::print("Equal\n")
    elif a > b
        io::print("Greater\n")
    else
        io::print("Less\n")
    end

    sys::msleep(1000)
    return 0
end