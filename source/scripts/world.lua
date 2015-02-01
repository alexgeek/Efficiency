-- world setup
world = {}
world.entities = {}
world.name = "Perry Land"

-- world methods
world.add = function(entity) world.entities[entity.id] = entity end
world.remove = function(entity) world.entities[entity.id] = nil end
world.get_block_at = function(x, y, z) if y < 5 then return 1 else return 0 end end
world.get_entities_excluding =
function(entity)
  local found = {}
  for i,e in pairs(world.entities) do
    if e.id ~= entity.id then table.insert(found, e) end
  end
  return found
end
