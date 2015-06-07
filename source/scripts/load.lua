
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