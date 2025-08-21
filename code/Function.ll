from io import *
from sys import *
from window import *

function main()
    w = window::new("Hello World",1000,1000)
    w.init()

    rx = 10.0
    ry = 10.0
    rw = 200.0
    rh = 100.0

    while w.running()
        w.update()

        if w.key("W","down")
            ry = ry - 400.0 * w.elapsed()
        elif w.key("S","down")
            ry = ry + 400.0 * w.elapsed()
        end

        if w.key("A","down")
            rx = rx - 400.0 * w.elapsed()
        elif w.key("D","down")
            rx = rx + 400.0 * w.elapsed()
        end

        w.clear(0xFF000000)
        w.rect(rx,ry,rw,rh,0xFF00FF00)

        w.render()
        sys::msleep(5)
    end

    return 0
end