entity = CompRend.Entity.Create("foo", 5,5)
entity2 = CompRend.Entity.Create("foo", 5,5)

local ep = {x = 0, y = 7}
local Petrole = {{10,10},{0,0},{10,20}, {0,20}, {0,10}}
local i = 2
petrole_count = 4
local position = {x = 0, y = 0}

entity.update = function() 
    position.x = position.x + 0.001
    CompRend.Entity.Translate(entity.obj, position)
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
        ep.x = ep.x + 0.005
    else
        ep.x = ep.x - 0.005
    end
    if Petrole[i][2] > ep.y then
        ep.y = ep.y + 0.005
    else
        ep.y = ep.y - 0.005
    end
    CompRend.Entity.Translate(entity2.obj, ep)
end

CompRend.Scene.Entities = {
    entity,
    entity2,
}
