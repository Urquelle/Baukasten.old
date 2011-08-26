if not entity:hasState( "exp" ) then
	return
end

state = entity:getState( "exp" )

pOld = state:getValue()
pNew = pOld + 10

state:setValue( pNew )

name = entity:getState( "name" )

print( name:getValue() .. ": just scored 10 exp points! (" .. state:getValue() .. ")" )

if pOld < 10 and pNew >= 10 then
	entity:invokeAction( "levelUp" )
	entity:runActions()
end
