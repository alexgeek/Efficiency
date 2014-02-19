Block = class(Component, function(b)
    b.name = "block"
    b.texture = "stone.png"
end)

function Block:render(x, y, z)
    drawblock(x, y, z)
end
