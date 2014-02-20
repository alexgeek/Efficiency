for id, entity in pairs(world.entities) do
    local block = entity.get("block")
    if block then block:render(entity.x, entity.y, entity.z) end
end
