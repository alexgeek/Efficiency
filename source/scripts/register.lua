local register = function(name, renderer)
    local b = Block.new(name)
    b:SetRenderer(renderer)
    blockRegistry:RegisterBlock(b)
    return b
end

register("stone", BatchedRenderCube.new("assets/textures/stone.jpg"))
register("dirt", BatchedRenderCube.new("assets/textures/dirt.jpg"))
register("grass", BatchedRenderCube.new("assets/textures/grass.jpg", "assets/textures/dirt.jpg"))
register("icebrick", BatchedRenderCube.new("assets/textures/icebrick.png"))
register("templebrick", BatchedRenderCube.new("assets/textures/jap.png"))
register("hellstone", BatchedRenderCube.new("assets/textures/hellstone.png"))
