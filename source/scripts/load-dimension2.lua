local dimension = game:GetDimension(0);

local stone = blockRegistry:GetBlockID("stone")
local dirt = blockRegistry:GetBlockID("dirt")
local grass = blockRegistry:GetBlockID("grass")
local templeBrick = blockRegistry:GetBlockID("templebrick")
local iceBrick = blockRegistry:GetBlockID("icebrick")

local size = 16
count = 0
for x = 0, size do
  --for y = 0, 1 do
    for z = 0, size do
      if x % 2 == 0 then
        dimension:SetBlock(x,1,z,stone)
      else
        dimension:SetBlock(x,1,z,dirt)
      end
      count = count + 1
    end
  --end
end

print("Count", count)

