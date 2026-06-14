from io import *
from sys import *
from window import *
from obj import *
from math import *

function overlap(r1_x,r1_y,r1_w,r1_h,r2_x,r2_y,r2_w,r2_h)
    return r1_x >= r2_x - r1_w && r1_x < r2_x + r2_w && r1_y >= r2_y - r1_h && r1_y < r2_y + r2_h
end

function main()
    w = window::new("Hello World",1900,1000)
    w.init()

    PADDLEWIDTH = 0.03
    PADDLEHEIGHT = 0.2
    BALLWIDTH = 0.027
    BALLHEIGHT = 0.05

    score1 = 0
    score2 = 0

    rect1_x = 0.0
    rect1_y = 0.5
    rect2_x = 1.0 - PADDLEWIDTH
    rect2_y = 0.5

    ball_x = 0.5
    ball_y = 0.5
    ballvelo_x = -0.2
    ballvelo_y = 0.2

    while w.running()
        w.update()

        if w.key("W","down")
            rect1_y = rect1_y - 0.5 * w.elapsed()
        elif w.key("S","down")
            rect1_y = rect1_y + 0.5 * w.elapsed()
        end

        if w.key("UP","down")
            rect2_y = rect2_y - 0.5 * w.elapsed()
        elif w.key("DOWN","down")
            rect2_y = rect2_y + 0.5 * w.elapsed()
        end

        ball_x = ball_x + ballvelo_x * w.elapsed()
        ball_y = ball_y + ballvelo_y * w.elapsed()

        if rect1_y < 0.0
            rect1_y = 0.0
        end
        if rect1_y > 1.0 - PADDLEHEIGHT
            rect1_y = 1.0 - PADDLEHEIGHT
        end
        if rect2_y < 0.0
            rect2_y = 0.0
        end
        if rect2_y > 1.0 - PADDLEHEIGHT
            rect2_y = 1.0 - PADDLEHEIGHT
        end

        if ball_y < 0.0
            ball_y = 0.0
            ballvelo_y = -ballvelo_y * 1.05
        end
        if ball_y > 1.0 - BALLHEIGHT
            ball_y = 1.0 - BALLHEIGHT
            ballvelo_y = -ballvelo_y * 1.05
        end
        if ball_x < -PADDLEWIDTH
            ball_x = 0.5
            ball_y = 0.5
            ballvelo_x = 0.2
            ballvelo_y = 0.2
            score2 = score2 + 1
        end
        if ball_x > 1.0
            ball_x = 0.5
            ball_y = 0.5
            ballvelo_x = 0.2
            ballvelo_y = 0.2
            score1 = score1 + 1
        end

        -- if rect1_x >= (ball_x - PADDLEWIDTH) && rect1_x < (ball_x + BALLWIDTH) && rect1_y >= (ball_y - PADDLEHEIGHT) && rect1_y < (ball_y + BALLHEIGHT)
        --     ballvelo_x = -ballvelo_x * 1.1
        -- end
        if overlap(rect1_x,rect1_y,PADDLEWIDTH,PADDLEHEIGHT,ball_x,ball_y,BALLWIDTH,BALLHEIGHT)
            ballvelo_x = -ballvelo_x * 1.1
        end
        if overlap(rect2_x,rect2_y,PADDLEWIDTH,PADDLEHEIGHT,ball_x,ball_y,BALLWIDTH,BALLHEIGHT)
            ballvelo_x = -ballvelo_x * 1.1
        end


        w.clear(0xFF000000)
        
        wwidth = w.width()
        wheight = w.height()
        w.rect(rect1_x * wwidth,rect1_y * wheight,PADDLEWIDTH * wwidth,PADDLEHEIGHT * wheight,0xFF0000FF)
        w.rect(rect2_x * wwidth,rect2_y * wheight,PADDLEWIDTH * wwidth,PADDLEHEIGHT * wheight,0xFFFF0000)
        w.rect(ball_x * wwidth,ball_y * wheight,BALLWIDTH * wwidth,BALLHEIGHT * wheight,0xFFFFFFFF)

        sc1 = math::getInt(score1)
        sc2 = math::getInt(score2)
        w.string(sc1+" : "+sc2,0.5 * wwidth,0.01 * wheight,0xFFFFFFFF)

        w.render()
        sys::msleep(5)
    end

    return 1
end