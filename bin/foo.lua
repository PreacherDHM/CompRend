CompRend.foo{ -- CompRend is the namespace / container for all of the entities
              -- for the program / game.
    init = function() -- This gets run once.
        object = Entity.Create()
        object:Move({4,5})
    end,

    update = function() -- This get run every frame.
        local position = object:GetPosition() -- Gets Object Current Position
                                              -- In a tabe {x,y}.

        if position.x == 10 then 
            position.y += 0.1;
        else 
            position.x += 0.1
        end

        object:Move(position) -- Move takes a table of x and y.
    end
}

