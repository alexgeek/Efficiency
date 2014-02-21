for id, entity in pairs(world.entities) do
    --local block = entity.get("block")
    --if block then block:render(entity.x, entity.y, entity.z) end
    for cid, c in pairs(entity.components) do
        if c:is_a(Block) then
            c:render(entity.x, entity.y, entity.z)
        end
    end
end
if drawbatch then drawbatch() end
