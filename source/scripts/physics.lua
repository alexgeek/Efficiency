Physics = class(Component, function(p)
    p.name = "physics"
    p.mass = 1
    p.velocity_x = 0
    p.velocity_y = 0
    p.velocity_z = 0
    p.acceleration_x = 0
    p.acceleration_y = 0
    p.acceleration_z = 0
end)

function Physics:update()
    delta = math.abs(1/60)
    self.velocity_x = self.velocity_x + (self.acceleration_x * delta)
    self.velocity_y = self.velocity_y + (self.acceleration_y * delta)
    self.velocity_z = self.velocity_z + (self.acceleration_z * delta)
    self.owner.x = self.owner.x + (self.velocity_x * delta)
    self.owner.y = self.owner.y + (self.velocity_y * delta)
    self.owner.z = self.owner.z + (self.velocity_z * delta)
end

function Physics:apply_force(fx, fy, fz)
    self.acceleration_x = fx / self.mass
    self.acceleration_y = fy / self.mass
    self.acceleration_z = fz / self.mass
end
