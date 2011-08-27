source = action:getSource()
worldMap = source:getChild( "worldmap" )
keepRunning = source:getState( "keepRunning" )

if worldMap == nil then
	return
end

gomez = worldMap:getChild( "gomez" )
hp = gomez:getState( "hp" )

if hp:getValue() == 0 then
	keepRunning:setValue( false )
end
