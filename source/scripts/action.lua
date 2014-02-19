--print("[INFO] Actions: " .. world.name)
for id, entity in pairs(world.entities) do
    entity:action()
    --local health = entity.get("health")
    --if health then print(entity.name .. ": " .. health.hitpoints .. "/10") end
end
