if not entity:hasState( "level" ) then
	return
end

state = entity:getState( "level" )
state:setValue( state:getValue() + 1 )

name = entity:getState( "name" )

print( name:getValue() .. " reached level " .. state:getValue() .. "! Ooohh ... shiny!" )
