Item = class(Component, function(b)
    b.name = "item"
    b.renderer = 0 -- should be a default renderer
end)

function Item:render(x, y, z)
    drawitem(self.renderer, x, y, z)
end

