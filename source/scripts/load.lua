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
camera(10, 10, 10,
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

local size = 8
local ctr = 0
for x = -size, size do
  for y = -size, 0 do
    for z = -size, size do
      local b = entity("block<" .. tostring(x) .. "," .. tostring(y) .. "," .. tostring(z) .. ">")
      b.add(Block())
      b.x = x
      b.y = y
      b.z = z
      b.tick = math.abs(x) + y + math.abs(z)
      b.tick = b.tick * 20
      b.update = function(b) b.tick = b.tick - 1; if b.tick <= 0 then world.remove(b) end end
      if y <= -2 or ctr == 0 then world.add(b) end
      ctr = (ctr + 1) % 2
    end
  end
end

triangle(0, 1, 0, 2, -1, 0, -1, -1, 0)
