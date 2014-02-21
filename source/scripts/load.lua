function dump(t, level)
  level = level or 0
  for i,v in pairs(t) do
    io.write(string.rep('  ', level))
    io.write(i..': ')
    if type(v) == 'table' then
      print ''
      dump(v, level + 1)
    else
      print(tostring(v))
    end
  end
end

-- camera setup
camera(20, 5, 20,
      0, 0, 0);

-- initial scene set up
local player = entity("player")
local victim = entity("victim")
victim.add(Living(20))
player.add(Living(100))
player.add(Sword(5))
player.action = function() player.get("sword"):attack() end
world.add(victim)
world.add(player)


local size = 0
--[[
for x = -size, size do
  for y = -size, 0 do
    for z = -size, size do
      local b = entity("block<" .. tostring(x) .. "," .. tostring(y) .. "," .. tostring(z) .. ">")
      if math.random(10) < 3 then b.add(blocks["grass"]) else b.add(blocks["stone"]) end
      b.x = x
      b.y = y
      b.z = z
      --b.tick = math.abs(x) + math.abs(y) + math.abs(z)
      --b.tick = b.id
      --b.tick = b.tick * 2
      --b.update = function(b) b.tick = b.tick - 1; if b.tick <= 0 then world.remove(b) end end
      world.add(b)
      
    end
  end
end
--]]
for x = -size, size do
for y = 5, 9 do
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

--[[
local iceblock = entity()
local grassblock = entity()
iceblock.z = 2
iceblock.add(blocks["icebrick"])
grassblock.z = -2
grassblock.add(blocks["grass"])
--world.add(iceblock)
world.add(grassblock)
world.add(entity().add(blocks["stone"]))
local foo = entity().add(blocks["stone"])
foo.y = -2
world.add(foo)
local foo2 = entity().add(blocks["stone"])
foo2.z = 2
world.add(foo2)
local foo3 = entity("fucker").add(blocks["icebrick"])
foo3.y = 2
world.add(foo3)

--]]
