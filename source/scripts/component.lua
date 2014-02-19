Component = class(function(c)
  c.name = "component"
end)

function Component:__tostring()
    return self.name;
end

Living = class(Component, function(h, hp)
  h.name = "living"
  h.hitpoints = hp or 10
end)

function Living:accept_damage(damage)
  print("Entity " .. self.owner.name .. " attacked for " .. damage); 
  self.hitpoints = self.hitpoints - damage; 
  if self.hitpoints == 0 then 
    world.remove(self.owner); 
    print(self.owner.name .. " was killed") 
  end 
end

Sword = class(Component, function(s, damage)
  s.name = "sword"
  s.damage = damage or 2
end)

function Sword:attack()
  for i,v in pairs(world.get_entities_excluding(self.owner)) do
    local h = v.get("living")
    if h then
      h:accept_damage(self.damage) 
    end
  end
end

function Sword:foo(x)
    print(self.name .. ": " .. x)
end
