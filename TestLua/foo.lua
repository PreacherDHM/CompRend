
local spritef = { sprite = "\\_0_/  |    ^   / \\  | | ", bounds = {x = 5, y = 5} }

b = false

entity = CompRend.Entity.Create("foo", 5,5)
entity2 = CompRend.Entity.Create("foo", 5,5, spritef)

local ep = {x = 0, y = 7}
local Petrole = {{10,10},{0,0},{10,20}, {0,20}, {0,10}}
local i = 2
local speed = 5
--petrole_count = 4
local position = {x = 0, y = 0}

entity.update = function() 
    --local upp = true
    if CompRend.GetKeyDown("W") then
        position.y = position.y + speed * CompRend.DeltaTime()
        CompRend.Entity.Translate(entity.obj, position)
    end
    if CompRend.GetKeyDown("S") then
        position.y = position.y - speed * CompRend.DeltaTime()
        CompRend.Entity.Translate(entity.obj, position)
    end
    if CompRend.GetKeyDown("D") then
        position.x = position.x - speed * CompRend.DeltaTime()
        CompRend.Entity.Translate(entity.obj, position)
    end
    if CompRend.GetKeyDown("A") then
        position.x = position.x + speed * CompRend.DeltaTime()
        CompRend.Entity.Translate(entity.obj, position)
    end
    
    
    if CompRend.GetKey("B") then
        position.x = position.x + 5 * CompRend.DeltaTime()
        CompRend.Entity.Translate(entity.obj, position)
    end
            


end
entity2.update = function() 
    if ep.x <= Petrole[i][1] +0.05  then
        if ep.x >= Petrole[i][1] -0.05 then
            if ep.y <= Petrole[i][2] +0.05  then
                if ep.y >= Petrole[i][2] -0.05 then
                    if i == #Petrole then
                        i = 1
                    else
                        i = i + 1
                    end
                end
            end
        end
    end
    if Petrole[i][1] > ep.x then
        ep.x = ep.x + 20 * CompRend.DeltaTime()
    else
        ep.x = ep.x - 20 * CompRend.DeltaTime()
    end
    if Petrole[i][2] > ep.y then
        ep.y = ep.y + 20 * CompRend.DeltaTime()
    else
        ep.y = ep.y - 20 * CompRend.DeltaTime()
    end
    CompRend.Entity.Translate(entity2.obj, ep)
end

CompRend.Scene.Entities = {
    entity,
    entity2,
}
