
function fib(a)
    if a <= 1
        if a >= 0
            return a
        end
    end
    return fib(a - 1) + fib(a - 2)
end

function add(a,b)
    return a + b
end

function main()
    --return fib(7)
    --return fib(3)
    --return add(1,2) + add(3,4) + add(5,6)
    return add(add(add(1,2),add(3,4)),add(add(5,6),add(7,8)))
end