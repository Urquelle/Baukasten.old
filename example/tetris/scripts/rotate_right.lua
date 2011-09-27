block = source:getForm():getVSpace():getEntity( "block:current" )
state = block:getState( "state:currentMatrix" )
next_value = state:getValue() - 1
if next_value == 0 then
	next_value = 4
end
state:setValue( next_value )
