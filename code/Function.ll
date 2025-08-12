function hello(a,b)
    return a + b
end

function main()
    --return hello(hello(1,2),hello(3,4))
    return hello(1,2) + hello(3,4)
end