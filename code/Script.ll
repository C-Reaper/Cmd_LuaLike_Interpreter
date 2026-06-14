
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
    return add(1,add(1,2))
    
    --return fib(9)
    return add(add(add(1,2),add(3,4)),add(add(5,6),add(7,8)))
end
