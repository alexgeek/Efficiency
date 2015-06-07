Block = class(Component, function(b)
    b.name = "block"
    b.renderer = 0 -- should be a default renderer
end)

function Block:render(x, y, z)
    drawblock(self.renderer, x, y, z)
end

function Block:on_break(x, y, z)
    if self.itemdrop then print("Dropping " .. self.itemdrop .. " at " .. x .. y .. z) end
end


RenderBlock = class(Block, function(rb)
    rb.name = "renderblock"
end)

function RenderBlock:set_renderer(renderer_id)
    self.renderer = renderer_id
end

StoneBlock = class(RenderBlock, function(sb)
    sb.name = "stone"
    sb.renderer = load_renderer("assets/textures/stone.jpg")
end)

DirtBlock = class(RenderBlock, function(db)
    db.name = "dirt"
    db.renderer = load_renderer("assets/textures/dirt.jpg")
end)

GrassBlock = class(RenderBlock, function(gb)
    gb.name = "grass"
    gb.renderer = load_renderer("assets/textures/dirt.jpg", "assets/textures/grass.jpg")
end)

IceBrickBlock = class(RenderBlock, function(ib)
    ib.name = "icebrick"
    ib.renderer = load_renderer("assets/textures/icebrick.png")
end)

TempleBrickBlock = class(RenderBlock, function(ib)
    ib.name = "templebrick"
    ib.renderer = load_renderer("assets/textures/jap.png")
end)

HellStoneBlock = class(RenderBlock, function(ib)
    ib.name = "hellstone"
    ib.renderer = load_renderer("assets/textures/hellstone.png")
end)

blocks = {}

function add_block(block)
    blocks[block.name] = block
    return block
end

add_block(StoneBlock())
add_block(DirtBlock())
add_block(GrassBlock())
add_block(IceBrickBlock())
add_block(TempleBrickBlock())
add_block(HellStoneBlock())
