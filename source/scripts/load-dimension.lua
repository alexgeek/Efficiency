local dimension = game:GetDimension(0);

local stone = blockRegistry:GetBlockID("stone")
local dirt = blockRegistry:GetBlockID("dirt")
local grass = blockRegistry:GetBlockID("grass")
local templeBrick = blockRegistry:GetBlockID("templebrick")
local iceBrick = blockRegistry:GetBlockID("icebrick")

local size = 8
count = 0
for x = -size, size do
    for y = 0, size*4 do
        for z = -size, size do
          if math.random(0,10) < 3 then
            dimension:SetBlock(x,y,z,grass)
          else
            dimension:SetBlock(x,y,z,stone)
          end
          count = count + 1
        end
    end
end

print("Count", count)
--[[
for x = -size, size do
    for y = size*4, size*4+9 do
        for z = -size, size do
            if math.abs(x) == math.abs(size) or math.abs(z) == math.abs(size) then
                if math.abs(x) == math.abs(z) then
                    dimension:SetBlock(x,y,z,templeBrick)
                else
                    dimension:SetBlock(x,y,z,iceBrick)
                end
                count = count + 1
            end
        end
    end
end
--]]
print("Count", count)
