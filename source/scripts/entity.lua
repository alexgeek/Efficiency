local id = 0;
function entity(name)
  local e = {}
  e.id = id
  id = id + 1 
  e.components = {}
  e.name = name or "entity_" .. e.id
  e.update = function () end
  e.action = function() end
  e.add = function(c) table.insert(e.components, c); c.owner = e; return e end
  e.get = function(name) for i, component in pairs(e.components) do if component.name == name then return component end end end
  e.x = 0
  e.y = 0
  e.z = 0
  return e
end
