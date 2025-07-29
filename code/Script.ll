
function fib(a)
    if a <= 1
        return 1
    end
    return fib(a - 1) + fib(a - 2)
end
