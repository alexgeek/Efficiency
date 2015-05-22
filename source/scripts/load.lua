-- camera setup
--camera(5, 5, 5,
--       4.9, 4.9, 4.9);

-- initial scene set up
local player = entity("player")
local victim = entity("victim")
victim.add(Living(20))
player.add(Living(100))
player.add(Sword(5))
player.action = function() player.get("sword"):attack() end
world.add(victim)
world.add(player)


local size = 8
for x = -size, size do
  for y = -size*4, 0 do
    for z = -size, size do
      local b = entity("block<" .. tostring(x) .. "," .. tostring(y) .. "," .. tostring(z) .. ">")
      if math.random(-y+1) < 3 then b.add(blocks["grass"]) else b.add(blocks["stone"]) end
      b.x = x
      b.y = y
      b.z = z
      --b.tick = math.abs(x) + math.abs(y) + math.abs(z)
      --b.tick = b.tick*(b.tick+1) + 10
      --b.tick = b.id
      --b.tick = b.tick * 2
      --b.update = function(b) b.tick = b.tick - 1; if b.tick <= 0 then world.remove(b) end end
      world.add(b)
    end
  end
end

for x = -size, size do
for y = 0, 9 do
for z = -size, size do
    local iceblock = entity("block<" .. tostring(x) .. "," .. tostring(y) .. "," .. tostring(z) .. ">")
    local grassblock = entity("block<" .. tostring(x) .. "," .. tostring(y) .. "," .. tostring(z+1) .. ">")

    iceblock.x = x
    iceblock.y = y
    iceblock.z = z

    if math.abs(x) == math.abs(size) or math.abs(z) == math.abs(size) then
        if math.abs(x) == math.abs(z) then
            iceblock.add(blocks["templebrick"])
        else
            iceblock.add(blocks["icebrick"])
        end
        world.add(iceblock)
    end
end end end

local hellblock = entity("actor")
hellblock.add(blocks["hellstone"])
local physics = Physics()
--physics:apply_force(0, 10, 0)
hellblock.add(physics)
hellblock.y = 10
hellblock.action = function() physics:apply_force(0, 2, 0) end
--[[
hellblock.update = function()
    physics:update()
    if hellblock.y < 1 then
        physics:apply_force(0, 0.05, 0)
    else physics:apply_force(0, -0.01, 0)
end end
--]]
world.add(hellblock)
