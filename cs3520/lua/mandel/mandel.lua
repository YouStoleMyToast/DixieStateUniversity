function generateImage(filename)
    file = io.open(filename, "w")
    file:write("P3\n512 512\n255\n")
    local inc = 4.0 / 511.0
    local rowstart = 2.0
    local colstart = -2.0
    local y = rowstart
    for row = 1, 512 do
        local x = colstart
        for col = 1, 512 do
            local iters = calcPoint(x, y, 200)
            if iters == 0.0 then
                file:write("0 0 0 ")
            else
                local color = 54 + iters
                file:write("0".." "..color.." ".."0".." ")
            end
            file:write("\n")
            x = x + inc
        end
        y = y - inc
    end
    file:close()
end

function hw()
    print("Hello, world")
end
